#include <common.h>

void MM_JumpTo_Title_Returning(void)
{
  // return to main menu
  sdata->ptrDesiredMenuBox = &D230.menubox_mainMenu;

  // return to main menu from another menu
  D230.MM_State = 3;

  D230.countMeta0xD = D230.title_numFrameTotal;
}
