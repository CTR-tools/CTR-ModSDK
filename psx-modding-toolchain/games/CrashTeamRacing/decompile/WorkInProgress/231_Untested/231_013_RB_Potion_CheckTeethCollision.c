#include <common.h>

// This is broken even in retail CTR,
// cause teeth collision is detected 
// by Potion_InAir, so this can be scrapped
void DECOMP_RB_Potion_CheckTeethCollision(struct Instance* inst)
{
	#define WSD \
	((struct WeaponSearchData*)0x1f800108)
	
	WSD->pos[0] = (short)inst->matrix.t[0];
	WSD->pos[1] = (short)inst->matrix.t[1];
	WSD->pos[2] = (short)inst->matrix.t[2];
	WSD->hitRadius = 0x140;
	WSD->hitRadiusSquared = 0x19000;
	WSD->modelID = inst->model->modelID;
	WSD->thread = inst->thread;
	WSD->funcCallback = RB_Potion_OpenTeeth;
	
	Weapon_MakeHitboxAndSearchBSP(WSD);
}