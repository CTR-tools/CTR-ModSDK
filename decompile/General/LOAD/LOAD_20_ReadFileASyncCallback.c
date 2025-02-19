#include <common.h>

// test a failure
#if 0
int last = -1;
#endif

void DECOMP_LOAD_ReadFileASyncCallback(CdlIntrResult result, uint8_t* unk)
{
	CdReadCallback(0);
	
	struct LoadQueueSlot* lqs = &data.currSlot;
	
	// test a failure
	#if 0
	if(last != lqs->subfileIndex)
	{
		last = lqs->subfileIndex;
		result = -5;
		printf("Retry: %d\n", last);
	}
	#endif
	
	if(result == CdlComplete)
	{
		// callback
		if(sdata->ReadFileAsyncCallbackFuncPtr != 0)
		{
			(*sdata->ReadFileAsyncCallbackFuncPtr)(lqs);
		}
	}
	
	// CdlDiskError
	else
	{
		if(lqs->flags & 1)
		{
			// undo allocation, try again
			DECOMP_MEMPACK_ReallocMem(0);
		}
		
		sdata->queueRetry = 1;
		
		sdata->queueReady = 1;
		sdata->queueLength++;
	}
}