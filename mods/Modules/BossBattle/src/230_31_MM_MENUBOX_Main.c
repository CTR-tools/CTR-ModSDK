#include <common.h>

// byte budget
// 840/1108

void MM_ParseCheatCodes();
void MM_ToggleRows_Difficulty();
void MM_ToggleRows_PlayerCount();
void MM_Title_MenuUpdate();
void MM_Title_Init();

extern struct RectMenu boss_battle_menu;

void DECOMP_MM_MenuProc_Main(struct RectMenu *mainMenu)
{
  int choose;
  struct GameTracker *gGT = sdata->gGT;

  // if scrapbook is unlocked
  if ((sdata->gameProgress.unlocks[1] & 0x10) != 0)
  {
    // change D230.rowsMainMenuBasic
    // to D230.rowsMainMenuWithScrapbook
    mainMenu->rows = &D230.rowsMainMenuWithScrapbook[0];
  }

  MM_ParseCheatCodes();

  MM_ToggleRows_Difficulty();

  MM_ToggleRows_PlayerCount();

  // If you are at the highest hierarchy level of main menu
  if (mainMenu->unk1e == 1)
  {
    MM_Title_MenuUpdate();

    if (
        (
            // If you are in main menu
            (D230.MM_State == 1) &&

            // if "title" object exists
            (D230.titleObj != NULL)) &&
        (0xe5 < D230.timerInTitle))
    {
      // "TM" trademark string
      DecalFont_DrawLineOT(
          sdata->lngStrings[0x244], 0x10e, 0x9c, FONT_SMALL, ORANGE,
          &gGT->backBuffer->otMem.startPlusFour[3]);
    }

    if ((D230.menuMainMenu.state & 0x10) == 0)
    {
      gGT->numPlyrNextGame = 1;

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

  // if drawing ptrNextBox_InHierarchy
  if ((mainMenu->state & 0x10) != 0)
  {
    D230.timerInTitle = 1000;
  }

  if ((mainMenu->state & 0x400) == 0)
  {
    return;
  }

  struct Title *titleObj = D230.titleObj;

  // if "title" object exists
  if (titleObj != NULL)
  {
    // CameraPosOffset X
    titleObj->cameraPosOffset[0] = 0;
  }

  // if you are at highest level of menu hierarchy
  if (mainMenu->unk1e != 0)
  {
    // leave the function
    return;
  }

  // If you are here, then you must not be
  // at the highest level of menu hierarchy

  // if row is negative, do nothing
  if ((mainMenu->rowSelected) < 0)
  {
    return;
  }

  // clear flags from game mode
  gGT->gameMode1 &= ~(BATTLE_MODE | ADVENTURE_MODE | TIME_TRIAL | ADVENTURE_ARENA | ARCADE_MODE | ADVENTURE_CUP);

  // clear more game mode flags
  gGT->gameMode2 &= ~(CUP_ANY_KIND);

  // set a flag that you're in main menu
  mainMenu->state |= 4;

  // number of laps is 3
  gGT->numLaps = 3;

  // get LNG index of row selected
  choose = (int)mainMenu->rows[mainMenu->rowSelected].stringIndex;

  // choose Adventure
  if (choose == 0x4c)
  {
    // Turn on Adventure Mode, turn off item cheats
    gGT->gameMode1 |= ADVENTURE_MODE;
    gGT->gameMode2 &= ~(CHEAT_WUMPA | CHEAT_MASK | CHEAT_TURBO | CHEAT_ENGINE | CHEAT_BOMBS);

    // menu for new/load
    mainMenu->ptrNextBox_InHierarchy = &D230.menuAdventure;
    mainMenu->state |= 0x10;
    return;
  }

  // If you choose Time Trial in Main Menu
  if (choose == 0x4d)
  {
    // Leave main menu hierarchy
    D230.MM_State = 2;

    // Set next stage to 2 for Time Trial
    D230.desiredMenuIndex = 2;

    // set number of players to 1
    gGT->numPlyrNextGame = 1;

    // set game mode to Time Trial Mode
    gGT->gameMode1 |= TIME_TRIAL;
    gGT->gameMode2 &= ~(CHEAT_WUMPA | CHEAT_MASK | CHEAT_TURBO | CHEAT_ENGINE | CHEAT_BOMBS);
    return;
  }

  // if one-lap-race cheat is enabled
  // works in Arcade, VS, not Adv, not Time Trial
  if ((gGT->gameMode2 & CHEAT_ONELAP) != 0)
  {
    gGT->numLaps = 1;
  }

  if (choose == 0x4e)
  {
    // set game mode to Arcade Mode
    gGT->gameMode1 |= ARCADE_MODE;

    // set next menu
    mainMenu->ptrNextBox_InHierarchy = &boss_battle_menu; // this line will set to go to new boss battle mode
    mainMenu->state |= 0x10;
    return;
  }

  // if you entered VS mode
  if (choose == 0x4f)
  {
    // next menu is choosing single+cup
    mainMenu->ptrNextBox_InHierarchy = &D230.menuRaceType;
    mainMenu->state |= 0x10;
    return;
  }

  // if you chose Battle
  if (choose == 0x50)
  {
    D230.characterSelect_transitionState = 2;

    // set game mode to Battle Mode
    gGT->gameMode1 |= BATTLE_MODE;

    // set next menu to 2P,3P,4P
    mainMenu->ptrNextBox_InHierarchy = &D230.menuPlayers2P3P4P;
    mainMenu->state |= 0x10;
    return;
  }

  // if you chose High Score
  if (choose == 0x51)
  {
    // Set next stage to high score menu
    D230.desiredMenuIndex = 3;

    // Leave main menu hierarchy
    D230.MM_State = 2;

    return;
  }

  // if you chose Scrapbook
  if (choose == 0x234)
  {
    // Set next stage to Scrapbook
    D230.desiredMenuIndex = 5;

    // Leave main menu hierarchy
    D230.MM_State = 2;

    return;
  }
}
