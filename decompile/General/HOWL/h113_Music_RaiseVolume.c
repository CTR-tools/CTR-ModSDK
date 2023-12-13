#include <common.h>

// after "FINAL LAP!" is done
void DECOMP_Music_RaiseVolume(void)
{
    u_int setVolume;

    if (sdata->cseqBoolPlay != 0)
    {
        // 100% volume
        setVolume = 255;
		
        if (1 < sdata->cseqHighestIndex - 1)
        {
            // 75% volume
            setVolume = 190;
        }
        
		DECOMP_CseqMusic_ChangeVolume(sdata->cseqHighestIndex & 0xffff, setVolume, 8);
    }
}