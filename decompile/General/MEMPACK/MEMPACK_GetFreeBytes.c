#include <common.h>

int DECOMP_MEMPACK_GetFreeBytes()
{
	register struct sData* sdata asm("gp"); // r28

	struct Mempack* ptrMempack;

	// Get the pointer to the memory allocation system
	ptrMempack = sdata->PtrMempack;

	// subtract last byte from first byte, to return size
	return ptrMempack->lastFreeByte - ptrMempack->firstFreeByte;
}