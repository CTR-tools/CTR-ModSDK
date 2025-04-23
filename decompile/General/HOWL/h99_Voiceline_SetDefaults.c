#include <common.h>

void DECOMP_Voiceline_SetDefaults(void)
{
    sdata->unkAudioState = 0;
	
#if 0 // unused
    sdata->desiredXA_RaceIntroIndex = 0;
    sdata->desiredXA_FinalLapIndex = 0;
#endif

    sdata->WrongWayDirection_bool = false;

    sdata->framesDrivingSameDirection = 0;
    sdata->nTropyVoiceCount = 0;
    sdata->boolNeedXASeek = 0;

    DECOMP_Music_SetDefaults();
}