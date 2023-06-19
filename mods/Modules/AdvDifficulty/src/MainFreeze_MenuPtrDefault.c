#include <common.h>

extern struct MenuBox AdvMainFreeze_Difficulty;

extern struct MenuBox arcadeMainFreeze_Difficulty;

void DECOMP_MainFreeze_MenuPtrDefault(struct MenuBox *mb)
{
	u_short stringID = mb->rows[mb->rowSelected].stringIndex;
	struct GameTracker *gGT = sdata->gGT;
	u_int gameMode = gGT->gameMode1;
	struct MenuBox *nextMenubox = NULL;

	if (gGT->cooldownfromPauseUntilUnpause != 0)
		return;

	if (mb->unk1e != 0)
	{
		mb->drawStyle &= 0xfeff;
		if (gGT->numPlyrCurrGame > 2)
			mb->drawStyle |= 0x100;
		if (!(gameMode & ADVENTURE_ARENA) || (mb->state & NEEDS_TO_CLOSE))
			return;
		if (LOAD_IsOpen_AdvHub() == 0)
			return;
		AH_Pause_Update();
		return;
	}

	if (mb->rowSelected < 0)
		return;

	switch (stringID)
	{
	case 14: // "OPTIONS"
		nextMenubox = &data.menuBox_optionsMenu_racingWheel;
		data.menuBox_optionsMenu_racingWheel.rowSelected = 8;
		break;
	case 11: // "AKU AKU HINTS"
	case 12: // "UKA UKA HINTS"
		nextMenubox = (struct MenuBox *)0x800b518c;
		break;
	case 3: // "QUIT"
		nextMenubox = &data.menuBox_quit;
		data.menuBox_quit.rowSelected = 1;
		break;
	case 7:
		nextMenubox = (gameMode & ARCADE_MODE) ? &arcadeMainFreeze_Difficulty : &AdvMainFreeze_Difficulty;
		break;
	}

	if (nextMenubox != NULL)
	{
		sdata->ptrDesiredMenuBox = nextMenubox;
		return;
	}

	gGT->cooldownFromUnpauseUntilPause = 5;
	MENUBOX_Hide(mb);
	MainFreeze_SafeAdvDestroy();

	switch (stringID)
	{
	case 1: // "RESTART"
	case 4: // "RETRY"
		gGT->gameMode1 &= ~PAUSE_1;
		if (TitleFlag_IsFullyOffScreen() == 1)
			TitleFlag_BeginTransition(1);
		if (!sdata->boolPlayGhost || !sdata->ptrGhostTapePlaying)
		{
			sdata->Loading.stage = -5;
			return;
		}
		data.characterIDs[1] = *(short *)((int)sdata->ptrGhostTapePlaying + 6);
		sdata->Loading.stage = -5;
		return;
	case 2: // "RESUME"
		ElimBG_Deactivate(gGT);
		gGT->gameMode1 &= ~PAUSE_1;
		MainFrame_TogglePauseAudio(0);
		OtherFX_Play(1, 1);
		return;
	case 5: // "CHANGE CHARACTER"
	case 6: // "CHANGE LEVEL"
		GhostBuffer_Destroy();
	case 10: // "CHANGE SETUP"
		sdata->mainMenuState = (stringID == 10) ? (stringID - 7) : (stringID - 4);
		sdata->Loading.OnBegin.AddBitsConfig0 |= MAIN_MENU;
		gGT->gameMode1 &= ~PAUSE_1;
		break;
	case 13: // "EXIT TO MAP"
		sdata->Loading.OnBegin.AddBitsConfig0 |= ADVENTURE_ARENA;
		sdata->Loading.OnBegin.RemBitsConfig0 |= (RELIC_RACE | CRYSTAL_CHALLENGE);
		sdata->Loading.OnBegin.RemBitsConfig8 |= 8;
		gGT->gameMode1 &= ~PAUSE_1;
		if ((gameMode & ADVENTURE_CUP) == 0)
		{
			if ((int)gameMode < 0) // BOSS Race
			{
				sdata->Loading.OnBegin.RemBitsConfig0 |= (ADVENTURE_BOSS | RELIC_RACE | CRYSTAL_CHALLENGE);
				sdata->Loading.OnBegin.AddBitsConfig8 |= 1;
			}
			MainRaceTrack_RequestLoad(gGT->prevLEV);
		}
		else
		{
			MainRaceTrack_RequestLoad(GEM_STONE_VALLEY);
			gGT->levelID = gGT->cup.cupID + 100;
		}
		return;
	}
	MainRaceTrack_RequestLoad(MAIN_MENU_LEVEL);
}
