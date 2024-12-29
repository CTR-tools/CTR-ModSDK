#include <common.h>

int DECOMP_MEMCARD_ReadFile(int start_offset, int end_offset)

{
    if ((lseek(sdata->memcard_fd, start_offset, 0) >= 0) &&
        (read(sdata->memcard_fd, sdata->memcard_ptrStart, end_offset) >= 0))
    {
        return 7;
    }

    MEMCARD_CloseFile();
    return 1;
}