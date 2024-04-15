#include <common.h>

extern struct RectMenu MyMenu;

// an extension of SelectPause
void MyMainFreeze(struct GameTracker* gGT)
{
	// Check conditions for pausing the game
	if
	(
		// if flag is not fully on screen
		(RaceFlag_IsFullyOnScreen() == 0) &&

		// if you are not drawing loading screen (after fully off screen)
		((gGT->renderFlags & 0x1000) == 0) &&

		// if aku is not giving a hint
		(sdata->AkuAkuHintState == 0) &&

		// if not in a menu, time trial, and not paused yet
		(sdata->ptrActiveMenu == 0 && (gGT->gameMode1 & (END_OF_RACE | PAUSE_ALL)) == 0) &&

		// not in Main Menu and not in Demo Mode
		(gGT->levelID != MAIN_MENU_LEVEL && ((gGT->gameMode1 & GAME_CUTSCENE) == 0 && gGT->boolDemoMode == 0)) &&

		// if game is not loading and not in a cutscene where you can't move
		((1 < (gGT->levelID - OXIDE_ENDING) && (sdata->load_inProgress == 0 && (!(gGT->gameMode2 & 4)))) == 0)
	)
	{
		// pause the game
		gGT->gameMode1 |= PAUSE_1;

		// make menu visible
		RECTMENU_Show(&MyMenu);

		// pause audio
		MainFrame_TogglePauseAudio(1);

		// OtherFX_Play to pause
		OtherFX_Play(1, 1);

		// Activate pause menu
		ElimBG_Activate(gGT);
	}
}

// handles stuff that happens when you press select to pause the game
void SelectPause(struct GameTracker* gGT, struct GamepadSystem* gGamepads)
{
	int isTitleFlagFullyOnScreen = 0;
	int isGamepadConnected = GAMEPAD_GetNumConnected(gGamepads);
	int HaveAllPads = 0;

	if (!(gGT->gameMode1 & END_OF_RACE))
	{
		if (gGT->cooldownFromUnpauseUntilPause == 0)
		{
			if
			(
				(((gGT->gameMode1 & (GAME_CUTSCENE | END_OF_RACE | MAIN_MENU)) == 0) && (sdata->ptrActiveMenu == 0)) &&
				(
					(
						sdata->AkuAkuHintState == 0 &&
						(
							(
								isTitleFlagFullyOnScreen = RaceFlag_IsFullyOnScreen(), isTitleFlagFullyOnScreen == 0
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
					gGT->cooldownfromPauseUntilUnpause = FPS_DOUBLE(5);
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
		SelectPause(gGT, gGamepads);
		//MenuInfodump(gGT);
	}
}

/*
void MenuInfodump(struct GameTracker* gGT)
{
	//string1[]  = "         ";
	char string2[]  = "         ";
	char string3[]  = "         ";
	char string4[]  = "         ";
	char string5[]  = "         ";
	char string6[]  = "         ";
	char string7[]  = "         ";
	char string8[]  = "         ";
	char string9[]  = "         ";
	char string10[] = "         ";
	char string11[] = "         ";
	char string12[] = "         ";
	char string13[] = "         ";
	char string14[] = "         ";
	char string15[] = "         ";
	char string16[] = "         ";
	char string17[] = "         ";
	char string18[] = "         ";
	struct RectMenu* m = &data.menuArcadeRace;

	//sprintf(string1,  "%d\n", m->stringIndexTitle);
	sprintf(string2,  "%d\n", m->posX_curr);
	sprintf(string3,  "%d\n", m->posY_curr);
	sprintf(string4,  "%X\n", m->unk1);
	sprintf(string5,  "%X\n", m->state);
	sprintf(string6,  "%X\n", m->rows);
	sprintf(string7,  "%X\n", m->funcPtr);
	sprintf(string8,  "%X\n", m->drawStyle);
	sprintf(string9,  "%d\n", m->posX_prev);
	sprintf(string10, "%d\n", m->posY_prev);
	sprintf(string11, "%d\n", m->rowSelected);
	sprintf(string12, "%X\n", m->unk1a);
	sprintf(string13, "%X\n", m->unk1e);
	sprintf(string14, "%d\n", m->width);
	sprintf(string15, "%d\n", m->height);
	sprintf(string16, "%X\n", m->ptrNextBox_InHierarchy);
	sprintf(string17, "%X\n", m->ptrPrevBox_InHierarchy);
	sprintf(string18, "%X\n", &data.menuArcadeRace);

	DecalFont_DrawLine("stringTitle:",  6, 10 + 10*0,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("posX_curr:",  6, 10 + 10*1,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("posY_curr:",  6, 10 + 10*2,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("unk1:",  6, 10 + 10*3,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("state:",  6, 10 + 10*4,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("rows:",  6, 10 + 10*5,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("funcPtr:",  6, 10 + 10*6,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("drawStyle:",  6, 10 + 10*7,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("posX_prev:",  6, 10 + 10*8,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("posY_prev:", 6, 10 + 10*9,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("rowSelected:", 6, 10 + 10*10, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("unk1a:", 6, 10 + 10*11, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("unk1e", 6, 10 + 10*12, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("width", 6, 10 + 10*13, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("height", 6, 10 + 10*14, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("ptrNextBox:", 6, 10 + 10*15, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("ptrPrevBox:", 6, 10 + 10*16, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("ptrCurrBox:", 6, 10 + 10*17, FONT_SMALL, COCO_MAGENTA);

	DecalFont_DrawLine(sdata->lngStrings[m->stringIndexTitle],  6 + 150, 10 + 10*0,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string2,  6 + 150, 10 + 10*1,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string3,  6 + 150, 10 + 10*2,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string4,  6 + 150, 10 + 10*3,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string5,  6 + 150, 10 + 10*4,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string6,  6 + 150, 10 + 10*5,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string7,  6 + 150, 10 + 10*6,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string8,  6 + 150, 10 + 10*7,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string9,  6 + 150, 10 + 10*8,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string10, 6 + 150, 10 + 10*9,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string11, 6 + 150, 10 + 10*10, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string12, 6 + 150, 10 + 10*11, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string13, 6 + 150, 10 + 10*12, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string14, 6 + 150, 10 + 10*13, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string15, 6 + 150, 10 + 10*14, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string16, 6 + 150, 10 + 10*15, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string17, 6 + 150, 10 + 10*16, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string18, 6 + 150, 10 + 10*17, FONT_SMALL, COCO_MAGENTA);
}
*/