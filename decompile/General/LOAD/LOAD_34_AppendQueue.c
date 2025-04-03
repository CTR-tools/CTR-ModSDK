#include <common.h>

// This is a wonderful hack that removes an unused parameter,
// which saves bytes everywhere, without needing to alter the game code,
// We need the 'bigfile' parameter to stay in the C code, just to keep
// the front-end looking similar to ghidra, for easy comparison purposes
#define DECOMP_LOAD_AppendQueue(a,b,c,d,e) DECOMP_LOAD_AppendQueue_ex(b,c,d,e)

void DECOMP_LOAD_AppendQueue_ex(/*int bigfile,*/ int flags, int fileIndex, void* destinationPtr, void (*callback)(struct LoadQueueSlot*))
{
	struct LoadQueueSlot* lqs;
	
	#ifndef USE_BIGQUEUE
	if(sdata->queueLength >= 8)
		return;
	#endif

	lqs = &sdata->queueSlots[sdata->queueLength];
	lqs->flags = flags;
	lqs->subfileIndex = fileIndex;
	lqs->ptrDestination = destinationPtr;
	lqs->callbackFuncPtr = callback;
	
	sdata->queueLength++;
	sdata->load_inProgress = 1;
}