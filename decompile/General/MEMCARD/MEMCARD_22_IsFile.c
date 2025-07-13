#include <common.h>

int DECOMP_MEMCARD_IsFile(int slotIdx, char *save_name)
{
    char name[64];

    MEMCARD_StringSet(name, slotIdx, save_name);

    // 0x8002, in sys/fcntl.h
    // 0x8000 = FASYNC, for asynchronous I/O
    // 0x0002 = FWRITE, for writing
    sdata->memcard_fd = open(name, FASYNC|FWRITE);

    if (sdata->memcard_fd == -1)
        return MC_RETURN_NODATA;

    close(sdata->memcard_fd);
    sdata->memcard_fd = -1;
    return MC_RETURN_IOE;
}