#include <common.h>

// byte budget
// 840/1108

void DECOMP_MM_MENUBOX_Main(struct MenuBox *mainMenu)
{
  short row;
  struct GameTracker *gGT = sdata->gGT;

  // if scrapbook is unlocked
  if ((sdata->gameProgress.unlocks[0] & 0x10) != 0)
  {
    // change OVR_230.rows_mainMenu_Basic
    // to OVR_230.rows_mainMenu_WithScrapbook
    mainMenu->rows = &OVR_230.rows_mainMenu_WithScrapbook[0];
  }

  DECOMP_MM_ParseCheatCodes();

  MM_ToggleRows_Difficulty();

  MM_ToggleRows_PlayerCount();

  // If you are at the highest hierarchy level of main menu
  if (mainMenu->unk1e == 1)
  {
    MM_Title_MenuUpdate();

    if ( // If you are in main menu
        ((OVR_230.MM_State == 1) &&
         // if "title" object exists
         (OVR_230.titleObj != NULL)) &&
        (229 < OVR_230.unkTimerMM))
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
    OVR_230.unkTimerMM = 1000;
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

  // number of laps is 3 otherwise 1 if cheat is enabled
  gGT->numLaps = ((gGT->gameMode2 & CHEAT_ONELAP) == 0) ? 3 : 1;

  // get LNG index of row selected
  row = mainMenu->rows[mainMenu->rowSelected].stringIndex;

  switch (row)
  {
  // Adventure Mode
  case 76:
    // Turn on Adventure Mode, turn off item cheats
    gGT->gameMode1 |= ADVENTURE_MODE;
    gGT->gameMode2 &= ~(CHEAT_WUMPA | CHEAT_MASK | CHEAT_TURBO | CHEAT_ENGINE | CHEAT_BOMBS);

    // menubox for new/load
    mainMenu->ptrNextBox_InHierarchy = &OVR_230.menubox_adventure;
    mainMenu->state |= DRAW_NEXT_MENU_IN_HIERARCHY;
    return;
  // Time Trial
  case 77:
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
  // Arcade Mode
  case 78:
    // set game mode to Arcade Mode
    gGT->gameMode1 |= ARCADE_MODE;

    // set next menuBox
    mainMenu->ptrNextBox_InHierarchy = &OVR_230.menubox_raceType;
    mainMenu->state |= DRAW_NEXT_MENU_IN_HIERARCHY;
    return;
  // Versus
  case 79:
    // next menuBox is choosing single+cup
    mainMenu->ptrNextBox_InHierarchy = &OVR_230.menubox_raceType;
    mainMenu->state |= DRAW_NEXT_MENU_IN_HIERARCHY;
    return;
  // Battle
  case 80:
    OVR_230.transitionState = 2;

    // set game mode to Battle Mode
    gGT->gameMode1 |= BATTLE_MODE;

    // set next menuBox to 2P,3P,4P
    mainMenu->ptrNextBox_InHierarchy = &OVR_230.menubox_players2P3P4P;
    mainMenu->state |= DRAW_NEXT_MENU_IN_HIERARCHY;
    return;
  // High Score
  case 81:
    // Set next stage to high score menu
    OVR_230.desiredMenu = 3;

    // Leave main menu hierarchy
    OVR_230.MM_State = 2;

    return;
  // Scrapbook
  case 564:
    // Set next stage to Scrapbook
    OVR_230.desiredMenu = 5;

    // Leave main menu hierarchy
    OVR_230.MM_State = 2;

    return;
  }
}
