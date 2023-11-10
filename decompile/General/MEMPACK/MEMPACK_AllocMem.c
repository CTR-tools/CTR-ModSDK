#include <common.h>

void* DECOMP_MEMPACK_AllocMem(int allocSize)
{
	int firstFreeByte;
	int newAllocSize;
	struct Mempack* ptrMempack;

	// Get the pointer to the memory allocation system
	ptrMempack = sdata->PtrMempack;

	// if out of memory
	if(DECOMP_MEMPACK_GetFreeBytes() < allocSize)
	{
		DECOMP_CTR_ErrorScreen(0xFF,0,0);

		// infinite loop
		for(;;) {}
	}

	// align up
	newAllocSize = (allocSize + 3) & 0xfffffffc;

	// save the amount of memory we allocated
	// so that it can be used for Realloc, if needed
	ptrMempack->sizeOfPrevAllocation = newAllocSize;

	// get the first byte in RAM that can be used by CTR
	firstFreeByte = (int)ptrMempack->firstFreeByte;

	// append allocator for next allocation
	ptrMempack->firstFreeByte = (void *)(firstFreeByte + newAllocSize);

	return (void*)firstFreeByte;
}