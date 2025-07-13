#include <common.h>

uint8_t DECOMP_MEMCARD_WriteFile(int start_offset, const uint8_t *data, int size)
{
    if ((lseek(sdata->memcard_fd, start_offset, 0) >= 0) &&
        (write(sdata->memcard_fd, data, size) >= 0))
    {
        return MC_RETURN_SUCCESS;
    }

    MEMCARD_CloseFile();
    return MC_RETURN_TIMEOUT;
}