#include <common.h>

void DECOMP_SetReverbMode(u_short newReverbMode)
{
    if (newReverbMode < 5)
    {
        if (sdata->curReverb != newReverbMode)
        {
            // update reverb setting if mode has changed
            SpuSetReverbModeDepth(0, 0);
            SpuSetReverb(1);

            SpuSetReverbModeParam(&data.reverbParams[newReverbMode]);

            SpuSetReverbModeDepth(data.reverbParams[newReverbMode].depth.left, data.reverbParams[newReverbMode].depth.right);

            sdata->curReverb = newReverbMode;
        }
		return;
    }
    else if (sdata->curReverb != 5)
    {
        // disable reverb and reset mode to 5
        SpuSetReverbModeDepth(0, 0);
        SpuSetReverb(0);
        sdata->curReverb = 5;
    }
}