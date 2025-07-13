#include <common.h>

// param2 = BASCUS-94426G* 
// TODO: 4 bytes over budget
char* DECOMP_MEMCARD_FindFirstGhost(int slotIdx, char *srcString)
{
    if (sdata->memcard_stage != MC_STAGE_IDLE)
    {
        return 0;
    }

    struct DIRENTRY *firstEntry;
    struct DIRENTRY someEntry;
    MEMCARD_StringSet(sdata->s_bu00_BASCUS_94426_slots, slotIdx, srcString);

    // string for directory and file of save that is in use
    firstEntry = firstfile(sdata->s_bu00_BASCUS_94426_slots, &someEntry);

	// [error]
	// They cant be true, a firstfile pointer wont "equal" a stack pointer,
	// maybe compare the strings instead?
    if (firstEntry == &someEntry)
    {
        sdata->memcard_stage = MC_STAGE_GHOST_FOUND;
        strcpy(firstEntry->name, someEntry.name); // 0x80
        return &sdata->s_memcardFindGhostFile[0];
    }
}