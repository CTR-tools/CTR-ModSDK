#include <common.h>

void DECOMP_LOAD_CDRequestCallback(struct LoadQueueSlot* lqs)
{
	if (lqs->callbackFuncPtr != 0)
		lqs->callbackFuncPtr(lqs);
}