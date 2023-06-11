#include <common.h>

// ghidra couldn't detect parameters,
// because they were passed directly from this func to another
// TODO: proper flags from #defines
uint8_t MEMCARD_Load(int slotIdx, char *name, uint8_t *ptrMemcard, int memcardFileSize)

{
    if (sdata->unk_card_8008D404 != 0)
    {
        return 1;
    }
    MEMCARD_NewTask(slotIdx, name, ptrMemcard, memcardFileSize);
    // 800990a4
    // string for directory and file of save that is in use

    // 0x8001, in sys/fcntl.h
    // 0x8000 = FASYNC, for asynchronous I/O
    // 0x0001 = FREAD, for reading

    sdata->memcard_fd = open(sdata->s_bu00_BASCUS_94426_slots, 0x8001);

    if (sdata->memcard_fd == -1)
    {
        MEMCARD_CloseFile();
        return 6;
    }
    else
    {
        // process crc16 to the end of memory
        sdata->memcardStatusFlags = sdata->memcardStatusFlags | 8;
        sdata->unk_card_8008D404 = 3;

        // Read memory card
        return MEMCARD_ReadFile(0, 0x80);
    }
}
