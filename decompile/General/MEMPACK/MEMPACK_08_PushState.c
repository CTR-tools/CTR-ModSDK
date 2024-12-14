#include <common.h>

int DECOMP_MEMPACK_PushState()
{
	struct Mempack* ptrMempack;
	int numBookmarks;

	// Get the pointer to the memory allocation system
	ptrMempack = sdata->PtrMempack;

	// current number of bookmarks, before push
	numBookmarks = ptrMempack->numBookmarks;

	// if less than 16
	if(numBookmarks < 0x10)
	{
		// set bookmark address
		ptrMempack->bookmarks[numBookmarks] = ptrMempack->firstFreeByte;

		// increment number of bookmarks
		ptrMempack->numBookmarks++;
	}

	// return original number of bookmarks,
	// AKA, return ID of bookmark pushed
	return numBookmarks;
}