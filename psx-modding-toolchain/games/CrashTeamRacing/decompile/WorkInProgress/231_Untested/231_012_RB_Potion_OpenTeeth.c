#include <common.h>

// This is broken even in retail CTR,
// cause teeth collision is detected 
// by Potion_InAir, so this can be scrapped
int RB_Potion_OpenTeeth(int unk, struct VisData* vd)
{
	struct Instance* teethInst;
	struct InstDef* instDef = vd->hitbox.instDef;
	
	if(instDef == 0) return;
	
	teethInst = instDef->ptrInstance;
	if(teethInst == 0) return;
	
	// STATIC_TEETH
	if(teethInst->id != 0x70) return;

	RB_Teeth_OpenDoor(teethInst);
}