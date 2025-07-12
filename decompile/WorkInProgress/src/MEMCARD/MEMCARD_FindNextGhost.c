#include <common.h>

// === Does not work ===

// Try loading a memcard with multiple ghosts

char* DECOMP_MEMCARD_FindNextGhost(void)
{
    struct DIRENTRY *nextEntry;
    struct DIRENTRY someEntry;

    if (sdata->memcard_stage == 0xf)
	{
		nextEntry = nextfile(&someEntry);
		if (nextEntry == &someEntry)
		{
			strcpy(nextEntry->name, someEntry.name);
			return &sdata->s_memcardFindGhostFile[0];
		}
		sdata->memcard_stage = 0;
	}
	
	return (char *)0;
}