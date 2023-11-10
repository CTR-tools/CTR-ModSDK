#include <common.h>

void LOAD_Callback_LEV();
void LOAD_HubCallback();

void DECOMP_LOAD_Hub_ReadFile(int bigfilePtr, int levID, int packID)
{
	int iVar2;
	struct GameTracker* gGT = sdata->gGT;
	
	// if level is already loaded, quit
	if(gGT->levID_in_each_mempack[packID] == levID) 
		return;
	
	gGT->levID_in_each_mempack[packID] = levID;
	
	gGT->level2 = 0;
	
	sdata->modelMaskHints3D = 0;
	sdata->load_inProgress = 1;
	
	DECOMP_MEMPACK_SwapPacks(packID);
	MEMPACK_ClearLowMem();
	
	iVar2 = LOAD_GetBigfileIndex(levID, 1, LVI_VRAM);
	LOAD_AppendQueue(bigfilePtr, LT_VRAM, iVar2, 0, 0);
	
	iVar2 = LOAD_GetBigfileIndex(levID, 1, LVI_LEV);
	LOAD_AppendQueue(bigfilePtr, LT_DRAM, iVar2, 0, LOAD_Callback_LEV);
	
	iVar2 = LOAD_GetBigfileIndex(levID, 1, LVI_PTR);
	LOAD_AppendQueue(bigfilePtr, LT_RAW, iVar2, sdata->PatchMem_Ptr, LOAD_HubCallback);
}