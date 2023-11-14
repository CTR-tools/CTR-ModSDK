#include <common.h>

void DECOMP_MM_JumpTo_BattleSetup(void)
{
  // Go to battle setup
  sdata->ptrActiveMenuBox = &D230.menubox_battleWeapons;

  D230.menubox_battleWeapons.state &= ~(ONLY_DRAW_TITLE);

  DECOMP_MM_Battle_Init();
}