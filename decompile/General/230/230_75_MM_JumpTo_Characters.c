#include <common.h>

void MM_JumpTo_Characters(void)
{
  // return to character selection
  sdata->ptrActiveMenuBox = &OVR_230.menubox_characterSelect;

  OVR_230.menubox_characterSelect.state &= ~(ONLY_DRAW_TITLE);

  MM_Characters_RestoreIDs();
}