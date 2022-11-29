#include <common.h>

void DECOMP_RB_Potion_CheckTeethCollision(struct Instance* inst)
{
	// unknown if this was ever a struct, or always
	// programmed as hard-coded scratchpad addr
	
	*(short*)0x1f800108 = (short)inst->matrix.t[0];
	*(short*)0x1f80010A = (short)inst->matrix.t[1];
	*(short*)0x1f80010C = (short)inst->matrix.t[2];
	*(short*)0x1f80010E = 0x140;
	*(short*)0x1f800110 = 0x19000;
	*(int*)0x1f800114 = inst->model->modelID;
	// hole
	*(int*)0x1f800120 = inst->thread;
	// hole
	*(int*)0x1f800130 = RB_Potion_OpenTeeth;
	
	Weapon_MakeHitboxAndSearchBSP(0x1f800108);
}