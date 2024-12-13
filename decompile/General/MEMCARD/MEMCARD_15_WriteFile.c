#include <common.h>

uint8_t DECOMP_MEMCARD_WriteFile(int start_offset, const uint8_t *data, int end_offset)
{
    if ((lseek(sdata->memcard_fd, start_offset, 0) >= 0) &&
        (write(sdata->memcard_fd, data, end_offset) >= 0))
    {
        return 7;
    }

    MEMCARD_CloseFile();
    return 1;
}