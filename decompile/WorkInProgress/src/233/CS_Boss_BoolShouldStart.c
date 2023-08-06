#include <common.h>

int CS_Boss_BoolShouldStart(void)
{
    int uVar1;
    short *psVar2;

    if (
        (
            (
                // If you are not at the podium for winning a relic
                (sdata->gGT->podiumRewardID != 0x61) ||

                // if number of relics is less than 18
                (sdata->gGT->currAdvProfile.numRelics < 0x12)) ||
            ((sdata->advProgress.rewards[2] & 0x100000) != 0)) &&

        // If you are not at podium for winning a key
        (sdata->gGT->podiumRewardID != 99))
    {
        psVar2 = *(short **)(*(int *)(*(int *)(sdata->gGT + 0x160) + 0x144) + 0xc);

        uVar1 = 1;
        if (
            (
                // driver -> instance -> posX
                *(int *)(*(int *)(*(int *)(sdata->gGT + 0x24ec) + 0x1c) + 0x44) == (int)*psVar2) &&
            (uVar1 = 0,

             // driver -> instance -> posZ
             *(int *)(*(int *)(*(int *)(sdata->gGT + 0x24ec) + 0x1c) + 0x4c) != (int)psVar2[2]))
        {
            uVar1 = 1;
        }
        return uVar1;
    }
    return 1;
}