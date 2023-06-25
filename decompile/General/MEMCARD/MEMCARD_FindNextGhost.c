#include <common.h>

char *DECOMP_MEMCARD_FindNextGhost(void)
{
    struct DIRENTRY *nextEntry;
    struct DIRENTRY someEntry;

    if (sdata->unk_card_8008D404 != 0xf)
        return (char *)0;

    nextEntry = nextfile(&someEntry);
    if (nextEntry == &someEntry)
    {
        strcpy(nextEntry->name, someEntry.name);
        return sdata->s_unk_someOtherMemcardString;
    }
    sdata->unk_card_8008D404 = 0;
}