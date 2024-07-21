#include <common.h>

// all in this file
void DrawUnpluggedMsg(struct GameTracker* gGT, struct GamepadSystem* gGamepads);
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

// original CTR funcs
void UI_CupStandings_InputAndDraw();
void VB_EndEvent_DrawMenu();
void RR_EndEvent_DrawMenu();
void AA_EndEvent_DrawMenu();
void TT_EndEvent_DrawMenu();
void CC_EndEvent_DrawMenu();
void CS_BoxScene_InstanceSplitLines();
void RB_Player_ToggleInvisible();
void RB_Player_ToggleFlicker();
void RB_Burst_ProcessBucket(struct Thread* thread);
void RB_Blowup_ProcessBucket(struct Thread* thread);
void RB_Follower_ProcessBucket(struct Thread* thread);
void RB_StartText_ProcessBucket(struct Thread* thread);
u_int MM_Video_CheckIfFinished(int param_1);

#ifdef USE_60FPS || USE_HIGH1P
void PatchModel_60fps(struct Model* m)
{
	struct ModelHeader* h;
	struct ModelAnim** a;
	int i;
	int j;
	int loopNum;
	struct Thread* search;

	// error check (yes, needed)
	if(m == 0) return;

	// model header
	h = m->headers;

	// skip if the model is patched
	if(h[0].name[0xf] == 1) return;

	// record the model is patched
	h[0].name[0xf] = 1;

	// skip "big1" because it needs LODs
	// to shift from 1st to 8th UI polygons
	if(*(int*)&h[0].name[0] == 0x31676962) return;

	#if 1
	// Only do this for drivers, because we dont have
	// enough primitives to boost "all" instance LODs,
	// but also LOD[1] and LOD[2] for drivers are lerp'd,
	// so we cant force-lerp with pre-lerp'd animations
	if(m->id == -1)
	{
		// human drivers have 1 LOD,
		// robotcar AIs have 4 LODs
		if(m->numHeaders == 4)
		{
			// LODs are 0x140, 0x258, 0x550, 0x2000

			// expand range of LOD[0], but dont expand
			// all the way to LOD[3], cause polygons
			// explode when they get too small on-screen
			h[0].maxDistanceLOD = 0x1000;

			// skip LOD[1] and LOD[2]
			h[1].maxDistanceLOD = 0;
			h[2].maxDistanceLOD = 0;

			// dont touch LOD[3], that is the cutoff
			// to stop rendering the model. Without that,
			// polygons explode in the distance
		}
	}
	#endif

	#if 0
	// min graphics
	for(i = 0; i < m->numHeaders-1; i++)
	{
		h[i].maxDistanceLOD = 0;
	}
	#endif

	#ifndef USE_60FPS
	return;
	#endif

	// loop through headers
	for(i = 0; i < m->numHeaders; i++)
	{
		// pointer to array of pointers
		a = h[i].ptrAnimations;

		// number of animations
		loopNum = h[i].numAnimations;

		// loop through all animations
		for(j = 0; j < loopNum; j++)
		{
			// skip doubling, if interpolation already happens,
			// known to happen in spiders, and drivers for
			// low LOD anims, and high LOD crashing + reversing
			if(a[j]->numFrames & 0x8000) continue;

			// multiply by 2
			a[j]->numFrames =
			a[j]->numFrames << 1;

			// should only need to subtract one,
			// but then many animations break on last frame,
			// need to patch code that manipulates last frame
			a[j]->numFrames--;

			// negative, or flag?
			a[j]->numFrames =
			a[j]->numFrames | 0x8000;
		}
	}
}
void ScanInstances_60FPS(struct GameTracker* gGT)
{
	struct JitPool* instPool = &sdata->gGT->JitPools.instance;

	// check if pool is empty
	if(instPool->free.count == 0) return;
	if(instPool->taken.first == 0) return;

	// ignore ND box, intro models, oxide intro, podiums, etc
	if(DECOMP_LOAD_IsOpen_Podiums())
	{
		struct Driver* d = gGT->drivers[0];
		if(d == 0) return;

		struct Instance* i = d->instSelf;
		if(i == 0) return;

		struct Model* m = i->model;
		if(m == 0) return;

		#ifdef USE_60FPS
		// need this, or it'll somehow become
		// 0x13 instead of 0x14? May as well leave it here
		i->animFrame = FPS_DOUBLE(10);
		#endif

		// make an exception for driver when 233 is still
		// loaded, and aku/uka says "congratulations, you win"
		PatchModel_60fps(m);

		// nothing else
		return;
	}

	for(
			struct Instance* inst = instPool->taken.first;
			inst != 0;
			inst = inst->next
		)
	{
		PatchModel_60fps(inst->model);
	}

	if(gGT->level1 != 0)
	for(int i = 0; i < gGT->level1->numInstances; i++)
	{
		struct Instance* inst = gGT->level1->ptrInstDefs[i].ptrInstance;

		if(inst != 0)
			PatchModel_60fps(inst->model);
	}
}
#endif

void DECOMP_MainFrame_RenderFrame(struct GameTracker* gGT, struct GamepadSystem* gGamepads)
{
	struct Level* lev = gGT->level1;

	#ifdef USE_60FPS || USE_HIGH1P
	if ((gGT->renderFlags & 0x20) != 0)
		ScanInstances_60FPS(gGT);
	#endif

	DrawUnpluggedMsg(gGT, gGamepads);
	DrawFinalLap(gGT);

	DECOMP_ElimBG_HandleState(gGT);

#ifndef REBUILD_PS1
	#ifndef USE_HIGHMP
	if((gGT->renderFlags & 0x21) != 0)
		MainFrame_VisMemFullFrame(gGT, gGT->level1);
	#endif
#endif


	if((gGT->renderFlags & 1) != 0)
		if(gGT->visMem1 != 0)
			if(lev != 0)
				DECOMP_CTR_CycleTex_LEV(
					lev->ptr_anim_tex,
					gGT->timer);

	if(
		(sdata->ptrActiveMenu != 0) ||
		((gGT->gameMode1 & END_OF_RACE) != 0)
	)
	{
		DECOMP_RECTMENU_CollectInput();
	}

	if(sdata->ptrActiveMenu != 0)
		if(sdata->Loading.stage == -1)
			DECOMP_RECTMENU_ProcessState();

	RainLogic(gGT);
	DECOMP_DropRain_MakeSound(gGT);
	MenuHighlight();

#ifndef REBUILD_PS1
	RenderAllWeather(gGT);
	RenderAllConfetti(gGT);
	RenderAllStars(gGT);

	#if 0
	// Multiplayer PixelLOD Part 1
	#endif
#endif

	RenderAllHUD(gGT);

#ifndef REBUILD_PS1
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

#else

	// PC port version of ExecuteAllInstances
	if ((gGT->renderFlags & 0x20) != 0)
	{
		RenderDispEnv_World(gGT); // == RenderDispEnv_World ==
		void TEST_DrawInstances(struct GameTracker* gGT);
		TEST_DrawInstances(gGT);
	}
#endif

	DECOMP_PushBuffer_FadeAllWindows();

	if((gGT->renderFlags & 1) != 0)
	{
#ifndef REBUILD_PS1
		RenderAllLevelGeometry(gGT);
#else
		for (int i = 0; i < gGT->numPlyrCurrGame; i++)
		{
			// 226-229
			// placeholder for DrawLevelOvr1P
			TEST_226(
				0,
				&gGT->pushBuffer[i],
				gGT->level1->ptr_mesh_info,
				&gGT->backBuffer->primMem,
				0,
				0); // waterEnvMap?

			// placeholder for DrawSky_Full
			TEST_DrawSkybox(
				gGT->level1->ptr_skybox,
				&gGT->pushBuffer[i],
				&gGT->backBuffer->primMem);
		}
#endif


		RenderDispEnv_World(gGT); // == RenderDispEnv_World ==

		// We just draw full wumpa geometry instead
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
			DECOMP_DotLights(gGT);

			#ifndef USE_ONLINE
			if((gGT->renderFlags & 0x8000) != 0)
			{
				WindowBoxLines(gGT);

				WindowDivsionLines(gGT);
			}
			#endif
		}

#ifndef REBUILD_PS1
		// if game is not loading
		if (sdata->Loading.stage == -1)
		{
			// If game is not paused
			if ((gGT->gameMode1 & PAUSE_ALL) == 0)
			{
				PickupBots_Update();
			}

			PlayLevel_UpdateLapStats();
		}
#endif
	}

#ifndef REBUILD_PS1
	// If in main menu, or in adventure arena,
	// or in End-Of-Race menu
	if ((gGT->gameMode1 & (ADVENTURE_ARENA | END_OF_RACE | MAIN_MENU)) != 0) {
		RefreshCard_Entry();
	}
#endif

	// clear swapchain
	if (
			((gGT->renderFlags & 0x2000) != 0) &&
			(
				(lev->clearColor[0].enable != 0) ||
				(lev->clearColor[1].enable != 0)
			)
		)
	{
		DECOMP_CAM_ClearScreen(gGT);
	}

	if ((gGT->renderFlags & 0x1000) != 0)
	{
		DECOMP_RaceFlag_DrawSelf();
	}

	RenderDispEnv_UI(gGT);

#ifndef REBUILD_PS1
	gGT->countTotalTime =
		Timer_GetTime_Total();
#endif

	RenderVSYNC(gGT);

#ifndef REBUILD_PS1
	RenderFMV();

	gGT->countTotalTime =
		Timer_GetTime_Elapsed(gGT->countTotalTime,0);
#endif

	RenderSubmit(gGT);
}

void DrawUnpluggedMsg(struct GameTracker* gGT, struct GamepadSystem* gGamepads)
{
	int posY;
	int lngArrStart;
	RECT window;
	int i;

	// dont draw error if demo mode, or cutscene,
	// or if no controllers are missing currently
	if(gGT->boolDemoMode == 1) return;
	if((gGT->gameMode1 & GAME_CUTSCENE) != 0) return;

#ifndef REBUILD_PS1
	if(MainFrame_HaveAllPads(gGT->numPlyrNextGame) == 1) return;
#else
	// assume all connected on PC
	return;
#endif

	// if main menu is open, assume 230 loaded,
	// quit if menu is at highest level (no ptrNext to draw)
	if(sdata->ptrActiveMenu == 0x800B4540)
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
		(gGamepads->slotBuffer[0].controllerData == (PAD_ID_MULTITAP << 4))
	)
	{
		// change to "1A", "1B", "1C", "1D",
		lngArrStart = 2;
	}

	for(i = 0; i < gGT->numPlyrNextGame; i++)
	{
		struct ControllerPacket* ptrControllerPacket = gGamepads->gamepad[i].ptrControllerPacket;

		if(ptrControllerPacket != 0)
			if(ptrControllerPacket->isControllerConnected == 0) continue;

		// if controller is unplugged

		DECOMP_DecalFont_DrawLine(
			sdata->lngStrings
			[
				data.lngIndex_gamepadUnplugged[lngArrStart + i]
			],
			0x100, posY + window.h, FONT_SMALL, (JUSTIFY_CENTER | ORANGE));

		// add for each line
		window.h += 8;
	}

	// PLEASE CONNECT A CONTROLLER
	DECOMP_DecalFont_DrawLine(
		sdata->lngStrings[0xac/4],
		0x100, posY + window.h, FONT_SMALL, (JUSTIFY_CENTER | ORANGE));

	// add for each line
	window.h += 8;

	// add 3 pixels above, 3 pixels bellow
	window.h += 6;

	DECOMP_RECTMENU_DrawInnerRect(&window, 1, gGT->backBuffer->otMem.startPlusFour);
}

void DrawFinalLap(struct GameTracker* gGT)
{
	int i;
	int textTimer;
	struct PushBuffer* pb;

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
		textTimer = FPS_DOUBLE(90) - textTimer;

		// camera
		pb = &gGT->pushBuffer[i];

		// << 0x10, >> 0x12
		posY = pb->rect.h / 4;

		// fly from right to center
		if(textTimer <= FPS_DOUBLE(10))
		{
			startX = pb->rect.w + 100;
			endX = pb->rect.w / 2;

			goto DrawFinalLapString;
		}

		// sit in center
		if(textTimer <= FPS_DOUBLE(0x50))
		{
			startX = pb->rect.w / 2;
			endX = startX;

			// for duration
			textTimer -= FPS_DOUBLE(10);

			goto DrawFinalLapString;
		}

		// fly from center to left
		startX = pb->rect.w / 2;
		endX = -100;
		textTimer -= FPS_DOUBLE(0x50);

DrawFinalLapString:

		DECOMP_UI_Lerp2D_Linear(
			&resultPos,
			startX, posY,
			endX, posY,
			textTimer, FPS_DOUBLE(10));

		// need to specify OT, or else "FINAL LAP" will draw on top of character icons,
		// and by doing this, "FINAL LAP" draws under the character icons instead
		DECOMP_DecalFont_DrawLineOT(
			sdata->lngStrings[0x8cc/4],
			resultPos[0], resultPos[1],
			FONT_BIG, (JUSTIFY_CENTER | ORANGE),
			pb->ptrOT);

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
#ifndef REBUILD_PS1
		PushBuffer_UpdateFrustum(&gGT->pushBuffer[i]);
#else
		// temporary until PushBuffer_UpdateFrustum is done
		DECOMP_PushBuffer_SetMatrixVP(&gGT->pushBuffer[i]);
#endif

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

	fc = FPS_HALF(sdata->frameCounter) << 7;
	trig = DECOMP_MATH_Sin(fc);

	trig = (trig << 6) >> 0xc;

	// sine curve of green, plus base color
	sdata->menuRowHighlight_Normal = ((trig + 0x40) * 0x100) | 0x80;
	sdata->menuRowHighlight_Green = ((trig + 0xA0) * 0x100) | 0x400040;
}

#ifndef REBUILD_PS1
void RenderAllWeather(struct GameTracker* gGT)
{
	int numPlyrCurrGame = gGT->numPlyrCurrGame;

	// only for single player,
	// probably Naughty Dog's last-minute hack
	if(numPlyrCurrGame != 1) return;

	// only if rain is enabled
	if((gGT->renderFlags & 2) == 0) return;

	RenderWeather(
		&gGT->pushBuffer[0],
		&gGT->backBuffer->primMem,
		&gGT->rainBuffer[0],
		numPlyrCurrGame,
		gGT->gameMode1 & PAUSE_ALL);
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
			&gGT->pushBuffer[gGT->winnerIndex[i]],
			&gGT->backBuffer->primMem,
			&gGT->confetti,
			gGT->frameTimer_Confetti,
			gGT->gameMode1 & PAUSE_ALL);
	}
}

void RenderAllStars(struct GameTracker* gGT)
{
	// only if stars are enabled
	if((gGT->renderFlags & 8) == 0) return;

	// quit if no stars exist
	if(gGT->stars.numStars == 0) return;

	RenderStars(
		&gGT->pushBuffer[0],
		&gGT->backBuffer->primMem,
		&gGT->stars,
		gGT->numPlyrCurrGame);
}
#endif

void RenderAllHUD(struct GameTracker* gGT)
{
	int hudFlags;
	int gameMode1;

	hudFlags = gGT->hudFlags;
	gameMode1 = gGT->gameMode1;

	// Why is this needed? What's broken
	// that causes this to run premature?
	#ifdef REBUILD_PS1
	// LOADING... and pause screen (see adv pause)
	if((gGT->gameMode1 & 0x4000000f) != 0) return;

	// before level is done loading
	if(gGT->level1 == 0) return;
	#endif

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
			#ifndef REBUILD_PS1
			// if standings
			if((hudFlags & 4) != 0)
			{
				UI_CupStandings_InputAndDraw();
			}
			#endif
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
						DECOMP_UI_RenderFrame_Racing();
					}

					// if crystal challenge
					else
					{
						#ifndef REBUILD_PS1
							#ifndef USE_ONLINE
							DECOMP_UI_RenderFrame_CrystChall();
							#endif
						#endif
					}
				}

				// drawing end of race
				else
				{
					if(
						// VS mode, and Cup
						((gGT->gameMode1 & ARCADE_MODE) == 0) &&
						((gGT->gameMode2 & CUP_ANY_KIND) != 0)
					  )
					{
						// disable drawing hud,
						// enable drawing "standings"
						gGT->hudFlags = (hudFlags & 0xfe) | 4;
						return;
					}

					#ifdef USE_ONLINE
					void OnlineEndOfRace();
					OnlineEndOfRace();
					return;
					#endif

					// PC can't share address spaces
					#ifndef REBUILD_PC

					// temporary, until we rewrite MainGameEnd_Initialize
					if((gGT->gameMode1 & RELIC_RACE) == 0)
					{
						// all 221-225 overlays share the same
						// function address, so call as one func
						void OVR_Region1();
						OVR_Region1();
					}

					// except relic, until we rewrite MainGameEnd_Initialize
					else
					{
						void DECOMP_RR_EndEvent_DrawMenu();
						DECOMP_RR_EndEvent_DrawMenu();
					}
					#endif

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
					#ifndef REBUILD_PS1
					gGT->overlayTransition--;
					if(gGT->overlayTransition == 1)
						LOAD_OvrThreads(2);
					#endif
				}

				// if 233 is still loaded
				if(DECOMP_LOAD_IsOpen_AdvHub() == 0)
				{
					// if any transition is over
					if(gGT->pushBuffer_UI.fadeFromBlack_currentValue > 0xfff)
					{
						#ifndef USE_ONLINE
						DECOMP_UI_RenderFrame_AdvHub();
						#endif
					}
				}

				// if 232 overlay is loaded
				else
				{
					// if any transition is over
					if(gGT->pushBuffer_UI.fadeFromBlack_currentValue > 0xfff)
					{
						DECOMP_AH_Map_Main();

						if(sdata->AkuHint_RequestedHint != -1)
						{
							DECOMP_AH_MaskHint_Start(
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

						#ifndef REBUILD_PS1
						INSTANCE_LevDelayedLInBs(
							gGT->level1->ptrInstDefs,
							gGT->level1->numInstances);
						#endif

						// allow instances again
						gGT->gameMode2 &= ~(DISABLE_LEV_INSTANCE);

						// fade transition
						gGT->pushBuffer_UI.fadeFromBlack_desiredResult = 0x1000;
						gGT->pushBuffer_UI.fade_step = 0x2aa;
					}
				}
			}
		}
	}

	// if drawing intro-race title bars
	else
	{
		#ifndef REBUILD_PS1
		UI_RaceStart_IntroText1P();
		#endif
	}
}

#ifndef REBUILD_PS1
void RenderAllBeakerRain(struct GameTracker* gGT)
{
	int numPlyrCurrGame = gGT->numPlyrCurrGame;

	// only for 1P/2P
	if(numPlyrCurrGame > 2) return;

	// only if beaker rain is enabled
	if((gGT->renderFlags & 0x10) == 0) return;

	RedBeaker_RenderRain(
		&gGT->pushBuffer[0],
		&gGT->backBuffer->primMem,
		&gGT->JitPools.rain,
		numPlyrCurrGame,
		gGT->gameMode1 & PAUSE_ALL);
}

void RenderAllBoxSceneSplitLines(struct GameTracker* gGT)
{
	// check 233 overlay, cause levelID is set
	// and MainFrame_RenderFrame runs, before 233 loads
	if(DECOMP_LOAD_IsOpen_Podiums() != 0)
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
		gGT->gameMode1 & PAUSE_ALL);

	RBI = RenderBucket_QueueNonLevInstances(
		gGT->JitPools.instance.taken.first,
		&gGT->backBuffer->otMem,
		RBI,
		sdata->LOD[lod],
		numPlyrCurrGame,
		gGT->gameMode1 & PAUSE_ALL);

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
			&gGT->pushBuffer[i],
			gGT->particleList_ordinary);
	}
}
#endif

void RenderDispEnv_World(struct GameTracker* gGT)
{
	int i;
	struct PushBuffer* pb;
	for(i = 0; i < gGT->numPlyrCurrGame; i++)
	{
		pb = &gGT->pushBuffer[i];
		DECOMP_PushBuffer_SetDrawEnv_Normal(
			&pb->ptrOT[0x3ff], pb, gGT->backBuffer, 0, 0);
	}
}

#ifndef REBUILD_PS1
// I need a better name
void RenderAllFlag0x40(struct GameTracker* gGT)
{
	if((gGT->renderFlags & 0x40) == 0) return;

	if(DECOMP_LOAD_IsOpen_RacingOrBattle() != 0)
	{
		RB_Player_ToggleInvisible();
		RB_Player_ToggleFlicker();
		RB_Burst_ProcessBucket(gGT->threadBuckets[BURST].thread);
		RB_Blowup_ProcessBucket(gGT->threadBuckets[BLOWUP].thread);

		DECOMP_RB_Spider_DrawWebs(gGT->threadBuckets[SPIDER].thread, &gGT->pushBuffer[0]);
		DECOMP_RB_Follower_ProcessBucket(gGT->threadBuckets[FOLLOWER].thread);

		// skipping RB_StartText_ProcessBucket, it's empty in 231
	}

	if(DECOMP_LOAD_IsOpen_AdvHub() != 0)
	{
		if((gGT->gameMode1 & ADVENTURE_ARENA) != 0)
		{
			DECOMP_AH_WarpPad_AllWarppadNum();
		}
	}

	VehTurbo_ProcessBucket(gGT->threadBuckets[TURBO].thread);

	int i;
	struct PushBuffer* pb;
	for(i = 0; i < gGT->numPlyrCurrGame; i++)
	{
		pb = &gGT->pushBuffer[i];
		VehGroundSkids_Main(gGT->threadBuckets[PLAYER].thread, pb);
		VehGroundSkids_Main(gGT->threadBuckets[ROBOT].thread, pb);
	}
}

void RenderAllTitleDPP(struct GameTracker* gGT)
{
	if((gGT->gameMode1 & MAIN_MENU) == 0) return;
	if(DECOMP_LOAD_IsOpen_MainMenu() == 0) return;
	DECOMP_MM_Title_SetTrophyDPP();
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
	VehGroundShadow_Main();
}

void RenderAllHeatParticles(struct GameTracker* gGT)
{
	if((gGT->renderFlags & 0x800) == 0) return;

	Torch_Main(
		gGT->particleList_heatWarp,
		&gGT->pushBuffer[0],
		&gGT->backBuffer->primMem,
		gGT->numPlyrCurrGame,
		gGT->swapchainIndex * 0x128);
}

#ifdef USE_HIGHMP

void RenderAllLevelGeometry(struct GameTracker* gGT)
{
	int i;
	int distToScreen;
	int numPlyrCurrGame;
	struct Level* level1;
	struct PushBuffer* pushBuffer;
	struct mesh_info* ptr_mesh_info;

	level1 = gGT->level1;
	if(level1 == 0) return;

	ptr_mesh_info = level1->ptr_mesh_info;
	if(ptr_mesh_info == 0) return;

	numPlyrCurrGame = gGT->numPlyrCurrGame;

	// === Temporary 60FPS macros ===
	// Emulate 30fps on 60fps for SCVert and OVert

	// if no SCVert
	if((level1->configFlags & 4) == 0)
	{
		// assume OVert (no primitives generated here)
		AnimateWater1P(FPS_HALF(gGT->timer), level1->numWaterVertices,
			level1->ptr_water, level1->ptr_tex_waterEnvMap,
			gGT->visMem1->visOVertList[0]);
	}

	// if SCVert
	else
	{
		// draw SCVert (no primitives generated here
		AnimateQuad(gGT->timer << FPS_LEFTSHIFT(7),
			level1->numSCVert, level1->ptrSCVert,
			gGT->visMem1->visSCVertList[0]);
	}

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
		distToScreen = gGT->pushBuffer[0].distanceToScreen_PREV;

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

	// backup
	struct Driver* d0 = gGT->drivers[0];
	struct CameraDC dc0;
	memcpy(&dc0, &gGT->cameraDC[0], sizeof(struct CameraDC));

	for(int i = 0; i < numPlyrCurrGame; i++)
	{
		pushBuffer = &gGT->pushBuffer[i];

		CTR_ClearRenderLists_1P2P(gGT, 1);
		RenderLists_PreInit();

		if(i != 0)
		{
			gGT->drivers[0] = gGT->drivers[i];
			memcpy(&gGT->cameraDC[0], &gGT->cameraDC[i], sizeof(struct CameraDC));
		}

		int backup = gGT->numPlyrCurrGame;
		gGT->numPlyrCurrGame = 1;
		if((gGT->renderFlags & 0x21) != 0)
			MainFrame_VisMemFullFrame(gGT, gGT->level1);
		gGT->numPlyrCurrGame = backup;

		// patch RenderLists_Init1P2P to have max LOD
		*(short*)0x80070090 = 0;
		*(short*)0x80070092 = 0x3408;

		RenderLists_Init1P2P(
			ptr_mesh_info->bspRoot,
			level1->visMem->visLeafList[0],
			pushBuffer,
			&gGT->LevRenderLists[0],
			level1->visMem->bspList[0],
			numPlyrCurrGame);

		// 226-229
		DrawLevelOvr1P(
			&gGT->LevRenderLists[0],
			pushBuffer,
			ptr_mesh_info,
			&gGT->backBuffer->primMem,
			gGT->visMem1->visFaceList[0],
			level1->ptr_tex_waterEnvMap); // waterEnvMap?

		DrawSky_Full(
			level1->ptr_skybox,
			pushBuffer,
			&gGT->backBuffer->primMem);

		// skybox gradient
		if((level1->configFlags & 1) != 0)
		{
			CAM_SkyboxGlow(
				&level1->glowGradient[0],
				pushBuffer,
				&gGT->backBuffer->primMem,
				&pushBuffer->ptrOT[0x3ff]);
		}
	}

	// restore
	gGT->drivers[0] = d0;
	memcpy(&gGT->cameraDC[0], &dc0, sizeof(struct CameraDC));
}

#else

void RenderAllLevelGeometry(struct GameTracker* gGT)
{
	int i;
	int distToScreen;
	int numPlyrCurrGame;
	struct Level* level1;
	struct PushBuffer* pushBuffer;
	struct mesh_info* ptr_mesh_info;

	level1 = gGT->level1;
	if(level1 == 0) return;

	ptr_mesh_info = level1->ptr_mesh_info;
	if(ptr_mesh_info == 0) return;

	numPlyrCurrGame = gGT->numPlyrCurrGame;

	if(numPlyrCurrGame == 1)
	{
		CTR_ClearRenderLists_1P2P(gGT, 1);

		// === Temporary 60FPS macros ===
		// Emulate 30fps on 60fps for SCVert and OVert

		// if no SCVert
		if((level1->configFlags & 4) == 0)
		{
			// assume OVert (no primitives generated here)
			AnimateWater1P(FPS_HALF(gGT->timer), level1->numWaterVertices,
				level1->ptr_water, level1->ptr_tex_waterEnvMap,
				gGT->visMem1->visOVertList[0]);
		}

		// if SCVert
		else
		{
			// draw SCVert (no primitives generated here
			AnimateQuad(gGT->timer << FPS_LEFTSHIFT(7),
				level1->numSCVert, level1->ptrSCVert,
				gGT->visMem1->visSCVertList[0]);
		}

		// camera of player 1
		pushBuffer = &gGT->pushBuffer[0];

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
			distToScreen = pushBuffer->distanceToScreen_PREV;

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

		RenderLists_PreInit();
		gGT->bspLeafsDrawn = 0;

		gGT->bspLeafsDrawn +=
		  RenderLists_Init1P2P(
			ptr_mesh_info->bspRoot,
			level1->visMem->visLeafList[0],
			pushBuffer,
			&gGT->LevRenderLists[0],
			level1->visMem->bspList[0],
			numPlyrCurrGame);

		// 226-229
		DrawLevelOvr1P(
			&gGT->LevRenderLists[0],
			pushBuffer,
			ptr_mesh_info,
			&gGT->backBuffer->primMem,
			gGT->visMem1->visFaceList[0],
			level1->ptr_tex_waterEnvMap); // waterEnvMap?

		DrawSky_Full(
			level1->ptr_skybox,
			pushBuffer,
			&gGT->backBuffer->primMem);

		// skybox gradient
		if((level1->configFlags & 1) != 0)
		{
			goto SkyboxGlow;
		}

		return;
	}

	if(numPlyrCurrGame == 2)
	{
		CTR_ClearRenderLists_1P2P(gGT, 2);

		// if no SCVert
		if((level1->configFlags & 4) == 0)
		{
			// assume OVert (no primitives generated here)
			AnimateWater2P(gGT->timer, level1->numWaterVertices,
				level1->ptr_water, level1->ptr_tex_waterEnvMap,
				gGT->visMem1->visOVertList[0],
				gGT->visMem1->visOVertList[1]);
		}

		RenderLists_PreInit();
		gGT->bspLeafsDrawn = 0;

		for(i = 0; i < numPlyrCurrGame; i++)
		{
			gGT->bspLeafsDrawn +=
			  RenderLists_Init1P2P(
				ptr_mesh_info->bspRoot,
				level1->visMem->visLeafList[i],
				&gGT->pushBuffer[i],
				&gGT->LevRenderLists[i],
				level1->visMem->bspList[i],
				numPlyrCurrGame);
		}

		// 226-229
		DrawLevelOvr2P(
			&gGT->LevRenderLists[0],
			&gGT->pushBuffer[0],
			ptr_mesh_info,
			&gGT->backBuffer->primMem,
			gGT->visMem1->visFaceList[0],
			gGT->visMem1->visFaceList[1],
			level1->ptr_tex_waterEnvMap); // waterEnvMap?

		goto SkyboxGlow;
	}

	// 3P or 4P
	CTR_ClearRenderLists_3P4P(gGT, numPlyrCurrGame);

	// if no SCVert
	if((level1->configFlags & 4) == 0)
	{
		if(numPlyrCurrGame == 3)
		{
			// assume OVert (no primitives generated here)
			AnimateWater3P(gGT->timer, level1->numWaterVertices,
				level1->ptr_water, level1->ptr_tex_waterEnvMap,
				gGT->visMem1->visOVertList[0],
				gGT->visMem1->visOVertList[1],
				gGT->visMem1->visOVertList[2]);
		}

		else // 4P mode
		{
			// assume OVert (no primitives generated here)
			AnimateWater4P(gGT->timer, level1->numWaterVertices,
				level1->ptr_water, level1->ptr_tex_waterEnvMap,
				gGT->visMem1->visOVertList[0],
				gGT->visMem1->visOVertList[1],
				gGT->visMem1->visOVertList[2],
				gGT->visMem1->visOVertList[3]);
		}
	}

	RenderLists_PreInit();
	gGT->bspLeafsDrawn = 0;

	for(i = 0; i < numPlyrCurrGame; i++)
	{
		gGT->bspLeafsDrawn +=
		  RenderLists_Init3P4P(
			ptr_mesh_info->bspRoot,
			level1->visMem->visLeafList[i],
			&gGT->pushBuffer[i],
			&gGT->LevRenderLists[i],
			level1->visMem->bspList[i]);
	}

	if(numPlyrCurrGame == 3)
	{
		// 226-229
		DrawLevelOvr3P(
			&gGT->LevRenderLists[0],
			&gGT->pushBuffer[0],
			ptr_mesh_info,
			&gGT->backBuffer->primMem,
			gGT->visMem1->visFaceList[0],
			gGT->visMem1->visFaceList[1],
			gGT->visMem1->visFaceList[2],
			level1->ptr_tex_waterEnvMap); // waterEnvMap?
	}

	else // 4P mode
	{
		// 226-229
		DrawLevelOvr4P(
			&gGT->LevRenderLists[0],
			&gGT->pushBuffer[0],
			ptr_mesh_info,
			&gGT->backBuffer->primMem,
			gGT->visMem1->visFaceList[0],
			gGT->visMem1->visFaceList[1],
			gGT->visMem1->visFaceList[2],
			gGT->visMem1->visFaceList[3],
			level1->ptr_tex_waterEnvMap); // waterEnvMap?
	}

SkyboxGlow:

	// skybox gradient
	for(i = 0; i < numPlyrCurrGame; i++)
	{
		pushBuffer = &gGT->pushBuffer[i];
		CAM_SkyboxGlow(
			&level1->glowGradient[0],
			pushBuffer,
			&gGT->backBuffer->primMem,
			&pushBuffer->ptrOT[0x3ff]);
	}

	return;
}

#endif // USE_HIGHMP

#endif // Rebuild_PS1

void MultiplayerWumpaHUD(struct GameTracker* gGT)
{
	// must also work for 1P, or Online breaks
	for(int i = 0; i < gGT->numPlyrCurrGame; i++)
	{
		struct Driver* d = gGT->drivers[i];

		// if race is over for driver
		if((d->actionsFlagSet & 0x2000000) != 0)
		{
			struct Instance* instFruitDisp =
				d->instFruitDisp;

			instFruitDisp->scale[0] = 0;
			instFruitDisp->scale[1] = 0;
			instFruitDisp->scale[2] = 0;
		}
	}

	if((gGT->hudFlags & 1) == 0) return;
	if(gGT->numPlyrCurrGame < 2) return;

	// we just draw 3D Wumpa instead of 2D,
	// come back to this later for purists
	#if 0
	UI_RenderFrame_Wumpa3D_2P3P4P(gGT);
	#endif
}

#ifndef USE_ONLINE
void WindowBoxLines(struct GameTracker* gGT)
{
	int i;

	// only battle and 3P4P mode allowed
	if((gGT->gameMode1 & BATTLE_MODE) == 0) return;
	if(gGT->numPlyrCurrGame < 3) return;

	for(i = 0; i < gGT->numPlyrCurrGame; i++)
	{
		Color color;
		color.self = *data.ptrColor[gGT->drivers[i]->BattleHUD.teamID + PLAYER_BLUE];
		DECOMP_RECTMENU_DrawOuterRect_LowLevel(

			// dimensions, thickness
			&gGT->pushBuffer[i].rect,4,2,

			// color data
			color,

			0,

			// pushBuffer_UI = 0x1388
			&gGT->pushBuffer_UI.ptrOT[3]);
	}
}

void WindowDivsionLines(struct GameTracker* gGT)
{
	POLY_F4* p;
	int numPlyrCurrGame;

	numPlyrCurrGame = gGT->numPlyrCurrGame;

	// horizontal bar
#ifdef USE_NEW2P
	if (numPlyrCurrGame > 2)
#else
    if (numPlyrCurrGame > 1)
#endif
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
		AddPrim(&gGT->pushBuffer_UI.ptrOT[3],p);

		gGT->backBuffer->primMem.curr = (void*)(p + 1);
    }

	// vertical bar
#ifdef USE_NEW2P
	if (numPlyrCurrGame > 1)
#else
    if (numPlyrCurrGame > 2)
#endif
	{
		// test for USE_NEW2P
		#if 0
		gGT->drivers[0]->numWumpas = 10;
		gGT->drivers[0]->heldItemID = 3;
		gGT->drivers[1]->numWumpas = 10;
		gGT->drivers[1]->heldItemID = 3;
		#endif

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
		AddPrim(&gGT->pushBuffer_UI.ptrOT[3],p);

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
		AddPrim(&gGT->pushBuffer_UI.ptrOT[3],p);

		// backBuffer->primMem.curr
		gGT->backBuffer->primMem.curr = (void*)(p + 1);
    }
}
#endif

void RenderDispEnv_UI(struct GameTracker* gGT)
{
	struct PushBuffer* pb = &gGT->pushBuffer_UI;

	DECOMP_PushBuffer_SetDrawEnv_Normal(
		&pb->ptrOT[4], pb, gGT->backBuffer, 0, 0);
}

__attribute__((optimize("O0")))
int ReadyToFlip(struct GameTracker* gGT)
{
	return

			// if DrawOTag finished
			(gGT->bool_DrawOTag_InProgress == 0) &&

			// two VSYNCs passed, 30fps lock
			(sdata->vsyncTillFlip < 1);
}

__attribute__((optimize("O0")))
int ReadyToBreak(struct GameTracker* gGT)
{
	return

		// if more than 6 VSYNCs passed since
		// the last successful draw, FPS < 10fps
		gGT->vSync_between_drawSync > 6;
}

#ifdef USE_ONLINE
#include "../AltMods/OnlineCTR/global.h"
#endif

void RenderVSYNC(struct GameTracker* gGT)
{
	// render checkered flag
	if((gGT->renderFlags & 0x1000) != 0)
	{
		VSync(0);
	}

	#ifdef USE_ONLINE
	int boolFirstFrame = 1;
	#endif

	while(1)
	{

#ifdef REBUILD_PC
		// must be called in the loop,
		// or else it wont properly sync
		DrawSync(0);
#endif

		if(ReadyToFlip(gGT))
		{
			// quit, end of stall
			return;
		}

#ifdef USE_ONLINE
		// gpu submission is not too late,
		// we got to this while() loop before
		// the flip was ready, so we're on-time
		boolFirstFrame = 0;
#endif

#ifndef REBUILD_PC
		if(ReadyToBreak(gGT))
		{
			// just quit and try the next frame
			BreakDraw();
			return;
		}
#endif
	}
}

#ifndef REBUILD_PS1
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
#endif

void RenderSubmit(struct GameTracker* gGT)
{
	// 1 VSYNC = 60fps
	// 2 VSYNCs = 30fps

#ifdef REBUILD_PC

	sdata->vsyncTillFlip = FPS_HALF(2);
#else

	// do I need the "if"? will it ever be nullptr?
	if(gGT->frontBuffer != 0)
	{
		sdata->vsyncTillFlip = FPS_HALF(2);

		// skip debug stuff

		PutDispEnv(&gGT->frontBuffer->dispEnv);
		PutDrawEnv(&gGT->frontBuffer->drawEnv);
	}

	// swap=0, get db[1]
	// swap=1, get db[0]
	gGT->frontBuffer = &gGT->db[1 - gGT->swapchainIndex];
#endif

	gGT->bool_DrawOTag_InProgress = 1;

	void* ot = &gGT->pushBuffer[0].ptrOT[0x3ff];

#if 0 && defined(USE_ONLINE)
	void OnlineMirrorMode(u_long* ot);
	OnlineMirrorMode(ot);
#endif

	DrawOTag(ot);

	gGT->frameTimer_notPaused = gGT->frameTimer_VsyncCallback;
}

#include "../AltMods/Mods7.c"

void __attribute__ ((section (".end"))) Mods7_EndOfFile()
{
	// leave empty
}