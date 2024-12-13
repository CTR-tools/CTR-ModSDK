#include <common.h>

void DECOMP_MEMCARD_CloseFile(void)
{
    // // NOTE: this impl 4 bytes over byte budget
    // if (sdata->memcard_fd != -1)
    // {
    //     close(sdata->memcard_fd);
    //     sdata->memcard_fd = -1;
    // }
    // sdata->unk_card_8008D404 = 0;

    int fd = sdata->memcard_fd;
    sdata->memcard_fd = -1;
    sdata->unk_card_8008D404 = 0;
    if (fd != -1)
        close(fd);
    return;
}