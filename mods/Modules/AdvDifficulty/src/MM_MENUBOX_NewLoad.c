#include <common.h>

extern struct RectMenu adv_difficulty;

void DECOMP_MM_MenuProc_NewLoad(struct RectMenu* menu)
{
  short row = menu->rowSelected;

  switch (row)
  {
  case -1:
    menu->ptrPrevBox_InHierarchy->state &= 0xffffffeb;
    return;
  case 0:
    menu->ptrNextBox_InHierarchy = &adv_difficulty;
    menu->state |= (ONLY_DRAW_TITLE | DRAW_NEXT_MENU_IN_HIERARCHY);
    return;
  case 1:
    #if BUILD == UsaRetail
        D230.desiredMenuIndex = 1;
        D230.MM_State = 2; // transitioning out
    #endif
    #if BUILD == EurRetail
        *(int *)0x800b6284 = 1;
        *(int *)0x800b62c0 = 2; // transitioning out
    #endif
    #if BUILD == JpnRetail
        *(int *)0x800b9a8c = 1;
        *(int *)0x800b9ac8 = 2; // transitioning out
    #endif
  default:
    return;
  }
}
