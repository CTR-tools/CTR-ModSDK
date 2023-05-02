#include <common.h>

// function (unused)?
uint8_t MEMCARD_EraseFile(int slotIdx, char *srcString)
// NOTE: This impl is 4-bytes over budget
// {
//     if (sdata->unk_card_8008D404)
//         return 1;
//     char name[64];
//     MEMCARD_StringSet(name, slotIdx, srcString);
//     sdata->unk_card_8008D404 = (erase(name) != 1) ? 0xd : 0xe;
//     MEMCARD_GetFreeBytes(slotIdx);
//     return 7;
// }

// NOTE: This impl will indiscriminately erase then check the unk_card_00D404... CAN CAUSE BUGS
{
    char name[64];
    MEMCARD_StringSet(name, slotIdx, srcString);

    sdata->unk_card_8008D404 = (erase(name) == 1) ? 0xe : 0xd;

    return sdata->unk_card_8008D404 ? 1 : 7;
}