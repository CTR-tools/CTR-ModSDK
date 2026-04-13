#include <common.h>

void DECOMP_Voiceline_Update(void)
{
    int length;
    struct Item *first;
    u_int voiceID;
    struct GameTracker *gGT = sdata->gGT;

    first = sdata->Voiceline2.first;

    if (!sdata->boolCanPlayVoicelines)
        return;

    // cooldown timer
    // This prevents "wrong way", and character voice effects,
    // from happening within one full second of each other (0x1e frames)

    if ((sdata->voicelineCooldown) && (sdata->voicelineCooldown != 1))
        return;

    sdata->voicelineCooldown--;

    if (sdata->XA_State)
        return;

    // if allowed to play "Wrong Way!"
    if (sdata->boolCanPlayWrongWaySFX)
    {
        if (((sdata->WrongWayDirection_bool) && (30 < sdata->framesDrivingSameDirection)) &&

            // currently not allowed to play "Wrong Way"
            (sdata->boolCanPlayWrongWaySFX = false,
             // only 1 player
             gGT->numPlyrCurrGame == 1))
        {

            // if you use uka-uka
            if (VehPickupItem_MaskBoolGoodGuy(gGT->drivers[0]) == 0)
            {
                // CDSYS_XAPlay(CDSYS_XA_TYPE_EXTRA, SPEAK_UKA_39);

                // if audio failed to play
                if (CDSYS_XAPlay(CDSYS_XA_TYPE_EXTRA, 0x3d) == 0)
                {
                    // sep 3
                    // fmt = "CDSYS_XAPlay( CDSYS_XA_TYPE_EXTRA, SPEAK_UKA_39 (wrong way) ) Failed\n";

                    // try again in 30 frames (1 second)
                    sdata->voicelineCooldown = 30;
                    return;
                }
                // use ID to get audio length
                voiceID = 61;
            }
            // if you use aku
            else
            {
                // if audio failed to play
                if (CDSYS_XAPlay(CDSYS_XA_TYPE_EXTRA, 30) == 0)
                {
                    // sep 3
                    // fmt = "CDSYS_XAPlay( CDSYS_XA_TYPE_EXTRA, SPEAK_AKU_39 (wrong way) ) Failed\n";

                    // try again in 30 frames (1 second)
                    sdata->voicelineCooldown = 30;
                    return;
                }

                // use ID to get audio length
                voiceID = 30;
            }

            // voicelineCooldown is length + 30 frames
            sdata->voicelineCooldown = (short)(CDSYS_XAGetTrackLength(CDSYS_XA_TYPE_EXTRA, voiceID) / 5) + 30;
            return;
        }

        if (sdata->boolCanPlayWrongWaySFX)
            goto LAB_8002d268;
    }

    if ((!sdata->WrongWayDirection_bool) && (30 < sdata->framesDrivingSameDirection))
    {
        sdata->boolCanPlayWrongWaySFX = true;
    }

LAB_8002d268:

    if (sdata->Voiceline2.first)
    {
        LIST_RemoveMember(&sdata->Voiceline2.first, sdata->Voiceline2.first);

        LIST_AddBack(&sdata->Voiceline1.first, first);

        Voiceline_StartPlay(first);
    }
}