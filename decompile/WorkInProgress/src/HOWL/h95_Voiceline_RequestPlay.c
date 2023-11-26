#include <common.h>
// param1 - voiceID
// param2 - characterID
// param3 - characterID
void Voiceline_RequestPlay(u_int voiceID, u_int param_2, u_int param_3)
{
    char bVar1;
    char bVar2;
    char bVar3;
    char bVar4;
    char bVar5;
    struct GameTracker *gGT;
    int iVar7;
    uint uVar8;
    int *piVar9;
    int iVar10;

    // voiceID
    // Final game has 0x13 total,
    // but 0x18 were planned
    if (0x17 < voiceID)
        return;

    // param_2 is character ID,
    if (15 < param_2)
        return;

    // param_3 is character ID (or 16 for null)
    if (16 < param_3)
        return;

    if ((gGT->gameMode1 & END_OF_RACE) != 0)
        return;

    bVar1 = data.voiceID[voiceID];

    if (7 < voiceID)
    {
        if (((*(u_int *)0x80096244)[param_2] & (1 << voiceID)) == 0)
        {
            sdata->audioRNG = ((sdata->audioRNG >> 3) + sdata->audioRNG * 0x20000000) * 5 + 1;
            uVar8 = sdata->audioRNG & 3;
        }
        else
        {
            sdata->audioRNG = ((sdata->audioRNG >> 3) + sdata->audioRNG * 0x20000000) * 5 + 1;
            uVar8 = sdata->audioRNG & 7;
        }

        if (uVar8 != 0)
        {
            return;
        }
    }

    // If player spoke more than two seconds ago
    bVar2 = 60 < gGT->frameTimer_MainFrame_ResetDB - (*(u_int *)0x80096284)[param_2];

    bVar5 = bVar1 < 2;

    bVar4 = bVar2 && bVar5;

    if ((sdata->boolCanPlayVoicelines == 0) ||
        // if voicelineCooldown is not done
        (((sdata->voicelineCooldown != 0 &&

           // DAT_8009619e
           (((short *)sdata->backupParams_FUN_8002cf28[2])[1] == param_2)) ||

          (bVar3 = true,

           // If player spoke less than two seconds ago
           gGT->frameTimer_MainFrame_ResetDB - (*(u_int *)0x80096284)[param_2]) < 60)))
    {
        bVar3 = false;
    }
    if (bVar3)
    {
        if (!bVar2 || !bVar5)
            goto LAB_8002ce20;
        sdata->audioRNG = ((sdata->audioRNG >> 3) + sdata->audioRNG * 0x20000000) * 5 + 1;
        bVar4 = false;
        if ((sdata->audioRNG & 1) == 0)
            goto LAB_8002cdcc;
    }
    else
    {
        if (!bVar2 || !bVar5)
        {
            return;
        }
    LAB_8002cdcc:
        if (!bVar4)
        {
        LAB_8002ce20:
            if (!bVar3)
            {
                return;
            }
            ((u_int *)0x80096244)[param_2] |= (1 << (voiceID));

            iVar10 = sdata->VoiceLine2.last;

            iVar7 = sdata->Voiceline1.first;

            piVar9 = (int *)sdata->Voiceline2.first;

            // check all voicelines
            while (piVar9 != NULL)
            {
                // if this voiceline is already playing
                if ((voiceID == *(short *)(piVar9 + 2)) &&
                    (param_2 == *(char *)((int)piVar9 + 10)))
                {
                    return;
                }

                // next voiceline
                piVar9 = (int *)*piVar9;
            }

            if (sdata->Voiceline1.first == NULL)
            {
                // if voiceline taken->back is null
                if (sdata->VoiceLine2.last == 0)
                    goto LAB_8002cee4;

                LIST_RemoveMember(&sdata->Voiceline2.first, sdata->VoiceLine2.last);
            }

            // if free voicelines are available
            else
            {
                LIST_RemoveMember(&sdata->Voiceline1.first, sdata->Voiceline1.first);

                iVar10 = iVar7;
            }

            LIST_AddFront(&sdata->Voiceline2.first, iVar10);

        LAB_8002cee4:

            // save voiceline parameters
            *(char *)(iVar10 + 10) = (char)param_2;
            *(char *)(iVar10 + 0xb) = (char)param_3;
            *(short *)(iVar10 + 8) = (short)voiceID;

            // voiceline -> startFrame
            *(u_int *)(iVar10 + 0xc) = gGT->timer;
            return;
        }
    }

    if (bVar1 == 0)
    {
        uVar8 = param_2 + 0x1c;
    }
    else
    {
        if (bVar1 != 1)
            goto LAB_8002ce00;
        uVar8 = param_2 + 0x2c;
    }

    OtherFX_Play(uVar8 & 0xffff, 2);

LAB_8002ce00:

    // store time stamp
    ((u_int *)0x80096284)[param_2] = sdata->gGT->frameTimer_MainFrame_ResetDB;
}