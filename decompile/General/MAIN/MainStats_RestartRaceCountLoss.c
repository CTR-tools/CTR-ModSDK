#include <common.h>

void DECOMP_MainStats_RestartRaceCountLoss(void)

{
  int index;
  char* countPtr;
  
  int gameMode1;
  struct GameTracker* gGT;

  gGT = sdata->gGT;
  gameMode1 = gGT->gameMode1;
  
  // Turn off HUD
  sdata->gGT->hudFlags &= 0xfe;

  // Reset team points
  for (int i = 0; i < 4; i++)
  {
	// if team is inactive, give -500, so if somebody
	// ends a battle with -1 points, they're not ranked
	// 4th place in a 2P battle, cause of other inactive
	// teams with zero points
    if ((gGT->battleSetup.teamFlags & (1 << i)) == 0)
        gGT->battleSetup.pointsPerTeam[i] = -500;
    else
        gGT->battleSetup.pointsPerTeam[i] = 0;
  }

  sdata->TurboDisplayPos_Only1P = 0;
  sdata->numPlayersFinishedRace = 0;

  gGT->numWinners = 0;
  gGT->numCrystalsInLEV = 0;
  gGT->timeCratesInLEV = 0;
  gGT->unknownFlags_1d44 = 0;
  gGT->frozenTimeRemaining = 0;
  gGT->numMissiles = 0;
  gGT->numPlayersWith3Missiles = 0;

  // only count if inside Adv Mode, but not Cup/Relic
  if ((gameMode1 & (ADVENTURE_MODE | RELIC_RACE | ADVENTURE_CUP)) != ADVENTURE_MODE)
    return;

  // only count loss if you rage-quit on lap 3
  if (gGT->drivers[0]->lapIndex != 2) {
    return;
  }

  // not in boss
  index = gGT->levelID;
  countPtr = &sdata->advProgress.timesLostRacePerLev[0];

  // if you're in boss mode
  if (gameMode1 < 0)
  {
	// in boss
    index = gGT->bossID;
	countPtr = &sdata->advProgress.timesLostBossRace[0];
  }

  if (countPtr[index] < 10)
	  countPtr[index]++;
}