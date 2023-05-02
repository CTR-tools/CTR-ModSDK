#include <common.h>

uint8_t MEMCARD_WriteFile(long start_offset, uint8_t *data, long end_offset)

{
    // NOTE: See MEMCARD_ReadFile note
    if ((lseek(sdata->memcard_fileOpen, start_offset, 0) != -1) &
        (write(sdata->memcard_fileOpen, *data, end_offset) != -1))
    {
        return 7;
    }

    MEMCARD_CloseFile();
    return 1;
}