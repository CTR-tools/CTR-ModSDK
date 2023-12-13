#include <common.h>

void DECOMP_Music_Start(u_int songID)
{
    sdata->cseqBoolPlay = true;

    // set highest song index
    sdata->cseqHighestIndex = songID & 0xffff;
}