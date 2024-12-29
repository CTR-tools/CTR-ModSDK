#include <common.h>

void DECOMP_LOAD_Hub_Main(int bigfilePtr)
{
	struct GameTracker* gGT;

	// quit if already loading
	if (sdata->Loading.stage != -1) return;

	gGT = sdata->gGT;

	int stepFlagSet = gGT->drivers[0]->stepFlagSet;
	int nextLevelID = (stepFlagSet & 0x30) >> 4;
	int needSwapNow = (stepFlagSet & 0xc0) >> 6;

	// if new level does not need to load
	if (nextLevelID == 0)
	{
		if (
			(needSwapNow != 0) ||
			(gGT->bool_AdvHub_NeedToSwapLEV != 0)
			)
		{
			gGT->bool_AdvHub_NeedToSwapLEV = 0;
			LOAD_Hub_SwapNow();
		}
	}

	// if new level needs to load
	else
	{
		// only in AdvHub, or else the game
		// crashes in 4P Nitro Court Life Limit
		unsigned int currLevelID = gGT->levelID - 0x19;
		if (currLevelID >= 5) return;

		LOAD_Hub_ReadFile(
			bigfilePtr,
			rdata.MetaDataHubs[currLevelID].connectedHub_LevID[nextLevelID - 1],
			3 - gGT->activeMempackIndex
		);
	}
}