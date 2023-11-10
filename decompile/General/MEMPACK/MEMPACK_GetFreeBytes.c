#include <common.h>

int DECOMP_MEMPACK_GetFreeBytes()
{
	struct Mempack* ptrMempack;

	// Get the pointer to the memory allocation system
	ptrMempack = sdata->PtrMempack;

	// subtract last byte from first byte, to return size
	return (u_int)ptrMempack->lastFreeByte - (u_int)ptrMempack->firstFreeByte;
}