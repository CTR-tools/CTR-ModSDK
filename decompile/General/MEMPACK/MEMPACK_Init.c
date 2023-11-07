#include <common.h>

#ifdef REBUILD_PC
char memory[2*1024*1024];
#endif

void DECOMP_MEMPACK_Init(int ramSize)
{
	struct Mempack* ptrMempack;

	// Get the pointer to the memory allocation system
	ptrMempack = sdata->PtrMempack;

	// start of memory allocation system
	// To Do: make this dynamic depending on OVR Region 3,
	// 			like it is in the original assembly that
	//			ghidra wont read
#ifdef REBUILD_PC
	ptrMempack->start = &memory[0];
	memset(memory, 0, 2*1024*1024);
#else
	ptrMempack->start = (void *)0x800ba9f0;
#endif

	// Set pointer to end of CTR Memory allocation
	// It adds so much so that it becomes 801FF800
	// with the '80' prefix
	ptrMempack->endOfAllocator = (void *)(ramSize + 0x7ffff800);
	ptrMempack->lastFreeByte = (void *)(ramSize + 0x7ffff800);

	ptrMempack->numBookmarks = 0;

	// dont set endOfMemory, waste of time
	// dont set packSize, waste of time

	// set end of allocation to the start of allocation
	ptrMempack->firstFreeByte = ptrMempack->start;
}