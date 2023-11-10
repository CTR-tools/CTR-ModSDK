#include <common.h>

char DECOMP_CS_Boss_BoolShouldStart(void)
{
    char boolStart;
    short *posCoords;
    struct GameTracker *gGT = sdata->gGT;

    if (((
             // If you are not at the podium for winning a relic
             (gGT->podiumRewardID != 0x61) ||

             // if number of relics is less than 18
             (gGT->currAdvProfile.numRelics < 0x12)) ||
         ((sdata->advProgress.rewards[2] & 0x100000) != 0)) &&

        // If you are not at podium for winning a key
        (gGT->podiumRewardID != 99))
    {
        posCoords = *(short **)(gGT->level1->ptrSpawnType2_PosRot + 0xc);

        boolStart = 1;
        if ((
            // driver -> instance -> posX
            gGT->drivers[0]->instSelf->matrix.t[0] == (int)posCoords[0]) &&
            (boolStart = 0,

            // driver -> instance -> posZ
            gGT->drivers[0]->instSelf->matrix.t[2] != (int)posCoords[2]))
        {
            boolStart = 1;
        }
        return boolStart;
    }
    return 1;
}