#include <common.h>

// all in this file
void DrawControllerError(struct GameTracker* gGT, struct GamepadSystem* gGamepads);
void DrawFinalLap(struct GameTracker* gGT);
void RainLogic(struct GameTracker* gGT);
void MenuHighlight();
void RenderAllWeather(struct GameTracker* gGT);
void RenderAllConfetti(struct GameTracker* gGT);
void RenderAllStars(struct GameTracker* gGT);
void RenderAllHUD(struct GameTracker* gGT);
void RenderAllBeakerRain(struct GameTracker* gGT);
void RenderAllBoxSceneSplitLines(struct GameTracker* gGT);
void RenderBucket_QueueAllInstances(struct GameTracker* gGT);
void RenderAllNormalParticles(struct GameTracker* gGT);
void RenderDispEnv_World(struct GameTracker* gGT);
void RenderAllFlag0x40(struct GameTracker* gGT);
void RenderAllTitleDPP(struct GameTracker* gGT);
void RenderBucket_ExecuteAllInstances(struct GameTracker* gGT);
void RenderAllTires(struct GameTracker* gGT);
void RenderAllShadows(struct GameTracker* gGT);
void RenderAllHeatParticles(struct GameTracker* gGT);
void RenderAllLevelGeometry(struct GameTracker* gGT);
void MultiplayerWumpaHUD(struct GameTracker* gGT);
void WindowBoxLines(struct GameTracker* gGT);
void WindowDivsionLines(struct GameTracker* gGT);
void RenderDispEnv_UI(struct GameTracker* gGT);
void RenderVSYNC(struct GameTracker* gGT);
void RenderFMV();
void RenderSubmit(struct GameTracker* gGT);

void MainFrame_RenderFrame(struct GameTracker* gGT, struct GamepadSystem* gGamepads)
{
	struct Level* lev = gGT->level1;
	
	//DrawControllerError(gGT, gGamepads);
	
	DrawFinalLap(gGT);
	ElimBG_HandleState(gGT);
	
	gGT->numPlyrCurrGame = 1;
	if((gGT->renderFlags & 0x21) != 0)
		MainFrame_VisMemFullFrame(gGT, gGT->level1);
	gGT->numPlyrCurrGame = 4;
	
	if((gGT->renderFlags & 1) != 0)
		if(gGT->visMem1 != 0)
			if(lev != 0)
				CTR_CycleTex_LEV(
					lev->ptr_anim_tex,
					gGT->timer);
					
	if(
		(sdata->ptrActiveMenuBox != 0) ||
		((gGT->gameMode1 & END_OF_RACE) != 0)
	)
	{
		MenuBox_CollectInput();
	}
	
	if(sdata->ptrActiveMenuBox != 0)
		if(sdata->Loading.stage == -1)
			MenuBox_ProcessState();
		
	RainLogic(gGT);
	EffectSfxRain_MakeSound(gGT);
	MenuHighlight();
	RenderAllWeather(gGT);
	RenderAllConfetti(gGT);
	RenderAllStars(gGT);
	
	#if 0
	// Multiplayer PixelLOD Part 1
	#endif
	
	RenderAllHUD(gGT);
	RenderAllBeakerRain(gGT);
	RenderAllBoxSceneSplitLines(gGT);
	
	RenderBucket_QueueAllInstances(gGT);
	RenderAllNormalParticles(gGT);
	RenderDispEnv_World(gGT); // == RenderDispEnv_World ==
	
	#if 0
	// Multiplayer PixelLOD Part 2
	#endif
	
	RenderAllFlag0x40(gGT); // I need a better name
	RenderAllTitleDPP(gGT);
	
	RenderBucket_ExecuteAllInstances(gGT);
	
	RenderAllTires(gGT);
	RenderAllShadows(gGT);
	RenderAllHeatParticles(gGT);
	
	TileView_FadeAllWindows();
	RenderAllLevelGeometry(gGT);
	RenderDispEnv_World(gGT); // == RenderDispEnv_World ==
	MultiplayerWumpaHUD(gGT);
	
	#if 0
	// Multiplayer Pixel LOD Part 3
	#endif
	
	if(
		// if not cutscene
		// if not in adventure arena
		// if not in main menu
		((gGT->gameMode1 & (GAME_CUTSCENE | ADVENTURE_ARENA | MAIN_MENU)) == 0) &&
		
		// if loading is 100% finished
		(sdata->Loading.stage != -4)
	)
	{
		// in DotLights.c
		void DotLights(struct GameTracker* gGT);
		DotLights(gGT);
	
		if((gGT->renderFlags & 0x8000) != 0)
		{
			WindowBoxLines(gGT);
			WindowDivsionLines(gGT);
		}
	
	}
	
	// if game is not loading
    if (sdata->Loading.stage == -1) {

	  // If game is not paused
      if ((gGT->gameMode1 & (PAUSE_1 | PAUSE_2 | PAUSE_3 | PAUSE_4)) == 0)
	  {
		RobotcarWeapons_Update();
      }

	  StartLine_Update();
    }

	// If in main menu, or in adventure arena,
	// or in End-Of-Race menu
	if ((gGT->gameMode1 & (ADVENTURE_ARENA | END_OF_RACE | MAIN_MENU)) != 0) {
		unk80047d64();
	}
	
	// clear swapchain
	if (
			((gGT->renderFlags & 0x2000) != 0) &&
			(
				(lev->clearColor[0].enable != 0) ||
				(lev->clearColor[1].enable != 0)
			)
		)
	{
		CAM_ClearScreen(gGT);
	}
	
	if ((gGT->renderFlags & 0x1000) != 0)
	{
		TitleFlag_DrawSelf();
	}

	RenderDispEnv_UI(gGT);
	
	gGT->countTotalTime = 
		RCNT_GetTime_Total();
	
	RenderVSYNC(gGT);
	RenderFMV();
	
	gGT->countTotalTime =
		RCNT_GetTime_Elapsed(gGT->countTotalTime,0);
	
	RenderSubmit(gGT);
}

void DrawControllerError(struct GameTracker* gGT, struct GamepadSystem* gGamepads)
{
	int posY;
	int lngArrStart;
	RECT window;
	int i;
	
	// dont draw error if demo mode, or cutscene,
	// or if no controllers are missing currently
	if(gGT->boolDemoMode == 1) return;
	if((gGT->gameMode1 & GAME_CUTSCENE) != 0) return;
	if(MainFrame_HaveAllPads(gGT->numPlyrNextGame) == 1) return;
	
	// if main menu is open, assume 230 loaded,
	// quit if menu is at highest level (no ptrNext to draw)
	if(sdata->ptrActiveMenuBox == 0x800B4540)
		if((*(int*)0x800b4548 & 0x10) == 0) return;
	
	// position of error
	posY = data.errorPosY[sdata->errorMessagePosIndex];

	// "Controller 1" or "Controller 2"
	lngArrStart = 0;
	
	window.x = 0xffec;
	window.y = posY - 3;
	window.w = 0x228;
	window.h = 0;
	
	// if more than 2 players, or if multitap used
	if(
		(gGT->numPlyrNextGame > 2) || 
		(gGamepads->slotBuffer[0].meta[1] == -0x80)
	)
	{
		// change to "1A", "1B", "1C", "1D",
		lngArrStart = 2;
	}
	
	for(i = 0; i < gGT->numPlyrNextGame; i++)
	{
		// yes, char*, not short*
		char* ptrRawInput = gGamepads->gamepad[i].ptrRawInput;
		
		if(ptrRawInput != 0)
			if(ptrRawInput[0] == 0) continue;
		
		// if controller is unplugged
		
		DecalFont_DrawLine(
			sdata->lngStrings
			[
				data.lngIndex_gamepadUnplugged[lngArrStart + i]
			],
			0x100, posY + window.h, FONT_SMALL, (CENTER_TEXT | ORANGE));

		// add for each line
		window.h += 8;
	}
	
	// PLEASE CONNECT A CONTROLLER
	DecalFont_DrawLine(
		sdata->lngStrings[0xac/4],
		0x100, posY + window.h, FONT_SMALL, (CENTER_TEXT | ORANGE));
		
	// add for each line
	window.h += 8;
	
	// add 3 pixels above, 3 pixels bellow
	window.h += 6;
		
	MenuBox_DrawInnerRect(&window, 1, gGT->backBuffer->otMem.startPlusFour);
}

void DrawFinalLap(struct GameTracker* gGT)
{
	int i;
	int textTimer;
	struct TileView* tileView;
	
	int startX;
	int endX;
	int posY;
	
	short resultPos[2];
	
	// number of players
	for(i = 0; i < 4; i++)
	{
		// time remaining in animation
		textTimer = sdata->finalLapTextTimer[i];
		
		// skip if not drawing "FINAL LAP"
		if(textTimer == 0)
			continue;
		
		// turn "time remaining" into "time elapsed",
		// 90 frames total in animation, 1.5 seconds
		textTimer = 90 - textTimer;
		
		// camera
		tileView = &gGT->tileView[i];
		
		// << 0x10, >> 0x12
		posY = tileView->rect.h / 4;
		
		// fly from right to center
		if(textTimer < 11)
		{
			startX = tileView->rect.w + 100;
			endX = tileView->rect.w / 2;

			goto DrawFinalLapString;
		}
		
		// sit in center
		if(textTimer < 0x51)
		{
			startX = tileView->rect.w / 2;
			endX = startX;
			
			// for duration
			textTimer -= 10;

			goto DrawFinalLapString;
		}

		// fly from center to left
		startX = tileView->rect.w / 2;
		endX = -100;
		textTimer -= 0x50;
		
DrawFinalLapString:

		UI_Lerp2D_Linear(&resultPos, startX, posY, endX, posY, textTimer, 10);

		// need to specify OT, or else "FINAL LAP" will draw on top of character icons,
		// and by doing this, "FINAL LAP" draws under the character icons instead
		DecalFont_DrawLineOT(
			sdata->lngStrings[0x8cc/4],
			resultPos[0], resultPos[1],
			FONT_BIG, (CENTER_TEXT | ORANGE),
			tileView->ptrOT);
			
		sdata->finalLapTextTimer[i]--;
	}
}

void RainLogic(struct GameTracker* gGT)
{
	int i;
	struct QuadBlock* camQB;
	int numPlyrCurrGame;
	
	numPlyrCurrGame = gGT->numPlyrCurrGame;
	
	for(i = 0; i < numPlyrCurrGame; i++)
	{
		TileView_UpdateFrustum(&gGT->tileView[i]);
		
		camQB = gGT->cameraDC[i].ptrQuadBlock;
		
		// skip if camera isn't over quadblock
		if(camQB == 0) continue;
		
		// assume numPlayers is never zero,
		// assume weather_intensity is always valid
		
		gGT->rainBuffer[i].numParticles_max =
			(camQB->weather_intensity << 2) / numPlyrCurrGame;
			
		gGT->rainBuffer[i].vanishRate =
			(camQB->weather_vanishRate << 2) / numPlyrCurrGame;
	}
}

void MenuHighlight()
{
	int fc;
	int trig;
	
	fc = sdata->frameCounter << 7;
	trig = MATH_Sin(fc);
	
	trig = (trig << 6) >> 0xc;
	
	// sine curve of green, plus base color
	sdata->menuRowHighlight_Normal = ((trig + 0x40) * 0x100) | 0x80;
	sdata->menuRowHighlight_Green = ((trig + 0xA0) * 0x100) | 0x400040;
}

void RenderAllWeather(struct GameTracker* gGT)
{
	int numPlyrCurrGame = gGT->numPlyrCurrGame;
	
	// only for single player, 
	// probably Naughty Dog's last-minute hack
	if(numPlyrCurrGame != 1) return;
	
	// only if rain is enabled
	if((gGT->renderFlags & 2) == 0) return;
	
	RenderWeather(
		&gGT->tileView[0],
		&gGT->backBuffer->primMem,
		&gGT->rainBuffer[0],
		numPlyrCurrGame,
		gGT->gameMode1 & (PAUSE_1 | PAUSE_2 | PAUSE_3 | PAUSE_4));
}

void RenderAllConfetti(struct GameTracker* gGT)
{
	int i;
	int numWinners = gGT->numWinners;
	
	// only if someone needs confetti
	if(numWinners == 0) return;
	
	// only if confetti is enabled
	if((gGT->renderFlags & 4) == 0) return;
	
	for(i = 0; i < numWinners; i++)
	{
		DrawConfetti(
			&gGT->tileView[gGT->winnerIndex[i]],
			&gGT->backBuffer->primMem,
			&gGT->confetti,
			gGT->frameTimer_Confetti,
			gGT->gameMode1 & (PAUSE_1 | PAUSE_2 | PAUSE_3 | PAUSE_4));
	}
}

void RenderAllStars(struct GameTracker* gGT)
{
	// only if stars are enabled
	if((gGT->renderFlags & 8) == 0) return;

	// quit if no stars exist
	if(gGT->stars.numStars == 0) return;

	RenderStars(
		&gGT->tileView[0],
		&gGT->backBuffer->primMem,
		&gGT->stars,
		gGT->numPlyrCurrGame);
}

void RenderAllHUD(struct GameTracker* gGT)
{
	int hudFlags;
	int gameMode1;
	
	hudFlags = gGT->hudFlags;
	gameMode1 = gGT->gameMode1;
	
	// if not drawing intro-race title bars
	if(
		(gGT->numPlyrCurrGame != 1) ||
		((hudFlags & 8) == 0) ||
		((gameMode1 & START_OF_RACE) == 0)
	)
	{
		// if no hud
		if((hudFlags & 1) == 0)
		{
			// if standings
			if((hudFlags & 4) != 0)
			{
				CupStandings_InputAndDraw();
			}
		}
		
		// if hud
		else
		{
			// if not adv hub
			if((gameMode1 & ADVENTURE_ARENA) == 0)
			{
				// if not drawing end of race
				if(
					// end of race is not reached
					((gameMode1 & END_OF_RACE) == 0) ||
					
					// cooldown after end of race not expired
					(gGT->timerEndOfRaceVS != 0)
				)
				{
					// not crystal challenge
					if((gameMode1 & CRYSTAL_CHALLENGE) == 0)
					{
						UI_RenderFrame_Racing();
					}
					
					// if crystal challenge
					else
					{
						UI_RenderFrame_CrystChall();
					}
				}
				
				// drawing end of race
				else
				{
					if((gGT->gameMode2 & CUP_ANY_KIND) != 0)
					{
						// disable drawing hud,
						// enable drawing "standings"
						gGT->hudFlags = (hudFlags & 0xfe) | 4;
						return;
					}
					
					if((gameMode1 & RELIC_RACE) != 0)
					{
						RR_EndEvent_DrawMenu();
						return;
					}
					
					if((gameMode1 & TIME_TRIAL) != 0)
					{
						TT_EndEvent_DrawMenu();
						return;
					}
					
					if((gameMode1 & CRYSTAL_CHALLENGE) != 0)
					{
						CC_EndEvent_DrawMenu();
						return;
					}
					
					if((gameMode1 & (ADVENTURE_MODE | ARCADE_MODE)) != 0)
					{
						AA_EndEvent_DrawMenu();
						return;
					}
					
					// only remaining option
					VB_EndEvent_DrawMenu();
					return;
				}
			}
			
			// if adv hub
			else
			{
				// load on last frame of waiting to load 232,
				// leave transition at 1 (see later in func),
				// and load the 232 overlay
				if(gGT->overlayTransition > 1)
				{
					gGT->overlayTransition--;
					if(gGT->overlayTransition == 1)
						LOAD_OvrThreads(2);
				}
				
				// if 233 is still loaded
				if(LOAD_IsOpen_AdvHub() == 0)
				{
					// if any transition is over
					if(gGT->tileView_UI.fadeFromBlack_currentValue > 0xfff)
					{
						UI_RenderFrame_AdvHub();
					}
				}
				
				// if 232 overlay is loaded
				else
				{
					// if any transition is over
					if(gGT->tileView_UI.fadeFromBlack_currentValue > 0xfff)
					{
						AH_Map_Main();
						
						if(sdata->AkuHint_RequestedHint != -1)
						{
							AH_MaskHint_Start(
								sdata->AkuHint_RequestedHint,
								sdata->AkuHint_boolInterruptWarppad
							);
							
							//erase submitted request
							sdata->AkuHint_RequestedHint = -1;
							sdata->AkuHint_boolInterruptWarppad = 0;
						}
					}
					
					// if first frame of transition to 232
					if(gGT->overlayTransition != 0)
					{
						gGT->overlayTransition = 0;
						
						INSTANCE_LevDelayedLInBs(
							gGT->level1->ptrInstDefs,
							gGT->level1->numInstances);
							
						// allow instances again
						gGT->gameMode2 &= ~(DISABLE_LEV_INSTANCE);

						// fade transition
						gGT->tileView_UI.fadeFromBlack_desiredResult = 0x1000;
						gGT->tileView_UI.fade_step = 0x2aa;
					}
				}
			}
		}
	}
	
	// if drawing intro-race title bars
	else
	{
		UI_RaceStart_IntroText1P();
	}
}

void RenderAllBeakerRain(struct GameTracker* gGT)
{
	int numPlyrCurrGame = gGT->numPlyrCurrGame;
	
	// only for 1P/2P
	if(numPlyrCurrGame > 2) return;
	
	// only if beaker rain is enabled
	if((gGT->renderFlags & 0x10) == 0) return;
	
	RedBeaker_RenderRain(
		&gGT->tileView[0],
		&gGT->backBuffer->primMem,
		&gGT->JitPools.rain,
		numPlyrCurrGame,
		gGT->gameMode1 & (PAUSE_1 | PAUSE_2 | PAUSE_3 | PAUSE_4));
}

void RenderAllBoxSceneSplitLines(struct GameTracker* gGT)
{
	// check 233 overlay, cause levelID is set
	// and MainFrame_RenderFrame runs, before 233 loads
	if(LOAD_IsOpen_Podiums() != 0)
	{
		// ND Box Scene
		if(gGT->levelID == NAUGHTY_DOG_CRATE)
		{
			CS_BoxScene_InstanceSplitLines();
		}
	}
}

void RenderBucket_QueueAllInstances(struct GameTracker* gGT)
{
	int lod;
	int* RBI;
	int numPlyrCurrGame = gGT->numPlyrCurrGame;
	
	if((gGT->renderFlags & 0x20) == 0) return;

	lod = numPlyrCurrGame - 1;
	if((gGT->gameMode1 & RELIC_RACE) != 0)
		lod |= 4;
	
	RBI = RenderBucket_QueueLevInstances(
		&gGT->cameraDC[0],
		&gGT->backBuffer->otMem,
		gGT->ptrRenderBucketInstance,
		sdata->LOD[lod],
		numPlyrCurrGame,
		gGT->gameMode1 & (PAUSE_1 | PAUSE_2 | PAUSE_3 | PAUSE_4));
		
	RBI = RenderBucket_QueueNonLevInstances(
		gGT->JitPools.instance.taken.first,
		&gGT->backBuffer->otMem,
		RBI,
		sdata->LOD[lod],
		numPlyrCurrGame,
		gGT->gameMode1 & (PAUSE_1 | PAUSE_2 | PAUSE_3 | PAUSE_4));
		
	// Aug prototype
#if 0
		// ptrEnd of otmem is less than ptrCurr otmem
    if (*(uint *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x98) <
        *(uint *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x9c)) {
      printf("OTMEM OVERFLOW!\n");
    }
#endif

	// null terminator at end of list
	*RBI = 0;
}

void RenderAllNormalParticles(struct GameTracker* gGT)
{
	int i;
	
	if((gGT->renderFlags & 0x200) == 0) return;
	
	for(i = 0; i < gGT->numPlyrCurrGame; i++)
	{
		Particle_RenderList(
			&gGT->tileView[i],
			gGT->particleList_ordinary);
	}
}

void RenderDispEnv_World(struct GameTracker* gGT)
{
	int i;
	struct TileView* tileView;
	for(i = 0; i < gGT->numPlyrCurrGame; i++)
	{
		tileView = &gGT->tileView[i];
		TileView_SetDrawEnv_Normal(
			&tileView->ptrOT[0x3ff],
			tileView, gGT->backBuffer, 0, 0);
	}
}

// I need a better name
void RenderAllFlag0x40(struct GameTracker* gGT)
{
	int i;
	struct TileView* tileView;
	
	if((gGT->renderFlags & 0x40) == 0) return;
	
	if(LOAD_IsOpen_RacingOrBattle() != 0)
	{
		RB_Player_ToggleInvisible();
		RB_Player_ToggleFlicker();
		RB_Burst_ProcessBucket(gGT->threadBuckets[BURST].thread);
		RB_Blowup_ProcessBucket(gGT->threadBuckets[BLOWUP].thread);
		RB_Spider_DrawWebs(gGT->threadBuckets[SPIDER].thread, &gGT->tileView[0]);
		RB_Follower_ProcessBucket(gGT->threadBuckets[FOLLOWER].thread);
		
		// skipping RB_StartText_ProcessBucket, it's empty in 231
	}
	
	if(LOAD_IsOpen_AdvHub() != 0)
	{
		if((gGT->gameMode1 & ADVENTURE_ARENA) != 0)
		{
			AH_WarpPad_AllWarppadNum();
		}
	}
	
	Turbo_ProcessBucket(gGT->threadBuckets[TURBO].thread);

	for(i = 0; i < gGT->numPlyrCurrGame; i++)
	{
		tileView = &gGT->tileView[i];
		DrawSkidMarks_Main(gGT->threadBuckets[PLAYER].thread, tileView);
		DrawSkidMarks_Main(gGT->threadBuckets[ROBOT].thread, tileView);
	}
}

void RenderAllTitleDPP(struct GameTracker* gGT)
{
	if((gGT->gameMode1 & MAIN_MENU) == 0) return;
	if(LOAD_IsOpen_MainMenu() == 0) return;
	MM_Title_SetTrophyDPP();
}

void RenderBucket_ExecuteAllInstances(struct GameTracker* gGT)
{
	if((gGT->renderFlags & 0x20) == 0) return;
	
	RenderBucket_Execute(
		gGT->ptrRenderBucketInstance,
		&gGT->backBuffer->primMem);
}

void RenderAllTires(struct GameTracker* gGT)
{
	int i;
	struct Thread* th;
	int numPlyrCurrGame;
	struct PrimMem* gGT_primMem;
	if((gGT->renderFlags & 0x80) == 0) return;

	// replace checking number of AIs, with 
	// checking if the threadBucket exists,
	// then roll this up into a loop
	
	gGT_primMem = &gGT->backBuffer->primMem;
	numPlyrCurrGame = gGT->numPlyrCurrGame;
	
	// player, robot, ghost
	for(i = 0; i < 3; i++)
	{
		th = gGT->threadBuckets[i].thread;
		if(th == 0) continue;
		
		DrawTires_Solid(th, gGT_primMem, numPlyrCurrGame);
		DrawTires_Reflection(th, gGT_primMem, numPlyrCurrGame);
	}
}

void RenderAllShadows(struct GameTracker* gGT)
{
	if((gGT->renderFlags & 0x200) == 0) return;
	DrawShadows_Main();
}

void RenderAllHeatParticles(struct GameTracker* gGT)
{
	if((gGT->renderFlags & 0x800) == 0) return;
	
	Torch_Main(
		gGT->particleList_heatWarp,
		&gGT->tileView[0],
		&gGT->backBuffer->primMem,
		gGT->numPlyrCurrGame,
		gGT->swapchainIndex * 0x128);
}

void RenderAllLevelGeometry(struct GameTracker* gGT)
{
	int i;
	int distToScreen;
	int numPlyrCurrGame;
	struct Level* level1;
	struct TileView* tileView;
	struct mesh_info* ptr_mesh_info;
	
	if((gGT->renderFlags & 1) == 0) return;
	
	level1 = gGT->level1;
	if(level1 == 0) return;
	
	ptr_mesh_info = level1->ptr_mesh_info;
	if(ptr_mesh_info == 0) return;
	
	numPlyrCurrGame = gGT->numPlyrCurrGame;
	
	CTR_ClearRenderLists_1P2P(gGT, 1);
	
	// if no SCVert
	if((level1->configFlags & 4) == 0)
	{
		// assume OVert (no primitives generated here)
		AnimateWater1P(gGT->timer, level1->count_water,
			level1->ptr_water, level1->ptr_tex_waterEnvMap,
			gGT->visMem1->visOVertList[0]);
	}
	
	// if SCVert
	else
	{
		// draw SCVert (no primitives generated here
		AnimateQuad(gGT->timer << 7, 
			level1->numSCVert, level1->ptrSCVert,
			gGT->visMem1->visSCVertList[0]);
	}
	
	// camera of player 1
	tileView = &gGT->tileView[0];
	
	if(
		// adv character selection screen
		(gGT->levelID == ADVENTURE_CHARACTER_SELECT) ||
		
		// cutscene that's not Crash Bandicoot intro
		// where he's sleeping and snoring on a hill
		(
			((gGT->gameMode1 & GAME_CUTSCENE) != 0) &&
			(gGT->levelID != INTRO_CRASH)
		)
	)
	{	
		// relationship between near-clip and far-clip,
		// for each RenderList LOD set in the level
		*(int*)0x1f800014 = 0x1e00;
		*(int*)0x1f800018 = 0x640;
		*(int*)0x1f80001c = 0x640;
		*(int*)0x1f800020 = 0x500;
		*(int*)0x1f800024 = 0x280;
		*(int*)0x1f800028 = 0x140;
		*(int*)0x1f80002c = 0x640+0x140;
	}
	
	// every non-cutscene,
	// except for Crash Bandicoot intro
	else
	{
		// 0x1c2 in 1P mode
		distToScreen = tileView->distanceToScreen_PREV;
		
		// int and unsigned int have specific purposes
		*(unsigned int*)0x1f800014 = distToScreen * 0x2080;
		if(*(int*)0x1f800014 < 0) *(int*)0x1f800014 = *(int*)0x1f800014 + 0xff;
		*(int*)0x1f800014 = *(int*)0x1f800014 >> 8; // 0x3921
		
		*(int*)0x1f800018 = distToScreen * 0x1a;	// 0x2DB4
		*(int*)0x1f80001c = distToScreen * 0x18;	// 0x2A30
		*(int*)0x1f800020 = distToScreen * 0xc;		// 0x1518
		*(int*)0x1f800024 = distToScreen * 7;		// 0xC4E
		*(int*)0x1f80002c = *(int*)0x1f800018 + 0x140; // 0x2EF4
		
		// int and unsigned int have specific purposes
		*(unsigned int*)0x1f800028 = distToScreen * 0x380;
		if(*(int*)0x1f800028 < 0) *(int*)0x1f800028 = *(int*)0x1f800028 + 0xff;
		*(int*)0x1f800028 = *(int*)0x1f800028 >> 8; // 0x627
	}
	
	VisData_CopyJMPsToScratchpad();
	gGT->numVisDataLinks = 0;
	
	gGT->numVisDataLinks += 
	  CreateRenderLists_1P2P(
		ptr_mesh_info->ptrVisDataArray,
		level1->visMem->visLeafList[0],
		tileView,
		&gGT->LevRenderLists[0],
		level1->visMem->bspList[0],
		gGT->numPlyrCurrGame);
	
			
	// skybox gradient
	for(i = 0; i < numPlyrCurrGame; i++)
	{
		tileView = &gGT->tileView[i];
		
		// 226-229
		DrawLevelOvr1P(
			&gGT->LevRenderLists[0],
			tileView,
			ptr_mesh_info,
			&gGT->backBuffer->primMem,
			gGT->visMem1->visFaceList[0],
			level1->ptr_tex_waterEnvMap); // waterEnvMap?
			
		DrawSky_Full(
			level1->ptr_skybox,
			tileView,
			&gGT->backBuffer->primMem);
			
		// skybox gradient
		if((level1->configFlags & 1) != 0)
		{
			CAM_SkyboxGlow(
				&level1->glowGradient[0],
				tileView,
				&gGT->backBuffer->primMem,
				&tileView->ptrOT[0x3ff]);
		}
	}
}

void MultiplayerWumpaHUD(struct GameTracker* gGT)
{
	if((gGT->hudFlags & 1) == 0) return;
	if(gGT->numPlyrCurrGame < 2) return;
	UI_RenderFrame_Wumpa3D_2P3P4P(gGT);
}

void WindowBoxLines(struct GameTracker* gGT)
{
	int i;
	
	// only battle and 3P4P mode allowed
	if((gGT->gameMode1 & BATTLE_MODE) == 0) return;
	if(gGT->numPlyrCurrGame < 3) return;
	
	for(i = 0; i < gGT->numPlyrCurrGame; i++)
	{
		MenuBox_DrawOuterRect_LowLevel(

			// dimensions, thickness
			&gGT->tileView[i].rect,4,2,

			// color data, 0x18 is enum offset of BLUE
			data.ptrColor[gGT->drivers[i]->BattleHUD.teamID + PLAYER_BLUE],

			0,

			// tileView_UI = 0x1388
			&gGT->tileView_UI.ptrOT[3]);
	}
}

void WindowDivsionLines(struct GameTracker* gGT)
{
	POLY_F4* p;
	int numPlyrCurrGame;

	numPlyrCurrGame = gGT->numPlyrCurrGame;

	// if numPlyrCurrGame is more than 1
    if (1 < numPlyrCurrGame)
	{
		p = gGT->backBuffer->primMem.curr;

		// set R, G, B, CODE, all to zero,
		// this makes black color, and invalid CODE
		*(int*)&p->r0 = 0;

		// this sets CODE to the proper value
		setPolyF4(p);

		// Make four (x,y) coordinates
		p->y0 = 0x6a;
		p->y1 = 0x6a;
		p->x0 = 0;
		p->x1 = 0x200;

		p->x2 = 0;
		p->y2 = 0x6e;
		p->x3 = 0x200;
		p->y3 = 0x6e;

		// Draw a bar from left to right,
		// dividing the screen in half on top and bottom
		AddPrim(&gGT->tileView_UI.ptrOT[3],p);

		gGT->backBuffer->primMem.curr = (void*)(p + 1);
    }

	// if numPlyrCurrGame is more than 2
    if (2 < numPlyrCurrGame)
	{
		p = gGT->backBuffer->primMem.curr;

		// set R, G, B, CODE, all to zero,
		// this makes black color, and invalid CODE
		*(int*)&p->r0 = 0;

		// this sets CODE to the proper value
		setPolyF4(p);

		// Make four (x,y) coordinates
		p->x0 = 0xfd;
		p->x2 = 0xfd;
		p->y0 = 0;
		p->x1 = 0x103;

		p->y1 = 0;
		p->y2 = 0xd8;
		p->x3 = 0x103;
		p->y3 = 0xd8;

		// Draw a bar from left to right,
		// dividing the screen in half on top and bottom
		AddPrim(&gGT->tileView_UI.ptrOT[3],p);

		// backBuffer->primMem.curr
		gGT->backBuffer->primMem.curr = (void*)(p + 1);
    }

	// if numPlyrCurrGame is 3
    if (numPlyrCurrGame == '\x03')
	{
		// This is useless, cause it gets cleared
		// to black anyway, even without this block,
		// at least it does it Crash Cove, does it always?

		p = gGT->backBuffer->primMem.curr;

		// set R, G, B, CODE, all to zero,
		// this makes black color, and invalid CODE
		*(int*)&p->r0 = 0;

		// this sets CODE to the proper value
		setPolyF4(p);

		// xy0
		p->x0 = 0x100;
		p->x2 = 0x100;
		p->y0 = 0x6c;
		p->y1 = 0x6c;
		p->x1 = 0x200;
		p->y2 = 0xd8;
		p->x3 = 0x200;
		p->y3 = 0xd8;

		// Draw a bar from left to right,
		// dividing the screen in half on top and bottom
		AddPrim(&gGT->tileView_UI.ptrOT[3],p);

		// backBuffer->primMem.curr
		gGT->backBuffer->primMem.curr = (void*)(p + 1);
    }
}

void RenderDispEnv_UI(struct GameTracker* gGT)
{
	struct TileView* tileView = &gGT->tileView_UI;
	
	TileView_SetDrawEnv_Normal(
		&tileView->ptrOT[4],
		tileView, gGT->backBuffer, 0, 0);
}

void RenderVSYNC(struct GameTracker* gGT)
{	
	// render checkered flag
	if((gGT->renderFlags & 0x1000) != 0)
	{
		VSync(0);
	}

	while(1)
	{
		if(
			// if DrawOTag finished
			(gGT->bool_DrawOTag_InProgress == 0) &&
			
			// two VSYNCs passed, 30fps lock
			(sdata->vsyncTillFlip < 1)
		  )
		{
			// quit, end of stall
			return;
		}
		
		// if more than 6 VSYNCs passed since
		// the last successful draw, FPS < 10fps
		if(gGT->vSync_between_drawSync > 6)
		{
			// just quit and try the next frame
			BreakDraw();
			return;
		}
	}
}

void RenderFMV()
{
	if(sdata->boolPlayVideoSTR == 1)
	{
		MM_Video_CheckIfFinished(1);
		
		MoveImage(
			&sdata->videoSTR_src_vramRect,
			sdata->videoSTR_dst_vramX, 
			sdata->videoSTR_dst_vramY);
			
		DrawSync(0);
	}
}

void RenderSubmit(struct GameTracker* gGT)
{		
	// do I need the "if"? will it ever be nullptr?
	if(gGT->frontBuffer != 0)
	{
		// wait two VSYNCs per frame,
		// this is the 30fps lock
		sdata->vsyncTillFlip = 2;
		
		// skip debug stuff
		
		PutDispEnv(&gGT->frontBuffer->dispEnv);
		PutDrawEnv(&gGT->frontBuffer->drawEnv);
	}
	
	// swap=0, get db[1]
	// swap=1, get db[0]
	gGT->frontBuffer = &gGT->db
		[
			1 - gGT->swapchainIndex
		];
		
	gGT->bool_DrawOTag_InProgress = 1;
	
	DrawOTag(&gGT->tileView[0].ptrOT[0x3ff]);
	
	gGT->frameTimer_notPaused = gGT->frameTimer_VsyncCallback;
}