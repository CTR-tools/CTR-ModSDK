#include <common.h>

void DECOMP_MainInit_PrimMem(struct GameTracker* gGT)
{
	int size;
	int levelID = gGT->levelID;
	
	size = 0x200000;
	goto EndFunc;
	
EndFunc:
	MainDB_PrimMem(&gGT->db[0].primMem, size);
	MainDB_PrimMem(&gGT->db[1].primMem, size);
}

void DECOMP_MainInit_OTMem(struct GameTracker* gGT)
{
	int size;
	int levelID = gGT->levelID;
	
	size = 0x20000;
	goto EndFunc;
	
EndFunc:
	MainDB_OTMem(&gGT->db[0].otMem, size);
	MainDB_OTMem(&gGT->db[1].otMem, size);
	
	// 0x1000 per player, plus 0x18 for linking
	size = ((gGT->numPlyrCurrGame) << 0xC) | 0x18;
	gGT->ot_camera110_UI[0] = MEMPACK_AllocMem(size); // "ot1"
	gGT->ot_camera110_UI[1] = MEMPACK_AllocMem(size); // "ot2"
}