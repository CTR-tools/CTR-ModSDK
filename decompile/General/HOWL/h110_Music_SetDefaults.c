#include <common.h>

void DECOMP_Music_SetDefaults(void)
{
    // no music playing
    sdata->cseqBoolPlay = false;
    sdata->cseqHighestIndex = -1;
    sdata->cseqTempo = 0;
}