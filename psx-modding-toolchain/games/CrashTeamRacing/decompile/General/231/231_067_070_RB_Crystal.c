#include <common.h>

void DECOMP_RB_Crystal_ThTick(struct Thread* t)
{
	int sine;
	struct Instance* crystalInst;
	struct Crystal* crystalObj;
	
	crystalInst = t->inst;
	crystalObj = t->object;
	
	// rotate each frame
	crystalObj->rot[1] += 0x80;
	ConvertRotToMatrix(&crystalInst->matrix, &crystalObj->rot[0]);
	
	// sine curve for vertical bounce
	sine = MATH_Sin(crystalObj->rot[1]);
	
	// set posY
	crystalInst->matrix.t[1] =
		crystalInst->instDef->pos[1] + 	// original posY
		((sine << 4) >> 0xc) +			// sine (bounce up/down)
		0x30;							// airborne bump
	
	// to do: find 0x800b5968 and reallocate (probably light dir)
	SpecularLight_Spinning3D(crystalInst, &crystalObj->rot[0], 0x800b5968);
}

void DECOMP_RB_Crystal_LInB(struct Instance* inst)
{
	struct Crystal* crystalObj;
	
	struct Thread* t = 
		THREAD_BirthWithObject
		(
			// creation flags
			SIZE_RELATIVE_POOL_BUCKET
			(
				sizeof(struct Crystal), 
				NONE, 
				SMALL, 
				STATIC
			), 
			
			DECOMP_RB_Crystal_ThTick,	// behavior
			0,							// debug name
			0							// thread relative
		);
	
	if(t == 0) return;
	inst->thread = t;
	t->inst = inst;
	
	crystalObj = ((struct Crystal*)t->object);
	crystalObj->rot[0] = 0;
	crystalObj->rot[1] = 0;
	crystalObj->rot[2] = 0;
	
	inst->colorRGB = 0xd22fff0;
	
	// specular light
	inst->flags |= 0x20000;
	
	RB_Default_LInB(inst);
}

int DECOMP_RB_Crystal_LInC(
	struct Instance* crystalInst,
	struct Thread* driverTh,
	struct WeaponSearchData* info)
{
	short posWorld[4];
	short posScreen[2];
	MATRIX* m;
	struct Driver* driver;
	struct Camera110* c110;
	int driverID;
	int modelID;

	modelID = info->modelID;
	
	// if crystal did not collide with 
	// DYNAMIC_PLAYER or DYNAMIC_ROBOT_CAR,
	// quit function
	if (!((modelID == 0x18) || (modelID == 0x3f))) return 0;
	
	// handle scale
	if(crystalInst->scale[0] == 0) return 0;
	crystalInst->scale[0] = 0;
	crystalInst->scale[1] = 0;
	crystalInst->scale[2] = 0;
	
	// kill thread
	crystalInst->thread->flags |= 0x800;
	crystalInst->thread = 0;
	
	// get driver object
	driver = driverTh->object;
	driverID = driver->driverID;
	
	// load camera matrix
	c110 = &sdata->gGT->camera110[driverID];
	m = &c110->matrix_ViewProj;
    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);
	
	// load input vector
	posWorld[0] = *(short*)&crystalInst->matrix.t[0];
	posWorld[1] = *(short*)&crystalInst->matrix.t[1];
	posWorld[2] = *(short*)&crystalInst->matrix.t[2];
	posWorld[3] = 0;
	gte_ldv0(&posWorld[0]);
	
// inline_c.h gte_rtps() is broken? swap for mine:
// copied from 231.c, address 800B514C, CTR Letter World->HUD
#define gte_rtps_NikoVersion() __asm__ volatile ( \
	"nop;"							\
	"nop;"							\
	".word 0x4A180001" )

	// perspective projection
	gte_rtps_NikoVersion();
	
	// get result
	gte_stsxy(&posScreen[0]);
	
	// screenPosX
	driver->PickupWumpaHUD.startX = 
		c110->rect.x + posScreen[0];
		
	// screenPosY
	driver->PickupWumpaHUD.startY = 
		c110->rect.y + posScreen[1] - 0x14;
	
	// transition should last 5 frames
	driver->PickupWumpaHUD.cooldown = 5;
	
	// increment number of items in hud
	driver->PickupWumpaHUD.numCollected++;
	
	return 1;
}