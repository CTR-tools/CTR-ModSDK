#include <common.h>

void* DECOMP_MEMPACK_ReallocMem(int allocSize)
{
	int firstFreeByte;
	int newAllocSize;
	struct Mempack* ptrMempack;

	// Get the pointer to the memory allocation system
	ptrMempack = sdata->PtrMempack;

	// no safety check if you're out of memory

	// align up
	newAllocSize = (allocSize + 3) & 0xfffffffc;

	// undo old, allocate new
	ptrMempack->firstFreeByte = (void*)(
			(int)ptrMempack->firstFreeByte -
			ptrMempack->sizeOfPrevAllocation +
			newAllocSize);

	// save the amount of memory we allocated
	// so that it can be used for Realloc, if needed
	ptrMempack->sizeOfPrevAllocation = newAllocSize;

	return ptrMempack->firstFreeByte;
}