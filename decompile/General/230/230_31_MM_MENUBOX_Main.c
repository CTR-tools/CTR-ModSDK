#include <common.h>

// byte budget
// 840/1108

void DECOMP_MM_MENUBOX_Main(struct MenuBox *mainMenu)
{
  short choose;
  struct GameTracker *gGT = sdata->gGT;

  // if scrapbook is unlocked, change "rows" to extended array
  if ((sdata->gameProgress.unlocks[1] & 0x10) != 0)
    mainMenu->rows = &OVR_230.rows_mainMenu_WithScrapbook[0];

  DECOMP_MM_ParseCheatCodes();

  MM_ToggleRows_Difficulty();

  MM_ToggleRows_PlayerCount();

  // If you are at the highest hierarchy level of main menu
  if (mainMenu->unk1e == 1)
  {
    MM_Title_MenuUpdate();

    if (
		// main menu, "title" exists, and timer >= 230
		(OVR_230.MM_State == 1) &&
		(OVR_230.titleObj != NULL) &&
		(229 < OVR_230.timerInTitle)
	   )
    {
      // "TM" trademark string
      DecalFont_DrawLineOT(
          sdata->lngStrings[0x244], 0x10e, 0x9c, FONT_SMALL, ORANGE,
          &gGT->backBuffer->otMem.startPlusFour[3]);
    }

    if ((OVR_230.menubox_mainMenu.state & DRAW_NEXT_MENU_IN_HIERARCHY) == 0)
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
          OVR_230.MM_State = 2;

          // Go to a cutscene of some kind
          // (either oxide intro or demo mode)
          OVR_230.desiredMenu = 4;
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
  if ((mainMenu->state & DRAW_NEXT_MENU_IN_HIERARCHY) != 0)
  {
    OVR_230.timerInTitle = 1000;
  }
  
  // if funcPtr is null
  if ((mainMenu->state & EXECUTE_FUNCPTR) == 0)
  {
    return;
  }

  struct Title *titleObj = OVR_230.titleObj;

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

    // menubox for new/load
    mainMenu->ptrNextBox_InHierarchy = &OVR_230.menubox_adventure;
    mainMenu->state |= DRAW_NEXT_MENU_IN_HIERARCHY;
    return;
  }
  
  // Time Trial
  if (choose == 0x4d)
  {
    // Leave main menu hierarchy
    OVR_230.MM_State = 2;

    // Set next stage to 2 for Time Trial
    OVR_230.desiredMenu = 2;

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

    // set next menuBox
    mainMenu->ptrNextBox_InHierarchy = &OVR_230.menubox_raceType;
    mainMenu->state |= DRAW_NEXT_MENU_IN_HIERARCHY;
    return;
  }
  
  // Versus
  if (choose == 0x4f)
  {
    // next menuBox is choosing single+cup
    mainMenu->ptrNextBox_InHierarchy = &OVR_230.menubox_raceType;
    mainMenu->state |= DRAW_NEXT_MENU_IN_HIERARCHY;
    return;
  }
  
  // Battle
  if (choose == 0x50)
  {
    OVR_230.characterSelect_transitionState = 2;

    // set game mode to Battle Mode
    gGT->gameMode1 |= BATTLE_MODE;

    // set next menuBox to 2P,3P,4P
    mainMenu->ptrNextBox_InHierarchy = &OVR_230.menubox_players2P3P4P;
    mainMenu->state |= DRAW_NEXT_MENU_IN_HIERARCHY;
    return;
  }
  
  // High Score
  if (choose == 0x51)
  {
    // Set next stage to high score menu
    OVR_230.desiredMenu = 3;

    // Leave main menu hierarchy
    OVR_230.MM_State = 2;

    return;
  }
  
  // Scrapbook
  if (choose == 0x234) 
  {
	// Set next stage to Scrapbook
    OVR_230.desiredMenu = 5;

    // Leave main menu hierarchy
    OVR_230.MM_State = 2;

    return;
  }
}
