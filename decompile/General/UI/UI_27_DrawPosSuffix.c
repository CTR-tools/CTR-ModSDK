#include <common.h>

void DECOMP_UI_DrawPosSuffix(short posX, short posY, struct Driver *d, short flags)
{
  int currRank;
  struct GameTracker *gGT = sdata->gGT;

  // If you're not in Battle Mode
  if ((gGT->gameMode1 & BATTLE_MODE) == 0)
    // Get the rank you're in (1st, 2nd, 3rd, etc)
    currRank = d->driverRank;
  else
    // get the rank that the battle team is in
    currRank = gGT->battleSetup.finishedRankOfEachTeam[d->BattleHUD.teamID];

  // Draw the suffix of your current position
  DECOMP_DecalFont_DrawLine(sdata->lngStrings[data.stringIndexSuffix[currRank]], posX, posY, FONT_BIG, flags);

  // setting posZ changes which number draws
  if (d->instBigNum != 0)
	d->instBigNum->matrix.t[2] = (d->driverRank + 0x100);
  
  return;
}
