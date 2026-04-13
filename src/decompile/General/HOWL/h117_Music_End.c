#include <common.h>

void DECOMP_Music_End(void)
{
    sdata->cseqBoolPlay = false;

    // no songs are playing
    sdata->cseqHighestIndex = -1;
}