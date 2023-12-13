#include <common.h>

void Music_End(void)
{
    sdata->cseqBoolPlay = false;

    // no songs are playing
    sdata->cseqHighestIndex = -1;
}