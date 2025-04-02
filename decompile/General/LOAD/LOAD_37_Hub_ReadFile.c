#include <common.h>

void DECOMP_LOAD_Hub_ReadFile(int bigfile, int levID, int packID)
{
	int iVar2;
	struct GameTracker* gGT = sdata->gGT;
	
	// if level is already loaded, quit
	if(gGT->levID_in_each_mempack[packID] == levID) 
		return;
	
	gGT->levID_in_each_mempack[packID] = levID;
	
	gGT->level2 = 0;
	sdata->modelMaskHints3D = 0;
	
	DECOMP_MEMPACK_SwapPacks(packID);
	DECOMP_MEMPACK_ClearLowMem();
	
	// base index for group
	iVar2 = DECOMP_LOAD_GetBigfileIndex(levID, 1);
	
	DECOMP_LOAD_AppendQueue(bigfile, LT_VRAM, iVar2+LVI_VRAM, 0, NULL);
	DECOMP_LOAD_AppendQueue(bigfile, LT_DRAM, iVar2+LVI_LEV, &sdata->ptrLevelFile, NULL);
	DECOMP_LOAD_AppendQueue(bigfile, LT_RAW,  iVar2+LVI_PTR, (void*)sdata->PatchMem_Ptr, DECOMP_LOAD_HubCallback);
}