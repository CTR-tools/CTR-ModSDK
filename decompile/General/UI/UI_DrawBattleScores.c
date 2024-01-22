#include <common.h>

// Draw how many points or lifes the player has in battle
void DECOMP_UI_DrawBattleScores(int posX, int posY, struct Driver * d) {
  struct Icon * icon;
  int value;
  char string[32];
  struct GameTracker * gGT = sdata->gGT;

  // battleScoreColor has 16 shorts, each short is color + alignment
  // First 4 shorts show how text is drawn for 4 players in 1P Mode
  // Next  4 shorts show how text is drawn for 4 players in 2P Mode
  // Then 3P mode, then 4P mode

  // If you dont have a point limit (battle)
  if ((gGT->gameMode1 & POINT_LIMIT) == 0) {
    // if you dont have a life limit (battle)
    if ((gGT->gameMode1 & LIFE_LIMIT) == 0)
      return;

    // if you have a life limit (battle)
    value = d->BattleHUD.numLives;

    // pointer to lives icon
    icon = gGT->ptrIcons[0x84];
  }
  // If you have a point limit (battle)
  else {

    // Battle Team of Player->points on this team
    value = gGT->battleSetup.pointsPerTeam[d->BattleHUD.teamID];

    // pointer to points icon
    icon = gGT->ptrIcons[0x85];
  }
  
  // add value to string
  sprintf(string, &sdata->s_longInt, value);

  // Set color of your string
  u_short scoreColor = data.battleScoreColor[gGT->numPlyrCurrGame - 1][d->driverID];

  // Draw the string
  DecalFont_DrawLine(string, (short)(posX + 37), (short)(posY + 4), FONT_SMALL, (u_int)scoreColor);

  u_long * ot = gGT->tileView_UI.ptrOT;
  struct PrimMem * primMem = &gGT->backBuffer->primMem;

  DecalHUD_DrawPolyFT4(
    icon,
    posX,
    posY,
    primMem, 
    ot,
    1, 0x1000);
}