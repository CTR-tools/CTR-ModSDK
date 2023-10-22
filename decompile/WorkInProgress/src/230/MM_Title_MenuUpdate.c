#include <common.h>

void DECOMP_MM_Title_MenuUpdate(void)
{
  struct GameTracker *gGT = sdata->gGT;
  u_short seenDemo;
  int iVar4;

  // 0 - watching Crash + C-T-R letters animation
  // 1 - in the main menu
  // 2 - leaving main menu
  // 3 - coming back to main menu after exiting another menu

  // If main menu is in focus
  if (OVR_230.MM_State == 1)
  {
    // no transitioning action is needed,
    // skip to end of function
    goto END_FUNCTION;
  }

  // If you aren't in main menu

  // if not transitioning out
  if (OVR_230.MM_State < 2)
  {

    // If your state is less than 2, and
    // not 1, then it must be 0 by default

    // If not transitioning in
    if (OVR_230.MM_State != 0)

      // error, just skip everything
      goto END_FUNCTION;

    // assume main menu state = 0,
    // if you are transitioning in

    // if not done watching C-T-R letters
    if (OVR_230.unkTimerMM < 230)
    {
      OVR_230.countMeta0xD = OVR_230.title_OtherStuff[0];

      // end function
      goto END_FUNCTION;
    }

    OVR_230.menubox_mainMenu.state &= ~(DISABLE_INPUT_ALLOW_FUNCPTRS) | BIG_TEXT_IN_TITLE;

    MM_TransitionInOut((u_short *)0x800b4864, OVR_230.countMeta0xD, *(int *)0x800b4844);

    // If the animation ends
    if (OVR_230.countMeta0xD == 0)
    {
      // you are now in main menu
      OVR_230.MM_State = 1;

      // no further transitioning is needed,
      // skip to end of function
      goto END_FUNCTION;
    }

  LAB_800ac004:

    // decrease amount of time remaining in animation
    OVR_230.countMeta0xD -= 1;
    goto END_FUNCTION;
  }

  // If not transitioning out
  if (OVR_230.MM_State != 2)
  {
    // if you are not returning from another menu,
    // so either in main menu or watching C-T-R trophy animation
    if (OVR_230.MM_State != 3)
    {
      // no further action is needed
      goto END_FUNCTION;
    }

    // assume OVR_230.MM_State = 3
    // if you are returning from another menu

    MM_TransitionInOut((u_short *)0x800b4864, OVR_230.countMeta0xD, *(int *)0x800b4844);

    // If "fade-in" animation from other menu is done
    if (OVR_230.countMeta0xD == 0)
    {
      // you are now in main menu
      OVR_230.MM_State = 1;

      // end the function
      goto END_FUNCTION;
    }

    // If you're transitioning from another menu,
    // and the animation is not done, loop back and
    // check again if the transition is done
    goto LAB_800ac004;
  }

  // assume OVR_230.MM_State = 2
  // If you are transitioning out

  // MM_TransitionInOut
  MM_TransitionInOut((u_short *)0x800b4864, OVR_230.countMeta0xD, *(int *)0x800b4844);

  // Increment frame timer, increase time left in "fade-in"
  // animation, which plays it in reverse, as "fade-out"
  OVR_230.countMeta0xD += 1;

  // If the "fade-out" animation is not over, skip "switch" statemenet
  if (OVR_230.countMeta0xD <= OVR_230.title_OtherStuff[0])
    goto END_FUNCTION;

  // If you are transitioning out of the menu,
  // and if the "fade-out" animation is done,
  // time to figure out where you're going next

  switch (OVR_230.desiredMenu)
  {

  // advanture character selection
  case 0:

    GAMEPROG_NewProfile_InsideAdv(&sdata->advProgress.rewards);
    sdata->advProfileIndex = 0xffff;

    // go to adventure character select screen
    sdata->mainMenuState = 4;

    MM_Title_CameraReset();
    MM_Title_KillThread();

    MainRaceTrack_RequestLoad(ADVENTURE_CHARACTER_SELECT);
    break;

  // adventure save/load
  case 1:

    // Go to save/load
    sdata->ptrDesiredMenuBox = &data.menuBox_FourAdvProfiles;

    MM_Title_CameraReset();

    LoadSave_ToggleMode(0x10);
    break;

  // regular character selection screen
  case 2:

    MM_Title_CameraReset();

    MM_Title_KillThread();

    // return to character selection
    sdata->ptrDesiredMenuBox = &OVR_230.menubox_characterSelect;

    DECOMP_MM_Characters_RestoreIDs();
    break;

  // high score menu
  case 3:

    MM_Title_CameraReset();

    MM_HighScore_Init();

    // Go to high score menu
    sdata->ptrDesiredMenuBox = &OVR_230.menubox_highScores;
    break;

  case 4:

    MM_Title_CameraReset();

    MM_Title_KillThread();

    gGT->gameMode1 &= ~(BATTLE_MODE | ADVENTURE_MODE | TIME_TRIAL | ADVENTURE_ARENA | ARCADE_MODE | ADVENTURE_CUP);
    gGT->gameMode2 &= ~(CUP_ANY_KIND);

    // enable Arcade Mode
    gGT->gameMode1 |= ARCADE_MODE;

    // If you have not viewed Oxide cutscene yet
    if (gGT->boolSeenOxideIntro == 0)
    {
      gGT->boolSeenOxideIntro = 1;
      iVar4 = 0x1e;
    }

    // If you've already seen Oxide Cutscene
    else
    {
      // enable Demo Mode
      gGT->boolDemoMode = 1;

      // number of times you've seen Demo Mode,
      seenDemo = sdata->demoModeIndex;

	  // 60 seconds
      gGT->demoCountdownTimer = 1800;

      // use the number of time's you've seen
      // Demo Mode, to decide the order of characters

      for (iVar4 = 0; iVar4 < 8; iVar4++)
      {
        // set character ID
        data.characterIDs[iVar4] = seenDemo & 7;

        // iterate character ID
        seenDemo++;
      }

      // set number of players to 1
      gGT->numPlyrCurrGame = 1;

      // get trackID from demo mode index,
      // in order of Single Race track selection
      iVar4 = OVR_230.arcadeTracks[sdata->demoModeIndex].levID;

      // increment number of times you've been in demo mode
      sdata->demoModeIndex += 1;
    }
    goto LAB_800abfc0;

  // scrapbook
  case 5:

    MM_Title_CameraReset();

    MM_Title_KillThread();

    // go to scrapbook
    sdata->mainMenuState = 5;

    iVar4 = SCRAPBOOK;
  LAB_800abfc0:

    // Load level
    MainRaceTrack_RequestLoad(iVar4);

    // make main menu disappear
    MENUBOX_Hide((struct MenuBox *)0x800b4540);
  }

END_FUNCTION:

  // All these might be various timers for audio,
  // flashing highlight menu bars, waving flag, etc

  // if you're entering menu for first time in
  // Crash + C-T-R animation cutscene
  if (OVR_230.MM_State == 0)
  {
    OVR_230.titleCameraPosRot[0] = OVR_230.title_OtherStuff[0x1C];
    OVR_230.titleCameraPosRot[2] = OVR_230.title_OtherStuff[0x1E];
    OVR_230.titleCameraPosRot[4] = OVR_230.title_OtherStuff[0x20];
  }
  else
  {
    OVR_230.titleCameraPosRot[0] = OVR_230.title_OtherStuff[0x1C] + OVR_230.title_OtherStuff[0x5C];
    OVR_230.titleCameraPosRot[2] = OVR_230.title_OtherStuff[0x1E] + OVR_230.title_OtherStuff[0x5E];
    OVR_230.titleCameraPosRot[4] = OVR_230.title_OtherStuff[0x20] + OVR_230.title_OtherStuff[0x66];
  }

  OVR_230.menubox_mainMenu.posX_curr = OVR_230.title_OtherStuff[0x08] + OVR_230.title_OtherStuff[0x2A];
  OVR_230.menubox_mainMenu.posY_curr = OVR_230.title_OtherStuff[0x0A] + OVR_230.title_OtherStuff[0x2C];
  OVR_230.menubox_players1P2P.posX_curr = OVR_230.title_OtherStuff[0x34] + OVR_230.title_OtherStuff[0x48];
  OVR_230.menubox_players1P2P.posY_curr = OVR_230.title_OtherStuff[0x36] + OVR_230.title_OtherStuff[0x4A];
  OVR_230.menubox_players2P3P4P.posX_curr = OVR_230.title_OtherStuff[0x34] + OVR_230.title_OtherStuff[0x48];
  OVR_230.menubox_players2P3P4P.posY_curr = OVR_230.title_OtherStuff[0x36] + OVR_230.title_OtherStuff[0x4A];
  OVR_230.menubox_difficulty.posX_curr = OVR_230.title_OtherStuff[0x38] + OVR_230.title_OtherStuff[0x52];
  OVR_230.menubox_difficulty.posY_curr = OVR_230.title_OtherStuff[0x3A] + OVR_230.title_OtherStuff[0x54];
  OVR_230.menubox_raceType.posX_curr = OVR_230.title_OtherStuff[0x30] + OVR_230.title_OtherStuff[0x3E];
  OVR_230.menubox_raceType.posY_curr = OVR_230.title_OtherStuff[0x32] + OVR_230.title_OtherStuff[0x40];
  OVR_230.menubox_adventure.posX_curr = OVR_230.title_OtherStuff[0x2C] + OVR_230.title_OtherStuff[0x34];
  OVR_230.menubox_adventure.posY_curr = OVR_230.title_OtherStuff[0x2E] + OVR_230.title_OtherStuff[0x36];
}
