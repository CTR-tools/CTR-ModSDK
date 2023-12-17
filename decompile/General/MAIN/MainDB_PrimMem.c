#include <common.h>

void DECOMP_MainDB_PrimMem(struct PrimMem* primMem, u_int size)
{
	void* pvVar1;
	
	#ifdef REBUILD_PC
	size = size*8;
	#endif
	
	pvVar1 = DECOMP_MEMPACK_AllocMem(size);
	primMem->size = size;
	primMem->unk2 = (int)pvVar1;
	primMem->curr = pvVar1;
	primMem->start = pvVar1;
	
	// skip alignment by & 0xfffffffc,
	// all possible size inputs are already aligned
	pvVar1 = (void*)((int)pvVar1 + size);
	primMem->end = pvVar1;
	primMem->endMin100 = (void*)((int)pvVar1 - 0x100);
	
	return;
}