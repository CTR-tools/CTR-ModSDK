#include <common.h>

void MM_JumpTo_Characters(void)
{
  // return to character selection
  sdata->ptrActiveMenuBox = &D230.menubox_characterSelect;

  D230.menubox_characterSelect.state &= ~(ONLY_DRAW_TITLE);

  MM_Characters_RestoreIDs();
}