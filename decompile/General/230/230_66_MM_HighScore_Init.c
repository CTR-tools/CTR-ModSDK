#include <common.h>

void MM_HighScore_Init(void)
{
  OVR_230.highScore_transitionState = ENTERING_MENU;
  OVR_230.highScore_transitionFrames[0] = 0xc;
  OVR_230.highScore_rowDesired = 0;
  OVR_230.highScore_rowCurr = 0;

  // reset all video variables
  MM_TrackSelect_Video_SetDefaults();
}