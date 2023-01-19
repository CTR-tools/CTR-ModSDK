#include <common.h>

void RenderFrame(struct GameTracker* gGT, struct GamepadSystem* gGamepads)
{
	struct Level* lev = gGT->level1;
	unsigned int end;
	
	DrawControllerError(gGT, gGamepads);
	DrawFinalLap(gGT);
	ElimBG_HandleState(gGT);
	
	if((gGT->renderFlags & 0x21) != 0)
		VisMem_FullFrame(gGT, gGT->level1);
	
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
	
	end = (unsigned int)gGT->camera110[0].ptrOT;
	
	RenderBucket_QueueAllInstances(gGT);
	RenderAllNormalParticles(gGT);
	LinkCameraOTs(gGT); // == LinkCameraOTs ==
	
	#if 0
	// Multiplayer PixelLOD Part 2
	#endif
	
	RenderAllFlag0x40(gGT); // I need a better name
	RenderAllTitleDPP(gGT);
	
	RenderBucket_ExecuteAllInstances(gGT);
	
	RenderAllTires(gGT);
	RenderAllShadows(gGT);
	RenderAllHeatParticles(gGT);
	
	Camera110_FadeAllWindows();
	RenderAllLevelGeometry(gGT);
	
	DF_ParseOT((unsigned int)gGT->camera110[0].ptrOT + 0xffc, end);
	
	LinkCameraOTs(gGT); // == LinkCameraOTs ==
	MultiplayerWumpaHUD(gGT);
	
	#if 0
	// Multiplayer Pixel LOD Part 3
	#endif
	
	if(
		// if not cutscene
		// if not in adventure arena
		// if not in main menu
		((gGT->gameMode1 & 0x20102000) == 0) &&
		
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
      if ((gGT->gameMode1 & 0xf) == 0)
	  {
		RivalWeapons_Update();
      }

	  StartLine_Update();
    }

	// If in main menu, or in adventure arena,
	// or in End-Of-Race menu
	if ((gGT->gameMode1 & 0x302000) != 0) {
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
		CheckeredFlag_DrawSelf();
	}

	LinkCameraOT_UI(gGT);
	
	gGT->countTotalTime = 
		RCNT_GetTime_Total();
	
	RenderVSYNC(gGT);
	RenderFMV();
	
	gGT->countTotalTime =
		RCNT_GetTime_Elapsed(gGT->countTotalTime,0);
	
	RenderSubmit(gGT);
}

void DF_ParseOT(u_long* param_1, unsigned int end)
{
  u_int* header;

  int screenX;
  int screenY;
  int centerX;
  int centerY;
  int backup;

  // divide by two (more zoom out)
  // #define DIVIDE 0x200 >> 0xc

  // divide by four (original from june 1999)
  // #define DIVIDE 0x400 >> 0xc

  // divide by eight (less zoom out)
  #define DIVIDE 0x800 >> 0xc

  // original resolution
  screenX = 0x200;
  screenY = 0xd8;

  // center
  centerX = screenX >> 1;
  centerY = screenY >> 1;

  // start at beginning of OT
  header = (u_int*)param_1;

  // parse all PrimMem and OT
  while(1)
  {
	// OrderTabl header = XX-YYYYYY,
	//		Y is addr of Prim

	// Primitive header = XX-YYYYYY,
	//		if(XX==0)	Y is addr of next OT
	//		else		Y is addr of next Prim, XX = size

	// 24 bits address
	// 8 bits length
	// header = header->next
    header = (u_int *)(*header & 0xffffff | 0x80000000);

	// end loop condition
    if (header == end) break;

	// if header->length (8 bits in libgpu.h) == 0,
	// then this is not a pointer to next prim, must be ptr to OT,
	// so "continue" loop to get the next prim from this OT
	if ((*header & 0xff000000) == 0) continue;

	// 7th u_char of every primitive is a prim "code" that defines type,
	// ND's code was & 0xfc, but 0x7c is the correct logic
	switch(((P_TAG*)header)->code & 0x7c)
	{

	// 0x20 PolyF3
	// 0x48 LineF3
    case 0x20:
    case 0x48:
      ((POLY_F3*)header)->x0 = 0x200 - ((POLY_F3*)header)->x0;
      ((POLY_F3*)header)->x1 = 0x200 - ((POLY_F3*)header)->x1;
      ((POLY_F3*)header)->x2 = 0x200 - ((POLY_F3*)header)->x2;
	  backup = ((POLY_F3*)header)->x0;
	  ((POLY_F3*)header)->x0 = ((POLY_F3*)header)->x1;
	  ((POLY_F3*)header)->x1 = backup;
	  backup = ((POLY_F3*)header)->y0;
	  ((POLY_F3*)header)->y0 = ((POLY_F3*)header)->y1;
	  ((POLY_F3*)header)->y1 = backup;
      break;

	// 0x24 PolyFT3
	// 0x30 PolyG3
    case 0x24:
    case 0x30:
      ((POLY_FT3*)header)->x0 = 0x200 - ((POLY_FT3*)header)->x0;
      ((POLY_FT3*)header)->x1 = 0x200 - ((POLY_FT3*)header)->x1;
      ((POLY_FT3*)header)->x2 = 0x200 - ((POLY_FT3*)header)->x2;
	  backup = ((POLY_FT3*)header)->x0;
	  ((POLY_FT3*)header)->x0 = ((POLY_FT3*)header)->x1;
	  ((POLY_FT3*)header)->x1 = backup;
	  backup = ((POLY_FT3*)header)->y0;
	  ((POLY_FT3*)header)->y0 = ((POLY_FT3*)header)->y1;
	  ((POLY_FT3*)header)->y1 = backup;
	  backup = ((POLY_FT3*)header)->u0;
	  ((POLY_FT3*)header)->u0 = ((POLY_FT3*)header)->u1;
	  ((POLY_FT3*)header)->u1 = backup;
	  backup = ((POLY_FT3*)header)->v0;
	  ((POLY_FT3*)header)->v0 = ((POLY_FT3*)header)->v1;
	  ((POLY_FT3*)header)->v1 = backup;
      break;

	// 0x28 PolyF4
	// 0x4c LineF4
    case 0x28:
    case 0x4c:
      ((POLY_F4*)header)->x0 = 0x200 - ((POLY_F4*)header)->x0;
      ((POLY_F4*)header)->x1 = 0x200 - ((POLY_F4*)header)->x1;
      ((POLY_F4*)header)->x2 = 0x200 - ((POLY_F4*)header)->x2;
      ((POLY_F4*)header)->x3 = 0x200 - ((POLY_F4*)header)->x3;
	  backup = ((POLY_F4*)header)->x0;
	  ((POLY_F4*)header)->x0 = ((POLY_F4*)header)->x3;
	  ((POLY_F4*)header)->x3 = backup;
	  backup = ((POLY_F4*)header)->x1;
	  ((POLY_F4*)header)->x1 = ((POLY_F4*)header)->x2;
	  ((POLY_F4*)header)->x2 = backup;
	  backup = ((POLY_F4*)header)->y0;
	  ((POLY_F4*)header)->y0 = ((POLY_F4*)header)->y3;
	  ((POLY_F4*)header)->y3 = backup;
	  backup = ((POLY_F4*)header)->y1;
	  ((POLY_F4*)header)->y1 = ((POLY_F4*)header)->y2;
	  ((POLY_F4*)header)->y2 = backup;
      break;

	// 0x38 PolyG4
    case 0x38:
      ((POLY_FT4*)header)->x0 = 0x200 - ((POLY_FT4*)header)->x0;
      ((POLY_FT4*)header)->x1 = 0x200 - ((POLY_FT4*)header)->x1;
      ((POLY_FT4*)header)->x2 = 0x200 - ((POLY_FT4*)header)->x2;
      ((POLY_FT4*)header)->x3 = 0x200 - ((POLY_FT4*)header)->x3;
	  backup = ((POLY_FT4*)header)->x0;
	  ((POLY_FT4*)header)->x0 = ((POLY_FT4*)header)->x3;
	  ((POLY_FT4*)header)->x3 = backup;
	  backup = ((POLY_FT4*)header)->x1;
	  ((POLY_FT4*)header)->x1 = ((POLY_FT4*)header)->x2;
	  ((POLY_FT4*)header)->x2 = backup;
	  backup = ((POLY_FT4*)header)->y0;
	  ((POLY_FT4*)header)->y0 = ((POLY_FT4*)header)->y3;
	  ((POLY_FT4*)header)->y3 = backup;
	  backup = ((POLY_FT4*)header)->y1;
	  ((POLY_FT4*)header)->y1 = ((POLY_FT4*)header)->y2;
	  ((POLY_FT4*)header)->y2 = backup;
	  break;
	  
	// 0x2C PolyFT4
    case 0x2c:
      ((POLY_FT4*)header)->x0 = 0x200 - ((POLY_FT4*)header)->x0;
      ((POLY_FT4*)header)->x1 = 0x200 - ((POLY_FT4*)header)->x1;
      ((POLY_FT4*)header)->x2 = 0x200 - ((POLY_FT4*)header)->x2;
      ((POLY_FT4*)header)->x3 = 0x200 - ((POLY_FT4*)header)->x3;
	  backup = ((POLY_FT4*)header)->x0;
	  ((POLY_FT4*)header)->x0 = ((POLY_FT4*)header)->x3;
	  ((POLY_FT4*)header)->x3 = backup;
	  backup = ((POLY_FT4*)header)->x1;
	  ((POLY_FT4*)header)->x1 = ((POLY_FT4*)header)->x2;
	  ((POLY_FT4*)header)->x2 = backup;
	  backup = ((POLY_FT4*)header)->y0;
	  ((POLY_FT4*)header)->y0 = ((POLY_FT4*)header)->y3;
	  ((POLY_FT4*)header)->y3 = backup;
	  backup = ((POLY_FT4*)header)->y1;
	  ((POLY_FT4*)header)->y1 = ((POLY_FT4*)header)->y2;
	  ((POLY_FT4*)header)->y2 = backup;
	  backup = ((POLY_FT4*)header)->u0;
	  ((POLY_FT4*)header)->u0 = ((POLY_FT4*)header)->u3;
	  ((POLY_FT4*)header)->u3 = backup;
	  backup = ((POLY_FT4*)header)->u1;
	  ((POLY_FT4*)header)->u1 = ((POLY_FT4*)header)->u2;
	  ((POLY_FT4*)header)->u2 = backup;
	  backup = ((POLY_FT4*)header)->v0;
	  ((POLY_FT4*)header)->v0 = ((POLY_FT4*)header)->v3;
	  ((POLY_FT4*)header)->v3 = backup;
	  backup = ((POLY_FT4*)header)->v1;
	  ((POLY_FT4*)header)->v1 = ((POLY_FT4*)header)->v2;
	  ((POLY_FT4*)header)->v2 = backup;
	  break;

	// PolyGT3
    case 0x34:
      ((POLY_GT3*)header)->x0 = 0x200 - ((POLY_GT3*)header)->x0;
      ((POLY_GT3*)header)->x1 = 0x200 - ((POLY_GT3*)header)->x1;
      ((POLY_GT3*)header)->x2 = 0x200 - ((POLY_GT3*)header)->x2;
	  backup = ((POLY_GT3*)header)->x0;
	  ((POLY_GT3*)header)->x0 = ((POLY_GT3*)header)->x1;
	  ((POLY_GT3*)header)->x1 = backup;
	  backup = ((POLY_GT3*)header)->y0;
	  ((POLY_GT3*)header)->y0 = ((POLY_GT3*)header)->y1;
	  ((POLY_GT3*)header)->y1 = backup;
	  backup = ((POLY_GT3*)header)->u0;
	  ((POLY_GT3*)header)->u0 = ((POLY_GT3*)header)->u1;
	  ((POLY_GT3*)header)->u1 = backup;
	  backup = ((POLY_GT3*)header)->v0;
	  ((POLY_GT3*)header)->v0 = ((POLY_GT3*)header)->v1;
	  ((POLY_GT3*)header)->v1 = backup;
	  break;

	// PolyGT4
    case 0x3c:
      ((POLY_GT4*)header)->x0 = 0x200 - ((POLY_GT4*)header)->x0;
      ((POLY_GT4*)header)->x1 = 0x200 - ((POLY_GT4*)header)->x1;
      ((POLY_GT4*)header)->x2 = 0x200 - ((POLY_GT4*)header)->x2;
      ((POLY_GT4*)header)->x3 = 0x200 - ((POLY_GT4*)header)->x3;
	  backup = ((POLY_GT4*)header)->x0;
	  ((POLY_GT4*)header)->x0 = ((POLY_GT4*)header)->x3;
	  ((POLY_GT4*)header)->x3 = backup;
	  backup = ((POLY_GT4*)header)->x1;
	  ((POLY_GT4*)header)->x1 = ((POLY_GT4*)header)->x2;
	  ((POLY_GT4*)header)->x2 = backup;
	  backup = ((POLY_GT4*)header)->y0;
	  ((POLY_GT4*)header)->y0 = ((POLY_GT4*)header)->y3;
	  ((POLY_GT4*)header)->y3 = backup;
	  backup = ((POLY_GT4*)header)->y1;
	  ((POLY_GT4*)header)->y1 = ((POLY_GT4*)header)->y2;
	  ((POLY_GT4*)header)->y2 = backup;
	  backup = ((POLY_GT4*)header)->u0;
	  ((POLY_GT4*)header)->u0 = ((POLY_GT4*)header)->u3;
	  ((POLY_GT4*)header)->u3 = backup;
	  backup = ((POLY_GT4*)header)->u1;
	  ((POLY_GT4*)header)->u1 = ((POLY_GT4*)header)->u2;
	  ((POLY_GT4*)header)->u2 = backup;
	  backup = ((POLY_GT4*)header)->v0;
	  ((POLY_GT4*)header)->v0 = ((POLY_GT4*)header)->v3;
	  ((POLY_GT4*)header)->v3 = backup;
	  backup = ((POLY_GT4*)header)->v1;
	  ((POLY_GT4*)header)->v1 = ((POLY_GT4*)header)->v2;
	  ((POLY_GT4*)header)->v2 = backup;
      break;

	// LineF2
    case 0x40:
      ((LINE_F2*)header)->x0 = 0x200 - ((LINE_F2*)header)->x0;
      ((LINE_F2*)header)->x1 = 0x200 - ((LINE_F2*)header)->x1;
	  break;

	// LineG2
    case 0x50:
      ((LINE_G2*)header)->x0 = 0x200 - ((LINE_G2*)header)->x0;
      ((LINE_G2*)header)->x1 = 0x200 - ((LINE_G2*)header)->x1;
	  break;

	// does this even exist?
	#if 0
	// LineG4
	case 0x5C:
	  ((LINE_G4*)header)->x0 = ((((LINE_G4*)header)->x0 -centerX) * DIVIDE) + centerX;
      ((LINE_G4*)header)->x1 = ((((LINE_G4*)header)->x1 -centerX) * DIVIDE) + centerX;
      ((LINE_G4*)header)->x2 = ((((LINE_G4*)header)->x2 -centerX) * DIVIDE) + centerX;
      ((LINE_G4*)header)->x3 = ((((LINE_G4*)header)->x3 -centerX) * DIVIDE) + centerX;
	  break;
	#endif
	default:
		break;
	}
  };
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
	if(BoolAllPadsConnected(gGT->numPlyrNextGame) == 1) return;
	
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
			0x100, posY + window.h, 2, 0xffff8000);

		// add for each line
		window.h += 8;
	}
	
	// PLEASE CONNECT A CONTROLLER
	DecalFont_DrawLine(
		sdata->lngStrings[0xac/4],
		0x100, posY + window.h, 2, 0xffff8000);
		
	// add for each line
	window.h += 8;
	
	// add 3 pixels above, 3 pixels bellow
	window.h += 6;
		
	DrawTextBackground(&window, 1, gGT->backBuffer->otMem.startPlusFour);
}

void DrawFinalLap(struct GameTracker* gGT)
{
	int i;
	int textTimer;
	struct Camera110* c110;
	
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
		c110 = &gGT->camera110[i];
		
		// << 0x10, >> 0x12
		posY = c110->rect.h / 4;
		
		// fly from right to center
		if(textTimer < 11)
		{
			startX = c110->rect.w + 100;
			endX = c110->rect.w / 2;

			goto DrawFinalLapString;
		}
		
		// sit in center
		if(textTimer < 0x51)
		{
			startX = c110->rect.w / 2;
			endX = startX;
			
			// for duration
			textTimer -= 10;

			goto DrawFinalLapString;
		}

		// fly from center to left
		startX = c110->rect.w / 2;
		endX = -100;
		textTimer -= 0x50;
		
DrawFinalLapString:

		InterpolatePosition2D_Linear(&resultPos, startX, posY, endX, posY, 10);

		// need to specify OT, or else "FINAL LAP" will draw on top of character icons,
		// and by doing this, "FINAL LAP" draws under the character icons instead
		DecalFont_DrawLineOT(
			sdata->lngStrings[0x8cc/4],
			resultPos[0], resultPos[1],
			1, 0xffff8000,
			c110->ptrOT);
			
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
		Camera110_UpdateFrustum(&gGT->camera110[i]);
		
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
		&gGT->camera110[0],
		&gGT->backBuffer->primMem,
		&gGT->rainBuffer[0],
		numPlyrCurrGame,
		gGT->gameMode1 & 0xf);
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
			&gGT->camera110[gGT->winnerIndex[i]],
			&gGT->backBuffer->primMem,
			&gGT->confetti,
			gGT->frameTimer_Confetti,
			gGT->gameMode1 & 0xf);
	}
}

void RenderAllStars(struct GameTracker* gGT)
{
	// only if stars are enabled
	if((gGT->renderFlags & 8) == 0) return;

	// quit if no stars exist
	if(gGT->stars.numStars == 0) return;

	RenderStars(
		&gGT->camera110[0],
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
		((gameMode1 & RACE_INTRO_CUTSCENE) == 0)
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
						DrawHUD_Racing();
					}
					
					// if crystal challenge
					else
					{
						DrawHUD_CrystalChallenge();
					}
				}
				
				// drawing end of race
				else
				{
					if((gameMode1 & (ADVENTURE_MODE | ARCADE_MODE)) != 0)
					{
						AA_EndEvent_DrawMenu();
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
					
					if((gGT->gameMode2 & ARCADE_VS_CUP) != 0)
					{
						// disable drawing hud,
						// enable drawing "standings"
						gGT->hudFlags = (hudFlags & 0xfe) | 4;
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
					if(gGT->camera110_UI.fadeFromBlack_currentValue > 0xfff)
					{
						DrawHUD_AdvStrings();
					}
				}
				
				// if 232 overlay is loaded
				else
				{
					// if any transition is over
					if(gGT->camera110_UI.fadeFromBlack_currentValue > 0xfff)
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
						
						INSTANCE_LevRestartLInBs(
							gGT->level1->ptrInstDefs,
							gGT->level1->numInstances);
							
						// allow instances again
						gGT->gameMode2 &= ~(DISABLE_LEV_INSTANCE);

						// fade transition
						gGT->camera110_UI.fadeFromBlack_desiredResult = 0x1000;
						gGT->camera110_UI.fade_step = 0x2aa;
					}
				}
			}
		}
	}
	
	// if drawing intro-race title bars
	else
	{
		DrawIntroRaceText_1P();
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
		&gGT->camera110[0],
		&gGT->backBuffer->primMem,
		&gGT->AllocPools.rain,
		numPlyrCurrGame,
		gGT->gameMode1 & 0xf);
}

void RenderAllBoxSceneSplitLines(struct GameTracker* gGT)
{
	// check 233 overlay, cause levelID is set
	// and RenderFrame runs, before 233 loads
	if(LOAD_IsOpen_Podiums() != 0)
	{
		// ND Box Scene
		if(gGT->levelID == 0x29)
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
		gGT->gameMode1 & 0xf);
		
	RBI = RenderBucket_QueueNonLevInstances(
		gGT->AllocPools.instance.taken.first,
		&gGT->backBuffer->otMem,
		RBI,
		sdata->LOD[lod],
		numPlyrCurrGame,
		gGT->gameMode1 & 0xf);
		
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
			&gGT->camera110[i],
			gGT->particleList_ordinary);
	}
}

void LinkCameraOTs(struct GameTracker* gGT)
{
	int i;
	struct Camera110* c110;
	for(i = 0; i < gGT->numPlyrCurrGame; i++)
	{
		c110 = &gGT->camera110[i];
		Camera110_LinkOT_Normal(
			(unsigned int)c110->ptrOT + 0xffc,
			c110, gGT->backBuffer, 0, 0);
	}
}

// I need a better name
void RenderAllFlag0x40(struct GameTracker* gGT)
{
	int i;
	struct Camera110* c110;
	
	if((gGT->renderFlags & 0x40) == 0) return;
	
	if(LOAD_IsOpen_RacingOrBattle() != 0)
	{
		RB_Player_ToggleInvisible();
		RB_Player_ToggleFlicker();
		RB_Burst_ProcessBucket(gGT->threadBuckets[BURST].thread);
		RB_Blowup_ProcessBucket(gGT->threadBuckets[BLOWUP].thread);
		RB_Spider_DrawWebs(gGT->threadBuckets[SPIDER].thread, &gGT->camera110[0]);
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
		c110 = &gGT->camera110[i];
		DrawSkidMarks_Main(gGT->threadBuckets[PLAYER].thread, c110);
		DrawSkidMarks_Main(gGT->threadBuckets[ROBOT].thread, c110);
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
	
	DrawHeat_Main(
		gGT->particleList_heatWarp,
		&gGT->camera110[0],
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
	struct Camera110* c110;
	struct mesh_info* ptr_mesh_info;
	
	if((gGT->renderFlags & 1) == 0) return;
	
	level1 = gGT->level1;
	if(level1 == 0) return;
	
	ptr_mesh_info = level1->ptr_mesh_info;
	if(ptr_mesh_info == 0) return;
	
	numPlyrCurrGame = gGT->numPlyrCurrGame;
	
	if(numPlyrCurrGame == 1)
	{	
		CTR_ClearRenderLists_1P2P(gGT, 1);
		
		// if no SCVert
		if((level1->configFlags & 4) == 0)
		{
			// assume OVert (no primitives generated here)
			AnimateWater1P(gGT->timer, level1->count_water,
				level1->ptr_water, level1->ptr_tex_waterEnvMap,
				gGT->visMem1->Water_Bit_Visibility[0]);
		}
		
		// if SCVert
		else
		{
			// draw SCVert (no primitives generated here
			AnimateQuad(gGT->timer << 7, 
				level1->numSCVert, level1->ptrSCVert,
				gGT->visMem1->AnimatedVertex_Bit_Visibility[0]);
		}
		
		// camera of player 1
		c110 = &gGT->camera110[0];
		
		if(
			// adv character selection screen
			(gGT->levelID == 0x28) ||
			
			// cutscene that's not Crash Bandicoot intro
			// where he's sleeping and snoring on a hill
			(
				((gGT->gameMode1 & GAME_CUTSCENE) != 0) &&
				(gGT->levelID != 0x25)
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
			distToScreen = c110->distanceToScreen_PREV;
			
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
			level1->visMem->VisDataLeaf_Bit_Visibility[0],
			c110,
			&gGT->LevRenderLists[0],
			level1->visMem->VisData_List_Memory[0],
			gGT->numPlyrCurrGame);
			
		// 226-229
		DrawLevelPrims_EntryFunc(
			&gGT->LevRenderLists[0],
			c110,
			ptr_mesh_info,
			&gGT->backBuffer->primMem,
			gGT->visMem1->QuadBlock_Bit_Visibliity[0],
			level1->ptr_tex_waterEnvMap); // waterEnvMap?
			
		DrawSky_Full(
			level1->ptr_skybox,
			c110,
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
			AnimateWater2P(gGT->timer, level1->count_water,
				level1->ptr_water, level1->ptr_tex_waterEnvMap,
				gGT->visMem1->Water_Bit_Visibility[0],
				gGT->visMem1->Water_Bit_Visibility[1]);
		}
		
		VisData_CopyJMPsToScratchpad();
		gGT->numVisDataLinks = 0;
		
		for(i = 0; i < numPlyrCurrGame; i++)
		{
			gGT->numVisDataLinks += 
			  CreateRenderLists_1P2P(
				ptr_mesh_info->ptrVisDataArray,
				level1->visMem->VisDataLeaf_Bit_Visibility[i],
				&gGT->camera110[i],
				&gGT->LevRenderLists[i],
				level1->visMem->VisData_List_Memory[i],
				gGT->numPlyrCurrGame);
		}
		
		// 226-229
		DrawLevelPrims_EntryFunc(
			&gGT->LevRenderLists[0],
			&gGT->camera110[0],
			ptr_mesh_info,
			&gGT->backBuffer->primMem,
			gGT->visMem1->QuadBlock_Bit_Visibliity[0],
			gGT->visMem1->QuadBlock_Bit_Visibliity[1],
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
			AnimateWater3P(gGT->timer, level1->count_water,
				level1->ptr_water, level1->ptr_tex_waterEnvMap,
				gGT->visMem1->Water_Bit_Visibility[0],
				gGT->visMem1->Water_Bit_Visibility[1],
				gGT->visMem1->Water_Bit_Visibility[2]);
		}
		
		else // 4P mode
		{
			// assume OVert (no primitives generated here)
			AnimateWater4P(gGT->timer, level1->count_water,
				level1->ptr_water, level1->ptr_tex_waterEnvMap,
				gGT->visMem1->Water_Bit_Visibility[0],
				gGT->visMem1->Water_Bit_Visibility[1],
				gGT->visMem1->Water_Bit_Visibility[2],
				gGT->visMem1->Water_Bit_Visibility[3]);
		}
	}
	
	VisData_CopyJMPsToScratchpad();
	gGT->numVisDataLinks = 0;
	
	for(i = 0; i < numPlyrCurrGame; i++)
	{
		gGT->numVisDataLinks += 
		  CreateRenderLists_3P4P(
			ptr_mesh_info->ptrVisDataArray,
			level1->visMem->VisDataLeaf_Bit_Visibility[i],
			&gGT->camera110[i],
			&gGT->LevRenderLists[i],
			level1->visMem->VisData_List_Memory[i]);
	}
	
	if(numPlyrCurrGame == 3)
	{
		// 226-229
		DrawLevelPrims_EntryFunc(
			&gGT->LevRenderLists[0],
			&gGT->camera110[0],
			ptr_mesh_info,
			&gGT->backBuffer->primMem,
			gGT->visMem1->QuadBlock_Bit_Visibliity[0],
			gGT->visMem1->QuadBlock_Bit_Visibliity[1],
			gGT->visMem1->QuadBlock_Bit_Visibliity[2],
			level1->ptr_tex_waterEnvMap); // waterEnvMap?
	}
	
	else // 4P mode
	{
		// 226-229
		DrawLevelPrims_EntryFunc(
			&gGT->LevRenderLists[0],
			&gGT->camera110[0],
			ptr_mesh_info,
			&gGT->backBuffer->primMem,
			gGT->visMem1->QuadBlock_Bit_Visibliity[0],
			gGT->visMem1->QuadBlock_Bit_Visibliity[1],
			gGT->visMem1->QuadBlock_Bit_Visibliity[2],
			gGT->visMem1->QuadBlock_Bit_Visibliity[3],
			level1->ptr_tex_waterEnvMap); // waterEnvMap?
	}
		
SkyboxGlow:
		
	// skybox gradient
	for(i = 0; i < numPlyrCurrGame; i++)
	{
		c110 = &gGT->camera110[i];
		CAM_SkyboxGlow(
			&level1->glowGradient[0],
			c110,
			&gGT->backBuffer->primMem,
			(unsigned int)c110->ptrOT + 0xffc);
	}
	
	return;
}

void MultiplayerWumpaHUD(struct GameTracker* gGT)
{
	if((gGT->hudFlags & 1) == 0) return;
	if(gGT->numPlyrCurrGame < 2) return;
	DrawHUD_Wumpa3D_2P3P4P(gGT);
}

void WindowBoxLines(struct GameTracker* gGT)
{
	int i;
	
	// only battle and 3P4P mode allowed
	if((gGT->gameMode1 & BATTLE_MODE) == 0) return;
	if(gGT->numPlyrCurrGame < 3) return;
	
	for(i = 0; i < gGT->numPlyrCurrGame; i++)
	{
		DrawBoxOutline_LowLevel(

			// dimensions, thickness
			&gGT->camera110[i].rect,4,2,

			// color data, 0x18 is enum offset of BLUE
			data.ptrColor[gGT->drivers[i]->BattleHUD.teamID + 0x18],

			0,

			// camera110_UI = 0x1388
			(unsigned int)gGT->camera110_UI.ptrOT + 0xC);
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
		AddPrim((unsigned int)gGT->camera110_UI.ptrOT + 0xC,p);

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
		AddPrim((unsigned int)gGT->camera110_UI.ptrOT + 0xC,p);

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
		AddPrim((unsigned int)gGT->camera110_UI.ptrOT + 0xC,p);

		// backBuffer->primMem.curr
		gGT->backBuffer->primMem.curr = (void*)(p + 1);
    }
}

void LinkCameraOT_UI(struct GameTracker* gGT)
{
	struct Camera110* c110 = &gGT->camera110_UI;
	
	Camera110_LinkOT_Normal(
		(unsigned int)c110->ptrOT + 0x10,
		c110, gGT->backBuffer, 0, 0);
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
	
	DrawOTag((unsigned int)gGT->camera110[0].ptrOT + 0xffc);
	
	gGT->frameTimer_notPaused = gGT->frameTimer_VsyncCallback;
}