#include <common.h>

extern struct RectMenu menuLanguage;

void DECOMP_MM_MenuProc_Main(struct RectMenu *mainMenu)
{
  short choose;
  struct GameTracker *gGT = sdata->gGT;
  struct RectMenu *nextBox;

  // if scrapbook is unlocked, change "rows" to extended array
  if ((sdata->gameProgress.unlocks[1] & 0x10) != 0)
  {
    // so it doesn't do this again once rewritten
    if (mainMenu->rows[7].stringIndex < 0)
    {
      mainMenu->rows[6].rowOnPressDown = 7;
      #if BUILD == JpnRetail
      mainMenu->rows[7].stringIndex = 0x240;
      #else
      mainMenu->rows[7].stringIndex = 0x234;
      #endif
    }
  }

  MM_ParseCheatCodes();

  MM_ToggleRows_Difficulty();

  MM_ToggleRows_PlayerCount();

  // If you are at the highest hierarchy level of main menu
  if (mainMenu->unk1e == 1)
  {
    MM_Title_MenuUpdate();

    if (
        // main menu, "title" exists, and timer >= 230
        (D230.MM_State == 1) &&
        (D230.titleObj != NULL) &&
        (229 < D230.timerInTitle))
    {

      // "TM" trademark string
      DecalFont_DrawLineOT(
#if BUILD == JpnRetail
          sdata->lngStrings[0x250],
          0x11d, 0xb8,
#else
          sdata->lngStrings[0x244],
          0x10e, 0x9c,
#endif
          FONT_SMALL, ORANGE,
          &gGT->backBuffer->otMem.startPlusFour[3]);
    }

    if ((D230.menuMainMenu.state & DRAW_NEXT_MENU_IN_HIERARCHY) == 0)
    {
#if BUILD == JpnRetail
      if (D230.MM_State != 2)
#endif
      {
        gGT->numPlyrNextGame = 1;
      }

      // if no buttons pressed, check demo mode
      if (sdata->gGamepads->anyoneHeldCurr == 0)
      {
        gGT->demoCountdownTimer--;

        // If time runs out
        if (gGT->demoCountdownTimer < 1)
        {
          // Transition out of main menu
          D230.MM_State = 2;

          // Go to a cutscene of some kind
          // (either oxide intro or demo mode)
          D230.desiredMenuIndex = 4;
        }
      }

      // if button pressed, reset timer
      else
      {
        // 900 = 30 seconds at 30fps
        gGT->demoCountdownTimer = 900;
      }
    }
  }

  MM_Title_Init();

  if ((mainMenu->state & DRAW_NEXT_MENU_IN_HIERARCHY) != 0)
    D230.timerInTitle = 1000;

  // if funcPtr is null
  if ((mainMenu->state & EXECUTE_FUNCPTR) == 0)
    return;

  struct Title *titleObj = D230.titleObj;

  // if "title" object exists
  if (titleObj != NULL)
  {
    // CameraPosOffset X or Z
#if BUILD != JpnRetail
    titleObj->cameraPosOffset[0] = 0;
#else
    titleObj->cameraPosOffset[2] = 0;
#endif
  }

  // if you are at highest level of menu hierarchy
  if (mainMenu->unk1e != 0)
    // leave the function
    return;

  // if row is negative, do nothing
  if ((mainMenu->rowSelected) < 0)
    return;

  // clear flags from game mode
  gGT->gameMode1 &= ~(BATTLE_MODE | ADVENTURE_MODE | TIME_TRIAL | ADVENTURE_ARENA | ARCADE_MODE | ADVENTURE_CUP);

  // clear more game mode flags
  gGT->gameMode2 &= ~(CUP_ANY_KIND);

  mainMenu->state |= ONLY_DRAW_TITLE;

  gGT->numLaps = 3;

  // get LNG index of row selected
  choose = mainMenu->rows[mainMenu->rowSelected].stringIndex;

  switch (choose)
  {
  case 0x4c: // Adventure Mode
    gGT->gameMode1 |= ADVENTURE_MODE;
    gGT->gameMode2 &= ~(CHEAT_WUMPA | CHEAT_MASK | CHEAT_TURBO | CHEAT_ENGINE | CHEAT_BOMBS);
    nextBox = &D230.menuAdventure;
    break;

  case 0x4d: // Time Trial
    D230.MM_State = 2;
    D230.desiredMenuIndex = 2;
    gGT->numPlyrNextGame = 1;
    gGT->gameMode1 |= TIME_TRIAL;
    gGT->gameMode2 &= ~(CHEAT_WUMPA | CHEAT_MASK | CHEAT_TURBO | CHEAT_ENGINE | CHEAT_BOMBS);
    break;

  case 0x4e: // Arcade Mode
    gGT->gameMode1 |= ARCADE_MODE;
    nextBox = &D230.menuRaceType;
    break;

  case 0x4f: // Versus
    nextBox = &D230.menuRaceType;
    break;

  case 0x50: // Battle
    D230.characterSelect_transitionState = 2;
    gGT->gameMode1 |= BATTLE_MODE;
    nextBox = &D230.menuPlayers2P3P4P;
    break;

  case 0x51: // High Score
    D230.desiredMenuIndex = 3;
    D230.MM_State = 2;
    break;

  case 82: // Language
    menuLanguage.unk1e = 0;
    menuLanguage.posX_curr = 0;
    menuLanguage.posY_curr = 0;
    menuLanguage.state = (CENTER_ON_X | 0x400000);
    menuLanguage.width = 141;
    nextBox = &menuLanguage;
    break;
    // Scrapbook
#if BUILD == JpnRetail
  case 0x240:
#else
  case 0x234: 
#endif
    D230.desiredMenuIndex = 5;
    D230.MM_State = 2;
    break;
  }
  if (nextBox)
  {
    mainMenu->ptrNextBox_InHierarchy = nextBox;
    mainMenu->state |= DRAW_NEXT_MENU_IN_HIERARCHY;
  }
}
