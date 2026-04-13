#include <common.h>

void DECOMP_MEMCARD_CloseFile(void)
{
    int fd = sdata->memcard_fd;
    sdata->memcard_fd = -1;
    sdata->memcard_stage = MC_STAGE_IDLE;
	
    if (fd != -1)
        close(fd);
    
	return;
}