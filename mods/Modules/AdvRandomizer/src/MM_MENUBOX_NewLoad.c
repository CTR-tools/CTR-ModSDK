#include <common.h>

extern struct MenuBox adv_difficulty;

void DECOMP_MM_MENUBOX_NewLoad(struct MenuBox *mb)
{
  // row number
  short row = mb->rowSelected;

  if (row == -1) 
  {
    mb->ptrPrevBox_InHierarchy->state &= ~(ONLY_DRAW_TITLE | DRAW_NEXT_MENU_IN_HIERARCHY);
    return;
  }

  if (row == 0)
  {
    mb->ptrNextBox_InHierarchy = &adv_difficulty;
    mb->state |= 0x14;
    return;
  }
  // if Load was chosen
  else
  {
    OVR_230.desiredMenu = row;
    OVR_230.MM_State = 2; // transitioning out
  }
}
