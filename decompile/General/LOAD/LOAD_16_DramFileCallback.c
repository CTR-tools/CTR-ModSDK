#include <common.h>

void DECOMP_LOAD_DramFileCallback(struct LoadQueueSlot* lqs)
{
	char* fileBuf = lqs->ptrDestination;
	
	if(fileBuf != 0)
	{
		int ptrMapOffset = *(int*)&fileBuf[0];
		char* realFileBuf = &fileBuf[4];
		lqs->ptrDestination = realFileBuf;
		
		// if no map
		if(ptrMapOffset < 0)
		{
			lqs->flags |= 2;
		}
		
		// if ptrMapOffset is valid
		else
		{
			
			struct DramPointerMap* dpm = (struct DramPointerMap*)&realFileBuf[ptrMapOffset];
		
			DECOMP_LOAD_RunPtrMap((int)realFileBuf, (int*)DRAM_GETOFFSETS(dpm), dpm->numBytes>>2);

			// undo allocation, allocate "needed" size,
			// ptrMapOffset+4 equals the filesize
			DECOMP_MEMPACK_ReallocMem(ptrMapOffset+4);
		}
	}
	
	sdata->queueReady = 1;
	if (lqs->callbackFuncPtr != 0)
		lqs->callbackFuncPtr(lqs);
}