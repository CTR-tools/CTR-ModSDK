#include <common.h>

u_char DECOMP_CS_Boss_BoolShouldStart(void)
{
    struct GameTracker* gGT = sdata->gGT;
    // driver instance
    struct Instance* inst = gGT->drivers[0]->instSelf;

    // If you are not at the podium for winning a relic or winning a key
    if (!((gGT->podiumRewardID == 0x61 &&
           // if number of relics is less than 18
           gGT->currAdvProfile.numRelics >= 18 &&

           (sdata->advProgress.rewards[2] & 0x100000) == 0) ||
          // If you are not at podium for winning a key
          (gGT->podiumRewardID == 99)))
    {
        short *posCoords = gGT->level1->ptrSpawnType2_PosRot[1].posCoords;

        // check if driver is not at these coords
        return (inst->matrix.t[0] != posCoords[0] && inst->matrix.t[2] != posCoords[2]);
    }

    return false;
}
