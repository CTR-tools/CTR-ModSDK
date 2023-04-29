#include <common.h>

int TitleFlag_IsFullyOffScreen();
void TitleFlag_BeginTransition(int param_1);

void DECOMP_MainRaceTrack_RequestLoad(short levelID)

{
  // Turn off HUD
  sdata->gGT->hudFlags &= 0xfe;

  if (TitleFlag_IsFullyOffScreen() == 1)
  {
    TitleFlag_BeginTransition(1);
  }
  TitleFlag_ResetTextAnim();

  sdata->Loading.stage = -4;
  sdata->Loading.Lev_ID_To_Load = levelID;
  return;
}