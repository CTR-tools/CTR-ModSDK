#include <common.h>

void DECOMP_LOAD_Callback_MaskHints3D();

void DECOMP_LOAD_TalkingMask(int packID, int maskID)
{
	sdata->load_inProgress = 1;
	sdata->modelMaskHints3D = 0;
	
	sdata->gGT->levID_in_each_mempack[packID] = -1;
	
	DECOMP_MEMPACK_SwapPacks(packID);
	
	DECOMP_MEMPACK_ClearLowMem();
	
	int offset = maskID*4 + (packID-1)*2;
	
	DECOMP_LOAD_AppendQueue(
		sdata->ptrBigfileCdPos_2, LT_VRAM, 
		BI_UKAHEAD+offset, 
		0, 0);
	
	DECOMP_LOAD_AppendQueue(
		sdata->ptrBigfileCdPos_2, LT_DRAM, 
		BI_UKAHEAD+offset+1, 
		0, DECOMP_LOAD_Callback_MaskHints3D);
}