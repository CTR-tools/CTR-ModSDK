#include <common.h>

void DECOMP_MainRaceTrack_RequestLoad(short levelID)
{
  // Turn off HUD
  sdata->gGT->hudFlags &= 0xfe;

  if (DECOMP_RaceFlag_IsFullyOffScreen() == 1)
  {
    DECOMP_RaceFlag_BeginTransition(1);
  }
  DECOMP_RaceFlag_ResetTextAnim();

  sdata->Loading.stage = -4;
  sdata->Loading.Lev_ID_To_Load = levelID;
  return;
}