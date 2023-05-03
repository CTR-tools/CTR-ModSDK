#include <common.h>

// param2 = BASCUS-94426G* // TODO: Check type
// TODO: Return type? I assume string from the unk Thing
char *MEMCARD_FindFirstGhost(int slotIdx, char *srcString)
{
    if (sdata->unk_card_8008D404)
    {
        return (char *)0;
    }

    struct DIRENTRY *firstEntry;
    struct DIRENTRY someEntry; // some stack variable?
    MEMCARD_StringSet(sdata->s_bu00_BASCUS_94426_slots, slotIdx, &srcString);

    // string for directory and file of save that is in use
    firstEntry = firstfile(&sdata->s_bu00_BASCUS_94426_slots, &someEntry);

    if (firstEntry == &someEntry)
    {
        sdata->unk_card_8008D404 = 0xf;
        strcpy(firstEntry, &someEntry); // 0x80
        return sdata->s_unk_someOtherMemcardString;
    }
}