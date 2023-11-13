#include <common.h>

void MM_JumpTo_BattleSetup(void)
{
  // Go to battle setup
  sdata->ptrActiveMenuBox = &OVR_230.menubox_battleWeapons;

  OVR_230.menubox_battleWeapons.state &= ~(ONLY_DRAW_TITLE);

  MM_Battle_Init();
}