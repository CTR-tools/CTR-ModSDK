#include <common.h>

uint8_t MEMCARD_WriteFile(int start_offset, const uint8_t *data, int end_offset)
{
    // NOTE: See MEMCARD_ReadFile note
    // NOTE: 4 bytes over budget
    if ((lseek(sdata->memcard_fileOpen, start_offset, 0) != -1) &
        (write(sdata->memcard_fileOpen, data, end_offset) != -1))
    {
        return 7;
    }

    MEMCARD_CloseFile();
    return 1;
}