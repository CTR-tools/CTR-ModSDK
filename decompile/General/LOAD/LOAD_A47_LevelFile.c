#include <common.h>

void DECOMP_LOAD_LevelFile(int levelID)
{
	struct GameTracker* gGT = sdata->gGT;
	
	// why here?
	sdata->modelMaskHints3D = 0;
	
	gGT->hudFlags &= 0xfe;
	
	gGT->prevLEV = gGT->levelID;
	gGT->levelID = levelID;
	
	// disable all rendering except checkeredFlag
	gGT->renderFlags &= 0x1000;
	
	if(DECOMP_RaceFlag_IsFullyOffScreen() == 1)
	{
		DECOMP_RaceFlag_BeginTransition(1);
	}
	
	// start loading
	sdata->Loading.stage = 0;
}