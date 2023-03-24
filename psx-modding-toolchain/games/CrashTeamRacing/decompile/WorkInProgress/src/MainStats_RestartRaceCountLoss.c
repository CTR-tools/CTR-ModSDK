#include <common.h>

void DECOMP_MainStats_RestartRaceCountLoss8(void)

{
  char loss;
  int temp;
  struct GameTracker *gt1;
  struct GameTracker *gt2;
  struct GameTracker *gt3;

  // Turn off HUD
  sdata->gGT->hudFlags &= 0xfe;

  gt1 = sdata->gGT;
  gt3 = sdata->gGT;

  // Reset team points and check if someone is on each battle team
  for (int i = 0; i < 4; i++)
  {
    if (gt1->battleSetup.teamFlags & (1 << i) == 0)
        gt3->battleSetup.pointsPerTeam[i] = 0xFFFFFE0C;
    else
        gt3->battleSetup.pointsPerTeam[i] = 0;
  
    gt2 = sdata->gGT;
    gt3 = gt3->gameMode1_prevFrame;
  }

  // TurboDisplayPos_Only1P
  sdata->TurboDisplayPos_Only1P = 0;
  *(int*)0x8008d2aa = 0;

  // no winners, nobody gets confetti
  sdata->gGT->numWinners = 0;
  // reset stats
  gt2->numCrystalsInLEV = 0;
  gt2->timeCratesInLEV = 0;
  gt2->unknownFlags_1d44 = 0;
  gt2->frozenTimeRemaining = 0;
  gt2->numMissiles = 0;
  gt2->numPlayersWith3Missiles = 0;

  int gameMode = sdata->gGT->gameMode1;
  
  // Stop if you're in Adventure Mode or in Adventure Cup/Relic
  if ((gameMode & 0x14080000) != 0)
    return;

  // if the lap you're on is not the 3rd lap,
  // then it means you just loaded track, and did not hit "Restart"
  if (gt2->drivers[0]->lapIndex != 2) {
    return;
  }

   // get level ID
  int levelID= sdata->gGT->levelID;
  temp = sdata->advProgress.rewards[levelID];
  loss = sdata->advProgress.timesLostRacePerLev[levelID];

  // if you lost less than 10 times, increment counter
  if (loss >= 10) 
    return;

  // if you're in boss mode
  if ((int)gameMode < 0)
  {
    // get boss (0-5)
    int bossID = gt2->bossID;

	// pointer to somewhere random,
	// assembly is generated with pointers to
	// random places when accessing global variables,
	// there is no significance to this address
	temp = bossID + -0x7ff70445; // 0x8008FBBB

    // get number of times lost boss race
    loss = sdata->advProgress.timesLostBossRace[bossID];

    // if you lost less than 10 times, increment counter
    if (loss >= 10)
        return;
  } 

  // increment number of times lost this event
  *(char *)(temp + 0x30) = loss++;
  return;
}