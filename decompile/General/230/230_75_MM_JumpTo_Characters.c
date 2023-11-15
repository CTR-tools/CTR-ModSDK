#include <common.h>

void DECOMP_MM_JumpTo_Characters(void)
{
  // return to character selection
  sdata->ptrActiveMenuBox = &D230.menubox_characterSelect;

  D230.menubox_characterSelect.state &= ~(ONLY_DRAW_TITLE);

  DECOMP_MM_Characters_RestoreIDs();
}