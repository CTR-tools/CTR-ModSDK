#include <common.h>

// byte budget
// 840/1108

#ifdef USE_HIGHMP
extern struct MenuRow rowsOnlyVsBattle[3];
#endif

void DECOMP_MM_MenuProc_Main(struct RectMenu *mainMenu)
{
  short choose;
  struct GameTracker *gGT = sdata->gGT;

  // if scrapbook is unlocked, change "rows" to extended array
  if ((sdata->gameProgress.unlocks[1] & 0x10) != 0)
    mainMenu->rows = &D230.rowsMainMenuWithScrapbook[0];

  #ifdef USE_HIGHMP
  mainMenu->rows = &rowsOnlyVsBattle[0];
  #endif

  DECOMP_MM_ParseCheatCodes();
  DECOMP_MM_ToggleRows_Difficulty();
  DECOMP_MM_ToggleRows_PlayerCount();

  // If you are at the highest hierarchy level of main menu
  if (mainMenu->unk1e == 1)
  {
    DECOMP_MM_Title_MenuUpdate();

    if (
		// main menu, "title" exists, and timer >= 230
		(D230.MM_State == 1) &&
		(D230.titleObj != NULL) &&
		(229 < D230.timerInTitle)
	   )
    {
      // "TM" trademark string
      DECOMP_DecalFont_DrawLineOT(
          sdata->lngStrings[0x244], 0x10e, 0x9c, FONT_SMALL, ORANGE,
          &gGT->backBuffer->otMem.startPlusFour[3]);
    }

    if ((D230.menuMainMenu.state & DRAW_NEXT_MENU_IN_HIERARCHY) == 0)
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
        gGT->demoCountdownTimer = FPS_DOUBLE(900);
      }
    }
  }

  DECOMP_MM_Title_Init();

  // if drawing ptrNextBox_InHierarchy
  if ((mainMenu->state & DRAW_NEXT_MENU_IN_HIERARCHY) != 0)
  {
    D230.timerInTitle = 1000;
  }
  
  // if funcPtr is null
  if ((mainMenu->state & EXECUTE_FUNCPTR) == 0)
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

  mainMenu->state |= ONLY_DRAW_TITLE;

  // Default to 3,
  // this intentionally disables the 1-lap cheat
  // in Time Trial and Adventure, DONT change it
  gGT->numLaps = 3;

  // get LNG index of row selected
  choose = mainMenu->rows[mainMenu->rowSelected].stringIndex;

  // Adventure Mode
  if (choose == 0x4c)
  {
    // Turn on Adventure Mode, turn off item cheats
    gGT->gameMode1 |= ADVENTURE_MODE;
    gGT->gameMode2 &= ~(CHEAT_WUMPA | CHEAT_MASK | CHEAT_TURBO | CHEAT_ENGINE | CHEAT_BOMBS);

    // menu for new/load
    mainMenu->ptrNextBox_InHierarchy = &D230.menuAdventure;
    mainMenu->state |= DRAW_NEXT_MENU_IN_HIERARCHY;
    return;
  }
  
  // Time Trial
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
  
  // DONT change, should only work in Arcade, and VS
  if ((gGT->gameMode2 & CHEAT_ONELAP) != 0) 
  {
    gGT->numLaps = 1;
  }
  
  // Arcade Mode
  if (choose == 0x4e)
  {
    // set game mode to Arcade Mode
    gGT->gameMode1 |= ARCADE_MODE;

    // set next menu
    mainMenu->ptrNextBox_InHierarchy = &D230.menuRaceType;
    mainMenu->state |= DRAW_NEXT_MENU_IN_HIERARCHY;
    return;
  }
  
  // Versus
  if (choose == 0x4f)
  {
    // next menu is choosing single+cup
    mainMenu->ptrNextBox_InHierarchy = &D230.menuRaceType;
    mainMenu->state |= DRAW_NEXT_MENU_IN_HIERARCHY;
    return;
  }
  
  // Battle
  if (choose == 0x50)
  {
    D230.characterSelect_transitionState = 2;

    // set game mode to Battle Mode
    gGT->gameMode1 |= BATTLE_MODE;

    // set next menu to 2P,3P,4P
    mainMenu->ptrNextBox_InHierarchy = &D230.menuPlayers2P3P4P;
    mainMenu->state |= DRAW_NEXT_MENU_IN_HIERARCHY;
    return;
  }
  
  // High Score
  if (choose == 0x51)
  {
    // Set next stage to high score menu
    D230.desiredMenuIndex = 3;

    // Leave main menu hierarchy
    D230.MM_State = 2;

    return;
  }
  
  // Scrapbook
  if (choose == 0x234) 
  {
	// Set next stage to Scrapbook
    D230.desiredMenuIndex = 5;

    // Leave main menu hierarchy
    D230.MM_State = 2;

    return;
  }
}

#ifdef USE_HIGHMP
struct MenuRow rowsOnlyVsBattle[3] =
{
	{0x4F, 0,1,0,0},
	{0x50, 0,1,1,1},
	{-1},
};
#endif