#include <common.h>

void DECOMP_PROC_DestroyTracker(struct Thread* t)
{
	struct GameTracker* gGT = sdata->gGT;
	
	if(gGT->numMissiles > 0) gGT->numMissiles--;
	
	DECOMP_PROC_DestroyInstance(t);
}