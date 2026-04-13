#include <common.h>

void DECOMP_CAM_EndOfRace(struct CameraDC* cDC, struct Driver* d)
{
	struct GameTracker* gGT = sdata->gGT;
	
	#if BUILD > SepReview

		// If not in Battle Mode and track path points exist and game is on 1P or 2P mode
		if
		(
			((gGT->gameMode1 & BATTLE_MODE) == 0) &&
			(1 < gGT->level1->ptrSpawnType1->count) &&
			(gGT->numPlyrCurrGame < 3)
		)
		{
			// Activate end-of-race cDC flag in CameraDC struct
			cDC->flags |= 0x20;
		}
		else
		{
			// Call function to initialize end-of-race cDC for Battle Mode
			CAM_EndOfRace_Battle(cDC, d);
		}
		return;

	#else
	// this is SepReview's more error-prone version of the function

		if (gGT->level1->ptrSpawnType1->count < 2 || gGT->numPlyrCurrGame > 2)
			CAM_EndOfRace_Battle(cDC, d);
		else
			cDC->flags |= 0x20;
    
  #endif
}