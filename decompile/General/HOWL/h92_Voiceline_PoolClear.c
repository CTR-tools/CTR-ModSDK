#include <common.h>

void DECOMP_Voiceline_PoolClear(void)
{
    sdata->boolCanPlayWrongWaySFX = false;

    sdata->voicelineCooldown = 0;

    sdata->boolCanPlayVoicelines = false;

    LIST_Clear(&sdata->Voiceline1);

    LIST_Clear(&sdata->Voiceline2.first);

    // put them all on free list
    LIST_Init(&sdata->Voiceline1, &sdata->voicelinePool[0].next, 0x10, 8);

    Voiceline_ClearTimeStamp();
}