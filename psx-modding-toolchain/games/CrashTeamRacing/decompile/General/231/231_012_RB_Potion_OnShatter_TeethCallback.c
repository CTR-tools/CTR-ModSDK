#include <common.h>

// Required to make door open
// when driver hits potion, or 
// potion shatters due to full MinePool
int RB_Potion_OnShatter_TeethCallback(int unk, struct VisData* vd)
{
	struct InstDef* instDef;
	struct Instance* teethInst;

	instDef = vd->data.hitbox.instDef;
	if(instDef == 0) return;
	
	teethInst = instDef->ptrInstance;
	if(teethInst == 0) return;
	
	// STATIC_TEETH
	if(instDef->modelID != 0x70) return;

	RB_Teeth_OpenDoor(teethInst);
}