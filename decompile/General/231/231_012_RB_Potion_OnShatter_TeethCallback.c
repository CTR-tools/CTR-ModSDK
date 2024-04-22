#include <common.h>

// Required to make door open
// when driver hits potion, or 
// potion shatters due to full MinePool
int RB_Potion_OnShatter_TeethCallback(int unk, struct BSP* bspHitbox)
{
	struct InstDef* instDef;
	struct Instance* teethInst;

	instDef = bspHitbox->data.hitbox.instDef;
	if(instDef == 0) return;
	
	teethInst = instDef->ptrInstance;
	if(teethInst == 0) return;
	
	// STATIC_TEETH
	if(instDef->modelID != 0x70) return;

	DECOMP_RB_Teeth_OpenDoor(teethInst);
}