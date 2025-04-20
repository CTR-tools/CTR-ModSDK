#include <common.h>
#include "utils.h"

static void InitGame();
static void OnLoadingEnd();
static void ResetStage();
static void OnGameplay();

u_int CTR_Main()
{
	__main();
	do
	{
		LOAD_NextQueuedFile();
		CDSYS_XAPauseAtEnd();
		HotReload();
		switch(sdata->mainGameState)
		{
			case STATE_INIT:
				InitGame();
				break;
			case STATE_LOADING_END:
				OnLoadingEnd();
				break;
			case STATE_RESET_STAGE:
				ResetStage();
				break;
			case STATE_GAMEPLAY:
				OnGameplay();
				break;
		}
	} while( true );
}

static void InitGame()
{
	struct GameTracker* gGT = sdata->gGT;
	struct GamepadSystem* gGS = sdata->gGamepads;

	SetVideoMode(0);
	ResetCallback();

	const int MEMPACK_SIZE = 0x200000; // 2MB
	MEMPACK_Init(MEMPACK_SIZE);
	LOAD_InitCD();
	RaceFlag_SetFullyOffScreen();

	ResetGraph(0);
	SetGraphDebug(0);
	MainInit_VRAMClear();
	SetDispMask(1);
	SetDefDrawEnv(&gGT->db[0].drawEnv, 0, 0, 0x200, 0xd8);
	SetDefDrawEnv(&gGT->db[1].drawEnv, 0, 0x128, 0x200, 0xd8);
	SetDefDispEnv(&gGT->db[0].dispEnv, 0, 0x128, 0x200, 0xd8);
	SetDefDispEnv(&gGT->db[1].dispEnv, 0, 0, 0x200, 0xd8);

	gGT->db[0].dispEnv.screen.x = 0;
	gGT->db[0].dispEnv.screen.y = 0xc;
	gGT->db[0].dispEnv.screen.w = 0x100;
	gGT->db[0].dispEnv.screen.h = 0xd8;

	gGT->db[1].dispEnv.screen.x = 0;
	gGT->db[1].dispEnv.screen.y = 0xc;
	gGT->db[1].dispEnv.screen.w = 0x100;
	gGT->db[1].dispEnv.screen.h = 0xd8;

	gGT->db[0].drawEnv.isbg = 1;
	gGT->db[0].drawEnv.r0 = 0;
	gGT->db[0].drawEnv.g0 = 0;
	gGT->db[0].drawEnv.b0 = 0;

	gGT->db[1].drawEnv.isbg = 1;
	gGT->db[1].drawEnv.r0 = 0;
	gGT->db[1].drawEnv.g0 = 0;
	gGT->db[1].drawEnv.b0 = 0;

	gGT->battleLifeLimit = 5;
	gGT->constVal_9000 = 9000; // counter?
	gGT->numLaps = 3;
	gGT->battleSetup.enabledWeapons |= 0x34de;
	gGT->numPlyrCurrGame = 1;
	gGT->numPlyrNextGame = 1;
	*(u_int*)&gGT->battleSetup.teamOfEachPlayer = 0x3020100;
	gGT->trafficLightsTimer = SECONDS(-1);

	Timer_Init();
	EnterCriticalSection();
	DrawSyncCallback(&MainDrawCb_DrawSync);
	ExitCriticalSection();

	MEMCARD_InitCard();
	VSync(0);
	GAMEPAD_Init(gGS);
	VSync(0);
	GAMEPAD_GetNumConnected(gGS);

	sdata->ptrBigfile1 = LOAD_ReadDirectory(rdata.s_PathTo_Bigfile);
	LOAD_LangFile((int)sdata->ptrBigfile1, 1); // English = 1
	GAMEPROG_NewGame_OnBoot();
	gGT->overlayIndex_null_notUsed = 0;
	gGT->levelID = MAIN_MENU_LEVEL;

	InitGeom();
	SetGeomOffset(0x100, 0x78);	// width/2, height/2
	SetGeomScreen(0x140);		// "distance" to screen, alters FOV
	RenderBucket_InitDepthGTE();
	Vector_BakeMatrixTable();

	gGT->swapchainIndex = 0;
	gGT->backBuffer = &gGT->db[0];

	gGT->overlayIndex_EndOfRace = 0xff;
	gGT->overlayIndex_LOD = 0xff;
	gGT->overlayIndex_Threads = 0xff;

	PutDispEnv(&gGT->db[1].dispEnv);
	PutDrawEnv(&gGT->db[1].drawEnv);
	DrawSync(0);
	howl_InitGlobals(data.kartHwlPath); // \SOUNDS\KART.HWL;1
	VSyncCallback(MainDrawCb_Vsync);
	DecalGlobal_Clear(gGT);

	int vramSize;
	LOAD_VramFile(sdata->ptrBigfile1, 0x102, 0, &vramSize, 0xffffffff); // shared.vrm in the last two tex pages top right

	sdata->mainGameState = STATE_GAMEPLAY;
	sdata->Loading.stage = 0; // start loading
	gGT->gameMode1 |= LOADING;
	gGT->clockEffectEnabled &= 0xfffe;

	LOAD_AppendQueue(sdata->ptrBigfile1, LT_VRAM, 222, CUSTOM_VRAM_ADDR, 0);
	LOAD_AppendQueue(sdata->ptrBigfile1, LT_DRAM, 221, CUSTOM_MAP_PTR_ADDR, 0);

	char* currDriver = DRIVER_ADDR;
	for (int i = 0; i < 15; i++) // load every character except oxide. oxide will come with time trial pack
	{
		int fileSize;
		LOAD_ReadFile(sdata->ptrBigfile1, LT_DRAM, BI_RACERMODELHI + i, currDriver, &fileSize, 0);
		int* pMap = (int*) (currDriver + 4 + (*(int*)currDriver));
		LOAD_RunPtrMap(currDriver + 4, pMap + 1, *pMap >> 2);
		struct Model** g_charModelPtrs = CHAR_MODEL_PTRS;
		g_charModelPtrs[i] = (struct Model*) (currDriver + 4);
		currDriver += fileSize;
	}
}

static void OnLoadingEnd()
{
	struct GameTracker* gGT = sdata->gGT;
	struct GamepadSystem* gGS = sdata->gGamepads;
	ElimBG_Deactivate(gGT);
	MainStats_RestartRaceCountLoss();
	Voiceline_ClearTimeStamp();

	// Disable End-Of-Race menu
	gGT->gameMode1 &= ~END_OF_RACE;
	if (gGT->levelID == MAIN_MENU_LEVEL)
	{
		if (RaceFlag_IsFullyOffScreen() != 0) { RaceFlag_SetFullyOnScreen(); }
	}
	else
	{
		if (RaceFlag_IsFullyOnScreen() != 0) { RaceFlag_BeginTransition(2); }
	}
	DropRain_Reset(gGT);
	GAMEPROG_GetPtrHighScoreTrack();
	MainInit_FinalizeInit(gGT);
	GAMEPAD_GetNumConnected(gGS);
	sdata->boolSoundPaused = 0;
	VehBirth_EngineAudio_AllPlayers();

	const int AUDIO_INTRO_CUSTSCENE = 9;
	const int AUDIO_TRAFFIC_LIGHTS = 10;
	if (gGT->levelID < NITRO_COURT) { Audio_SetState_Safe(AUDIO_INTRO_CUSTSCENE); }
	else if (gGT->levelID >= NITRO_COURT && gGT->levelID < GEM_STONE_VALLEY) { Audio_SetState_Safe(AUDIO_TRAFFIC_LIGHTS); }
	sdata->mainGameState = STATE_GAMEPLAY;
	gGT->clockEffectEnabled &= 0xfffe;

	if (sdata->gGT->levelID == CUSTOM_LEVEL_ID) { sdata->ptrActiveMenu = 0; }
}

static void ResetStage()
{
	Audio_SetState_Safe(1);
	MEMPACK_PopState();
	LevInstDef_RePack(sdata->gGT->level1->ptr_mesh_info, 0);
	sdata->mainGameState = STATE_LOADING_END;
}

static void OnGameplay()
{
	struct GameTracker* gGT = sdata->gGT;
	struct GamepadSystem* gGS = sdata->gGamepads;

	if (sdata->Loading.stage != -1) // if loading, or gameplay interrupted
	{
		int finishedLoading = 0;
		if ((RaceFlag_IsFullyOnScreen() == 1) || (gGT->levelID == NAUGHTY_DOG_CRATE) || (sdata->pause_state != 0))
		{
			gGT->gameMode1 |= LOADING;
		}

		gGT->elapsedTimeMS = FPS_HALF(32);
		int loadingStage = sdata->Loading.stage;
		if (loadingStage == -6) // if loading VLC
		{
			if (sdata->bool_IsLoaded_VlcTable != 1) { return; }
			finishedLoading = 1;
		}
		else if (loadingStage == -5) // if restarting race
		{
			if (RaceFlag_IsFullyOnScreen() == 1)
			{
				sdata->mainGameState = STATE_RESET_STAGE;
				sdata->Loading.stage = -1; // no loading, and no interruption
				gGT->gameMode1 &= ~LOADING; // Turn off the "Loading..." flag
				return;
			}
		}
		else if (loadingStage == -4) // waiting for checkered flag to cover screen
		{
			unsigned int RemBitsConfig8 = sdata->Loading.OnBegin.RemBitsConfig8;
			unsigned int AddBitsConfig8 = sdata->Loading.OnBegin.AddBitsConfig8;
			unsigned int RemBitsConfig0 = sdata->Loading.OnBegin.RemBitsConfig0;
			unsigned int AddBitsConfig0 = sdata->Loading.OnBegin.AddBitsConfig0;
			if (RaceFlag_IsFullyOnScreen() == 1)
			{
				gGT->hudFlags &= 0xf7;
				int gameMode1 = gGT->gameMode1;
				int gameMode2 = gGT->gameMode2;
				sdata->Loading.OnBegin.AddBitsConfig0 = 0;
				sdata->Loading.OnBegin.RemBitsConfig0 = 0;
				sdata->Loading.OnBegin.AddBitsConfig8 = 0;
				sdata->Loading.OnBegin.RemBitsConfig8 = 0;
				gGT->gameMode2 = gameMode2 | AddBitsConfig8;
				gGT->gameMode1 = gameMode1 | AddBitsConfig0;
				gGT->gameMode1 = (gameMode1 | AddBitsConfig0) & ~RemBitsConfig0;
				gGT->gameMode2 = (gameMode2 | AddBitsConfig8) & ~RemBitsConfig8;
				MainRaceTrack_StartLoad(sdata->Loading.Lev_ID_To_Load);
			}
			else if (RaceFlag_IsFullyOffScreen() == 1) { RaceFlag_BeginTransition(1); }
		}
		else // if something is being loaded
		{
			sdata->Loading.stage = LOAD_TenStages(gGT, loadingStage, sdata->ptrBigfile1);

			// If just finished loading stage 9
			if (sdata->Loading.stage == -2)
			{
				if ((gGT->levelID == MAIN_MENU_LEVEL) || (gGT->levelID == SCRAPBOOK))
				{
					MainLoadVLC();
					sdata->Loading.stage = -6; // start loading VLC
					return;
				}
				finishedLoading = 1;
			}
		}
		if (finishedLoading)
		{
			sdata->Loading.stage = -1;
			sdata->mainGameState = STATE_LOADING_END;
			gGT->gameMode1 &= ~LOADING;
			return;
		}
	}

// =========== Main Game Loop ======================

	if ((gGT->trafficLightsTimer > SECONDS(-1)) && ((gGT->gameMode1 & (START_OF_RACE | PAUSE_ALL)) == 0))
	{
		gGT->trafficLightsTimer -= gGT->elapsedTimeMS;
		if (gGT->trafficLightsTimer < SECONDS(-1)) { gGT->trafficLightsTimer = SECONDS(-1); }
	}

	sdata->frameCounter++;
	GAMEPAD_ProcessAnyoneVars(gGS);
	MainFrame_ResetDB(gGT);

	if (gGT->boolDemoMode != 0)
	{
		gGT->hudFlags &= 0xfe; // turn off HUD
		if (sdata->Loading.stage == -1) // not loading
		{
			gGT->demoCountdownTimer--;
			if (gGT->demoCountdownTimer < 1)
			{
				gGT->boolDemoMode = 0;
				gGT->numPlyrNextGame = 1;
				sdata->mainMenuState = 0;
				MainRaceTrack_RequestLoad(MAIN_MENU_LEVEL);
			}
			else if (gGS->anyoneHeldCurr != 0)
			{
				gGT->boolDemoMode = 0;
				MainRaceTrack_RequestLoad(MAIN_MENU_LEVEL);
			}

			int posY = 100;
			if (gGT->numPlyrCurrGame == 1) { posY = 35; }
			// "DEMO MODE\rPRESS ANY BUTTON TO EXIT"
			DecalFont_DrawMultiLine(sdata->lngStrings[0x8c0 / 4], 0x100, posY, 0x200, 2, 0xffff8000);
		}
	}

	if ((gGT->gameMode1 & LOADING) == 0) { MainFrame_GameLogic(gGT, gGS); }
	if (gGT->boolDemoMode != 0) { gGT->hudFlags &= 0xfe; } // Turn off HUD
	gGT->vSync_between_drawSync = 0;
	MainFrame_RenderFrame(gGT, gGS);
	if (sdata->boolDraw3D_AdvMask != 0) { AH_MaskHint_Update(); }
}