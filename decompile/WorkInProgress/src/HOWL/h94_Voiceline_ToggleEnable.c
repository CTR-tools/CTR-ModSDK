#include <common.h>

void Voiceline_ToggleEnable(int toggle)
{
    // if this is disabling
    if (toggle == 0)
    {
        sdata->voicelineCooldown = 0;

        Voiceline_StopAll();
    }
    sdata->boolCanPlayVoicelines = toggle;
}