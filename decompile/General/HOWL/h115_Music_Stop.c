#include <common.h>

void DECOMP_Music_Stop(void)
{
	// quit if no music is playing
    if (sdata->cseqBoolPlay == 0) return;
    
    sdata->cseqBoolPlay = 0;
    sdata->cseqHighestIndex = -1;
    
	// function call comes last, so it compiles to jmp
    DECOMP_CseqMusic_Stop(sdata->cseqHighestIndex & 0xffff);
}