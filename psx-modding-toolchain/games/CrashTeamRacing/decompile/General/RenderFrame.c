#include <common.h>

void DrawControllerError(struct GameTracker* gGT, struct GamepadSystem* gGamepads);

void RenderFrame(struct GameTracker* gGT, struct GamepadSystem* gGamepads)
{
	DrawControllerError(gGT, gGamepads);
	DrawFinalLap(gGT);
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
	if((gGT->gameMode1 & GAME_CUSTSCENE) != 0) return;
	if(BoolAllPadsConnected(gGT->numScreens) == 1) return;
	
	// if main menu is open, assume 230 loaded,
	// quit if menu is at highest level (no ptrNext to draw)
	if(sdata->ptrActiveMenuBox == 0x800B4540)
		if((*(int*)800b4548 & 0x10) == 0) return;
	
	// position of erro
	posY = data.errorPosY[sdata->errorMessagePosIndex];
	posY2 = posY;

	// "Controller 1" or "Controller 2"
	lngArrStart = 0;
	
	window.x = 0xffec;
	window.y = posY - 3;
	window.w = 0x228;
	window.h = 0;
	
	// if more than 2 players, or if multitap used
	if(
		(gGT->numScreens > 2) || 
		(gGamepads->slotBuffer[0].meta[1] == -0x80)
	)
	{
		// change to "1A", "1B", "1C", "1D",
		lngArrStart = 2;
	}
	
	for(i = 0; i < numScreens; i++)
	{
		// yes, char*, not short*
		char* ptrRawInput = gGamepads->gamepad[i].ptrRawInput;
		
		if(ptrRawInput == 0) continue;
		if(ptrRawInput[0] == 0) continue;
		
		// if controller is unplugged
		
		DecalFont_DrawLine(
			sdata->lngStrings
			[
				data.lngIndex_gamepadUnplugged[lngArrStart + i]
			],
			0x100, window.h, 2, 0xffff8000);

		// add for each line
		window.h += 8;
	}
	
	// PLEASE CONNECT A CONTROLLER
	DecalFont_DrawLine(
		sdata->lngStrings[0xac/4],
		0x100, posY2, 2, 0xffff8000);
		
	// add for each line
	window.h += 8;
	
	// add 3 pixels above, 3 pixels bellow
	window.h += 6;
		
	DrawTextBackground(&window, 1, sdata->gGT->backBuffer->otMem.startPlusFour);
}

void DrawFinalLap(struct GameTracker* gGT)
{
	int i;
	int textTimer;
	struct Camera110* c110;
	
	int startX;
	int endX;
	int posY;
	
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
		c110 = gGT->camera110[i];
		
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

		

	}
}