#include <common.h>

void StateZero();

//#define FastBoot

u_int DECOMP_main()
{
	u_int AddBitsConfig0;
	u_int RemBitsConfig0;
	u_int AddBitsConfig8;
	u_int RemBitsConfig8;
	int iVar8;
	u_int gameMode1;
	u_int gameMode2;
	u_int uVar12;

	struct GameTracker* gGT;
	gGT = sdata->gGT;

	struct GamepadSystem* gGS;
	gGS = sdata->gGamepads;

#ifndef REBUILD_PS1
	__main();
#endif

	do
	{
		#if 0
		// wont happen under normal conditions
		if (sdata->mainGameState == 5)
		{
			MainKillGame_StopCTR();
			return 0;
		}
		#endif

		DECOMP_LOAD_NextQueuedFile();
		DECOMP_CDSYS_XAPauseAtEnd();

		switch(sdata->mainGameState)
		{
			// Initialize Game (happens once)
			case 0:
				StateZero();
				break;

			// Happens on first frame that loading ends
			case 1:

				DECOMP_ElimBG_Deactivate(gGT);

#ifndef REBUILD_PS1
				MainStats_RestartRaceCountLoss();
				Voiceline_ClearTimeStamp();
#endif

				// Disable End-Of-Race menu
				gGT->gameMode1 &= ~END_OF_RACE;

				if (gGT->levelID == MAIN_MENU_LEVEL)
				{
					if (DECOMP_RaceFlag_IsFullyOffScreen() != 0)
						DECOMP_RaceFlag_SetFullyOnScreen();
				}

				else
				{
					if (DECOMP_RaceFlag_IsFullyOnScreen() != 0)
						DECOMP_RaceFlag_BeginTransition(2);
				}

				DECOMP_DropRain_Reset(gGT);
				DECOMP_GAMEPROG_GetPtrHighScoreTrack();
				DECOMP_MainInit_FinalizeInit(gGT);
				DECOMP_GAMEPAD_GetNumConnected(gGS);

				sdata->boolSoundPaused = 0;
				DECOMP_VehBirth_EngineAudio_AllPlayers();

				// 9 = intro cutscene
				// 10 = traffic lights
				// 11 = racing

				// Arcade-Style track starts with intro cutscene
				uVar12 = 9;

				if
				(
					// If Level ID is less than 18, it's one of the race tracks
					(gGT->levelID < 18) ||
					(
						// Battle-Style track starts with traffic lights
						uVar12 = 10,
						// Level ID >= 18 and < 23
						// Battle tracks
						gGT->levelID - 18 < 7
					)
				)
				{
					DECOMP_Audio_SetState_Safe(uVar12);
				}
				sdata->mainGameState = 3;
				gGT->clockEffectEnabled &= 0xfffe;
				break;

			// Reset stage, reset music
			case 2:
				DECOMP_Audio_SetState_Safe(1);
				DECOMP_MEMPACK_PopState();

				// ignore threads, because we PopState,
				// so the threadpool will reset anyway
				DECOMP_LevInstDef_RePack(gGT->level1->ptr_mesh_info, 0);

				sdata->mainGameState = 1;
				break;

			// Main Gameplay Update
			// Makes up all normal interaction with the game
			case 3:
				// if loading, or gameplay interrupted
				if (sdata->Loading.stage != -1)
				{
					if
					(
						(DECOMP_RaceFlag_IsFullyOnScreen() == 1) ||
						(gGT->levelID == NAUGHTY_DOG_CRATE) ||
						(sdata->pause_state != 0)
					)
					{
						gGT->gameMode1 |= LOADING;
					}

					iVar8 = sdata->Loading.stage;

					// elapsed milliseconds per frame, locked 32 here
					// impacts speed of flag wave during "loading...", but does not impact speed of flying text
					gGT->elapsedTimeMS = FPS_HALF(32);

					// if loading VLC
					if (iVar8 == -6)
					{
						// if VLC is not loaded, quit
						// we know when it's done from a load callback
						if (sdata->bool_IsLoaded_VlcTable != 1) break;

						// if == 1, finish the loading
						goto FinishLoading;
					}

					// if restarting race
					if (iVar8 == -5)
					{
						if (DECOMP_RaceFlag_IsFullyOnScreen() == 1)
						{
							// reinitialize world,
							// does not reinitialize pools
							sdata->mainGameState = 2;

							// no loading, and no interruption
							sdata->Loading.stage = -1;

							// Turn off the "Loading..." flag
							gGT->gameMode1 &= ~LOADING;
							break;
						}

						// if not fully on-screen, do not BREAK,
						// keep rendering the scene
					}

					// if waiting for checkered flag to cover screen,
					// right before loading the next requested level
					else if (iVar8 == -4)
					{
						RemBitsConfig8 = sdata->Loading.OnBegin.RemBitsConfig8;
						AddBitsConfig8 = sdata->Loading.OnBegin.AddBitsConfig8;
						RemBitsConfig0 = sdata->Loading.OnBegin.RemBitsConfig0;
						AddBitsConfig0 = sdata->Loading.OnBegin.AddBitsConfig0;

						if (DECOMP_RaceFlag_IsFullyOnScreen() == 1)
						{
							sdata->Loading.OnBegin.AddBitsConfig0 = 0;
							sdata->Loading.OnBegin.RemBitsConfig0 = 0;
							sdata->Loading.OnBegin.AddBitsConfig8 = 0;
							sdata->Loading.OnBegin.RemBitsConfig8 = 0;

							gameMode2 = gGT->gameMode2;

							gGT->hudFlags &= 0xf7;

							gameMode1 = gGT->gameMode1;
							gGT->gameMode2 = gameMode2 | AddBitsConfig8;
							gGT->gameMode1 = gameMode1 | AddBitsConfig0;
							gGT->gameMode1 = (gameMode1 | AddBitsConfig0) & ~RemBitsConfig0;
							gGT->gameMode2 = (gameMode2 | AddBitsConfig8) & ~RemBitsConfig8;

							DECOMP_MainRaceTrack_StartLoad(sdata->Loading.Lev_ID_To_Load);
						}

						else if (DECOMP_RaceFlag_IsFullyOffScreen() == 1)
							DECOMP_RaceFlag_BeginTransition(1);

						// do not BREAK,
						// keep rendering the scene
					}

					// if something is being loaded
					else
					{
						sdata->Loading.stage = DECOMP_LOAD_TenStages(gGT, iVar8, sdata->ptrBigfile1);

						// If just finished loading stage 9
						if (sdata->Loading.stage == -2)
						{
							if
							(
								(gGT->levelID == MAIN_MENU_LEVEL) ||
								(gGT->levelID == SCRAPBOOK)
							)
							{
								DECOMP_MainLoadVLC();

								// start loading VLC (scroll up to iVar8 == -6)
								sdata->Loading.stage = -6;
								break;
							}

FinishLoading:
							// loading is finished,
							// initialize world and pools,
							// remove LOADING... flag from gGT
							sdata->Loading.stage = -1;
							sdata->mainGameState = 1;
							gGT->gameMode1 &= ~LOADING;
							break;
						}

						// else, do not BREAK,
						// keep rendering the scene
						// which is the checkered flag
					}
				}

				// sync music, in case loading is too fast,
				// https://www.youtube.com/watch?v=rzJcVdm4ny4
				#ifndef REBUILD_PS1
				#if 1 // not part of the OG game
				else
				{
					if(gGT->levelID == NAUGHTY_DOG_CRATE)
					{
						// wait around
						int GetSongTime();
						while(GetSongTime() < 0x11c0)
						{}
					}
				}
				#endif
				#endif

// =========== Main Game Loop ======================

				if
				(
					(
						// Check value of traffic lights
						(-960 < gGT->trafficLightsTimer) &&
						// if not drawing intro race cutscene and if not paused
						((gGT->gameMode1 & (START_OF_RACE | PAUSE_ALL)) == 0)
					) &&
					(
						// amount of milliseconds on Traffic Lights - elapsed milliseconds per frame, ~32
						iVar8 = gGT->trafficLightsTimer - gGT->elapsedTimeMS,
						// decrease amount of time on Traffic Lights
						gGT->trafficLightsTimer = iVar8,
						// if countdown has gone down far enough for traffic lights to go off-screen
						iVar8 < -960
					)
				)
				{
					// set a floor value, so countdown can't go farther negative
					gGT->trafficLightsTimer = 0xfffffc40;
				}

				// frame counter, not represented in common.h currently
				sdata->frameCounter++;

				// Process all gamepad input
				DECOMP_GAMEPAD_ProcessAnyoneVars(gGS);

				#ifdef FastBoot
				// disable spawn
				gGT->Debug_ToggleNormalSpawn = 0;

				// disable maskgrab_init
				*(int*)0x800671b0 = 0x3E00008;
				*(int*)0x800671b4 = 0;

				if (
					// first frame of spawn
					(sdata->gGT->elapsedEventTime == 0) ||

					// L2 tap
					(gGS->gamepad[0].buttonsTapped & BTN_L2)
					)
				{
					gGT->hudFlags |= 1;

					gGT->drivers[0]->posCurr.x = 0x2e3152;
					gGT->drivers[0]->posCurr.y = 0x5f96;
					gGT->drivers[0]->posCurr.z = 0xfff59bd1;
					gGT->drivers[0]->angle = 0x5af;

					gGT->drivers[0]->heldItemID = 9;

					gGT->drivers[1]->posCurr.x = 0x2f8d79;
					gGT->drivers[1]->posCurr.y = 0x5f70;
					gGT->drivers[1]->posCurr.z = 0xffedde6f;
					gGT->drivers[1]->angle = 0x5af;
				}
				#endif

				// Start new frame (ClearOTagR)
				DECOMP_MainFrame_ResetDB(gGT);

				if
				(
					// If you're in Demo Mode
					(gGT->boolDemoMode != 0) &&

					(
						// Turn off HUD
						gGT->hudFlags &= 0xfe,
						// if game is not loading
						sdata->Loading.stage == -1
					)
				)
				{
					// All this code is for the 30-second timer within Demo Mode
					// To see 30-second timer in Main Menu, go to FUN_00001604 in 230.c
					// pressing (or holding) any button sets it to zero

					gGT->demoCountdownTimer--;

					// check to see if time ran out
					if (gGT->demoCountdownTimer < 1)
					{
						// leave demo mode, go to main menu
						gGT->boolDemoMode = 0;
						gGT->numPlyrNextGame = 1;
						sdata->mainMenuState = 0;

						LAB_8003ce08:
						DECOMP_MainRaceTrack_RequestLoad(MAIN_MENU_LEVEL);
					}

					// if time remains on the timer
					else
					{
						// if any button is pressed by anyone
						if (gGS->anyoneHeldCurr != 0)
						{
							// leave demo mode
							gGT->boolDemoMode = 0;
							goto LAB_8003ce08;
						}
					}

					// if numPlyrCurrGame is 1
					if (gGT->numPlyrCurrGame == 1)
					{
						// Draw text near top of screen
						uVar12 = 0x23;
					}

					// if this is multiplayer
					else
					{
						// draw text halfway to top of screen
						uVar12 = 100;
					}

					// "DEMO MODE\rPRESS ANY BUTTON TO EXIT"
					DECOMP_DecalFont_DrawMultiLine(sdata->lngStrings[0x8c0 / 4], 0x100, uVar12, 0x200, 2, 0xffff8000);
				}

				if ((gGT->gameMode1 & LOADING) == 0)
				{
					DECOMP_MainFrame_GameLogic(gGT, gGS);
				}

				// If you are in demo mode
				if (gGT->boolDemoMode != '\0')
				{
					// Turn off HUD
					gGT->hudFlags &= 0xfe;
				}

				// reset vsync calls between drawsync
				gGT->vSync_between_drawSync = 0;





// temporary, no camera thread yet
#ifdef REBUILD_PS1

				gGT->hudFlags &= 0xfe;
				if(gGT->levelID < 0x1C)
					gGT->hudFlags |= 1;

				if (
						(gGT->level1 != 0) && // for ND Box
						(gGT->levelID != MAIN_MENU_LEVEL) &&
						(gGT->levelID != ADVENTURE_CHARACTER_SELECT)
					)
				{
					// placeholder until 233 is done
					if (gGT->levelID == NAUGHTY_DOG_CRATE)
					{
						gGT->pushBuffer[0].pos[0] = 0;
						gGT->pushBuffer[0].pos[1] = 0x1c2;
						gGT->pushBuffer[0].pos[2] = 0x1dd;
						gGT->pushBuffer[0].rot[0] = 0x7dd;
						gGT->pushBuffer[0].rot[1] = 0;
						gGT->pushBuffer[0].rot[2] = 0;

						// wait 5 seconds
						if(gGT->timer > 30*5)
							DECOMP_MainRaceTrack_RequestLoad(MAIN_MENU_LEVEL);
					}

					int tap = gGS->gamepad[0].buttonsTapped;
					int held = gGS->gamepad[0].buttonsHeldCurrFrame;

					if (
							// on adv hub, freeze camera for a few frames
							(gGT->trafficLightsTimer > 3800) ||

							// on race tracks, wait for full countdown
							(
								(gGT->trafficLightsTimer > 0) &&
								(gGT->levelID < GEM_STONE_VALLEY)
							)
						)
					{
						// temporary workaround, cause if state
						// is not zero, then loading screen breaks
						// if we pause and quit
						sdata->XA_State = 0;

						for(int k = 0; k < gGT->numPlyrCurrGame; k++)
						{
							gGT->pushBuffer[k].pos[0] = gGT->level1->DriverSpawn[k].pos[0];
							gGT->pushBuffer[k].pos[1] = gGT->level1->DriverSpawn[k].pos[1] + 0x20;
							gGT->pushBuffer[k].pos[2] = gGT->level1->DriverSpawn[k].pos[2];

							gGT->pushBuffer[k].rot[0] = gGT->level1->DriverSpawn[k].rot[0] + 0x800;
							gGT->pushBuffer[k].rot[1] = gGT->level1->DriverSpawn[k].rot[1] - 0x400;
							gGT->pushBuffer[k].rot[2] = 0; // required

							// move backwards a little
							gGT->pushBuffer[k].pos[2] += (0xc0 * DECOMP_MATH_Cos(gGT->pushBuffer[k].rot[1])) >> 0xC;
							gGT->pushBuffer[k].pos[0] += (0xc0 * DECOMP_MATH_Sin(gGT->pushBuffer[k].rot[1])) >> 0xC;

						}
					}

					else if ((gGT->gameMode1 & PAUSE_ALL) == 0)
					{
						// temporary workaround, cause XA IRQ doesn't happen,
						// must be zero for level music to work
						sdata->XA_State = 0;

						int dirUD = 0;
						int dirLR = 0;
						int dirCT = 0;

						if ((held & BTN_UP) != 0) dirUD = -1;
						if ((held & BTN_DOWN) != 0) dirUD = 1;
						gGT->pushBuffer[0].pos[2] += (dirUD * FPS_HALF(0x40) * DECOMP_MATH_Cos(gGT->pushBuffer[0].rot[1])) >> 0xC;
						gGT->pushBuffer[0].pos[0] += (dirUD * FPS_HALF(0x40) * DECOMP_MATH_Sin(gGT->pushBuffer[0].rot[1])) >> 0xC;

						if ((held & BTN_LEFT) != 0) dirLR = 1;
						if ((held & BTN_RIGHT) != 0) dirLR = -1;
						gGT->pushBuffer[0].rot[1] += dirLR * FPS_HALF(0x20);

						if ((held & BTN_CROSS) != 0) dirCT = -1;
						if ((held & BTN_TRIANGLE) != 0) dirCT = 1;
						gGT->pushBuffer[0].pos[1] += dirCT * FPS_HALF(0x20);

						if ((tap & BTN_R1) != 0)
						{
							if(gGT->drivers[0]->heldItemID == 0xF)
							{
								gGT->drivers[0]->heldItemID = 0;
								gGT->drivers[0]->numHeldItems = 1;
							}

							else
							{
								gGT->drivers[0]->heldItemID++;
							}
						}

						if ((tap & BTN_L1) != 0)
						{
							if(gGT->drivers[0]->heldItemID != 0xF)
								gGT->drivers[0]->heldItemID--;

							if(gGT->drivers[0]->heldItemID < 0)
								gGT->drivers[0]->heldItemID = 0;
						}
					}

					if ((held & BTN_START) != 0)
					{
						if((gGT->gameMode1 & GAME_CUTSCENE) != 0)
						{
							DECOMP_MainRaceTrack_RequestLoad(MAIN_MENU_LEVEL);
						}
					}
				}
#endif





#ifdef REBUILD_PC
				PsyX_BeginScene();
#endif
				DECOMP_MainFrame_RenderFrame(gGT, gGS);
#ifdef REBUILD_PC
				PsyX_EndScene();
				int NikoCalcFPS();
				NikoCalcFPS();
#endif

				// if mask is talking in Adventure Hub
				if (sdata->boolDraw3D_AdvMask != 0)
				{
					DECOMP_AH_MaskHint_Update();
				}
				break;

			#if 0
			// In theory, this is left over from the demos,
			// which would "timeout" and restart after sitting idle
			case 4:

				// erase all data past the
				// last 3 bookmarks, if there
				// that many exist
				MEMPACK_PopState();
				MEMPACK_PopState();
				MEMPACK_PopState();

				CTR_ErrorScreen(0, 0, 0);
				Music_Stop();

				// clear backup, destroy music, destroy all fx
				howl_StopAudio(1, 1, 1);
				Bank_DestroyAll();
				howl_Disable();

				DECOMP_GAMEPAD_SetMainMode(gGS);

				// Set vsync to 2 FPS
				VSync(30);

				// reboot game
				sdata->mainGameState = 0;
			#endif
		}
	} while( true );
}

#ifndef REBUILD_PS1
__attribute__((optimize("O0")))
int GetSongTime()
{
	return sdata->songPool[0].timeSpentPlaying;
}
#endif

// by separating this, it can be
// overwritten dynamically (oxide fix)
void StateZero()
{
	u_short *clockEffect;
	int vramSize;

	struct GameTracker* gGT;
	gGT = sdata->gGT;

	struct GamepadSystem* gGS;
	gGS = sdata->gGamepads;

	// already zero, part of BSS
	#if 0
	memset(gGT, 0, sizeof(struct GameTracker));
	#endif

	// for modding
	void ModsMain();
	ModsMain();

	// Set Video Mode to NTSC
	SetVideoMode(0);
	ResetCallback();

	#ifndef USE_RAMEX
	#define MEMPACK_SIZE 0x200000 // 2mb
	#else
	#define MEMPACK_SIZE 0x800000 // 8mb
	#endif

	DECOMP_MEMPACK_Init(MEMPACK_SIZE);
	DECOMP_LOAD_InitCD();
	DECOMP_RaceFlag_SetFullyOffScreen();

	ResetGraph(0);
	SetGraphDebug(0);

#ifndef REBUILD_PS1
	DECOMP_MainInit_VRAMClear();
#endif

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

	// default number of lives in battle
	// this is left over from prototypes, useless in retail
	gGT->battleLifeLimit = 5;

	// 30 second counter?
	gGT->constVal_9000 = 9000;

	// set lap count to 3
	gGT->numLaps = 3;

	gGT->battleSetup.enabledWeapons |= 0x34de;
	gGT->numPlyrCurrGame = 1;
	gGT->numPlyrNextGame = 1;
	*(u_int*)&gGT->battleSetup.teamOfEachPlayer = 0x3020100;

	// traffic light countdown timer, set to negative one second
	gGT->trafficLightsTimer = 0xfffffc40;

	DECOMP_Timer_Init();

	// set callback and save callback
	EnterCriticalSection();
	sdata->MainDrawCb_DrawSyncPtr = DrawSyncCallback(&DECOMP_MainDrawCb_DrawSync);
	ExitCriticalSection();

	DECOMP_MEMCARD_InitCard();
	VSync(0);
	DECOMP_GAMEPAD_Init(gGS);
	VSync(0);
	DECOMP_GAMEPAD_GetNumConnected(gGS);

#ifndef REBUILD_PC
#define BIGPATH rdata.s_PathTo_Bigfile
#else
#define BIGPATH "\\BIGFILE.BIG;1"
#endif

	// Get CD Position fo BIGFILE
	sdata->ptrBigfile1 = DECOMP_LOAD_ReadDirectory(BIGPATH);

	// Defrag to save heap space,
	// required because MEMPACK_Init moves heap
	#ifndef REBUILD_PC
	extern char RB_NewEndFile[4];
	void OVR_Region3();

	// Dont load full overlay file, cut off the end
	struct BigEntry* firstEntry = BIG_GETENTRY(sdata->ptrBigfile1);
	firstEntry[231].size = 28*0x800;
	//firstEntry[231].size = (u_int)RB_NewEndFile - (u_int)OVR_Region3;
	//printf("Size: %08x\n", firstEntry[231].size);
	#endif

	#ifndef FastBoot
	// English=1
	// PAL SCES02105 calls it multiple times
	DECOMP_LOAD_LangFile(sdata->ptrBigfile1, 1);
	DECOMP_GAMEPROG_NewGame_OnBoot();
	gGT->overlayIndex_null_notUsed = 0;
	#endif

	gGT->levelID = NAUGHTY_DOG_CRATE;

	#ifdef USE_ONLINE
	gGT->levelID = 0x26;
	#endif

	#ifdef FastBoot
	gGT->levelID = POLAR_PASS;
	gGT->numPlyrCurrGame = 2;
	gGT->numPlyrNextGame = 2;
	#endif

	InitGeom();
	SetGeomOffset(0x100, 0x78);	// width/2, height/2
	SetGeomScreen(0x140);		// "distance" to screen, alters FOV

#ifndef REBUILD_PS1
	RenderBucket_InitDepthGTE();
	Vector_BakeMatrixTable();
#endif

	gGT->swapchainIndex = 0;
	gGT->backBuffer = &gGT->db[0];

	gGT->overlayIndex_EndOfRace = 0xff;
	gGT->overlayIndex_LOD = 0xff;
	gGT->overlayIndex_Threads = 0xff;

	PutDispEnv(&gGT->db[1].dispEnv);
	PutDrawEnv(&gGT->db[1].drawEnv);
	DrawSync(0);

	#ifndef FastBoot
	#ifndef REBUILD_PC
	// Load Intro TIM for "SCEA Presents" from VRAM file
	DECOMP_LOAD_VramFile(sdata->ptrBigfile1, 0x1fd, 0, &vramSize, 0xffffffff);
	DECOMP_MainInit_VRAMDisplay();
	#endif
	#endif

	// \SOUNDS\KART.HWL;1
	DECOMP_howl_InitGlobals(data.kartHwlPath);

	VSyncCallback(DECOMP_MainDrawCb_Vsync);

	#if !defined(FastBoot) && !defined(USE_ONLINE)
	DECOMP_Music_SetIntro();
	DECOMP_CseqMusic_StopAll();
	DECOMP_CseqMusic_Start(0, 0, 0, 0, 0);
	DECOMP_Music_Start(0);

	// "Start your engines, for Sony Computer..."
	DECOMP_CDSYS_XAPlay(CDSYS_XA_TYPE_EXTRA, 0x50);

#ifndef REBUILD_PC
	while (sdata->XA_State != 0)
	{
		// WARNING: Read-only address (ram, 0x8008d888) is written
		DECOMP_CDSYS_XAPauseAtEnd();
	}
#endif

	#endif

	DECOMP_DecalGlobal_Clear(gGT);

	// This loads UI textures (shared.vrm)
	// This includes traffic lights, font, and more
	// In nopsx VRAM debug viewer:
	// 	the area between 2 screen buffers and top right corner in vram
	// sdata->ptrBigfile1 is the Pointer to "cd position of bigfile"
	// Add a bookmark before loading (param_3 is 0 in the call)
	DECOMP_LOAD_VramFile(sdata->ptrBigfile1, 0x102, 0, &vramSize, 0xffffffff);

	sdata->mainGameState = 3;

	// start loading
	sdata->Loading.stage = 0;

	clockEffect = &gGT->clockEffectEnabled;
	gGT->gameMode1 |= LOADING;
	gGT->clockEffectEnabled = *clockEffect & 0xfffe;
}
