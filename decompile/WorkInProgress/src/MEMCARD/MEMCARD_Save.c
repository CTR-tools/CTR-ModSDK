#include <common.h>

uint8_t MEMCARD_Save(int slotIdx, char *name,
                     char *param_3, uint8_t* ptrData, int fileSize,
                     unsigned int param_6)

{
    char tmpCh;
    int i;
    int j;

    if (sdata->unk_card_8008D404 != 0)
        return 1;

    sdata->memcardIconSize = 0x100;

    // this will always be true
    if (MEMCARD_NewTask(slotIdx, name, ptrData, fileSize) == 0)
    {
        if (((param_6 & 1) == 0) && (1 < sdata->memcardIconSize + fileSize * 2 + 0x1fff >> 0xd))
        {
            DAT_800857a3 = (byte)(sdata->memcardIconSize + fileSize + 0x1fff >> 0xd);
            sdata->memcardStatusFlags = sdata->memcardStatusFlags | 4;
        }
        else
        {
            sdata->memcardStatusFlags = sdata->memcardStatusFlags & 0xfffffffb;
            // was cast to byte, byte doesn't exist so uint_least8_t
            DAT_800857a3 = (uint_least8_t)(sdata->memcardIconSize + fileSize * 2 + 0x1fff >> 0xd);
        }

        i = 0;
        do
        {
            j = i + 2;
            (&DAT_800857a4)[i] = 0x81;
            (&DAT_800857a5)[i] = 0x40;
            i = j;
        } while (j < 64);
        tmpCh = *param_3;
        i = 0;
        while ((tmpCh != '\0' && (i < 64)))
        {
            tmpCh = *param_3;
            param_3 = param_3 + 1;
            (&DAT_800857a4)[i] = tmpCh;
            tmpCh = *param_3;
            i++;
        }

        MEMCARD_ChecksumSave(ptrData, fileSize);

        // In sys/fcntl.h
        // 0x200 is FCREAT, create if it does not exist,
        // DAT_800857a3 handles read or write

        sdata->memcard_fd = open(sdata->s_bu00_BASCUS_94426_slots, (unsigned int)DAT_800857a3 << 0x10 | 0x200);

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
            return MEMCARD_WriteFile(0, Data->memcardIcon_PsyqHand, sdata->memcardIconSize);
        }

        MEMCARD_CloseFile(0);
        return 4;
    }
}