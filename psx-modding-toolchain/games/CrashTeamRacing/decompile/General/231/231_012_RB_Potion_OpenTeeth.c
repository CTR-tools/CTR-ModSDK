#include <common.h>

// This is broken even in retail CTR,
// cause teeth collision is detected 
// by Potion_InAir, so this can be scrapped
int RB_Potion_OpenTeeth(int unk, struct VisData* vd)
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