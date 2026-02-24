#include <common.h>

u_char DECOMP_CS_Camera_BoolGotoBoss(void)
{
    struct GameTracker* gGT = sdata->gGT;

	if (
			// If just got 18th relic
			(gGT->podiumRewardID == STATIC_RELIC) &&
			(gGT->currAdvProfile.numRelics >= 18)
			// skip check to BeatOxide2 (obvious not beaten)
		)
	{
		return 1;
	}
	
	// If just unlocked Key
	if (gGT->podiumRewardID == STATIC_KEY)
		return 1;

    struct Instance* inst = gGT->drivers[0]->instSelf;
    short *posCoords = gGT->level1->ptrSpawnType2_PosRot[1].posCoords;

    // TRUE if TeleportSelf did NOT spawn on podium (goto boss door)
    return 
		(inst->matrix.t.x != posCoords[0]) && 
		(inst->matrix.t.z != posCoords[2]);
}
