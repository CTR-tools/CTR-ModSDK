#include <common.h>

void LOAD_CDRequestCallback(struct LoadQueueSlot* lqs)
{
	sdata->queueReady = 1;
	
	if (lqs->callback.funcPtr != 0)
		lqs->callback.funcPtr(lqs);
}