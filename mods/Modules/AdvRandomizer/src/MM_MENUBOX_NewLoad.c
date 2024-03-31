#include <common.h>

extern struct RectMenu adv_difficulty;

void DECOMP_MM_MenuProc_NewLoad(struct RectMenu* menu)
{
  // row number
  short row = menu->rowSelected;

  if (row == -1) 
  {
    menu->ptrPrevBox_InHierarchy->state &= ~(ONLY_DRAW_TITLE | DRAW_NEXT_MENU_IN_HIERARCHY);
    return;
  }

  if (row == 0)
  {
    menu->ptrNextBox_InHierarchy = &adv_difficulty;
    menu->state |= 0x14;
    return;
  }
  // if Load was chosen
  else
  {
    D230.desiredMenuIndex = row;
    D230.MM_State = 2; // transitioning out
  }
}
