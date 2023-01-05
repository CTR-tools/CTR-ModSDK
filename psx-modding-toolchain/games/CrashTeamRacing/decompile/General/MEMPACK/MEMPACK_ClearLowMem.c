#include <common.h>

void DECOMP_MEMPACK_ClearLowMem()
{
	register struct sData* sdata asm("gp"); // r28

	struct Mempack* ptrMempack;

	// Get the pointer to the memory allocation system
	ptrMempack = sdata->PtrMempack;

	// reset bookmarks
	ptrMempack->numBookmarks = 0;

	// reset low-side allocation
	ptrMempack->firstFreeByte = ptrMempack->start;
}