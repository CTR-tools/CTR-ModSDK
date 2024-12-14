#include <common.h>

uint8_t DECOMP_MEMCARD_Format(int slotIdx)
{
    if (sdata->unk_card_8008D404 == 0)
    {
        char *someVar = MEMCARD_StringInit(slotIdx, 0);

        // format always returns 1
        if (format(someVar))
        {
            sdata->unk_card_8008D404 = 2;
            sdata->memcardSlot = slotIdx;
            MEMCARD_SkipEvents();

            while (!_card_load(sdata->memcardSlot))
                ;

            sdata->memcard_remainingAttempts = 8;
            return 7;
        }
    }
    return 1;
}