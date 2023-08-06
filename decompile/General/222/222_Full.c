#include <common.h>

static int str_number = 0x20; // " \0"
extern struct MenuBox menuBox222_arcade;

void DECOMP_AA_EndEvent_DisplayTime(short driverId, short param_2);

void DECOMP_AA_EndEvent_DrawMenu(void)
{
	struct GameTracker *gGT;
	struct Driver *driver;
	struct UiElement2D *hudCTR;
	struct AdvProgress *adv;
	struct Instance *hudC;
	struct Instance *hudT;
	struct Instance *hudR;
	struct Instance *hudToken;
	struct CtrLetter *letter;
	char i;
	char tokenUnlock;
	char numPlyr;
	char totalPlyr;
	short t;
	short elapsedFrames;
	short letterPos[2];
	short txtPos[2];
	short levSpawn;

	short lerpStartX;
	short txtStartX;
	short lerpStartY;
	short lerpEndX;
	short txtEndX;
	short lerpEndY;
	short lerpFrames;
	short currFrame;
	u_int scaleDown;
	u_int txtColor;
	u_int bitIndex;

	gGT = sdata->gGT;
	driver = gGT->drivers[0];
	numPlyr = gGT->numPlyrCurrGame;
	totalPlyr = numPlyr + gGT->numBotsNextGame;
	adv = &sdata->advProgress;
	hudC = sdata->ptrHudC;
	hudT = sdata->ptrHudT;
	hudR = sdata->ptrHudR;
	struct Instance *hudLetters[3] = {hudC, hudT, hudR};
	hudToken = sdata->ptrToken;

	hudCTR = &data.hud_1P_P1[0x24];

	elapsedFrames = sdata->framesSinceRaceEnded;

	// count frames if hasn't been 30 seconds
	if (elapsedFrames < 900)
		elapsedFrames = sdata->framesSinceRaceEnded + 1;

	sdata->framesSinceRaceEnded = elapsedFrames;

	if (driver->BigNumber[0]->scale[0] != 0x1e00)
	{
		driver->BigNumber[1]->scale[0] = 0;
		driver->BigNumber[1]->scale[1] = 0;
		driver->BigNumber[1]->scale[2] = 0;
	}

	// if not in Token mode, these won't be used until later;
	lerpStartY = 0;
	lerpEndY = 0;

	// If you're in Adventure Mode
	if ((gGT->gameMode1 & ADVENTURE_MODE) != 0)
	{
		
		// If you won the race, and you have all 3 letters (C, T, and R)
		if ((driver->driverRank == 0) && (driver->PickupLetterHUD.numCollected == 3))
		{
			// If you have not unlocked this CTR Token
			bitIndex = gGT->levelID + 0x4C;
			*(int *)&letterPos[0] = *(int *)&hudCTR[0];
			if ((CHECK_ADV_BIT(adv->rewards, bitIndex) & 1) == 0)
			{
				scaleDown = hudC->scale[0];
				scaleDown -= (scaleDown < 0x800) ? 0x800 : 0x401;
				scaleDown = scaleDown >> 10;

				// frames since race ended
				if (elapsedFrames < 231)
				{
					if (elapsedFrames < 141)
					{
						lerpStartX = hudCTR->x;
						lerpStartY = hudCTR->y;
						lerpEndX = lerpStartX + 0x10;
						lerpEndY = lerpStartY + 0x10;
						lerpFrames = 8;
						currFrame = elapsedFrames;
						goto INTERPOLATE;
					}
					UI_Lerp2D_Linear(&letterPos[0],
									 hudCTR->x + 0x10,
									 hudCTR->y + 0x10,
									 hudCTR->x - 0x10,
									 hudCTR->y + 0x50,
									 elapsedFrames - 140, 8);

					if (hudC->scale[0] == 0x800)
						OtherFX_Play(0x67, 1);

					// increment hudc scale and hudtoken scale
					if (letterPos[0] != (hudCTR->x - 0x10))
					{
						for (i = 0; i < 3; i++)
						{
							hudLetters[i]->scale[0] += 0x400;
							hudLetters[i]->scale[1] += 0x400;
							hudLetters[i]->scale[2] += 0x400;
						}
					}
				}
				else
				{
					lerpStartX = hudCTR->x + 0x10;
					lerpStartY = hudCTR->y + 0x50;
					lerpEndX = -400;
					lerpEndY = lerpStartY;
					currFrame = elapsedFrames - 230;

				INTERPOLATE:
					UI_Lerp2D_Linear(&letterPos[0], lerpStartX, lerpStartY, lerpEndX, lerpEndY, currFrame, lerpFrames);
				}

				for (i = 0; i < 3; i++)
				{
					hudLetters[i]->matrix.t[0] = UI_ConvertX_2(letterPos[0] + (scaleDown * (i * 12)) + (i * 29), 0x200);
					hudLetters[i]->matrix.t[1] = UI_ConvertY_2(letterPos[1] - (i & 1), 0x200);
				}

				hudToken->flags &= ~HIDE_MODEL;
				hudToken->matrix.t[0] = hudT->matrix.t[0];
				hudToken->matrix.t[1] = UI_ConvertY_2(letterPos[1] + 0x18, 0x200);

				// If time has passed and token is not full scale
				if (elapsedFrames > 140 && hudToken->scale[0] < 0x2001)
				{
					hudToken->scale[0] += 0x200;
					hudToken->scale[1] += 0x200;
					hudToken->scale[2] += 0x200;
				}

				if (elapsedFrames < 231)
				{
					if (elapsedFrames > 140)
					{
						txtStartX = 0x264;
						txtEndX = 0x100;
						currFrame = elapsedFrames - 140;
						goto PRINT_TEXT;
					}
				}
				else
				{
					txtStartX = 0x100;
					txtEndX = -150;
					currFrame = elapsedFrames - 50;
				PRINT_TEXT:
					UI_Lerp2D_Linear(&txtPos[0], txtStartX, 0xA6, txtEndX, 0xA6, currFrame, 8);
					// Flash colors depending on even or odd frame
					txtColor = (gGT->timer & 1) ? 0xFFFF8003 : 0xFFFF8004;
					// CTR TOKEN AWARDED
					DecalFont_DrawLine(sdata->lngStrings[0x16F], txtPos[0], txtPos[1], 1, txtColor);
				}
				lerpStartY = 120;
				lerpEndY = 160;
			}
			// If you already have this CTR Token unlocked
			else
			{
				if (elapsedFrames > 301)
				{
					lerpStartX = hudCTR->x;
					lerpStartY = hudCTR->y;
					lerpEndX = lerpStartX + 0x10;
					lerpEndY = lerpStartY + 0x10;
					currFrame = elapsedFrames;
					lerpFrames = 8;
				}
				else
				{
					lerpStartX = hudCTR->x + 0x10;
					lerpStartY = hudCTR->y + 0x10;
					lerpEndX = -400;
					lerpEndY = lerpStartY;
					currFrame = elapsedFrames - 300;
					lerpFrames = 10;
				}
				UI_Lerp2D_Linear(&letterPos[0], lerpStartX, lerpStartY, lerpEndX, lerpEndY, currFrame, lerpFrames);

				for (i = 0; i < 3; i++)
				{
					hudLetters[i]->matrix.t[0] = UI_ConvertX_2(letterPos[0] + (i * 29), 0x200);
					hudLetters[i]->matrix.t[1] = UI_ConvertY_2(letterPos[1] - (i & 1), 0x200);
				}
			}
		}
		// If you did not collect all 3 letters (C, T, and R), or you lost the race
		else
		{
			if (elapsedFrames < 900)
			{
				for (i = 0; i < 3; i++)
				{
					if (((hudLetters[i]->flags & HIDE_MODEL) == 0) &&
						(-300 < hudLetters[i]->matrix.t[1]))
					{
						letter = hudLetters[i]->thread->object;
						// move X position
						hudLetters[i]->matrix.t[0] += letter->velX;
						// make the letter fall off the screen
						hudLetters[i]->matrix.t[1] -= letter->velY;

						if (-0x14 < letter->velY)
						{
							letter->velY -= 2;
						}
					}
				}
			}
			driver->PickupLetterHUD.numCollected = 0;
		}
	}

	for (i = 0; i < numPlyr; i++)
	{
		// Draw how much time it took to finish laps and race
		DECOMP_AA_EndEvent_DisplayTime(i, lerpEndY);
	}

	// If it hasn't been 1 second from race ended
	if (elapsedFrames < 29)
		return;

	// If there is one player
	if (numPlyr == 1)
	{
		// start counting time 1 second after race ends
		t = (elapsedFrames & 0xffff) - 30;

		if (
			// Every 0.5 seconds or so
			((t % 10 & 0xffff) == 0) &&

			// sdata->numIconsEOR is the number of icons being
			// drawn on the end-of-race menu in 1P mode

			// If you have not drawn all drivers yet
			(sdata->numIconsEOR < totalPlyr))
		{
			// add an icon to draw
			sdata->numIconsEOR++;
		}

		// if you are drawing any player icons
		if (sdata->numIconsEOR)
		{
			// loop through all the driver icons
			for (i = 0; i < sdata->numIconsEOR; i++)
			{

				int iVar11 = gGT->tileView[0].rect.x +
							 (gGT->tileView[0].rect.w - totalPlyr * 56 + 12) / 2 + (i * 56);

				if (300 - lerpEndY < elapsedFrames)
				{
					lerpStartX = iVar11;
					lerpEndX = -100;
					currFrame = (elapsedFrames - 300) + lerpEndY;
				}
				else
				{
					lerpStartX = 0x218;
					lerpEndX = iVar11;
					currFrame = t;
				}

				t -= 10;

				// interpolate fly-in
				UI_Lerp2D_Linear(&letterPos[0], lerpStartX, 0x60, lerpEndX, 0x60, currFrame, 10);

				str_number = (char)i + '1';

				// print a single character, a number 1-8,
				DecalFont_DrawLine(&str_number, letterPos[0] + 0x20, 0x5f, 2, 4);

				// Draw the driver's character icon
				UI_DrawDriverIcon(gGT->ptrIcons[data.MetaDataCharacters[data.characterIDs[gGT->driversInRaceOrder[i]->driverID]].iconID],

								  letterPos[0], 0x60,

								  // pointer to PrimMem struct
								  &gGT->backBuffer->primMem,

								  // pointer to OT mem
								  gGT->tileView_UI.ptrOT,

								  1, 0x1000, 0x808080);
			}
		}
	}

	// 0x78 + 0x6e = 0xe6 (230) frames waited for Token Race
	if (elapsedFrames < lerpStartY + 110)
		return;
	if (
		// If you are in Adventure cup
		((gGT->gameMode1 & ADVENTURE_CUP) != 0) ||

		// If you are in Arcade or VS cup
		((gGT->gameMode2 & CUP_ANY_KIND) != 0))
	{
		// but text near middle of screen
		short posX = (numPlyr < 2) ? 0xbe : 100;

		// PRESS * TO CONTINUE
		DecalFont_DrawLine(sdata->lngStrings[0xC9], 0x100, posX, 1, 0xffff8000);

		// If you do not "Press X to continue"
		if ((sdata->AnyPlayerTap & 0x50) == 0)
			return;

		// If you are here, it means you pressed X to continue

		// clear gamepad input
		MENUBOX_ClearInput();

		sdata->menuReadyToPass = 0;
		sdata->framesSinceRaceEnded = 0;
		sdata->numIconsEOR = 1;

		// Disable HUD
		gGT->hudFlags &= 0xfe;

		// Enable Cup Standings
		gGT->hudFlags |= 4;
		return;
	}

	// if the menu is already drawing
	if (sdata->menuReadyToPass & 1)
		return;

	// If you're in Arcade mode
	if ((gGT->gameMode1 & ARCADE_MODE) != 0)
	{
		// End of Race based on number of players (1 or more)
		menuBox222_arcade.posY_curr = (numPlyr == 1) ? 170 : 108;

		MENUBOX_Show(&menuBox222_arcade);

		// record that the menu is drawing
		sdata->menuReadyToPass |= 1;
		return;
	}

	// If you are in adventure mode
	if ((gGT->gameMode1 & ADVENTURE_MODE) == 0)
		return;

	// PRESS * TO CONTINUE
	DecalFont_DrawLine(sdata->lngStrings[0xc9], 0x100, 0xbe, 1, 0xffff8000);

	// If you have not pressed X
	if ((sdata->AnyPlayerTap & 0x50) == 0)
		return;

	// clear gamepad input
	MENUBOX_ClearInput();

	// if event was not won
	if (driver->driverRank > 0)
	{
		// pass pointer to menu buffer that shows Retry / Exit To Map,
		// identical to buffer in 221 dll, except this one in EXE space
		MENUBOX_Show(&data.menuBox_Retry_ExitToMap);

		// record that the menu is now showing
		sdata->menuReadyToPass |= 1;
		return;
	}

	// If you won the race
	// If you have pressed X to continue...

	sdata->framesSinceRaceEnded = 0;
	sdata->numIconsEOR = 1;

	// when loading is done, add flag for "In Adventure Arena"
	sdata->Loading.OnBegin.AddBitsConfig0 |= ADVENTURE_ARENA;

	// Load the levelID for Adventure Hub that you came from
	levSpawn = gGT->prevLEV;

	// If you are in boss mode
	if (gGT->gameMode1 < 0)
	{
		// when loading is done, add flag for "spawn near boss door"
		sdata->Loading.OnBegin.AddBitsConfig8 |= 1;

		// when loading is done, remove flag for Boss Mode
		sdata->Loading.OnBegin.RemBitsConfig0 |= ADVENTURE_BOSS;

		// bit offset 0x5e is where progress holds keys
		// This checks if you've unlocked a key,
		// by getting bit offset, converting that
		// to integer offset, and remainder
		bitIndex = gGT->bossID + 0x5e;

		// If the number of keys you have is less than 4
		if (gGT->bossID < 4)
			// Go to Podium after returning to Adventure Hub
			gGT->podiumRewardID = 99; // key

		// If you have 4 keys (only here if you beat oxide)
		else
		{
			// goes to bits after purple gem, cause bossID is 5 or 6
			bitIndex = gGT->bossID + 0x6f;

			// Go to podium, with no key (0x38 = empty)
			gGT->podiumRewardID = 0x38;

			if ((sdata->advProgress.rewards[3] & 4) == 0)
				sdata->advProgress.rewards[3] |= 0x80004;
		}

		// hot air skyway
		if (gGT->levelID == 7)
		{
			// If you just beat Pinstripe
			// Load gemstone valley
			levSpawn = 0x19;
		}
	}
	// if you are in token race
	else if ((gGT->gameMode2 & 0x8) != 0)
	{
		// If you have collected 3 letters (C, T, and R)
		if (driver->PickupLetterHUD.numCollected == 3)
		{
			// set bit to tokens
			bitIndex = gGT->levelID + 0x4c;
			// when loading is done, remove flag for CTR Challenge
			sdata->Loading.OnBegin.RemBitsConfig8 |= TOKEN_RACE;
		}
	}
	// if you are in trophy race
	else
	{
		// 6th bit of adventure profile is where trophies start
		bitIndex = gGT->levelID + 6;
		if (CHECK_ADV_BIT(adv->rewards, bitIndex) == 0)
		{
			// go to podium with trophy
			gGT->podiumRewardID = 0x62;
		}
	}

	// If you haven't unlocked this reward
	if (CHECK_ADV_BIT(adv->rewards, bitIndex) == 0)
		UNLOCK_ADV_BIT(adv->rewards, bitIndex);

	MainRaceTrack_RequestLoad(levSpawn);
}

void DECOMP_AA_EndEvent_DisplayTime(short driverId, short param_2)
{
	struct GameTracker *gGT;
	struct Driver *driver;
	struct UiElement2D **hudArray;
	struct UiElement2D *hud;
	struct Instance *bigNum;
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
	hudArray = data.hudStructPtr[numPlyr - 1];
	hud = &hudArray[driverId * 0x28];
	bigNum = driver->BigNumber[0];

	// Lap time box height
	switch (gGT->numLaps)
	{
	// based on number of laps
	case 7:
		r.h = 0x49;
		break;
	case 5:
		r.h = 0x39;
		break;
	default:
		// default height for 1/3 laps.
		r.h = 0x44;
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
		(framesElapsed < 110) &&

		// If you press Cross or Circle
		((sdata->AnyPlayerTap & 0x50) != 0) &&

		// only one player
		(numPlyr == 1))
	{
		// Assume race ended 110 frames ago
		framesElapsed = 110;

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
		lerpStartY = UI_ConvertX_2(-100, hud[5].x);
		lerpStartX = -0xae;
		lerpEndX = lerpStartY;
		endFrame = 0xf;
		currFrame = framesElapsed - 300 + param_2;
		lerpStartY = lerpEndY;
	}
	// If not
	else
	{
		lerpStartX = UI_ConvertX_2(hud[4].x, hud[5].x);
		lerpStartY = UI_ConvertY_2(hud[4].y, hud[5].x);
		currFrame = framesElapsed;
		lerpEndX = -0xae;
		endFrame = 0x1e;
	}

	// interpolate fly-in
	UI_Lerp2D_Linear(&posXY[0], lerpStartX, lerpStartY, lerpEndX, lerpEndY, currFrame, endFrame);

	// Set X and Y position of Big Number
	bigNum->matrix.t[0] = posXY[0];
	bigNum->matrix.t[1] = posXY[1];

	// interpolate fly-in
	UI_Lerp2D_Linear(&posXY[0], hud[5].y, 0, 0x1e00, 0, framesElapsed, 30);

	// Set scale of Big Number in HUD
	bigNum->scale[0] = posXY[0];
	bigNum->scale[1] = posXY[0];
	bigNum->scale[2] = posXY[0];

	if (tenseconds)
	{
		lerpStartX = 0x78;
		lerpStartY = sVar1;
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

	UI_Lerp2D_Linear(&posXY[0], lerpStartX, sVar2, lerpEndX, sVar2, currFrame, endFrame);
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

void UI_RaceEnd_MenuBoxFuncPtr(struct MenuBox *);

struct MenuRow menuRows222_arcade[5] =
	{
		// Retry
		{
			.stringIndex = 4,
			.rowOnPressUp = 0,
			.rowOnPressDown = 1,
			.rowOnPressLeft = 0,
			.rowOnPressRight = 0,
		},
		// Change Level
		{
			.stringIndex = 6,
			.rowOnPressUp = 0,
			.rowOnPressDown = 2,
			.rowOnPressLeft = 1,
			.rowOnPressRight = 1,
		},
		// Change Character
		{
			.stringIndex = 5,
			.rowOnPressUp = 1,
			.rowOnPressDown = 3,
			.rowOnPressLeft = 2,
			.rowOnPressRight = 2,
		},
		// Quit
		{
			.stringIndex = 3,
			.rowOnPressUp = 2,
			.rowOnPressDown = 3,
			.rowOnPressLeft = 3,
			.rowOnPressRight = 3,
		},
		// NULL, end of menu
		{
			.stringIndex = 0xFFFF,
			.rowOnPressUp = 0,
			.rowOnPressDown = 0,
			.rowOnPressLeft = 0,
			.rowOnPressRight = 0,
		}};

struct MenuBox menuBox222_arcade =
	{
		.stringIndexTitle = 0xFFFF,
		.posX_curr = 256,
		.posY_curr = 170,
		.unk1 = 0,
		.state = (0x800 | USE_SMALL_FONT | CENTER_ON_COORDS), // 0x883
		.rows = menuRows222_arcade,
		.funcPtr = UI_RaceEnd_MenuBoxFuncPtr,
		.drawStyle = 4,
		// rest of variables all default zero
};