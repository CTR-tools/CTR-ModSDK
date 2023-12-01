#include <common.h>

void Voiceline_StartPlay(struct Item *voiceLine)
{
    ushort uVar1;
    int iVar2;
    uint uVar3;
    int *piVar4;
    int iVar5;

    sdata->backupParams_FUN_8002cf28[0] = voiceLine[0];
    sdata->backupParams_FUN_8002cf28[1] = voiceLine[1];
    sdata->backupParams_FUN_8002cf28[2] = voiceLine[2];
    sdata->backupParams_FUN_8002cf28[3] = voiceLine[3];

    if (
        (
            // If you're in a Boss Race
            // 0x80000000
            (sdata->gGT->gameMode1 < 0) &&
            (*(u_short *)(voiceLine + 2) - 10 < 6)) &&
        ((
            // if character is 8,9, 10, 11
            // pinstripe, papu, roo, or k-joe
            *(char *)((int)voiceLine + 10) - 8 < 4 ||

            // if character is 15 - Oxide
            (*(char *)((int)voiceLine + 10) == 0xf))))
    {
		// inline audioRNG scramble
        sdata->audioRNG = ((sdata->audioRNG >> 3) + sdata->audioRNG * 0x20000000) * 5 + 1;
        
		uVar3 = (sdata->audioRNG & 3) + 4;
    }

    else
    {
        uVar3 = data.voiceID[*(short *)(voiceLine + 2)];
    }

    // boss character ID
    piVar4 = (int *)(sdata->voiceSetPtr[*(char *)((int)voiceLine + 10)] + uVar3 * 8);
    uVar1 = *(ushort *)(piVar4 + 1);

    if (uVar1 == 0)
    {
        Voiceline_StopAll();
    }
    else
    {
		// inline audioRNG scramble
        sdata->audioRNG = ((sdata->audioRNG >> 3) + sdata->audioRNG * 0x20000000) * 5 + 1;

        // if (uVar1 == 0)
        // {
        //     trap(0x1c00);
        // }

        iVar5 = (sdata->audioRNG % uVar1) * 2;

        iVar2 = CDSYS_XAPlay(CDSYS_XA_TYPE_GAME, *(u_short *)(iVar5 + *piVar4));

        // if audio failed to play
        if (iVar2 == 0)
        {
            /*
            From Aug 5
        FUN_8006fbac("CDSYS_XAPlay( CDSYS_XA_TYPE_GAME, %d ) Failed\n",
                           (uint)*(ushort *)(iVar3 + *piVar4));
            */

            // try again in 30 frames (1 second)
            sdata->voicelineCooldown = 30;
        }

        // if audio can play
        else
        {
            iVar2 = CDSYS_XAGetTrackLength(CDSYS_XA_TYPE_GAME, *(u_short *)(iVar5 + *piVar4));
            = (short)(iVar2 / 5) + 30;
        }
    }
}