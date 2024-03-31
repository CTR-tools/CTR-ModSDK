#include <common.h>

int RB_Potion_OnShatter_TeethCallback(int unk, struct BSP* bspHitbox);

// This is broken even in retail CTR,
// cause teeth collision is detected 
// by Potion_InAir, so this can be scrapped
void DECOMP_RB_Potion_OnShatter_TeethSearch(struct Instance* inst)
{
	#define SPS \
	((struct ScratchpadStruct*)0x1f800108)
	
	SPS->Input1.pos[0] = (short)inst->matrix.t[0];
	SPS->Input1.pos[1] = (short)inst->matrix.t[1];
	SPS->Input1.pos[2] = (short)inst->matrix.t[2];
	SPS->Input1.hitRadius = 0x140;
	SPS->Input1.hitRadiusSquared = 0x19000;
	SPS->Input1.modelID = inst->model->id;
	
	SPS->Union.ThBuckColl.thread = inst->thread;
	SPS->Union.ThBuckColl.funcCallback = RB_Potion_OnShatter_TeethCallback;
	
	PROC_StartSearch_Self(SPS);
}