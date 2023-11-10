#include <common.h>

extern struct MenuBox adv_difficulty;

void DECOMP_MM_MENUBOX_NewLoad(struct MenuBox *mb)
{
  short row = mb->rowSelected;

  switch (row)
  {
  case -1:
    mb->ptrPrevBox_InHierarchy->state &= 0xffffffeb;
    return;
  case 0:
    mb->ptrNextBox_InHierarchy = &adv_difficulty;
    mb->state |= (ONLY_DRAW_TITLE | DRAW_NEXT_MENU_IN_HIERARCHY);
    return;
  case 1:
    #if BUILD == UsaRetail
        OVR_230.desiredMenu = 1;
        OVR_230.MM_State = 2; // transitioning out
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
