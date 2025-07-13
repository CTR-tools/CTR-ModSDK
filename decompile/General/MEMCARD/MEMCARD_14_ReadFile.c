#include <common.h>

int DECOMP_MEMCARD_ReadFile(int start_offset, int end_offset)

{
    if ((lseek(sdata->memcard_fd, start_offset, 0) >= 0) &&
        (read(sdata->memcard_fd, sdata->memcard_ptrStart, end_offset) >= 0))
    {
        return MC_RETURN_SUCCESS;
    }

    MEMCARD_CloseFile();
    return MC_RETURN_TIMEOUT;
}