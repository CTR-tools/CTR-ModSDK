#include <common.h>

void LOAD_RunPtrMap(struct Level* origin,void* map,int size);
void MEMPACK_SwapPacks(int system);
void MEMPACK_ClearHighMem();

void DECOMP_LOAD_Callback_LEV_Adv(struct LoadQueueSlot * lqs)
{		
	// pointer to first byte after file "started"
	// before being converted to CTR's "DRAM"
	char* patchPtr;
	
	// first pointer in the array of pointers to patch
	char* patchStart;
	
	// size array for patching
	int patchSize;
	
	// number of pointers to patch
	int patchNum;

	// sdata->ptrLEV_DuringLoading
	// is the same as ptrDestination
	
	// what? how?
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