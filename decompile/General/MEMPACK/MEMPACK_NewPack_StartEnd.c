#include <common.h>

void DECOMP_MEMPACK_NewPack_StartEnd(void* start,int size)
{
	struct Mempack* ptrMempack;

	// Get the pointer to the memory allocation system
	ptrMempack = sdata->PtrMempack;

	// store start
	ptrMempack->start = start;

	// dont write endOfMemory or packSize,
	// both of those are a waste of time

	ptrMempack->lastFreeByte = (u_int)start + size;
	ptrMempack->numBookmarks = 0;
	ptrMempack->firstFreeByte = start;

	return;
}