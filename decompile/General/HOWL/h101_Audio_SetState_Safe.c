#include <common.h>

void DECOMP_Audio_SetState_Safe(int state)
{
    // If this sound isn't already playing
    if (state != sdata->unkAudioState)
    {
        Voiceline_EmptyFunc();

        Audio_SetState(state);

        // set which sound is playing
        sdata->unkAudioState = state;
    }
}