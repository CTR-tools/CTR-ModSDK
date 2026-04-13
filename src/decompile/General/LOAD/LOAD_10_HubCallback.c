#include <common.h>

void DECOMP_LOAD_HubCallback(struct LoadQueueSlot* lqs)
{	
	DECOMP_LOAD_Callback_PatchMem();
	
	struct GameTracker* gGT = sdata->gGT;
	struct Level* lev = sdata->ptrLevelFile;
	
	gGT->level2 = lev;
	gGT->visMem2 = lev->visMem;
}