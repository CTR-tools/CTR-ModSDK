#include <common.h>

// param3 pointer to memcard
// param4 memcard size
int MEMCARD_NewTask(int slotIdx, char *name, uint8_t *param_3, int fileSize)
{
    sdata->memcardSlot = slotIdx;

    MEMCARD_StringSet(&sdata->s_bu00_BASCUS_94426_slots, slotIdx, name);

    // pointer to memcard 800992e4
    sdata->memcard_ptrStart = param_3;
    sdata->memcard_remainingAttempts = 8;
    sdata->memoryCardFileSize_0x1680 = fileSize;

    return 0;
}