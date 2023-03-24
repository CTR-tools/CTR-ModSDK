#include <common.h>

void DECOMP_UI_DrawPosSuffix(short param_1,short param_2,struct Driver* d,short param_4)
{
  int currRank;
  struct GameTracker* gGT = sdata->gGT;

  // If you're not in Battle Mode
  if ((gGT->gameMode1 & BATTLE_MODE) == 0) 
  {
    // Get the rank you're in (1st, 2nd, 3rd, etc)
	currRank = d->driverRank;
  }

  // If you are in Battle Mode
  else
  {
	// get the rank that the battle team is in
    currRank = gGT->battleSetup.finishedRankOfEachTeam[d->BattleHUD.teamID];
  }

  // Draw the suffix of your current position
  DecalFont_DrawLine(sdata->lngStrings[data.stringIndexSuffix[currRank]],
               (int)param_1,(int)param_2,1,(int)param_4);

  // If pointer to instance of "Big Number" is valid
  if (d->BigNumber[0] != 0)
  {
	// Set [something] to position in race + 0x100
    d->BigNumber[0]->matrix.t[2] = (d->driverRank + 0x100);
  }
  return;
}
