#include <common.h>

void DECOMP_MEMPACK_PopState()
{
	register struct sData* sdata asm("gp");

	struct Mempack* ptrMempack;
	int numBookmarks;

	// Get the pointer to the memory allocation system
	ptrMempack = sdata->PtrMempack;

	// if valid
	if(ptrMempack->numBookmarks > 0)
	{
		// go to bookmark address, go back one bookmark
		ptrMempack->firstFreeByte =
			ptrMempack->bookmarks[--ptrMempack->numBookmarks];
	}
}