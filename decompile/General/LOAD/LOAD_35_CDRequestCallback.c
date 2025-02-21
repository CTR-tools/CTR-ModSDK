#include <common.h>

void DECOMP_LOAD_CDRequestCallback(struct LoadQueueSlot* lqs)
{
	sdata->queueReady = 1;
	if (lqs->callbackFuncPtr != 0)
		lqs->callbackFuncPtr(lqs);
}