#include <common.h>

void DECOMP_LOAD_HubSwapPtrs(struct GameTracker* gGT)
{
	struct Level* oldLev1;
	struct VisMem* oldVisMem1;
	
	// if no secondary lev exists, quit
	if(gGT->level2 == 0) return;
	
	oldLev1 = gGT->level1;
	oldVisMem1 = gGT->visMem1;
	
	gGT->level1 = gGT->level2;
	gGT->visMem1 = gGT->visMem2;
	
	gGT->level2 = oldLev1;
	gGT->visMem2 = oldVisMem1;
}