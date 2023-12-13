#include <common.h>

void DECOMP_Voiceline_ToggleEnable(int toggle)
{
    // if this is disabling
    if (toggle == 0)
    {
        sdata->voicelineCooldown = 0;

        DECOMP_Voiceline_StopAll();
    }
    sdata->boolCanPlayVoicelines = toggle;
}