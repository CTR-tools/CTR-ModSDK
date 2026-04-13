#include <common.h>

void DECOMP_Music_Restart(void)
{
    // if cseq music is playing
    if (sdata->cseqBoolPlay != 0)
    {
        DECOMP_CseqMusic_Restart(sdata->cseqHighestIndex, 8);
    }
}
