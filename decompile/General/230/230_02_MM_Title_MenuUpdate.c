#include <common.h>

void DECOMP_MM_Title_MenuUpdate(void)
{
  struct GameTracker *gGT = sdata->gGT;
  u_short seenDemo;
  short cutsceneLev;

  // 0 - watching Crash + C-T-R letters animation
  // 1 - in the main menu
  // 2 - leaving main menu
  // 3 - coming back to main menu after exiting another menu

  // If main menu is in focus
  if (D230.MM_State == 1)
  {
    // no transitioning action is needed,
    // skip to end of function
    goto END_FUNCTION;
  }

  // If you aren't in main menu

  // if not transitioning out
  if (D230.MM_State < 2)
  {

    // If your state is less than 2, and
    // not 1, then it must be 0 by default

    // If not transitioning in
    if (D230.MM_State != 0)

      // error, just skip everything
      goto END_FUNCTION;

    // assume main menu state = 0,
    // if you are transitioning in

    // if not done watching C-T-R letters
    if (D230.timerInTitle < FPS_DOUBLE(230))
    {
      D230.countMeta0xD = D230.title_numFrameTotal;

      // end function
      goto END_FUNCTION;
    }

    D230.menuMainMenu.state &= ~(DISABLE_INPUT_ALLOW_FUNCPTRS); 
	D230.menuMainMenu.state |= EXECUTE_FUNCPTR;

	DECOMP_MM_TransitionInOut(&D230.transitionMeta_Menu[0], D230.countMeta0xD, D230.title_numTransition);

    // If the animation ends
    if (D230.countMeta0xD == 0)
    {
      // you are now in main menu
      D230.MM_State = 1;

      // no further transitioning is needed,
      // skip to end of function
      goto END_FUNCTION;
    }

  LAB_800ac004:

    // decrease amount of time remaining in animation
    D230.countMeta0xD -= 1;
    goto END_FUNCTION;
  }

  // If not transitioning out
  if (D230.MM_State != 2)
  {
    // if you are not returning from another menu,
    // so either in main menu or watching C-T-R trophy animation
    if (D230.MM_State != 3)
    {
      // no further action is needed
      goto END_FUNCTION;
    }

    // assume D230.MM_State = 3
    // if you are returning from another menu
	DECOMP_MM_TransitionInOut(&D230.transitionMeta_Menu[0], D230.countMeta0xD, D230.title_numTransition);

    // If "fade-in" animation from other menu is done
    if (D230.countMeta0xD == 0)
    {
      // you are now in main menu
      D230.MM_State = 1;

      // end the function
      goto END_FUNCTION;
    }

    // If you're transitioning from another menu,
    // and the animation is not done, loop back and
    // check again if the transition is done
    goto LAB_800ac004;
  }

  // assume D230.MM_State = 2
  // If you are transitioning out

  DECOMP_MM_TransitionInOut(&D230.transitionMeta_Menu[0], D230.countMeta0xD, D230.title_numTransition);

  // Increment frame timer, increase time left in "fade-in"
  // animation, which plays it in reverse, as "fade-out"
  D230.countMeta0xD += 1;

  // If the "fade-out" animation is not over, skip "switch" statemenet
  if (D230.countMeta0xD <= D230.title_numFrameTotal)
    goto END_FUNCTION;

  // If you are transitioning out of the menu,
  // and if the "fade-out" animation is done,
  // time to figure out where you're going next
  DECOMP_MM_Title_CameraReset();

  switch (D230.desiredMenuIndex)
  {

  // adventure character selection
  case 0:
  
    DECOMP_MM_Title_KillThread();
    DECOMP_GAMEPROG_NewProfile_InsideAdv(&sdata->advProgress.rewards);
	
    sdata->advProfileIndex = 0xffff;

    // go to adventure character select screen
    sdata->mainMenuState = 4;

    DECOMP_MainRaceTrack_RequestLoad(ADVENTURE_CHARACTER_SELECT);
    break;

  // adventure save/load
  case 1:

    // Go to save/load
    sdata->ptrDesiredMenu = &data.menuFourAdvProfiles;

#ifndef REBUILD_PS1
    SelectProfile_ToggleMode(0x10);
#endif
    break;

  // regular character selection screen
  case 2:

    DECOMP_MM_Title_KillThread();

    // return to character selection
    sdata->ptrDesiredMenu = &D230.menuCharacterSelect;

    DECOMP_MM_Characters_RestoreIDs();
    break;

  // high score menu
  case 3:

    DECOMP_MM_HighScore_Init();

    // Go to high score menu
    sdata->ptrDesiredMenu = &D230.menuHighScores;
    break;

  // demo mode
  case 4:

    DECOMP_MM_Title_KillThread();

    gGT->gameMode1 &= ~(BATTLE_MODE | ADVENTURE_MODE | TIME_TRIAL | ADVENTURE_ARENA | ARCADE_MODE | ADVENTURE_CUP);
    gGT->gameMode2 &= ~(CUP_ANY_KIND);

    // enable Arcade Mode
    gGT->gameMode1 |= ARCADE_MODE;

    // If you have not viewed Oxide cutscene yet
    if (gGT->boolSeenOxideIntro == 0)
    {
      gGT->boolSeenOxideIntro = 1;
      cutsceneLev = INTRO_RACE_TODAY;
    }

    // If you've already seen Oxide Cutscene
    else
    {
      // enable Demo Mode
      gGT->boolDemoMode = 1;
	  
      // set number of players to 1
      gGT->numPlyrCurrGame = 1;
	  
	  // 60 seconds
      gGT->demoCountdownTimer = FPS_DOUBLE(1800);

      // number of times you've seen Demo Mode,
      seenDemo = sdata->demoModeIndex;

      // set character ID
      data.characterIDs[0] = seenDemo;

      // get trackID from demo mode index,
      // in order of Single Race track selection
      cutsceneLev = D230.arcadeTracks[seenDemo].levID;

      // increment counter
      sdata->demoModeIndex = (seenDemo + 1) & 7;
    }
    goto LAB_800abfc0;

  // scrapbook
  case 5:

    DECOMP_MM_Title_KillThread();

    // go to scrapbook
    sdata->mainMenuState = 5;

    cutsceneLev = SCRAPBOOK;
  LAB_800abfc0:

    // Load level
    DECOMP_MainRaceTrack_RequestLoad(cutsceneLev);

    // make main menu disappear
    DECOMP_RECTMENU_Hide(&D230.menuMainMenu);
  }

END_FUNCTION:

  // if you're entering menu for first time in
  // Crash + C-T-R animation cutscene
  if (D230.MM_State == 0)
  {
    D230.titleCameraPos[0] = D230.title_camPos[0];
    D230.titleCameraPos[1] = D230.title_camPos[1];
    D230.titleCameraPos[2] = D230.title_camPos[2];
  }
  else
  {
    D230.titleCameraPos[0] = D230.title_camPos[0] + D230.transitionMeta_Menu[5].currX;
    D230.titleCameraPos[1] = D230.title_camPos[1] + D230.transitionMeta_Menu[5].currY;
    D230.titleCameraPos[2] = D230.title_camPos[2] + D230.transitionMeta_Menu[6].currX;
  }

  D230.menuMainMenu.posX_curr = D230.title_mainPosX + D230.transitionMeta_Menu[0].currX;
  D230.menuMainMenu.posY_curr = D230.title_mainPosY + D230.transitionMeta_Menu[0].currY;
  D230.menuAdventure.posX_curr = D230.title_advPosX + D230.transitionMeta_Menu[1].currX;
  D230.menuAdventure.posY_curr = D230.title_advPosY + D230.transitionMeta_Menu[1].currY;
  D230.menuRaceType.posX_curr = D230.title_racePosX + D230.transitionMeta_Menu[2].currX;
  D230.menuRaceType.posY_curr = D230.title_racePosY + D230.transitionMeta_Menu[2].currY;
  D230.menuPlayers1P2P.posX_curr = D230.title_plyrPosX + D230.transitionMeta_Menu[3].currX;
  D230.menuPlayers1P2P.posY_curr = D230.title_plyrPosY + D230.transitionMeta_Menu[3].currY;
  D230.menuPlayers2P3P4P.posX_curr = D230.title_plyrPosX + D230.transitionMeta_Menu[3].currX;
  D230.menuPlayers2P3P4P.posY_curr = D230.title_plyrPosY + D230.transitionMeta_Menu[3].currY;
  D230.menuDifficulty.posX_curr = D230.title_diffPosX + D230.transitionMeta_Menu[4].currX;
  D230.menuDifficulty.posY_curr = D230.title_diffPosY + D230.transitionMeta_Menu[4].currY;
}

void DECOMP_MM_Title_KillThread(void)
{
  char n;
  struct GameTracker *gGT = sdata->gGT;
  struct Title *title = D230.titleObj;

  if (// if "title" object exists
      (title != NULL) &&
      (// if you are in main menu
      (gGT->gameMode1 & MAIN_MENU) != 0))
  {
    // destroy six instances
    for (n = 0; n < 6; n++)
    {
      DECOMP_INSTANCE_Death(title->i[n]);
      title->i[n] = NULL;
    }
	
	// kill thread
    title->t->flags |= 0x800;
    D230.titleObj = NULL;

    // CameraDC, it must be zero to follow you
    gGT->cameraDC[0].transitionTo.rot[0] = 0;
    gGT->pushBuffer[0].distanceToScreen_CURR = 0x100;
  }
}