#include <common.h>

extern struct RectMenu UDCTRM_OM_GameplayMenu;
extern struct RectMenu UDCTRM_OM_ControllerSFXMenu;

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
		if (D230.timerInTitle < 230)
		{
			D230.countMeta0xD = D230.title_numFrameTotal;

			// end function
			goto END_FUNCTION;
		}

		D230.menuMainMenu.state &= ~(DISABLE_INPUT_ALLOW_FUNCPTRS); 
	D230.menuMainMenu.state |= EXECUTE_FUNCPTR;

	MM_TransitionInOut(&D230.transitionMeta_Menu[0], D230.countMeta0xD, D230.title_numTransition);

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
	MM_TransitionInOut(&D230.transitionMeta_Menu[0], D230.countMeta0xD, D230.title_numTransition);

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

	MM_TransitionInOut(&D230.transitionMeta_Menu[0], D230.countMeta0xD, D230.title_numTransition);

	// Increment frame timer, increase time left in "fade-in"
	// animation, which plays it in reverse, as "fade-out"
	D230.countMeta0xD += 1;

	// If the "fade-out" animation is not over, skip "switch" statemenet
	if (D230.countMeta0xD <= D230.title_numFrameTotal)
		goto END_FUNCTION;

	// If you are transitioning out of the menu,
	// and if the "fade-out" animation is done,
	// time to figure out where you're going next
	MM_Title_CameraReset();

	switch (D230.desiredMenuIndex)
	{
		// adventure character selection
		case 0:
		
			MM_Title_KillThread();
			GAMEPROG_NewProfile_InsideAdv(&sdata->advProgress.rewards);
		
			sdata->advProfileIndex = 0xffff;

			// go to adventure character select screen
			sdata->mainMenuState = 4;

			MainRaceTrack_RequestLoad(ADVENTURE_CHARACTER_SELECT);
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

			MM_Title_KillThread();

			// return to character selection
			sdata->ptrDesiredMenu = &D230.menuCharacterSelect;

			MM_Characters_RestoreIDs();
			break;

		// high score menu
		case 3:

			MM_HighScore_Init();

			// Go to high score menu
			sdata->ptrDesiredMenu = &D230.menuHighScores;
			break;

		// demo mode
		case 4:

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
				iVar4 = D230.arcadeTracks[sdata->demoModeIndex].levID;

				// increment number of times you've been in demo mode
				sdata->demoModeIndex += 1;
			}
			goto LAB_800abfc0;

		// scrapbook
		case 5:

			MM_Title_KillThread();

			// go to scrapbook
			sdata->mainMenuState = 5;

			iVar4 = SCRAPBOOK;
			LAB_800abfc0:

			// Load level
			MainRaceTrack_RequestLoad(iVar4);

			// make main menu disappear
			RECTMENU_Hide(&D230.menuMainMenu);
		/////////////////////////// CHANGED FOR UDCTRM ///////////////////////////
			break;

		case 0x2a:

			MM_Title_KillThread();

			sdata->ptrDesiredMenu = &UDCTRM_OM_GameplayMenu;
			break;

		case 0x45:

			MM_Title_KillThread();

			sdata->ptrDesiredMenu = &UDCTRM_OM_ControllerSFXMenu;
			MainFrame_TogglePauseAudio(1);
			break;
		/////////////////////////// END OF CHANGES     ///////////////////////////
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