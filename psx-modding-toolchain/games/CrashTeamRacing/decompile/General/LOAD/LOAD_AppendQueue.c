#include <common.h>

void LOAD_AppendQueue(int bigfile, int type, int fileIndex, void* destinationPtr, void* callback)
{
	struct LoadQueueSlot* lqs;
	
	if(sdata->queueLength < 8)
	{
		lqs = &sdata->queueSlots[sdata->queueLength];
		lqs->ptrBigfileCdPos = bigfile;
		lqs->flags = 0;
		lqs->type = type;
		lqs->subfileIndex = fileIndex;
		lqs->ptrDestination = destinationPtr;
		lqs->size = 0;
		lqs->callback.funcPtr = callback;
		
		sdata->queueLength++;
	}
}