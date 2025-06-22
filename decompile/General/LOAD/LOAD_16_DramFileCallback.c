#include <common.h>

void DECOMP_LOAD_DramFileCallback(struct LoadQueueSlot* lqs)
{
	char* fileBuf = lqs->ptrDestination;
	
	// Completely impossible
	#if 0
	if(fileBuf == 0)
		return;
	#endif
	
	int ptrMapOffset = *(int*)&fileBuf[0];
	char* realFileBuf = &fileBuf[4];
	
	// if ptrMapOffset is valid,
	// for all levels except AdvHub LEVs
	if(ptrMapOffset >= 0)
	{	
		struct DramPointerMap* dpm = (struct DramPointerMap*)&realFileBuf[ptrMapOffset];
	
		DECOMP_LOAD_RunPtrMap(realFileBuf, (int*)DRAM_GETOFFSETS(dpm), dpm->numBytes>>2);
		
		DRAM_SET_PATCHED(fileBuf);

		// undo allocation, allocate "needed" size,
		// ptrMapOffset+4 equals the filesize
		DECOMP_MEMPACK_ReallocMem(ptrMapOffset+4);
	}
}