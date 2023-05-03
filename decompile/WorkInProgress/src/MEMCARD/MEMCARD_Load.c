#include <common.h>

// ghidra couldn't detect parameters,
// because they were passed directly from this func to another
uint8_t MEMCARD_Load(param1, param2, param3, param4, param5)

{
    unsigned int param_5;

    if (
        (sdata->unk_card_8008D404 == 0) &&

         // this will always be true
         MEMCARD_NewTask(param1, param2, param3, param4, param5) == 0)
    {
        // 800990a4
        // string for directory and file of save that is in use

        // 0x8001, in sys/fcntl.h
        // 0x8000 = FASYNC, for asynchronous I/O
        // 0x0001 = FREAD, for reading

        sdata->memcard_fileOpen = open(&sdata->s_bu00_BASCUS_94426_slots, 0x8001);

        if (sdata->memcard_fileOpen == -1)
        {
            MEMCARD_CloseFile();
            return 6;
        }
        else
        {
            if ((param_5 & 2) == 0)
            {
                // dont process crc16 to the end of memory,
                // just the next 0x200 bytes (async)
                sdata->memcardStatusFlags = sdata->memcardStatusFlags & 0xfffffff7;
            }
            else
            {
                // process crc16 to the end of memory
                sdata->memcardStatusFlags = sdata->memcardStatusFlags | 8;
            }
            sdata->unk_card_8008D404 = 3;

            // Read memory card
            return MEMCARD_ReadFile(0, 0x80);
        }
    }
    else
    {
        return 1;
    }
}
