#include <common.h>

void Voiceline_SetDefaults(void)
{
    sdata->unkAudioState[0] = 0;
    sdata->unkAudioState[1] = 0;
    sdata->unkAudioState[2] = 0;

    sdata->WrongWayDirection_bool = false;

    sdata->framesDrivingSameDirection = 0;
    DAT_8008d7fa = 0;
    DAT_8008d7fc = 0;

    Music_SetDefaults();
}