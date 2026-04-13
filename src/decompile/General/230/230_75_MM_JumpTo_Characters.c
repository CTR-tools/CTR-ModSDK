#include <common.h>

void DECOMP_MM_JumpTo_Characters(void)
{
  // return to character selection
  sdata->ptrActiveMenu = &D230.menuCharacterSelect;

  D230.menuCharacterSelect.state &= ~(ONLY_DRAW_TITLE);

  DECOMP_MM_Characters_RestoreIDs();
}