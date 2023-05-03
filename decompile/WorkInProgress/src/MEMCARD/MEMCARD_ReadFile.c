#include <common.h>

int MEMCARD_ReadFile(int start_offset, int end_offset)

{
    // // NOTE: This impl is 4 bytes over byte budget
    // // seek to start offset
    // if (lseek(sdata->memcard_fd, start_offset, 0) != -1)
    // {
    //     // read to memcard buffer in RAM, param_2 size
    //     if (read(sdata->memcard_fd, sdata->memcard_ptrStart, end_offset) != -1)
    //     {
    //         return 7;
    //     }
    // }
    // MEMCARD_CloseFile();
    // return 1;

    // Bitwise AND to bail early if lseek returns invalid result
    if ((lseek(sdata->memcard_fd, start_offset, 0) != -1) &
        (read(sdata->memcard_fd, sdata->memcard_ptrStart, end_offset) != -1))
    {
        return 7;
    }

    MEMCARD_CloseFile();
    return 1;
}