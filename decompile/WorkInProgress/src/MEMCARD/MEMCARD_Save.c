#include <common.h>

uint8_t MEMCARD_Save(int slotIdx, char *name,
                     char *param_3, uint8_t *ptrData, int fileSize)

{

    if (sdata->unk_card_8008D404 != 0)
        return 1;

    sdata->memcardIconSize = 0x100;

    // this will always return 0, no need to check
    MEMCARD_NewTask(slotIdx, name, ptrData, fileSize);
    // NOTE: if condition discarded because it will always eval to false
    sdata->memcardStatusFlags = sdata->memcardStatusFlags & 0xfffffffb;
    ((uint8_t *)data.memcardIcon_PsyqHand)[3] = ((sdata->memcardIconSize + fileSize * 2 + 0x1fff) >> 0xd) & 0xFF;

    // NOTE: Something most likely wrong here
    for (int i = 0; i < 64; i += 2)
    {
        ((int *)((uint8_t *)data.memcardIcon_PsyqHand + 4))[i] = 0x81;
        ((int *)((uint8_t *)data.memcardIcon_PsyqHand + 5))[i] = 0x40;
    }

    for (int i = 0; i < 64 && param_3[i] != '\0'; i++)
    {
        // starts at 800857a4 and not 800857a0
        // data.memcardIcon_PsyqHand[i+1] = param_3[i];
        ((int *)((uint8_t *)data.memcardIcon_PsyqHand + 4))[i] = param_3[i];
    }

    MEMCARD_ChecksumSave(ptrData, fileSize);

    // In sys/fcntl.h
    // 0x200 is FCREAT, create if it does not exist,
    // DAT_800857a3 handles read or write

    // Access 4th byte of memcardIcon_PsyqHand
    sdata->memcard_fd = open(sdata->s_bu00_BASCUS_94426_slots,
                             ((unsigned int)*((uint8_t *)data.memcardIcon_PsyqHand + 3) << 0x10) | 0x200);

    if (sdata->memcard_fd != -1)
    {
        close(sdata->memcard_fd);
        sdata->memcard_fd = -1;
    }

    // 0x8002, in sys/fcntl.h
    // 0x8000 = FASYNC, for asynchronous I/O
    // 0x0001 = FWRITE, for writing

    sdata->memcard_fd = open(sdata->s_bu00_BASCUS_94426_slots, 0x8002);

    if (sdata->memcard_fd != -1)
    {
        sdata->unk_card_8008D404 = 9;

        // write to memory card, given pointer to icon
        // and the size of the icon, psyq hand
        return MEMCARD_WriteFile(0, data.memcardIcon_PsyqHand, sdata->memcardIconSize);
    }

    MEMCARD_CloseFile(0);
    return 4;
}