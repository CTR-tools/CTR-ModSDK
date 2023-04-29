#include <common.h>

void THREAD_DestroyTracker(struct Thread* t)
{
	struct GameTracker* gGT = sdata->gGT;
	
	if(gGT->numMissiles > 0) gGT->numMissiles--;
	
	THREAD_DestroyInstance(t);
}