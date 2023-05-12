#include <common.h>

void DECOMP_MEMPACK_PopToState(int id)
{
	struct Mempack* ptrMempack;
	int numBookmarks;

	// Get the pointer to the memory allocation system
	ptrMempack = sdata->PtrMempack;

	// go to bookmark address
	ptrMempack->firstFreeByte = ptrMempack->bookmarks[id];

	// upate count
	ptrMempack->numBookmarks = id;
}