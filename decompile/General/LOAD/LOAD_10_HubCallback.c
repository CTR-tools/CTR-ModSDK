#include <common.h>

void DECOMP_LOAD_HubCallback(struct LoadQueueSlot* lqs)
{	
	DECOMP_LOAD_Callback_PatchMem();
	
	struct GameTracker* gGT = sdata->gGT;	
	gGT->level2 = sdata->ptrLevelFile;
	DECOMP_MEMPACK_SwapPacks(gGT->activeMempackIndex);
}