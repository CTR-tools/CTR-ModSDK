#include <common.h>

extern struct RectMenu AdvMainFreeze_Difficulty;
extern struct RectMenu arcadeMainFreeze_Difficulty;

#if BUILD == UsaRetail
struct RectMenu * menu_hints = 0x800b518c; // in 232
#endif
#if BUILD == EurRetail
struct RectMenu * menu_hints = 0x800b5638;
#endif
#if BUILD == JpnRetail
struct RectMenu * menu_hints = 0x800b86a0;
#endif

void DECOMP_MainFreeze_MenuPtrDefault(struct RectMenu* menu)
{
	struct GameTracker *gGT = sdata->gGT;
	struct RectMenu *nextMenu = NULL;
	u_int gameMode = gGT->gameMode1;
	u_short stringID = menu->rows[menu->rowSelected].stringIndex;
	u_char level_to_load;

	if (gGT->cooldownfromPauseUntilUnpause != 0)
		return;

	if (menu->unk1e != 0)
	{
		menu->drawStyle &= 0xfeff;
		if (gGT->numPlyrCurrGame > 2)
			menu->drawStyle |= 0x100;
		if (!(gameMode & ADVENTURE_ARENA) || (menu->state & NEEDS_TO_CLOSE))
			return;
		if (LOAD_IsOpen_AdvHub() == 0)
			return;
		AH_Pause_Update();
		return;
	}

	if (menu->rowSelected < 0)
		return;

	switch (stringID)
	{
	case 14: // "OPTIONS"
		nextMenu = &data.menuRacingWheelConfig;
		data.menuRacingWheelConfig.rowSelected = 8;
		break;
	case 11: // "AKU AKU HINTS"
	case 12: // "UKA UKA HINTS"
		nextMenu = menu_hints;
		break;
	case 3: // "QUIT"
		nextMenu = &data.menuQuit;
		data.menuQuit.rowSelected = 1;
		break;
	case 7:
		nextMenu = (gameMode & ARCADE_MODE) ? &arcadeMainFreeze_Difficulty : &AdvMainFreeze_Difficulty;
		break;
	}

	if (nextMenu != NULL)
	{
		sdata->ptrDesiredMenu = nextMenu;
		return;
	}

	gGT->cooldownFromUnpauseUntilPause = FPS_DOUBLE(5);
	RECTMENU_Hide(mb);
	gGT->gameMode1 &= ~PAUSE_1;
	MainFreeze_SafeAdvDestroy();

	switch (stringID)
	{
	case 1: // "RESTART"
	case 4: // "RETRY"
		sdata->Loading.stage = -5;
		if (RaceFlag_IsFullyOffScreen() == 1)
			RaceFlag_BeginTransition(1);
		if (!sdata->boolReplayHumanGhost || !sdata->ptrGhostTapePlaying)
			return;
		data.characterIDs[1] = sdata->ptrGhostTapePlaying->characterID;
		return;
	case 2: // "RESUME"
		ElimBG_Deactivate(gGT);
		MainFrame_TogglePauseAudio(0);
		OtherFX_Play(1, 1);
		return;
	case 5: // "CHANGE CHARACTER"
	case 6: // "CHANGE LEVEL"
		GhostTape_Destroy();
	case 10: // "CHANGE SETUP"
		sdata->mainMenuState = (stringID == 10) ? (stringID - 7) : (stringID - 4);
		sdata->Loading.OnBegin.AddBitsConfig0 |= MAIN_MENU;
		break;
	case 13: // "EXIT TO MAP"
		sdata->Loading.OnBegin.AddBitsConfig0 |= ADVENTURE_ARENA;
		sdata->Loading.OnBegin.RemBitsConfig0 |= (RELIC_RACE | CRYSTAL_CHALLENGE);
		sdata->Loading.OnBegin.RemBitsConfig8 |= TOKEN_RACE;
		if ((gameMode & ADVENTURE_CUP) == 0)
		{
			if ((int)gameMode < 0) // BOSS Race
			{
				sdata->Loading.OnBegin.RemBitsConfig0 |= ADVENTURE_BOSS;
				sdata->Loading.OnBegin.AddBitsConfig8 |= 1;
			}
			level_to_load = gGT->prevLEV;
		}
		else
		{
			level_to_load = GEM_STONE_VALLEY;
			gGT->levelID = gGT->cup.cupID + 100;
		}
	default:
		break;
	}
	MainRaceTrack_RequestLoad(level_to_load);
}
