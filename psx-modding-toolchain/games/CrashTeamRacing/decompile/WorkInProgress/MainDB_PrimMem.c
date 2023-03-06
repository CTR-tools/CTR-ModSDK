#include <common.h>

void MainDB_PrimMem(struct PrimMem* primMem, u_int size)
{
	void* pvVar1;
	
	pvVar1 = MEMPACK_AllocMem(size);
	primMem->size = size;
	primMem->unk2 = (int)pvVar1;
	primMem->curr = pvVar1;
	primMem->start = pvVar1;
	pvVar1 = (void*)((int)pvVar1 + (size & 0xfffffffc));
	primMem->end = pvVar1;
	primMem->endMin100 = (void*)((int)pvVar1 - 0x100);
	return;
}