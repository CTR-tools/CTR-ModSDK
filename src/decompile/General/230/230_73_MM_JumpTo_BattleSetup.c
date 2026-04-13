#include <common.h>

void DECOMP_MM_JumpTo_BattleSetup(void)
{
  // Go to battle setup
  sdata->ptrActiveMenu = &D230.menuBattleWeapons;

  D230.menuBattleWeapons.state &= ~(ONLY_DRAW_TITLE);

  DECOMP_MM_Battle_Init();
}