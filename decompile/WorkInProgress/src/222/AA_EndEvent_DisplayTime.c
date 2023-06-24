#include <common.h>

void AA_EndEvent_DisplayTime(short driverId, short param_2)
{

	struct GameTracker *gGT;
	struct Driver *driver;
	struct UiElement2D **hudArray;
	struct UiElement2D *hud;
	char numPlyr, tenseconds;
	short framesElapsed;
	short lerpStartY;
	short lerpEndY;
	short lerpStartX;
	short lerpEndX;
	short currFrame;
	short width;
	short sVar1;
	short sVar2;
	short endFrame;
	short *posXY;
	RECT r;

	gGT = sdata->gGT;
	numPlyr = gGT->numPlyrCurrGame;
	driver = gGT->drivers[driverId];
	hudArray = sdata->hudStructPtr[numPlyr - 1];
	hud = hudArray[driverId];

	// Lap time box height
	switch (gGT->numLaps)
	{
	// based on number of laps
	case 7:
		r.h = 0x49;
		break;
	case 5:
		r.h = 0x44;
		break;
	default:
		// default height for 1/3 laps.
		r.h = 0x39;
		break;
	}

	// If this is player 2
	lerpEndY = 0x41;
	sVar1 = 0x89;
	sVar2 = 0xc3;

	// If this is player 1
	if (driverId == 0)
	{
		lerpEndY = -0x3d;
		sVar1 = 9;
		sVar2 = 0x3e;
	}

	// increment counter for number of frames since the player ended the race
	framesElapsed = driver->framesSinceRaceEnded_forThisDriver;
	framesElapsed++;

	if (
		// if player ended race less than 110 frames ago
		(framesElapsed < 0x6e) &&

		// If you press Cross or Circle
		((sdata->AnyPlayerTap & 0x50) != 0) &&

		// only one player
		(numPlyr == 1))
	{
		// Assume race ended 110 frames ago
		framesElapsed = 0x6e;

		sdata->numIconsEOR = numPlyr + gGT->numBotsNextGame;

		// clear gamepad input (for menus)
		MENUBOX_ClearInput();
	}

	// What is param2???

	// Prior to 300 frames,
	// Big number, Lap times, and Icons are all on screen

	// After 300 frames
	// They are all gone

	tenseconds = (300 - param_2 < framesElapsed);

	// If race ended more than 10 seconds ago.
	if (tenseconds)
	{
		lerpStartY = UI_ConvertX_2(0xffffff9c, hudArray[driverId]->x + 0x14);
		lerpStartX = -0xae;
		lerpEndX = lerpStartY;
		endFrame = 0xf;
		currFrame = framesElapsed + -300 + param_2;
		lerpStartY = lerpEndY;
	}
	// If not
	else
	{
		lerpStartY = UI_ConvertX_2(hud[4].x, hud[5].x);
		lerpStartX = lerpStartY;
		lerpStartY = UI_ConvertY_2(hud[4].y, hud[5].x);
		currFrame = framesElapsed;
		lerpEndX = -0xae;
		endFrame = 0x1e;
	}

	// interpolate fly-in
	UI_Lerp2D_Linear(&posXY[0], lerpStartX, lerpStartY, lerpEndX, lerpEndY, currFrame, endFrame);

	// Set X and Y position of Big Number
	driver->BigNumber[0]->matrix.t[0] = posXY[0];
	driver->BigNumber[0]->matrix.t[1] = posXY[1];

	// interpolate fly-in
	UI_Lerp2D_Linear(&posXY[0], hud[5].y, 0, 0x1e00, 0, currFrame, 0x1e);

	// Set scale of Big Number in HUD
	driver->BigNumber[0]->scale[0] = posXY[0];
	driver->BigNumber[0]->scale[1] = posXY[0];
	driver->BigNumber[0]->scale[2] = posXY[0];

	if (tenseconds)
	{
		lerpStartX = 0x78;
		lerpStartY = sVar1; // Not sure why either
		lerpEndX = -0x3c;
		currFrame = framesElapsed - 300 + param_2;
		endFrame = 0xf;
	}

	else
	{
		lerpStartX = hud[10].x;
		lerpStartY = hud[10].y;
		lerpEndX = 0x78;
		currFrame = framesElapsed;
		endFrame = 0x1e;
	}

	UI_Lerp2D_Linear(&posXY[0], lerpStartX, lerpStartY, lerpEndX, sVar1, currFrame, endFrame);

	UI_DrawPosSuffix(posXY[0], posXY[1], driver, 0);

	if (tenseconds)
	{
		lerpStartX = 0x150;
		lerpEndX = 0x27c;
		currFrame = framesElapsed - 300 + param_2;
		endFrame = 0xf;
	}

	else
	{
		lerpStartX = 0x218;
		lerpEndX = 0x150;
		currFrame = framesElapsed;
		endFrame = 0x1e;
	}

	UI_Lerp2D_Linear(&posXY[0], lerpStartX, sVar2, lerpEndX, lerpEndY, currFrame, endFrame);
	UI_DrawRaceClock(posXY[0], posXY[1], 1, driver);

	// "TOTAL"
	width = DecalFont_GetLineWidth(sdata->lngStrings[0xc4], 1);

	// calculate top left corner position
	r.x = (posXY[0] - width) + -6;
	r.y = (posXY[1] - r.h) + 0xd;

	// calculate size of box
	r.w = width + 0x94;
	r.h += 6;

	// Draw 2D Menu rectangle background
	MENUBOX_DrawInnerRect(&r, 4, gGT->backBuffer->otMem.startPlusFour);
	driver->framesSinceRaceEnded_forThisDriver = framesElapsed;
	return;
}
