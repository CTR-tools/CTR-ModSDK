#include <common.h>

void DECOMP_LOAD_Callback_MaskHints3D();

void DECOMP_LOAD_TalkingMask(int packID, int maskID)
{
	sdata->load_inProgress = 1;
	sdata->modelMaskHints3D = 0;
	
	sdata->gGT->levID_in_each_mempack[packID] = -1;
	
	DECOMP_MEMPACK_SwapPacks(packID);
	
	MEMPACK_ClearLowMem();
	
	int offset = maskID*4 + (packID-1)*2;
	
	LOAD_AppendQueue(sdata->ptrBigfileCdPos_2, LT_VRAM, offset+0x1b6, 0, 0);
	
	LOAD_AppendQueue(sdata->ptrBigfileCdPos_2, LT_DRAM, offset+0x1b7, 0, DECOMP_LOAD_Callback_MaskHints3D);
}