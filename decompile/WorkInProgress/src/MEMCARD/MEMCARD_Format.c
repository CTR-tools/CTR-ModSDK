#include <common.h>

// TODO: Double check this fn
uint8_t MEMCARD_Format(int slotIdx)
{
    char *someVar = 0;

    if (sdata->unk_card_8008D404 == 0)
    {
        MEMCARD_StringInit(slotIdx, someVar);

        if (format(someVar) == 1)
        {
            sdata->unk_card_8008D404 = 2;
            sdata->memcardSlot = slotIdx;
            MEMCARD_SkipEvents();

            while (_card_load(sdata->memcardSlot) != 1)
                ;

            sdata->memcard_remainingAttempts = 8;
            return 7;
        }
    }
    return 1;
}