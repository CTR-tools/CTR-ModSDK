#include <common.h>

void DrawControllerError(struct GameTracker* gGT, struct GamepadSystem* gGamepads);

void RenderFrame(struct GameTracker* gGT, struct GamepadSystem* gGamepads)
{
	DrawControllerError(gGT, gGamepads);
}

void DrawControllerError(struct GameTracker* gGT, struct GamepadSystem* gGamepads)
{
	int posY;
	int lngArrStart;
	
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
	
	RECT window;
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