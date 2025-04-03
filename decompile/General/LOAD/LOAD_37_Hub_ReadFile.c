#include <common.h>

// packID will always be 3-gGT->activeMempackIndex
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
	
	// Swap to pack of hub you're NOT on,
	// wipe the pack to reload the new hub
	DECOMP_MEMPACK_SwapPacks(packID);
	DECOMP_MEMPACK_ClearLowMem();
	
	// base index for group
	iVar2 = DECOMP_LOAD_GetBigfileIndex(levID, 1);
	
	DECOMP_LOAD_AppendQueue(0, LT_SETVRAM, iVar2+LVI_VRAM, 0, DECOMP_LOAD_VramFileCallback);
	DECOMP_LOAD_AppendQueue(0, LT_GETADDR, iVar2+LVI_LEV, &sdata->ptrLevelFile, DECOMP_LOAD_DramFileCallback);
	DECOMP_LOAD_AppendQueue(0, LT_SETADDR, iVar2+LVI_PTR, (void*)sdata->PatchMem_Ptr, DECOMP_LOAD_HubCallback);
}