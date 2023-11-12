#include <common.h>

void MM_JumpTo_Title_Returning(void)
{
  // return to main menu
  sdata->ptrDesiredMenuBox = &OVR_230.menubox_mainMenu;

  // return to main menu from another menu
  OVR_230.MM_State = 3;

  OVR_230.countMeta0xD = OVR_230.title_OtherStuff[0];
}
