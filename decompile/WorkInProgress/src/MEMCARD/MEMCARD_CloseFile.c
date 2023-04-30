#include <common.h>

void MEMCARD_CloseFile(void)
{
    // // NOTE: this impl 4 bytes over byte budget
    // if (sdata->memcard_fileOpen != -1)
    // {
    //     close(sdata->memcard_fileOpen);
    //     sdata->memcard_fileOpen = -1;
    // }
    // sdata->unk_card_8008D404 = 0;

    int fd = sdata->memcard_fileOpen;
    sdata->memcard_fileOpen = -1;
    sdata->unk_card_8008D404 = 0;
    if (fd != -1)
        close(fd);
    return;
}