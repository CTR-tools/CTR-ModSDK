#include <common.h>

// byte budget
// 920 / 1108

#define UDCTRM_MM_ROW_OPTIONS 6
#define UDCTRM_MM_ROW_SCRAPBOOK 7

extern struct RectMenu UDCTRM_OM_MenuProc;

void DECOMP_MM_MenuProc_Main(struct RectMenu *mainMenu)
{
	short rowLngID;
	struct GameTracker *gGT = sdata->gGT;

	// if scrapbook is unlocked, change "rows" to extended array
	if ((sdata->gameProgress.unlocks[1] & 0x10) != 0)
	{
		mainMenu->rows[UDCTRM_MM_ROW_OPTIONS].rowOnPressDown = UDCTRM_MM_ROW_SCRAPBOOK;
		mainMenu->rows[UDCTRM_MM_ROW_SCRAPBOOK].stringIndex = 564;
	}

	DECOMP_MM_ParseCheatCodes();
	MM_ToggleRows_Difficulty();
	MM_ToggleRows_PlayerCount();

	// If you are at the highest hierarchy level of main menu
	if (mainMenu->unk1e == 1)
	{
		MM_Title_MenuUpdate();

		if 
		(
			// main menu, "title" exists, and timer >= 230
			(D230.MM_State == 1) &&
			(D230.titleObj != NULL) &&
			(229 < D230.timerInTitle)
		)
		{
			// "TM" trademark string
			DecalFont_DrawLineOT
			(
				sdata->lngStrings[0x244],
				0x10e, 0x9c, FONT_SMALL, ORANGE,
				&gGT->backBuffer->otMem.startPlusFour[3]
			);
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
				gGT->demoCountdownTimer = 900;
			}
		}
	}

	MM_Title_Init();

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
	if ((mainMenu->unk1e != 0) || (mainMenu->rowSelected < 0))
	{
		// leave the function
		return;
	}

	// clear flags from game mode
	gGT->gameMode1 &= ~(BATTLE_MODE | ADVENTURE_MODE | TIME_TRIAL | ADVENTURE_ARENA | ARCADE_MODE | ADVENTURE_CUP);

	// clear more game mode flags
	gGT->gameMode2 &= ~(CUP_ANY_KIND);

	mainMenu->state |= ONLY_DRAW_TITLE;	

	// should only work in Arcade, and VS
	if ((gGT->gameMode2 & CHEAT_ONELAP) != 0) 
	{
		gGT->numLaps = 1;
	}
	
	// get LNG index of row selected
	rowLngID = mainMenu->rows[mainMenu->rowSelected].stringIndex;

	struct RectMenu *nextBox;

	switch (rowLngID)
	{
	case 76: // Adventure Mode
		gGT->numLaps = 3;
		gGT->gameMode1 |= ADVENTURE_MODE;
		gGT->gameMode2 &= ~(CHEAT_WUMPA | CHEAT_MASK | CHEAT_TURBO | CHEAT_ENGINE | CHEAT_BOMBS);
		nextBox = &D230.menuAdventure;
		break;

	case 77: // Time Trial
		D230.MM_State = EXITING_MENU;
		D230.desiredMenuIndex = 2;
		gGT->numPlyrNextGame = 1;
		gGT->numLaps = 3;
		gGT->gameMode1 |= TIME_TRIAL;
		gGT->gameMode2 &= ~(CHEAT_WUMPA | CHEAT_MASK | CHEAT_TURBO | CHEAT_ENGINE | CHEAT_BOMBS);
		break;

	case 78: // Arcade Mode
		gGT->gameMode1 |= ARCADE_MODE;
		nextBox = &D230.menuRaceType;
		break;

	case 79: // Versus
		nextBox = &D230.menuRaceType;
		break;

	case 80: // Battle
		D230.characterSelect_transitionState = 2;
		gGT->gameMode1 |= BATTLE_MODE;
		nextBox = &D230.menuPlayers2P3P4P;
		break;

	case 81: // High Score
		D230.desiredMenuIndex = 3;
		D230.MM_State = EXITING_MENU;
		break;

	case 564: // Scrapbook
		D230.desiredMenuIndex = 5;
		D230.MM_State = EXITING_MENU;
		break;

	/////////////////////////// CHANGED FOR UDCTRM ///////////////////////////
	// Options (new for this mod!)
	case 14: // Options
		nextBox = &UDCTRM_OM_MenuProc;
	/////////////////////////// END OF CHANGES     ///////////////////////////
	}
	if (nextBox)
	{
		mainMenu->ptrNextBox_InHierarchy = nextBox;
		mainMenu->state |= DRAW_NEXT_MENU_IN_HIERARCHY;
	}
}