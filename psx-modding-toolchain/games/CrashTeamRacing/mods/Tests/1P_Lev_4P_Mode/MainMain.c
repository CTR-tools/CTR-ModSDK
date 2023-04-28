#include <common.h>

void MainDrawCb_Vsync();
void MainDrawCb_DrawSync();
void StateZero();

//#define FastBoot

u_int main()
{
	struct GameTracker* gGT;
	
	u_int AddBitsConfig0;
	u_int RemBitsConfig0;
	u_int AddBitsConfig8;
	u_int RemBitsConfig8;
	int iVar8;
	u_int gameMode1;
	u_int gameMode2;
	u_int uVar12;
	
	gGT = sdata->gGT;
	
	__main();

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

		LOAD_NextQueuedFile();
		CDSYS_XAPauseAtEnd();

		switch(sdata->mainGameState)
		{
			// Initialize Game (happens once)
			case 0:
				StateZero();
				break;

			// Happens on first frame that loading ends
			case 1:
			
				// deactivate pause
				ElimBG_Deactivate(gGT);
				MainStats_RestartRaceCountLoss();
				Voiceline_ClearTimeStamp();
				
				// Disable End-Of-Race menu
				gGT->gameMode1 &= ~END_OF_RACE;

				// Main Menu Level ID
				if (gGT->levelID == 39)
				{
					LAB_8003ca68:
					iVar8 = TitleFlag_IsFullyOffScreen();
					if (iVar8 != 0)
					{
						TitleFlag_SetFullyOnScreen();
					}
				}
				
				// if not main menu
				else
				{
					iVar8 = TitleFlag_IsFullyOnScreen();
					if (iVar8 == 0)
					{
						// If you are drawing main menu, set fully on screen
						if (gGT->levelID == 39) goto LAB_8003ca68;
					}
					else
					{
						TitleFlag_BeginTransition(2);
					}
				}
				EffectSfxRain_Reset(gGT);
				GAMEPROG_GetPtrHighScoreTrack();
				MainInit_FinalizeInit(gGT);
				GAMEPAD_GetNumConnected(sdata->gGamepads);
				sdata->boolSoundPaused = 0;
				VehInit_EngineAudio_AllPlayers();
				
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
					Audio_SetState_Safe(uVar12);
				}
				sdata->mainGameState = 3;
				gGT->clockEffectEnabled &= 0xfffe;
				break;

			// Reset stage, reset music
			case 2:
				Audio_SetState_Safe(1);
				MEMPACK_PopState();
				
				// ignore threads, because we PopState, 
				// so the threadpool will reset anyway
				LevInstDef_RePack(gGT->level1->ptr_mesh_info, 0);
				sdata->mainGameState = 1;
				break;

			// Main Gameplay Update
			// Makes up all normal interaction with the game
			case 3:
				// if loading is not finished
				if (sdata->Loading.stage != -1)
				{
					iVar8 = TitleFlag_IsFullyOnScreen();
					if
					(
						// wait for flag to be fully on-screen before starting to load the game
						((iVar8 == 1) ||
						// If Level ID is Naughty Dog Box
						(gGT->levelID == 0x29)) || (sdata->pause_state != 0)
					)
					{
						gGT->gameMode1 |= LOADING;
					}
					iVar8 = sdata->Loading.stage;

					// elapsed milliseconds per frame, locked 32 here
					// impacts speed of flag wave during "loading...", but does not impact speed of flying text
					gGT->elapsedTimeMS = 32;
					
					// if loading is finished, but still in "loading mode", and if pools dont need to be reset (maybe for credits?)
					if (iVar8 == -5)
					{
						iVar8 = TitleFlag_IsFullyOnScreen();
						if (iVar8 == 1)
						{
							// set game state to 2 to initialize the world
							// does not initialize pools
							sdata->mainGameState = 2;

							// nothing is being loaded anymore
							sdata->Loading.stage = -1;
							
							// Turn off the "Loading..." flag
							gGT->gameMode1 &= ~LOADING;
							break;
						}
					}
					
					// if something is being loaded
					else
					{
						// if not waiting for checkered flag to cover screen
						if (iVar8 != -4)
						{
							// if loading VLC
							if (iVar8 == -6)
							{
								// if VLC is not loaded, quit
								// we know when it's done from a load callback
								if (sdata->bool_IsLoaded_VlcTable != 1) break;
							}
							else
							{
								sdata->Loading.stage = LOAD_TenStages(gGT, iVar8, sdata->ptrBigfile1);
								
								// if did not just complete loading stage 9, skip logic to load VLC, skip logic to end loading, skip logic if "if == -4", goto rendering.
								// We can skip rendering by changing BNE on 0x8003cca0 to "bne v0, v1, 8003cf3c"
								if (sdata->Loading.stage != -2) goto LAB_8003ccf8;
								
								// if stage 9 of loading was just finished
								if
								(
									// If you're in main menu
									(gGT->levelID == 39) ||
									// If you're in scrapbook
									(gGT->levelID == 64)
								)
								{
									MainLoadVLC();
									// start loading VLC (scroll up to iVar8 == -6)
									sdata->Loading.stage = -6;
									break;
								}
							}
							// loading is finished
							sdata->Loading.stage = -1;
							// set game state to 1, to initialize world, as well as initialize all pools
							sdata->mainGameState = 1;
							// remove "Loading..." flag from gGT
							gGT->gameMode1 &= ~LOADING;
							break;
						}
						iVar8 = TitleFlag_IsFullyOnScreen();
						RemBitsConfig8 = sdata->Loading.OnBegin.RemBitsConfig8;
						AddBitsConfig8 = sdata->Loading.OnBegin.AddBitsConfig8;
						RemBitsConfig0 = sdata->Loading.OnBegin.RemBitsConfig0;
						AddBitsConfig0 = sdata->Loading.OnBegin.AddBitsConfig0;
						
						// wait for flag to be fully on-screen
						if (iVar8 == 1)
						{
							sdata->Loading.OnBegin.AddBitsConfig0 = 0;
							sdata->Loading.OnBegin.RemBitsConfig0 = 0;
							sdata->Loading.OnBegin.AddBitsConfig8 = 0;
							sdata->Loading.OnBegin.RemBitsConfig8 = 0;

							gameMode2 = gGT->gameMode2;

							gGT->hudFlags &= 0xf7;

							iVar8 = sdata->Loading.Lev_ID_To_Load;

							gameMode1 = gGT->gameMode1;
							gGT->gameMode2 = gameMode2 | AddBitsConfig8;
							gGT->gameMode1 = gameMode1 | AddBitsConfig0;
							gGT->gameMode1 = (gameMode1 | AddBitsConfig0) & ~RemBitsConfig0;
							gGT->gameMode2 = (gameMode2 | AddBitsConfig8) & ~RemBitsConfig8;
							MainRaceTrack_StartLoad(iVar8);
						}
						else
						{
							iVar8 = TitleFlag_IsFullyOffScreen();
							if (iVar8 == 1)
							{
								TitleFlag_BeginTransition(1);
							}
						}
					}
				}
				LAB_8003ccf8:
				if
				(
					(
						// Check value of traffic lights
						(-960 < gGT->trafficLightsTimer) &&
						// if not drawing intro race cutscene and if not paused
						((gGT->gameMode1 & (START_OF_RACE | PAUSE_1 | PAUSE_2 | PAUSE_3 | PAUSE_4)) == 0)
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
				GAMEPAD_ProcessAnyoneVars(sdata->gGamepads);

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
					(sdata->gGamepads->gamepad[0].buttonsTapped & BTN_L2)
					)
				{
					gGT->drivers[0]->posCurr[0] = 0x857FF;
					gGT->drivers[0]->posCurr[1] = 0xFFFFBFA9;
					gGT->drivers[0]->posCurr[2] = 0xFFFC1453;
					gGT->drivers[0]->angle = 0xC10;
				}
				#endif

				// Start new frame (ClearOTagR)
				MainFrame_ResetDB(gGT, sdata->gGamepads);

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

					// 0x1edc is a countdown the timer
					// pressing (or holding) any button sets it to zero

					// Get the current value of the countdown timer
					iVar8 = gGT->demoCountdownTimer;

					// subtract one frame
					gGT->demoCountdownTimer = iVar8 - 1;

					// check to see if time ran out
					if (iVar8 - 1 < 1)
					{
						// leave demo mode
						gGT->boolDemoMode = 0;

						// set number of players to 1
						gGT->numPlyrNextGame = 1;

						// go to main menu
						sdata->mainMenuState = 0;

						// load LEV of main menu
						LAB_8003ce08:
						MainRaceTrack_RequestLoad(39);
					}
					
					// if time remains on the timer
					else
					{
						// if any button is pressed by anyone
						if (*(int *)(&((char*)sdata->gGamepads)[0x290]) != 0)
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
					DecalFont_DrawMultiLine(sdata->lngStrings[0x8c0 / 4], 0x100, uVar12, 0x200, 2, 0xffff8000);
				}
				
				if ((gGT->gameMode1 & LOADING) == 0)
				{
					MainFrame_GameLogic(gGT, sdata->gGamepads);
				}
				
				// If you are in demo mode
				if (gGT->boolDemoMode != '\0')
				{
					// Turn off HUD
					gGT->hudFlags &= 0xfe;
				}

				// reset vsync calls between drawsync
				gGT->vSync_between_drawSync = 0;

				MainFrame_RenderFrame(gGT, sdata->gGamepads);

				// if mask is talking in Adventure Hub
				if (sdata->boolDraw3D_AdvMask != 0)
				{
					AH_MaskHint_Update();
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

				GAMEPAD_SetMainMode(sdata->gGamepads);

				// Set vsync to 2 FPS
				VSync(30);
				
				// reboot game
				sdata->mainGameState = 0;
			#endif
		}
	} while( true );
}

// by separating this, it can be 
// overwritten dynamically (oxide fix)
void StateZero()
{
	u_short *clockEffect;
	int vramSize;
	
	struct GameTracker* gGT;
	gGT = sdata->gGT;
	
	memset(gGT, 0, sizeof(struct GameTracker));
	
	// Set Video Mode to NTSC
	SetVideoMode(0);
	ResetCallback();
	
	// We have 2mb RAM total
	MEMPACK_Init(0x800000);
	
	// also sets debug variables to "off"
	LOAD_InitCD();
	
	// Without this, checkered flag will draw one frame after the copyright page draws, then go away once Naughty Dog Box scene is ready
	TitleFlag_SetFullyOffScreen();
	
	ResetGraph(0);
	SetGraphDebug(0);
	
	MainInit_VRAMClear();
	
	SetDispMask(1);
	SetDefDrawEnv(&gGT->db[0].drawEnv, 0, 0, 0x200, 0xd8);
	SetDefDrawEnv(&gGT->db[1].drawEnv, 0, 0x128, 0x200, 0xd8);
	SetDefDispEnv(&gGT->db[0].dispEnv, 0, 0x128, 0x200, 0xd8);
	SetDefDispEnv(&gGT->db[1].dispEnv, 0, 0, 0x200, 0xd8);
	
	gGT->db[0].drawEnv.isbg = 1;
	
	gGT->db[0].dispEnv.screen.x = 0;
	gGT->db[0].dispEnv.screen.y = 0xc;
	gGT->db[0].dispEnv.screen.w = 0x100;
	gGT->db[0].dispEnv.screen.h = 0xd8;
	
	gGT->db[1].dispEnv.screen.x = 0;
	gGT->db[1].dispEnv.screen.y = 0xc;
	gGT->db[1].dispEnv.screen.w = 0x100;
	gGT->db[1].dispEnv.screen.h = 0xd8;
	
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
	
	RCNT_Init();
	
	// set callback and save callback
	EnterCriticalSection();
	sdata->MainDrawCb_DrawSyncPtr = DrawSyncCallback(&MainDrawCb_DrawSync);
	ExitCriticalSection();
	
	MEMCARD_InitCard();
	
	VSync(0);
	
	GAMEPAD_Init(sdata->gGamepads);
	
	VSync(0);
	
	GAMEPAD_GetNumConnected(sdata->gGamepads);
	
	// Get CD Position fo BIGFILE
	sdata->ptrBigfile1 = LOAD_ReadDirectory(rdata.s_PathTo_Bigfile);
	
	#ifndef FastBoot
	// Load Language
	// takes 1 as hard-coded parameter for English
	// PAL SCES02105 has this same function (different name), and calls it multiple times
	LOAD_LangFile(sdata->ptrBigfile1, 1);
	
	GAMEPROG_NewGame_OnBoot();
	
	gGT->overlayIndex_null_notUsed = 0;
	#endif
	
	// set level ID to naughty dog box
	gGT->levelID = 41;
	
	#ifdef FastBoot
	gGT->levelID = 4;
	gGT->numPlyrCurrGame = 1;
	gGT->numPlyrNextGame = 1;
	#endif
	
	InitGeom();
	
	// width / 2, and height / 2
	SetGeomOffset(0x100, 0x78);
	
	// "distance" to screen, alters FOV
	SetGeomScreen(0x140);
	
	RenderBucket_InitDepthGTE();
	Vector_BakeMatrixTable();
	
	gGT->overlayIndex_EndOfRace = 0xff;
	gGT->swapchainIndex = 0;
	gGT->backBuffer = &gGT->db[0];
	gGT->overlayIndex_LOD = 0xff;
	gGT->overlayIndex_Threads = 0xff;
	PutDispEnv(&gGT->db[1].dispEnv);
	PutDrawEnv(&gGT->db[1].drawEnv);
	DrawSync(0);
	
	#ifndef FastBoot
	// Load Intro TIM for "SCEA Presents" from VRAM file
	LOAD_VramFile(sdata->ptrBigfile1, 0x1fd, 0, &vramSize, 0xffffffff);
	MainInit_VRAMDisplay();
	#endif
	
	// \SOUNDS\KART.HWL;1
	// enable audio if not already enabled
	howl_InitGlobals(data.kartHwlPath);
	
	VSyncCallback(MainDrawCb_Vsync);
	
	#ifndef FastBoot
	Music_SetIntro();
	CseqMusic_StopAll();
	CseqMusic_Start(0, 0, 0, 0, 0);
	Music_Start(0);
	
	// CDSYS_XAPlay(CDSYS_XA_TYPE_EXTRA, 0x50);
	// "Start your engines, for Sony Computer..."
	CDSYS_XAPlay(1, 0x50);
	while (sdata->XA_State != 0)
	{
		// WARNING: Read-only address (ram, 0x8008d888) is written
		CDSYS_XAPauseAtEnd();
	}
	#endif
	
	// WARNING: Read-only address (ram, 0x8008d888) is written
	DecalGlobal_Clear(gGT);
	
	// This loads UI textures (shared.vrm)
	// This includes traffic lights, font, and more
	// In nopsx VRAM debug viewer:
	// 	the area between 2 screen buffers and top right corner in vram
	// sdata->ptrBigfile1 is the Pointer to "cd position of bigfile"
	// Add a bookmark before loading (param_3 is 0 in the call)
	LOAD_VramFile(sdata->ptrBigfile1, 0x102, 0, &vramSize, 0xffffffff);
	
	sdata->mainGameState = 3;
	
	// start loading
	sdata->Loading.stage = 0;
	
	clockEffect = &gGT->clockEffectEnabled;
	gGT->gameMode1 |= LOADING;
	gGT->clockEffectEnabled = *clockEffect & 0xfffe;
}