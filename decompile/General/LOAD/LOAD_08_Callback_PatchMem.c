#include <common.h>

void DECOMP_LOAD_Callback_PatchMem()
{		
	char* patchPtr;
	char* patchStart;
	int patchSize;	
	int patchNum;

	// CTR doesn't load one lev DRAM for AdvHub,
	// it loads one ReadFile for LEV in a sub-mempack,
	// it loads one ReadFile for PtrMap with AllocHighMem
	
	// that's why patchPtr is here
	patchPtr = sdata->PatchMem_Ptr;
	patchStart = &patchPtr[4];
	patchSize = *(int*)&patchPtr[0];
	patchNum = patchSize >> 2;
	
	DECOMP_LOAD_RunPtrMap((int)sdata->ptrLevelFile, (int*)patchStart, patchNum);
	
	#if 0
	// This was "intended" to clear AllocHighMem
	// that was used to allocate PtrFile, but this
	// should not happen anyway, cause PtrFile is
	// needed again after the callback
	DECOMP_MEMPACK_SwapPacks(0);
	DECOMP_MEMPACK_ClearHighMem();
	#endif
	
	DECOMP_MEMPACK_SwapPacks(sdata->gGT->activeMempackIndex);
	return;
}