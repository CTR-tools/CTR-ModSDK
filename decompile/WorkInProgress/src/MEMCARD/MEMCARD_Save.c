#include <common.h>

// NOTE: param6 is unused and passed as 0 from the only caller to this function. Kept in to not mess up $sp allocation
// ERROR: Does not write title in save. Should be "C T R: GAME SAVE AND SCORES" or something. Not blank
uint8_t MEMCARD_Save(int slotIdx, char *name,
                     char *param_3, uint8_t *ptrData, int fileSize, unsigned int param6)

{

    if (sdata->unk_card_8008D404 != 0)
        return 1;

    sdata->memcardIconSize = 0x100;

    // this will always return 0, no need to check
    MEMCARD_NewTask(slotIdx, name, ptrData, fileSize);

    // NOTE: Commented out because param6 always 0, will always eval to false
    /*
    if (((param6 & 1) == 0) && (1 < sdata->memcardIconSize + fileSize * 2 + 0x1fff >> 0xd))
        {
            DAT_800857a3 = (byte)(sdata->memcardIconSize + fileSize + 0x1fff >> 0xd);
            sdata->memcardStatusFlags = sdata->memcardStatusFlags | 4;
        }
        else
        {
    */
    sdata->memcardStatusFlags = sdata->memcardStatusFlags & 0xfffffffb;
    *((uint8_t *)(data.memcardIcon_PsyqHand) + 3) = ((sdata->memcardIconSize + fileSize * 2 + 0x1fff) >> 0xd) & 0xFF;
    /*
        }
    */

    uint8_t *memcardIconPtr = (uint8_t *)data.memcardIcon_PsyqHand[1];
    for (int i = 0; i < 64; i += 2)
    {
        *(memcardIconPtr + i) = 0x81;
        *(memcardIconPtr + i + 1) = 0x40;
    }

    // NOTE: Something most likely wrong here
    for (int i = 0; *param_3 != '\0' && i < 64; i++, param_3++)
    {
        // starts at 800857a4 and not 800857a0
        *(memcardIconPtr + i) = *param_3;
    }

    MEMCARD_ChecksumSave(ptrData, fileSize);

    // In sys/fcntl.h
    // 0x200 is FCREAT, create if it does not exist,
    // DAT_800857a3 handles read or write

    sdata->memcard_fd = open(sdata->s_bu00_BASCUS_94426_slots, 
    (unsigned int)*((uint8_t *)(data.memcardIcon_PsyqHand) + 3) << 0x10 | 0x200);

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
        return MEMCARD_WriteFile(0, data.memcardIcon_PsyqHand, sdata->memcardIconSize);
    }

    MEMCARD_CloseFile(0);
    return 4;
}