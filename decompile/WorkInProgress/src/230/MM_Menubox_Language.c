#include <common.h>

void MM_MENUBOX_Language(struct MenuBox *mb)
{
  char row = mb->rowSelected;

  if (row == -1)
  {
    mb->ptrPrevBox_InHierarchy->state &= ~(DRAW_NEXT_MENU_IN_HIERARCHY | ONLY_DRAW_TITLE);
  }
  else if ((-2 < row) && (row < 6))
  {
    // Language id in EurRetail gGT
    *(char *)(sdata->gGT + 0x1d58) =
        // OVR_230 global array of language ID
        ((short *)0x800b4e28)[row];

    sdata->gGT->gameMode2 |= 0x10000000; // Flag only foound in EurRetail

    mb->ptrPrevBox_InHierarchy->state &= ~(DRAW_NEXT_MENU_IN_HIERARCHY | ONLY_DRAW_TITLE);
  }
}