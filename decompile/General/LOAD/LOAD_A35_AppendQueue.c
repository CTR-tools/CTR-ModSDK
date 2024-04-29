#include <common.h>

void DECOMP_LOAD_AppendQueue(int bigfile, int type, int fileIndex, void* destinationPtr, void* callback)
{
	struct LoadQueueSlot* lqs;
	
	#ifdef USE_BIGQUEUE
	if(sdata->queueLength >= 8)
		return;
	#endif

	lqs = &sdata->queueSlots[sdata->queueLength];
	lqs->ptrBigfileCdPos = bigfile;
	lqs->flags = 0;
	lqs->type = type;
	lqs->subfileIndex = fileIndex;
	lqs->ptrDestination = destinationPtr;
	lqs->size = 0;
	lqs->callback.funcPtr = callback;
	
	sdata->queueLength++;
	
	#ifdef USE_OXIDE
	void Oxide_HookAppendLoadingQueue();
	Oxide_HookAppendLoadingQueue();
	#endif
}