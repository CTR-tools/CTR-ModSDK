#include <common.h>

void DECOMP_MM_JumpTo_TrackSelect(void)
{
  // return to track selection
  sdata->ptrActiveMenu = &D230.menuTrackSelect;

  D230.menuTrackSelect.state &= ~(ONLY_DRAW_TITLE);

  DECOMP_MM_TrackSelect_Init();
}