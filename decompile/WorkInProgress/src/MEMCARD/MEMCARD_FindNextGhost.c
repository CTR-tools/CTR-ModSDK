#include <common.h>

// === Does not work ===

// Try loading a memcard with multiple ghosts

char *DECOMP_MEMCARD_FindNextGhost(void)
{
    struct DIRENTRY *nextEntry;
    struct DIRENTRY someEntry;

    if (sdata->unk_card_8008D404 == 0xf)
	{
		nextEntry = nextfile(&someEntry);
		if (nextEntry == &someEntry)
		{
			strcpy(nextEntry->name, someEntry.name);
			return sdata->s_unk_someOtherMemcardString;
		}
		sdata->unk_card_8008D404 = 0;
	}
	
	return (char *)0;
}