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
	
	// whether success or fail...
	sdata->queueReady = 1;
	
	if(result == CdlComplete)
	{		
		if(sdata->queueLength == 0)
			sdata->load_inProgress = 0;

		if (lqs->callbackFuncPtr != 0)
			lqs->callbackFuncPtr(lqs);
	}
	
	// CdlDiskError
	else
	{
		if((lqs->flags & LT_MEMPACK) != 0)
		{
			// undo allocation, try again
			DECOMP_MEMPACK_ReallocMem(0);
		}
		
		sdata->queueRetry = 1;
		sdata->queueLength++;
	}
}