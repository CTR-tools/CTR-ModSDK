#include <common.h>

// NOTE: Always returns 0, should it become a void fn?
int DECOMP_MEMCARD_NewTask(int slotIdx, char *name, uint8_t *ptrMemcard, int memcardFileSize)
{
    sdata->memcardSlot = slotIdx;

    MEMCARD_StringSet(sdata->s_bu00_BASCUS_94426_slots, slotIdx, name);

    // pointer to memcard 800992e4
    sdata->memcard_ptrStart = ptrMemcard;
    sdata->memcard_remainingAttempts = 8;
    sdata->memoryCardFileSize_0x1680 = memcardFileSize;

    return 0;
}