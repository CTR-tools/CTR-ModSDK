#include <common.h>

uint8_t MEMCARD_IsFile(int slotIdx, char *save_name)
{
    char name[64];

    MEMCARD_StringSet(name, slotIdx, save_name);

    // 0x8002, in sys/fcntl.h
    // 0x8000 = FASYNC, for asynchronous I/O
    // 0x0001 = FWRITE, for writing
    sdata->memcard_fileOpen = open(name, 0x8002);

    if (sdata->memcard_fileOpen == -1)
        return 6;
    else
    {
        close(sdata->memcard_fileOpen);
        sdata->memcard_fileOpen = -1;
        return 0;
    }
}