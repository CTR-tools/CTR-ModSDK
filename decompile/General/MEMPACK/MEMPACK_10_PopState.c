#include <common.h>

void DECOMP_MEMPACK_PopState()
{
	struct Mempack* ptrMempack;
	int numBookmarks;

	// Get the pointer to the memory allocation system
	ptrMempack = sdata->PtrMempack;
	numBookmarks = ptrMempack->numBookmarks;

	// if valid
	if(numBookmarks != 0)
	{
		numBookmarks--;
		
		// go to bookmark address, go back one bookmark
		ptrMempack->firstFreeByte =
			ptrMempack->bookmarks[numBookmarks];
			
		ptrMempack->numBookmarks = numBookmarks;
	}
}