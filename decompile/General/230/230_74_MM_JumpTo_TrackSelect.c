#include <common.h>

void DECOMP_MM_JumpTo_TrackSelect(void)
{
  // return to track selection
  sdata->ptrActiveMenuBox = &D230.menubox_trackSelect;

  D230.menubox_trackSelect.state &= ~(ONLY_DRAW_TITLE);

  DECOMP_MM_TrackSelect_Init();
}