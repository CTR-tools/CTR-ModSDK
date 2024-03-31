#include <common.h>

// Draw how many points or lifes the player has in battle
void DECOMP_UI_DrawBattleScores(int posX, int posY, struct Driver * d) 
{
  struct Icon * icon;
  int value;
  char string[32];
  struct GameTracker * gGT = sdata->gGT;

  if ((gGT->gameMode1 & POINT_LIMIT) == 0) 
  {
    if ((gGT->gameMode1 & LIFE_LIMIT) == 0)
      return;

	// == Life Limit

    value = d->BattleHUD.numLives;
    icon = gGT->ptrIcons[0x84];
  }
  
  else 
  {
	// == Point Limit ==
	  
    value = gGT->battleSetup.pointsPerTeam[d->BattleHUD.teamID];
    icon = gGT->ptrIcons[0x85];
  }
  
  // add value to string
  sprintf(string, &sdata->s_longInt, value);

  DECOMP_DecalFont_DrawLine(
	string, (short)(posX + 37), (short)(posY + 4), FONT_SMALL, 
	data.battleScoreColor[gGT->numPlyrCurrGame - 1][d->driverID]);

  DECOMP_DecalHUD_DrawPolyFT4(
    icon,
    posX, posY,
    &gGT->backBuffer->primMem, 
    gGT->pushBuffer_UI.ptrOT,
    1, 0x1000);
}