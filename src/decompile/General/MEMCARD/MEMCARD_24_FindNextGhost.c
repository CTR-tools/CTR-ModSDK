#include <common.h>

char* DECOMP_MEMCARD_FindNextGhost(void)
{
    if (sdata->memcard_stage != MC_STAGE_GHOST_FOUND)
	{
		return 0;
	}

    struct DIRENTRY *nextEntry;
    struct DIRENTRY someEntry;
	
	nextEntry == nextfile(&someEntry);
	if (nextEntry == 0)
	{
		sdata->memcard_stage = MC_STAGE_IDLE;
		return 0;
	}
	
	strcpy(&sdata->s_memcardFindGhostFile[0], &someEntry.name[0]);
	return &sdata->s_memcardFindGhostFile[0];
}