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
	
	// Fix character model breaking post-roo?
	#if 1
	DECOMP_MEMPACK_SwapPacks(sdata->gGT->activeMempackIndex);
	#endif
	
	return;
}