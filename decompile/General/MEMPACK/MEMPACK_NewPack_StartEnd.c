#include <common.h>

void DECOMP_MEMPACK_NewPack_StartEnd(void* start,int size)
{
	register struct sData* sdata asm("gp"); // r28

	struct Mempack* ptrMempack;

	// Get the pointer to the memory allocation system
	ptrMempack = sdata->PtrMempack;

	// store start
	ptrMempack->start = start;

	// dont write endOfMemory or packSize,
	// both of those are a waste of time

	ptrMempack->lastFreeByte = start + size;
	ptrMempack->numBookmarks = 0;
	ptrMempack->firstFreeByte = start;

	return;
}