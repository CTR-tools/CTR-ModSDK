#include <common.h>

void DECOMP_QueueLoadTrack_MenuProc(struct RectMenu* menu)
{
  struct GameTracker* gGT = sdata->gGT;

  // If you're in Time Trial,
  // set P3 to N Tropy, and P4 to N Oxide
  if ((gGT->gameMode1 & TIME_TRIAL) != 0)
  {
    data.characterIDs[2] = 0xc;
    data.characterIDs[3] = 0xf;
  }

  // If you're in Adventure Mode, 
  // go to Adventure Arena from Title Screen
  if ((gGT->gameMode1 & ADVENTURE_MODE) != 0) 
	  gGT->gameMode1 |= ADVENTURE_ARENA;

  // If you're not in Battle Mode,
  // clear battle related variables
  if ((gGT->gameMode1 & BATTLE_MODE) == 0)
  {
    gGT->originalEventTime = 0x2a300;
    gGT->gameMode1 &= ~(POINT_LIMIT | LIFE_LIMIT | TIME_LIMIT);
  }

  DECOMP_MainRaceTrack_RequestLoad(gGT->currLEV);

  DECOMP_RECTMENU_Hide(menu);
}