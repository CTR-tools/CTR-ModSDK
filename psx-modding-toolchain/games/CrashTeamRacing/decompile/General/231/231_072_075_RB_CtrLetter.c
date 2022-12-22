#include <common.h>

void DECOMP_RB_CtrLetter_ThTick(struct Thread* t)
{
	int sine;
	struct Instance* letterInst;
	struct CtrLetter* letterObj;
	
	letterInst = t->inst;
	letterObj = t->object;
	
	// rotate each frame
	letterObj->rot[1] += 0x40;
	ConvertRotToMatrix(&letterInst->matrix, &letterObj->rot[0]);
	
	// to do: find 0x800b5970 and reallocate (probably light dir)
	SpecularLight_Spinning3D(letterInst, &letterObj->rot[0], 0x800b5970);
}

void DECOMP_RB_CtrLetter_LInB(struct Instance* inst)
{
	struct CtrLetter* letterObj;
	
	struct Thread* t = 
		THREAD_BirthWithObject
		(
			// creation flags
			SIZE_RELATIVE_POOL_BUCKET
			(
				sizeof(struct CtrLetter), 
				NONE, 
				SMALL, 
				STATIC
			), 
			
			DECOMP_RB_CtrLetter_ThTick,	// behavior
			0,							// debug name
			0							// thread relative
		);
	
	if(t == 0) return;
	inst->thread = t;
	t->inst = inst;
	
	letterObj = ((struct CtrLetter*)t->object);
	letterObj->rot[0] = 0;
	letterObj->rot[1] = 0;
	letterObj->rot[2] = 0;
	
	inst->scale[0] = 0x1800;
	inst->scale[1] = 0x1800;
	inst->scale[2] = 0x1800;
	
	inst->colorRGB = 0xffc8000;
	
	// specular light, plus another
	inst->flags |= 0x30000;
	
	RB_Default_LInB(inst);
}

int DECOMP_RB_CtrLetter_LInC(
	struct Instance* letterInst,
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
	// DYNAMIC_PLAYER, quit function
	if (modelID != 0x18) return 0;
	
	// handle scale
	if(letterInst->scale[0] == 0) return 0;
	letterInst->scale[0] = 0;
	letterInst->scale[1] = 0;
	letterInst->scale[2] = 0;
	
	// kill thread
	letterInst->thread->flags |= 0x800;
	letterInst->thread = 0;
	
	// play sound
	PlaySound3D(100,letterInst);
	
	// get driver object
	driver = driverTh->object;
	driverID = driver->driverID;
	
	// load camera matrix
	c110 = &sdata->gGT->camera110[driverID];
	m = &c110->matrix_ViewProj;
    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);
	
	// load input vector
	posWorld[0] = *(short*)&letterInst->matrix.t[0];
	posWorld[1] = *(short*)&letterInst->matrix.t[1];
	posWorld[2] = *(short*)&letterInst->matrix.t[2];
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
	driver->PickupLetterHUD.startX = 
		c110->rect.x + posScreen[0];
		
	// screenPosY
	driver->PickupLetterHUD.startY = 
		c110->rect.y + posScreen[1] - 0x14;
	
	// transition should last 10 frames
	driver->PickupLetterHUD.cooldown = 10;
	
	// increment number of items in hud
	driver->PickupLetterHUD.numCollected++;
	
	// which letter was grabbed
	driver->PickupLetterHUD.modelID = letterInst->model->id;
	
	return 1;
}