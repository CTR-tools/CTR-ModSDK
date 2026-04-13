#include <common.h>

void* DECOMP_LOAD_VramFile(void* bigfilePtr, int subfileIndex)
{
	DECOMP_LOAD_ReadFile(0,
		LT_SETVRAM | LT_SYNC, 
		subfileIndex, 0);
	
	// run callback
	DECOMP_LOAD_VramFileCallback(0);
	
	// wait 2 frames for LoadImage to finish
	VSync(2);
}