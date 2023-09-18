#include <common.h>

void DECOMP_LOAD_ReadFileASyncCallback(char result)
{
	CdReadCallback(0);
	
	struct LoadQueueSlot* lqs = &data.currSlot;
	int flags = lqs->flags & 1;
	
	if(result == CdlComplete)
	{
		if(flags)
		{
			// undo sector-align alloc,
			// allocate just "needed" bytes
			DECOMP_MEMPACK_ReallocMem(lqs->size);
		}
		
		// callback
		if(sdata->ReadFileAsyncCallbackFuncPtr != 0)
		{
			(*sdata->ReadFileAsyncCallbackFuncPtr)(lqs);
		}
	}
	
	// CdlDiskError
	else
	{
		if(flags)
		{
			DECOMP_MEMPACK_PopState();
		}
		
		sdata->queueRetry = 1;
	}
}