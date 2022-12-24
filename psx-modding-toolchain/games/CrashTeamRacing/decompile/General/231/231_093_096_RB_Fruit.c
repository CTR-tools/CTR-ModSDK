#include <common.h>

void RB_Fruit_GetScreenCoords(struct Camera110* c110, struct Instance* inst, short* output)
{
	MATRIX* m;
	short posWorld[4];
	
	// load camera matrix
	m = &c110->matrix_ViewProj;
    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);
	
	// load input vector, each int casts to short
	posWorld[0] = (short)inst->matrix.t[0];
	posWorld[1] = (short)inst->matrix.t[1];
	posWorld[2] = (short)inst->matrix.t[2];
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
	gte_stsxy(&output[0]);
}

void DECOMP_RB_Fruit_LInB(struct Instance* inst)
{
	RB_Default_LInB(inst);
	inst->animIndex = 0;
	inst->flags |= 0x10;
}

int DECOMP_RB_Fruit_LInC(
	struct Instance* fruitInst,
	struct Thread* driverTh,
	struct WeaponSearchData* info)
{
	struct Camera110* c110;
	short posScreen[2];
	struct Driver* driver;
	int driverID;
	int modelID;

	modelID = info->modelID;
	
	// if fruit did not collide with 
	// DYNAMIC_PLAYER or DYNAMIC_ROBOT_CAR,
	// quit function
	if (!((modelID == 0x18) || (modelID == 0x3f))) return 0;
	
	// check scale
	if(fruitInst->scale[0] == 0) return 0;
	
	// set scaleX, scaleY, scaleZ
	*(int*)&fruitInst->scale[0] = 0;
	fruitInst->scale[2] = 0;
	
	// play sound
	PlaySound3D(0x43,fruitInst);
	
	// get driver object
	driver = driverTh->object;
	driverID = driver->driverID;
	
	c110 = &sdata->gGT->camera110[driverID];
	RB_Fruit_GetScreenCoords(c110, fruitInst, &posScreen[0]);
	
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