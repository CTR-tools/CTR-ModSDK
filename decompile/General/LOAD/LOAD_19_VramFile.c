#include <common.h>

void* DECOMP_LOAD_VramFile(void* bigfilePtr, int subfileIndex)
{
	// This works cause all sync-loads for VRAM
	// happen before any of the async queue starts
	struct LoadQueueSlot* curr = &data.currSlot;
	
	// callback=0 means this calls CdSync and is not async
	DECOMP_LOAD_ReadFile(bigfilePtr, subfileIndex, 0, 0);
	
	// undo allocation, next LOAD queue request
	// will overwrite where VRAM was in RAM
	DECOMP_MEMPACK_ReallocMem(0);
	
	// run callback
	DECOMP_LOAD_VramFileCallback(curr);
	
	// wait 2 frames for LoadImage to finish
	VSync(2);
	
	// do NOT trigger code in vsync callback to handle queue
	sdata->frameFinishedVRAM = 0;
}