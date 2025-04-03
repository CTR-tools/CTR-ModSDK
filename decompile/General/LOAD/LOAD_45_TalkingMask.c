#include <common.h>

void DECOMP_LOAD_TalkingMask(int packID, int maskID)
{
	sdata->modelMaskHints3D = 0;
	
	// invalidate alternative-hub, because
	// the mask will load in that level's RAM
	sdata->gGT->levID_in_each_mempack[packID] = -1;
	
	DECOMP_MEMPACK_SwapPacks(packID);
	DECOMP_MEMPACK_ClearLowMem();
	
	int offset = maskID*4 + (packID-1)*2;
	
	DECOMP_LOAD_AppendQueue(
		0, LT_SETVRAM, BI_UKAHEAD+offset, 
		NULL, DECOMP_LOAD_VramFileCallback);
	
	DECOMP_LOAD_AppendQueue(
		0, LT_GETADDR, BI_UKAHEAD+offset+1, 
		&sdata->modelMaskHints3D, DECOMP_LOAD_DramFileCallback);
}