#include <common.h>

void MainDB_OTMem(struct OTMem* otMem, u_int size)
{
	void* pvVar1;
	
	pvVar1 = MEMPACK_AllocMem(size);
	otMem->size = size;
	otMem->curr = pvVar1;
	otMem->start = pvVar1;
	otMem->end = (void*)((int)pvVar1 + (size & 0xfffffffc));
	return;
}