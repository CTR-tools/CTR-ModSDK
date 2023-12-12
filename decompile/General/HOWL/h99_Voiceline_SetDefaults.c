#include <common.h>

void Voiceline_SetDefaults(void)
{
    sdata->unkAudioState = 0;
    sdata->desiredXA_1 = 0;
    sdata->desiredXA_2 = 0;

    sdata->WrongWayDirection_bool = false;

    sdata->framesDrivingSameDirection = 0;
    sdata->nTropyVoiceCount = 0;
    sdata->boolNeedXASeek = 0;

    Music_SetDefaults();
}