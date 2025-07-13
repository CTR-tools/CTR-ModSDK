#include <common.h>

// === Does not work ===

// Try loading a memcard with multiple ghosts

char* DECOMP_MEMCARD_FindNextGhost(void)
{
    struct DIRENTRY *nextEntry;
    struct DIRENTRY someEntry;

    if (sdata->memcard_stage != MC_STAGE_GHOST_FOUND)
	{
		return 0;
	}
	
	// [error]
	// They cant be true, a firstfile pointer wont "equal" a stack pointer,
	// maybe compare the strings instead?
	nextEntry = nextfile(&someEntry);
	if (nextEntry == &someEntry)
	{
		strcpy(nextEntry->name, someEntry.name);
		return &sdata->s_memcardFindGhostFile[0];
	}
	sdata->memcard_stage = MC_STAGE_IDLE;
}