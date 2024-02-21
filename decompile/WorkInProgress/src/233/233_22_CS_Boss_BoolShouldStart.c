#include <common.h>

u_char DECOMP_CS_Boss_BoolShouldStart(void)
{
    struct GameTracker* gGT = sdata->gGT;
    // driver instance
    struct Instance* inst = gGT->drivers[0]->instSelf;

	if (
			// If just got 18th relic
			(gGT->podiumRewardID == 0x61) &&
			(gGT->currAdvProfile.numRelics >= 18)
			// skip check to sdata->advProgress.rewards[3]
		)
	{
		return 1;
	}
	
	// If just unlocked Key
	if (gGT->podiumRewardID == 99)
		return 1;

	// What on earth is this?
    {
        short *posCoords = gGT->level1->ptrSpawnType2_PosRot[1].posCoords;

        // check if driver is not at these coords
        return (inst->matrix.t[0] != posCoords[0] && inst->matrix.t[2] != posCoords[2]);
    }

    return 0;
}
