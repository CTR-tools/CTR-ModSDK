#include <common.h>

int RB_Potion_OpenTeeth(int unk, struct BspSearchData* bsd)
{
	struct Instance* teethInst;
	struct InstDef instDef = bsd->instDef;
	
	if(instDef == 0) return;
	
	teethInst = instDef->ptrInstance;
	if(teethInst == 0) return;
	
	// STATIC_TEETH
	if(teethInst->id != 0x70) return;

	RB_Teeth_OpenDoor(teethInst);
}