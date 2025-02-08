#include <common.h>

u_char DECOMP_CS_Camera_BoolGotoBoss(void)
{
    struct GameTracker* gGT = sdata->gGT;

	if (
			// If just got 18th relic
			(gGT->podiumRewardID == 0x61) &&
			(gGT->currAdvProfile.numRelics >= 18)
			// skip check to BeatOxide2 (obvious not beaten)
		)
	{
		return 1;
	}
	
	// If just unlocked Key
	if (gGT->podiumRewardID == 99)
		return 1;

	// if podiumRewardID is reset to 0 after first frame of boss cutscene,
	// check if camera has moved to the correct position yet
    struct Instance* inst = gGT->drivers[0]->instSelf;
    short *posCoords = gGT->level1->ptrSpawnType2_PosRot[1].posCoords;

    // TRUE if not at these coordinates
    return 
		(inst->matrix.t[0] != posCoords[0]) && 
		(inst->matrix.t[2] != posCoords[2]);
}
