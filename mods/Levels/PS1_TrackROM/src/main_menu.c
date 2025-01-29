#include <common.h>

void MM_MenuProc_Main(struct RectMenu* mainMenu)
{
  struct GameTracker* gGT = sdata->gGT;

  DecalFont_DrawLine("Raw Track Tester: 1P Version", 5, 197, FONT_SMALL, ORANGE);
  DecalFont_DrawLine(__DATE__, 	5, 206, FONT_SMALL, ORANGE);
  DecalFont_DrawLine(__TIME__, 	170, 206, FONT_SMALL, ORANGE);

  if (mainMenu->unk1e == 1) { MM_Title_MenuUpdate(); }

  MM_Title_Init();

  if (((mainMenu->state & 0x400) == 0) || (mainMenu->unk1e != 0) || ((mainMenu->rowSelected) < 0)) { return; }

  gGT->gameMode1 &= ~(BATTLE_MODE | ADVENTURE_MODE | TIME_TRIAL | ADVENTURE_ARENA | ARCADE_MODE | ADVENTURE_CUP);
  gGT->gameMode2 &= ~(CUP_ANY_KIND);
  gGT->numLaps = 3;

  // set a flag that you're in main menu
  mainMenu->state |= 4;

  // If you choose Time Trial in Main Menu
  if (mainMenu->rows[mainMenu->rowSelected].stringIndex == 0x4d)
  {
    gGT->numPlyrNextGame = 1;
    gGT->gameMode1 |= TIME_TRIAL;
    gGT->gameMode2 &= ~CHEAT_ALL;
    sdata_static.gameProgress.unlocks[0] |= UNLOCK_CHARACTERS;

    // Leave main menu hierarchy
    D230.MM_State = 2;

    // Set next stage to 2 for Time Trial
    D230.desiredMenuIndex = 2;
  }
}
