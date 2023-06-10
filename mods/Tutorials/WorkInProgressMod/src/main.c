#include <common.h>
#include "header.h"

void MyMainFreeze(struct GameTracker* gGT)
{
	// Check conditions for pausing the game
	if
	(
		// if flag is not fully on screen
		(TitleFlag_IsFullyOnScreen() == 0) &&

		// if you are not drawing loading screen (after fully off screen)
		((gGT->renderFlags & 0x1000) == 0) &&

		// if aku is not giving a hint
		(sdata->AkuAkuHintState == 0) &&

		// if not in a menu, time trial, and not paused yet
		(sdata->ptrActiveMenuBox == 0 && (gGT->gameMode1 & (END_OF_RACE | PAUSE_ALL)) == 0) &&

		// not in Main Menu and not in Demo Mode
		(gGT->levelID != MAIN_MENU_LEVEL && ((gGT->gameMode1 & GAME_CUTSCENE) == 0 && gGT->boolDemoMode == 0)) &&

		// if game is not loading and not in a cutscene where you can't move
		((1 < (gGT->levelID - OXIDE_ENDING) && (sdata->load_inProgress == 0 && (!(gGT->gameMode2 & 4)))) == 0)
	)
	{
		// pause the game
		gGT->gameMode1 |= PAUSE_1;

		// set row selected to the top row
		//((struct MenuBox *)MainFreeze_GetMenuBox())->rowSelected = 0;

		// make menu visible
		MENUBOX_Show(&MyMenuBox);

		// pause audio
		MainFrame_TogglePauseAudio(1);

		// OtherFX_Play to pause
		OtherFX_Play(1, 1);

		// Activate pause menu
		ElimBG_Activate(gGT);
	}
}

// I don't really know what to name this function
void daisy(struct GameTracker* gGT, struct GamepadSystem* gGamepads)
{
	int isTitleFlagFullyOnScreen = 0;
	int isGamepadConnected = GAMEPAD_GetNumConnected(gGamepads);
	int HaveAllPads = 0;

	if (!(gGT->gameMode1 & END_OF_RACE))
	{
		/*
		if (gGT->gameMode1 & PAUSE_ALL)
		{
			if (gGT->cooldownfromPauseUntilUnpause == 0)
			{
				if
				(
					(
						(sdata->ptrActiveMenuBox != &data.menuBox_optionsMenu_racingWheel) &&
						(sdata->ptrActiveMenuBox != (struct MenuBox*)0x800b518c)
					) && (sdata->AnyPlayerTap & BTN_SELECT) // only changes I made to this portion of GameLogic so far
				)
				{
					MENUBOX_ClearInput();
					gGT->gameMode1 &= ~PAUSE_1;
					MainFrame_TogglePauseAudio(0);
					OtherFX_Play(1, 1);
					MainFreeze_SafeAdvDestroy();
					ElimBG_Deactivate(gGT);
					MENUBOX_Hide(sdata->ptrActiveMenuBox);
					gGT->cooldownFromUnpauseUntilPause = 5;
				}
			}
		}
		else */if (gGT->cooldownFromUnpauseUntilPause == 0)
		{
			if
			(
				(((gGT->gameMode1 & (GAME_CUTSCENE | END_OF_RACE | MAIN_MENU)) == 0) && (sdata->ptrActiveMenuBox == 0)) &&
				(
					(
						sdata->AkuAkuHintState == 0 &&
						(
							(
								isTitleFlagFullyOnScreen = TitleFlag_IsFullyOnScreen(), isTitleFlagFullyOnScreen == 0
					 		)
						)
					)
				)
			)
			{
				if
				(
					(
						(
							(isGamepadConnected) &&
							(
								(
									HaveAllPads = MainFrame_HaveAllPads(gGT->numPlyrNextGame),
									(HaveAllPads & 0xffff) == 0 && ((gGT->gameMode1 & PAUSE_ALL) == 0)
								)
							)
						) ||
						(gGamepads->gamepad[0].buttonsTapped & BTN_SELECT) // only changes I made to this portion of GameLogic so far
					) &&
					(gGT->overlayIndex_Threads != -1)
				)
				{
					gGT->unknownFlags_1d44 = gGT->gameMode1 & 0x3e0020 | PAUSE_1;
					MyMainFreeze(gGT);
					gGT->cooldownfromPauseUntilUnpause = 5;
				}
			}
		}
	}
}

int Hello_Main()
{
	struct GameTracker* gGT = sdata->gGT;
	struct GamepadSystem* gGamepads = sdata->gGamepads;

	if (gGT->numPlyrCurrGame == 1)
	{
		/*
		if (sdata->gGamepads->gamepad[0].buttonsTapped & BTN_SELECT)
			isSelectPause = (isSelectPause + 1) % 2;
		*/

		if (isSelectPause)
		{
			DecalFont_DrawLine("and so it begins", 10, 190, FONT_SMALL, COCO_MAGENTA);

			//MENUBOX_DrawInnerRect(&r, 4, (u_long*)(gGT->backBuffer->otMem).startPlusFour);
		}

		daisy(gGT, gGamepads);
	}
}