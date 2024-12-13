#include <common.h>

void* DECOMP_MEMPACK_AllocHighMem(int allocSize)
{
	int newLastFreeByte;

	// if out of memory
	while(DECOMP_MEMPACK_GetFreeBytes() < allocSize)
	{
		// enter infinite loop
	}

	// align up
	allocSize = (allocSize + 3) & 0xfffffffc;

	// dont use sizeOfPrevAlloc, cause you can't Realloc
	// on HighMem, that's only for low end allocations

	// address to return
	newLastFreeByte = (int)sdata->PtrMempack->lastFreeByte - allocSize;

	// allocator goes backwards for high end
	sdata->PtrMempack->lastFreeByte = (void *)newLastFreeByte;

	// new last free byte
	return (void *)newLastFreeByte;
}