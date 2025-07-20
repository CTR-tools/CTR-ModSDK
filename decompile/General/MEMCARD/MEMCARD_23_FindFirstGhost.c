#include <common.h>

char* DECOMP_MEMCARD_FindFirstGhost(int slotIdx, char *srcString)
{
    if (sdata->memcard_stage != MC_STAGE_IDLE)
    {
        return 0;
    }

    struct DIRENTRY *firstEntry;
    struct DIRENTRY someEntry;
    MEMCARD_StringSet(sdata->s_memcardFileCurr, slotIdx, srcString);

    firstEntry = firstfile(sdata->s_memcardFileCurr, &someEntry);
    if (firstEntry == 0)
		return 0;
    
    sdata->memcard_stage = MC_STAGE_GHOST_FOUND;
    strcpy(&sdata->s_memcardFindGhostFile[0], &firstEntry->name[0]);
    return &sdata->s_memcardFindGhostFile[0];
}