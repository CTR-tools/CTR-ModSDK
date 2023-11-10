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
			
			struct DramPointerMap* dpm = &realFileBuf[ptrMapOffset];
		
			DECOMP_LOAD_RunPtrMap(realFileBuf, (int*)DRAM_GETOFFSETS(dpm), dpm->numBytes>>2);
			
			// if overly allocated
			if(lqs->flags & 1)
			{
				// undo allocation, allocate "needed" size,
				// ptrMapOffset+4 equals the filesize
				DECOMP_MEMPACK_ReallocMem(ptrMapOffset+4);
			}
		}
	}
	
	void* callbackFunc = lqs->callback.funcPtr;
	
	if(callbackFunc != 0)
	{
		// if function, and not flags
		#ifndef REBUILD_PC
		if(((unsigned int)callbackFunc & 0xff000000) == 0x80000000)
		#else
		if((int)callbackFunc > 0)
		#endif
		{
			(*lqs->callback.funcPtr)(lqs);
		}
	}
	
	sdata->queueReady = 1;
}