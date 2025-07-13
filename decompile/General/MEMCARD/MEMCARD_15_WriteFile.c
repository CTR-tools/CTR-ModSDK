#include <common.h>

uint8_t DECOMP_MEMCARD_WriteFile(int start_offset, const uint8_t *data, int size)
{
    if ((lseek(sdata->memcard_fd, start_offset, 0) >= 0) &&
        (write(sdata->memcard_fd, data, size) >= 0))
    {
		// The write has started, the result will be found
		// the next time we wait for an event result
        return MC_RETURN_PENDING;
    }

    MEMCARD_CloseFile();
    return MC_RETURN_TIMEOUT;
}