#include <common.h>

int DECOMP_MEMCARD_IsFile(int slotIdx, char *save_name)
{
    char name[64];

    MEMCARD_StringSet(name, slotIdx, save_name);

    // 0x8002, in sys/fcntl.h
    // 0x8000 = FASYNC, for asynchronous I/O
    // 0x0001 = FWRITE, for writing
    sdata->memcard_fd = open(name, 0x8002);

    if (sdata->memcard_fd == -1)
        return 6;

    close(sdata->memcard_fd);
    sdata->memcard_fd = -1;
    return 0;
}