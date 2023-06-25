#include <common.h>

// param2 = BASCUS-94426G* 
// TODO: 4 bytes over budget
char *DECOMP_MEMCARD_FindFirstGhost(int slotIdx, char *srcString)
{
    if (sdata->unk_card_8008D404)
    {
        return (char *)0;
    }

    struct DIRENTRY *firstEntry;
    struct DIRENTRY someEntry;
    MEMCARD_StringSet(sdata->s_bu00_BASCUS_94426_slots, slotIdx, srcString);

    // string for directory and file of save that is in use
    firstEntry = firstfile(sdata->s_bu00_BASCUS_94426_slots, &someEntry);

    if (firstEntry == &someEntry)
    {
        sdata->unk_card_8008D404 = 0xf;
        strcpy(firstEntry->name, someEntry.name); // 0x80
        return sdata->s_unk_someOtherMemcardString;
    }
}