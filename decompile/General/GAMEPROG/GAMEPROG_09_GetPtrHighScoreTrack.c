#include <common.h>

void DECOMP_GAMEPROG_GetPtrHighScoreTrack()
{
	int gameMode1;
	struct GameTracker* gGT;
	
	gGT = sdata->gGT;
	gameMode1 = gGT->gameMode1;
	
	sdata->ptrActiveHighScoreEntry =
		&sdata->gameProgress
		.highScoreTracks[gGT->levelID]
		.scoreEntry[6*((gameMode1 & RELIC_RACE) != 0)];
}