#include <common.h>

void DECOMP_MM_HighScore_Init(void)
{
  D230.highScore_transitionState = ENTERING_MENU;
  D230.highScore_transitionFrames[0] = FPS_DOUBLE(0xc);
  D230.highScore_rowDesired = 0;
  D230.highScore_rowCurr = 0;

  // reset all video variables
  DECOMP_MM_TrackSelect_Video_SetDefaults();
}