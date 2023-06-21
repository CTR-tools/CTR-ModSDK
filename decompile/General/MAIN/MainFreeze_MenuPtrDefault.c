#include <common.h>

void DECOMP_MainFreeze_MenuPtrDefault(struct MenuBox* mb)
{
	int levID = 0;
	u_short stringID;
	u_int gameMode;

	struct GameTracker* gGT = sdata->gGT;
	gameMode = gGT->gameMode1;

	// if you have not waited 5 frames since the game was paused then quit
	if (gGT->cooldownfromPauseUntilUnpause != 0) return;

	// assume 5 frames have passed since paused

	if (mb->unk1e != 0)
	{
		mb->drawStyle &= 0xfeff;

		// if more than 2 screens
		if (2 < gGT->numPlyrCurrGame)
		{
			mb->drawStyle |= 0x100;
		}

		if
		(
			!(gameMode & ADVENTURE_ARENA) ||
			// mb is closing
			(mb->state & NEEDS_TO_CLOSE)
		)
		{
			return;
		}

		// quit adv hub if it's not loaded
		if (LOAD_IsOpen_AdvHub() == 0)
			return;

		AH_Pause_Update();

		return;
	}

	if (mb->rowSelected < 0) return;

	// get stringID from selected row
	stringID = mb->rows[mb->rowSelected].stringIndex;

	// stringID 14: "OPTIONS"
	if (stringID == 14)
	{
		// Set MenuBox to Options
		sdata->ptrDesiredMenuBox = &data.menuBox_optionsMenu_racingWheel;

		data.menuBox_optionsMenu_racingWheel.rowSelected = 8;
		return;
	}

	// stringID 11: "AKU AKU HINTS"
	// stringID 12: "UKA UKA HINTS"
	if (stringID == 11 || stringID == 12)
	{
		// Set MenuBox to Hints
		sdata->ptrDesiredMenuBox = (struct MenuBox *)0x800b518c;
		return;
	}

	// stringID 3: "QUIT"
	if (stringID == 3)
	{
		// Set MenuBox to Quit
		sdata->ptrDesiredMenuBox = &data.menuBox_quit;
		data.menuBox_quit.rowSelected = 1;
		return;
	}

	// must wait 5 frames until next pause
	gGT->cooldownFromUnpauseUntilPause = 5;

	// hide MenuBox
	MENUBOX_Hide(mb);

	MainFreeze_SafeAdvDestroy();

	// careful, it's stringID MINUS one
	switch (stringID - 1)
	{

		// stringID 1: "RESTART"
		case 0:

		// stringID 4: "RETRY"
		case 3:

			// get rid of pause flag
			gGT->gameMode1 &= ~PAUSE_1;

			if (TitleFlag_IsFullyOffScreen() == 1)
			{
				// checkered flag, begin transition on-screen
				TitleFlag_BeginTransition(1);
			}

			// if you are not showing a ghost during a race
			if (sdata->boolPlayGhost == 0)
			{
				// restart race
				sdata->Loading.stage = -5;
				return;
			}

			// If the ghost playing buffer is nullptr
			if (sdata->ptrGhostTapePlaying == 0)
			{
				// restart race
				sdata->Loading.stage = -5;
				return;
			}

			// At this point, we are certain there is a ghost buffer so you must be in time trial mode

			// Make P2 the character that is saved in the header of the ghost that you will see in the race
			data.characterIDs[1] = *(short *)((int)sdata->ptrGhostTapePlaying + 6);

			// restart race
			sdata->Loading.stage = -5;
			return;

		// stringID 2: "RESUME"
		case 1:

			// unpause game
			ElimBG_Deactivate(gGT);
			gGT->gameMode1 &= ~PAUSE_1;

			// unpause audio
			MainFrame_TogglePauseAudio(0);

			// play pause/unpause sound
			OtherFX_Play(1, 1);
			return;

		// stringID 5: "CHANGE CHARACTER"
		case 4:

			// erase ghost of previous race from RAM
			GhostBuffer_Destroy();

			// set level ID to main menu
			levID = MAIN_MENU_LEVEL;

			// return to character selection
			sdata->mainMenuState = 1;

			// when loading is done, add bit for "in mb"
			sdata->Loading.OnBegin.AddBitsConfig0 |= 0x2000;

			// get rid of pause flag
			gGT->gameMode1 &= ~PAUSE_1;
			break;

		// stringID 6: "CHANGE LEVEL"
		case 5:

			// erase ghost of previous race from RAM
			GhostBuffer_Destroy();

			// level ID of main mb
			levID = MAIN_MENU_LEVEL;

			// return to track selection
			sdata->mainMenuState = 2;

			// when loading is done
			// add bit for "in mb"
			sdata->Loading.OnBegin.AddBitsConfig0 |= 0x2000;

			// get rid of pause flag
			gGT->gameMode1 &= ~PAUSE_1;
			break;

		// stringID 10: "CHANGE SETUP"
		case 9:

			// set level ID to main menu
			levID = MAIN_MENU_LEVEL;

			// return to battle setup
			sdata->mainMenuState = 3;

			// when loading is done
			// add bit for "in mb"
			sdata->Loading.OnBegin.AddBitsConfig0 |= 0x2000;

			// get rid of pause flag
			gGT->gameMode1 &= ~PAUSE_1;
			break;

		// stringID 13: "EXIT TO MAP"
		case 12:

			// when loading is done
			// add this bit for In Adventure Arena
			sdata->Loading.OnBegin.AddBitsConfig0 |= 0x100000;

			// when loading is done
			// remove bits for Relic Race or Crystal Challenge
			sdata->Loading.OnBegin.RemBitsConfig0 |= 0xc000000;

			// when loading is done
			// remove bit for CTR Token Challenge
			sdata->Loading.OnBegin.RemBitsConfig8 |= 8;

			// get rid of pause flag
			gGT->gameMode1 &= ~PAUSE_1;

			// If you are not in Adventure cup
			if ((gameMode & ADVENTURE_CUP) == 0)
			{
				// 0x80000000
				// If you're in Boss Mode
				if ((int)gameMode < 0)
				{
					// when loading is done remove bit for Boss Race, relic, and crystal challenge
					sdata->Loading.OnBegin.RemBitsConfig0 |= 0x8c000000;

					// When loading is done add bit to spawn driver near boss door
					sdata->Loading.OnBegin.AddBitsConfig8 |= 1;
				}

				// set levID to level you were in previously
				levID = gGT->prevLEV;
			}

			// If you're in Adventure Cup
			else
			{
				levID = GEM_STONE_VALLEY;

				// when loading is done remove bits for Adventure Cup, relic, and crystal challenge
				sdata->Loading.OnBegin.RemBitsConfig0 |= 0x1c000000;

				// Level ID
				gGT->levelID = gGT->cup.cupID + 100;
			}
		default:
			break;
	}
	// load level ID
	MainRaceTrack_RequestLoad(levID);
	return;
}