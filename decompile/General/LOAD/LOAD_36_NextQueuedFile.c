#include <common.h>

void DECOMP_LOAD_NextQueuedFile()
{
	// Under 3 conditions, delay the load:
	//		During XA play
	//		Queue is in use
	//		Queue is empty
	if (sdata->XA_State != 0) return;
	if (sdata->queueReady == 0) return;
	if (sdata->queueLength == 0) return;
	

	sdata->queueReady = 0;
	
	struct LoadQueueSlot* curr = &data.currSlot;
	
	// retry previously-failed load
	if(sdata->queueRetry != 0)
	{
		sdata->queueRetry = 0;
	}
	
	// brand new load
	else
	{
		// Naughty Dog had inline copying,
		// is that faster on real PS1 hardware?
		
		memcpy(curr, &sdata->queueSlots[0], sizeof(struct LoadQueueSlot));
		
		for(int i = 1; i < sdata->queueLength; i++)
			memcpy(&sdata->queueSlots[i-1], &sdata->queueSlots[i], sizeof(struct LoadQueueSlot));
	}
	
	sdata->queueLength--;
	
	// get value originally passed
	// BEFORE calling ReadFile, which may change it
	int* prevValue = curr->ptrDestination;
	
	int* forceSetAddr = (int*)0;
	if ((curr->flags & LT_SETADDR) != 0)
		forceSetAddr = prevValue;
	
	DECOMP_LOAD_ReadFile(0,
		curr->flags | LT_ASYNC,
		curr->subfileIndex, (void*)forceSetAddr);
		
	if ((curr->flags & LT_GETADDR) != 0)
	{
		*prevValue = (int)curr->ptrDestination + 4;
	}
}