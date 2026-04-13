#include <common.h>

// happens during "FINAL LAP!"
void DECOMP_Music_LowerVolume(void)
{
    u_int setVolume;

    if (sdata->cseqBoolPlay != 0)
    {
        // 50% volume
        setVolume = 150;

        if (1 < sdata->cseqHighestIndex - 1)
        {
            // 25% volume
            setVolume = 90;
        }

        DECOMP_CseqMusic_ChangeVolume(sdata->cseqHighestIndex & 0xffff, setVolume, 8);
    }
}