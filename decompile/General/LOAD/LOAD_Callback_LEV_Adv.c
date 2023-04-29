#include <common.h>

void LOAD_RunPtrMap(struct Level* origin,void* map,int size);
void MEMPACK_SwapPacks(int system);
void MEMPACK_ClearHighMem();

void DECOMP_LOAD_Callback_LEV_Adv(struct LoadQueueSlot * lqs)
{		
	char* patchPtr;
	char* patchStart;
	int patchSize;	
	int patchNum;

	// CTR doesn't load one lev DRAM for AdvHub,
	// it loads one ReadFile for LEV in a sub-mempack,
	// it loads one ReadFile for PtrMap with AllocHighMem
	
	// that's why patchPtr is ptrDestination
	patchPtr = (char*)lqs->ptrDestination;
	patchStart = &patchPtr[4];
	patchSize = *(int*)&patchPtr[0];
	patchNum = patchSize >> 2;
	
	sdata->load_inProgress = 0;
	LOAD_RunPtrMap(sdata->ptrLEV_DuringLoading, patchStart, patchNum);
	MEMPACK_SwapPacks(0);
	MEMPACK_ClearHighMem();
	MEMPACK_SwapPacks(sdata->gGT->activeMempackIndex);
	return;
}