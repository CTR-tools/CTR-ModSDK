#include <common.h>

void DECOMP_MainRaceTrack_RequestLoad(short levelID)
{
  // Turn off HUD
  sdata->gGT->hudFlags &= 0xfe;

  if (DECOMP_TitleFlag_IsFullyOffScreen() == 1)
  {
    DECOMP_TitleFlag_BeginTransition(1);
  }
  DECOMP_TitleFlag_ResetTextAnim();

  sdata->Loading.stage = -4;
  sdata->Loading.Lev_ID_To_Load = levelID;
  return;
}