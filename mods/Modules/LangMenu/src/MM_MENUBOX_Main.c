#include <common.h>

extern struct MenuBox menubox_language;

void DECOMP_MM_MENUBOX_Main(struct MenuBox *mainMenu)
{
  short choose;
  struct GameTracker *gGT = sdata->gGT;
  struct MenuBox *nextBox;

  MM_ParseCheatCodes();

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
        (229 < OVR_230.timerInTitle))
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

    if ((OVR_230.menubox_mainMenu.state & DRAW_NEXT_MENU_IN_HIERARCHY) == 0)
    {
#if BUILD == JpnRetail
      if (OVR_230.MM_State != 2)
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

  if ((mainMenu->state & DRAW_NEXT_MENU_IN_HIERARCHY) != 0)
    OVR_230.timerInTitle = 1000;

  // if funcPtr is null
  if ((mainMenu->state & EXECUTE_FUNCPTR) == 0)
    return;

  struct Title *titleObj = OVR_230.titleObj;

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
    nextBox = &OVR_230.menubox_adventure;
    break;

  case 0x4d: // Time Trial
    OVR_230.MM_State = 2;
    OVR_230.desiredMenu = 2;
    gGT->numPlyrNextGame = 1;
    gGT->gameMode1 |= TIME_TRIAL;
    gGT->gameMode2 &= ~(CHEAT_WUMPA | CHEAT_MASK | CHEAT_TURBO | CHEAT_ENGINE | CHEAT_BOMBS);
    break;

  case 0x4e: // Arcade Mode
    gGT->gameMode1 |= ARCADE_MODE;
    nextBox = &OVR_230.menubox_raceType;
    break;

  case 0x4f: // Versus
    nextBox = &OVR_230.menubox_raceType;
    break;

  case 0x50: // Battle
    OVR_230.characterSelect_transitionState = 2;
    gGT->gameMode1 |= BATTLE_MODE;
    nextBox = &OVR_230.menubox_players2P3P4P;
    break;

  case 0x51: // High Score
    OVR_230.desiredMenu = 3;
    OVR_230.MM_State = 2;
    break;

  case 82: // Language
    menubox_language.unk1e = 0;
    menubox_language.posX_curr = 0;
    menubox_language.posY_curr = 0;
    menubox_language.state = (CENTER_ON_X | 0x400000);
    menubox_language.width = 141;
    nextBox = &menubox_language;
    break;
  }
  if (nextBox)
  {
    mainMenu->ptrNextBox_InHierarchy = nextBox;
    mainMenu->state |= DRAW_NEXT_MENU_IN_HIERARCHY;
  }
}
