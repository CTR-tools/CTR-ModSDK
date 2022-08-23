#include <common.h>

void CTR_ErrorScreen(char r, char g, char b);
int MEMPACK_GetFreeBytes();

void* DECOMP_MEMPACK_AllocMem(int allocSize)
{
	register struct sData* sdata asm("gp"); // r28

	int firstFreeByte;
	int newAllocSize;
	struct Mempack* ptrMempack;

	// Get the pointer to the memory allocation system
	ptrMempack = sdata->PtrMempack;

	// if out of memory
	if(MEMPACK_GetFreeBytes() < allocSize)
	{
		CTR_ErrorScreen(0xFF,0,0);

		// infinite loop
		for(;;) {}
	}

	// align up
	newAllocSize = (allocSize + 3) & 0xfffffffc;

	// save the amount of memory we allocated
	// so that it can be used for Realloc, if needed
	ptrMempack->sizeOfPrevAllocation = newAllocSize;

	// get the first byte in RAM that can be used by CTR
	firstFreeByte = *(int*)ptrMempack->firstFreeByte;

	// append allocator for next allocation
	ptrMempack->firstFreeByte = (void *)(firstFreeByte + newAllocSize);

	return (void*)firstFreeByte;
}