#include <common.h>

// NOTE: unused function?
uint8_t DECOMP_MEMCARD_EraseFile(int slotIdx, char *srcString)
{
    if (sdata->unk_card_8008D404)
        return 1;
    char name[64];
    MEMCARD_StringSet(name, slotIdx, srcString);
    sdata->unk_card_8008D404 = (erase(name)) ? 0xe : 0xd;
    MEMCARD_GetFreeBytes(slotIdx);
    return 7;
}