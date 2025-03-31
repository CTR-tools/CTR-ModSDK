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
		
	if(curr->type == LT_RAW)
	{
		// For LT_RAW:
		// INPUT  curr->ptrDestination is where the file WILL load
		// OUTPUT curr->ptrDestination is where the file DID load
		
		curr->ptrDestination =
			DECOMP_LOAD_ReadFile(
				curr->ptrBigfileCdPos,
				curr->subfileIndex,
				curr->ptrDestination,
				DECOMP_LOAD_CDRequestCallback);
	}
	
	else if(curr->type == LT_DRAM)
	{
		// For LT_DRAM:
		// OUTPUT curr->ptrDestination is where the file DID load
		// INPUT  curr->ptrDestination is where the output pointer is written
		
		int* prevValue = curr->ptrDestination;
		
		curr->ptrDestination =
			DECOMP_LOAD_ReadFile(
				curr->ptrBigfileCdPos,
				curr->subfileIndex,
				0,
				DECOMP_LOAD_DramFileCallback);
				
		if(prevValue != 0)
		{
			*prevValue = curr->ptrDestination;
		}
	}
	
	else if(curr->type == LT_VRAM)
	{
		// For LT_VRAM:
		// OUTPUT curr->ptrDestination is where the file DID load
		// INPUT  curr->ptrDestination is ignored
		
		curr->ptrDestination =
			DECOMP_LOAD_ReadFile(
				curr->ptrBigfileCdPos,
				curr->subfileIndex,
				0,
				DECOMP_LOAD_VramFileCallback);
				
		// undo allocation, next LOAD queue request
		// will overwrite where VRAM was in RAM
		DECOMP_MEMPACK_ReallocMem(0);
	}
	
#if defined(USE_PCDRV)
	// After curr->ptrDestination is written,
	// run the callback and use the destination
	DECOMP_LOAD_ReadFileASyncCallback(CdlComplete, NULL);
#endif
}