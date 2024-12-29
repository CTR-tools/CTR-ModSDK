#include <common.h>

void DECOMP_LOAD_CDRequestCallback(struct LoadQueueSlot* lqs)
{
	sdata->queueReady = 1;
	
	if (lqs->callback.funcPtr != 0)
		lqs->callback.funcPtr(lqs);
}