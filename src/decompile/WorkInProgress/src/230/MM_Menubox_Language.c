#include <common.h>

void MM_MenuProc_Language(struct RectMenu* menu)
{
  char row = menu->rowSelected;

  if (row == -1)
  {
    menu->ptrPrevBox_InHierarchy->state &= ~(DRAW_NEXT_MENU_IN_HIERARCHY | ONLY_DRAW_TITLE);
  }
  else if ((-2 < row) && (row < 6))
  {
    // Language id in EurRetail gGT
    *(char *)(sdata->gGT + 0x1d58) =
        
		// EurRetail OVR_230 global array of language ID
        D230.langIndex[row];

    sdata->gGT->gameMode2 |= 0x10000000; // Flag only foound in EurRetail related to lang change

    menu->ptrPrevBox_InHierarchy->state &= ~(DRAW_NEXT_MENU_IN_HIERARCHY | ONLY_DRAW_TITLE);
  }
}