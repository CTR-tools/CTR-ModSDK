#include <common.h>

uint8_t DECOMP_MEMCARD_GetInfo(int slotIdx)

{
    if (sdata->unk_card_8008D404 == 0)
    {
        MEMCARD_SkipEvents();
        sdata->unk_card_8008D404 = 1;
        sdata->memcardSlot = slotIdx;

        // loop until check is "submitted",
        // result is not "returned", result
        // is found in SwCARD descriptor/event (see libref)
        while (_card_info(slotIdx) != 1)
            ;

        sdata->memcard_remainingAttempts = 8;
        return 7;
    }
    else
    {
        return 1;
    }
}