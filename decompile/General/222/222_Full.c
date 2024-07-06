#include <common.h>

static int str_number = 0x20; // " \0"
extern struct RectMenu menu222;

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
	struct UiElement3D *letter;

	char i;
	char tokenUnlock;
	char numPlyr;
	char totalPlyr;

	short letterPos[2];
	short txtPos[2];

	short t;
	short elapsedFrames;
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
	int bitIndex;

	bitIndex = -1;
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
	hudCTR = &data.hud_1P_P1[0x12];

	elapsedFrames = sdata->framesSinceRaceEnded;

	// count frames if hasn't been 30 seconds
	if (elapsedFrames < FPS_DOUBLE(900))
		elapsedFrames++;

	sdata->framesSinceRaceEnded = elapsedFrames;

	if (driver->instBigNum->scale[0] != 0x1e00)
	{
		struct Instance* instFruitDisp = driver->instFruitDisp;
		instFruitDisp->scale[0] = 0;
		instFruitDisp->scale[1] = 0;
		instFruitDisp->scale[2] = 0;
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
			// lerp C-T-R letters closer to center by 16 pixels
			// default (unlocking and frames < 140) or (already unlocked and frames < 300)
			lerpStartX = hudCTR->x;
			lerpStartY = hudCTR->y;
			lerpEndX = lerpStartX + 0x10;
			lerpEndY = lerpStartY + 0x10;
			currFrame = elapsedFrames;
			lerpFrames = FPS_DOUBLE(8);

			// If you have not unlocked this CTR Token
			bitIndex = gGT->levelID + 0x4C;
			*(int *)&letterPos[0] = *(int *)&hudCTR[0];
			if (CHECK_ADV_BIT(adv->rewards, bitIndex) == 0)
			{
				scaleDown = hudC->scale[0];
				scaleDown -= (scaleDown < 0x800) ? 0x800 : 0x401;
				scaleDown = scaleDown >> 10;

				// lerp letters off-screen
				if (elapsedFrames > FPS_DOUBLE(230))
				{
					currFrame = elapsedFrames - FPS_DOUBLE(230);

					lerpStartX += 0x10;
					lerpStartY += 0x50;
					lerpEndX = -400;
					lerpEndY = lerpStartY;
				}

				// lerp letters to center
				else if (elapsedFrames > FPS_DOUBLE(140))
				{
					currFrame = elapsedFrames - FPS_DOUBLE(140);

					lerpStartX += 0x10;
					lerpStartY += 0x10;
					lerpEndX = hudCTR->x - 0x10;
					lerpEndY = hudCTR->y + 0x50;

					if (hudToken->scale[0] < 0x2001)
					{
						hudToken->scale[0] += FPS_HALF(0x200);
						hudToken->scale[1] += FPS_HALF(0x200);
						hudToken->scale[2] += FPS_HALF(0x200);
					}

					if (hudC->scale[0] == 0x800)
						OtherFX_Play(0x67, 1);

					// original code said < 0x2200, but the
					// actual desired value is 0x2400, needs
					// this change so 60fps doesn't stop at
					// 0x2200 when stepping at half speed
					if (hudLetters[0]->scale[0] < 0x2400)
					{
						for (i = 0; i < 3; i++)
						{
							hudLetters[i]->scale[0] += FPS_HALF(0x400);
							hudLetters[i]->scale[1] += FPS_HALF(0x400);
							hudLetters[i]->scale[2] += FPS_HALF(0x400);
						}
					}

					// Naughty Dog Bug: This was supposed to lerp off-screen at elapsedFrames > 230,
					// but they passed "elapsedFrames-50" instead of "elapsedFrames-230", kills effect.
					//	txtStartX = 0x100;
					//	txtEndX = -150;
					//	currFrame = elapsedFrames - 50;

					// lerp on-screen: CTR TOKEN AWARDED
					txtStartX = 0x264;
					txtEndX = 0x100;

					DECOMP_UI_Lerp2D_Linear(
						&txtPos[0],
						txtStartX, 0xA6,
						txtEndX, 0xA6,
						currFrame, FPS_DOUBLE(8));

					txtColor = (gGT->timer & FPS_DOUBLE(1)) ? 0xFFFF8003 : 0xFFFF8004;

					DecalFont_DrawLine(
						sdata->lngStrings[0x16F],
						txtPos[0], txtPos[1],
						1, txtColor);
				}

				DECOMP_UI_Lerp2D_Linear(
					&letterPos[0],
					lerpStartX, lerpStartY,
					lerpEndX, lerpEndY,
					currFrame, FPS_DOUBLE(8));

				hudToken->flags &= ~HIDE_MODEL;
				hudToken->matrix.t[0] = hudT->matrix.t[0];
				hudToken->matrix.t[1] = DECOMP_UI_ConvertY_2(letterPos[1] + 0x18, 0x200);

				// variable reuse, frame timers
				lerpStartY = FPS_DOUBLE(120);
				lerpEndY = FPS_DOUBLE(160);
			}

			// If you already have this CTR Token unlocked
			else
			{
				// or <= ?
				if (elapsedFrames > FPS_DOUBLE(300))
				{
					currFrame = elapsedFrames - FPS_DOUBLE(300);

					lerpStartX = hudCTR->x + 0x10;
					lerpStartY = hudCTR->y + 0x10;
					lerpEndX = -400;
					lerpEndY = lerpStartY;
					lerpFrames = FPS_DOUBLE(10);
				}

				DECOMP_UI_Lerp2D_Linear(
					&letterPos[0],
					lerpStartX, lerpStartY,
					lerpEndX, lerpEndY,
					currFrame, lerpFrames);

				// variable reuse, frame timers
				lerpStartY = 0;
				lerpEndY = 0;

				scaleDown = 0;
			}

			for (i = 0; i < 3; i++)
			{
				hudLetters[i]->matrix.t[0] = DECOMP_UI_ConvertX_2(letterPos[0] + (scaleDown * (i * 12)) + (i * 29), 0x200);
				hudLetters[i]->matrix.t[1] = DECOMP_UI_ConvertY_2(letterPos[1] - (i & 1), 0x200);
			}
		}

		// If you did not collect all 3 letters (C, T, and R), or you lost the race,
		// do this for the first 30 seconds (900 frames)
		else if (elapsedFrames < FPS_DOUBLE(900))
		{
			driver->PickupLetterHUD.numCollected = 0;

			for (i = 0; i < 3; i++)
			{
				if (
						// letter is visible
						((hudLetters[i]->flags & HIDE_MODEL) == 0) &&

						// delay letter (6 frames apart)
						(elapsedFrames > FPS_DOUBLE(6*i)) &&

						// letter not fully off-screen
						(-300 < hudLetters[i]->matrix.t[1])
					)
				{
					letter = hudLetters[i]->thread->object;

					// move X position (yes, C-Letter only, Naughty Dog bug?)
					hudLetters[0]->matrix.t[0] += letter->vel[0];

					// make the letter fall off the screen
					hudLetters[i]->matrix.t[1] -= letter->vel[1];

					if (FPS_HALF(-0x14) < letter->vel[1])
					{
						letter->vel[1] -= FPS_HALF(2);
					}
				}
			}
		}
	}

	for (i = 0; i < numPlyr; i++)
	{
		// Draw how much time it took to finish laps and race
		DECOMP_AA_EndEvent_DisplayTime(i, lerpEndY);
	}

	// If it hasn't been 1 second from race ended
	if (elapsedFrames < FPS_DOUBLE(29))
		return;

	// If there is one player
	if (numPlyr == 1)
	{
		// start counting time 1 second after race ends
		t = (elapsedFrames & 0xffff) - FPS_DOUBLE(30);

		if (
			// Every 0.5 seconds or so
			((t % FPS_DOUBLE(10) & 0xffff) == 0) &&

			// sdata->numIconsEOR is the number of icons being
			// drawn on the end-of-race menu in 1P mode

			// If you have not drawn all drivers yet
			(sdata->numIconsEOR < totalPlyr))
		{
			// add an icon to draw
			sdata->numIconsEOR++;
		}

		// loop through all the driver icons
		for (i = 0; i < sdata->numIconsEOR; i++)
		{
			int iVar11 = gGT->pushBuffer[0].rect.x +
						 (gGT->pushBuffer[0].rect.w - totalPlyr * 56 + 12) / 2 + (i * 56);

			if (elapsedFrames + lerpEndY > FPS_DOUBLE(300))
			{
				lerpStartX = iVar11;
				lerpEndX = -100;
				currFrame = elapsedFrames + lerpEndY - FPS_DOUBLE(300);
			}
			else
			{
				lerpStartX = 0x218;
				lerpEndX = iVar11;
				currFrame = t;
			}

			t -= FPS_DOUBLE(10);

			// interpolate fly-in
			DECOMP_UI_Lerp2D_Linear(
				&letterPos[0],
				lerpStartX, 0x60,
				lerpEndX, 0x60,
				currFrame, FPS_DOUBLE(10));

			str_number = (char)i + '1';

			// print a single character, a number 1-8,
			DecalFont_DrawLine(
				&str_number, letterPos[0] + 0x20, 0x5f, 2, 4);

			// Draw the driver's character icon
			DECOMP_UI_DrawDriverIcon(

				gGT->ptrIcons[
					data.MetaDataCharacters[
						data.characterIDs[
							gGT->driversInRaceOrder[i]->driverID
						]
					].iconID],

				MakePoint(letterPos[0], 0x60),

				// pointer to OT mem
				gGT->pushBuffer_UI.ptrOT,

				1, 0x1000, MakeColor(0x80, 0x80, 0x80));
		}
	}

	// 0x78 + 0x6e = 0xe6 (230) frames waited for Token Race
	if ((elapsedFrames-lerpStartY) < FPS_DOUBLE(110))
		return;
	if (
		// If you are in Adventure cup
		((gGT->gameMode1 & ADVENTURE_CUP) != 0) ||

		// If you are in Arcade or VS cup
		((gGT->gameMode2 & CUP_ANY_KIND) != 0)
	   )
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
		RECTMENU_ClearInput();

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
		menu222.posY_curr = (numPlyr == 1) ? 170 : 108;

		RECTMENU_Show(&menu222);

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
	RECTMENU_ClearInput();

	// if event was not won
	if (driver->driverRank > 0)
	{
		// pass pointer to menu buffer that shows Retry / Exit To Map,
		// identical to buffer in 221 dll, except this one in EXE space
		RECTMENU_Show(&data.menuRetryExit);

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

		// bitIndex of keys unlocked, and boss beaten
		bitIndex = gGT->bossID + 0x5e;

		// If the number of keys you have is less than 4
		if (gGT->bossID < 4)
		{
			// only if first time beating boss
			if (CHECK_ADV_BIT(adv->rewards, bitIndex) == 0)
			{
				// Go to Podium after returning to Adventure Hub
				gGT->podiumRewardID = 99; // key

				// hot air skyway
				if (gGT->levelID == 7)
				{
					// If you just beat Pinstripe
					// Load gemstone valley
					levSpawn = 0x19;
				}
			}
		}

		// If you have 4 keys (only here if you beat oxide)
		else
		{
			// Always go to podium after oxide,
			// with no key (0x38 = empty)
			gGT->podiumRewardID = 0x38;

			// assume oxide beaten 1st time
			adv->rewards[3] |= 0x80004;

			// if beaten oxide 2nd time
			if(gGT->bossID == 5)
			{
				// beat 2nd time
				adv->rewards[3] |= 0x100008;
			}
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

	// if something needs unlocking
	if(bitIndex > 0)
	{
		// Unlock reward
		UNLOCK_ADV_BIT(adv->rewards, bitIndex);
	}

	// if trophy is not won,
	// Dingo Bingo needs to win trophy and token in the same race
	bitIndex = gGT->levelID + 6;
	if (CHECK_ADV_BIT(adv->rewards, bitIndex) == 0)
	{
		// unlock tropy
		UNLOCK_ADV_BIT(adv->rewards, bitIndex);

		// go to podium with trophy
		gGT->podiumRewardID = 0x62;
	}

	MainRaceTrack_RequestLoad(levSpawn);
}

void DECOMP_AA_EndEvent_DisplayTime(short driverId, short param_2)
{
	struct GameTracker *gGT;
	struct Driver *driver;
	struct UiElement2D *hudArray;
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
	short endFrame;
	short posXY[2];
	RECT r;

	gGT = sdata->gGT;
	driver = gGT->drivers[driverId];

	// stop after 12 seconds
	if(driver->framesSinceRaceEnded_forThisDriver > FPS_DOUBLE(360))
		return;

	numPlyr = gGT->numPlyrCurrGame;
	hudArray = data.hudStructPtr[numPlyr - 1];
	hud = &hudArray[driverId * 0x14]; // to-do, use enum where 0x14 is number of hud
	bigNum = driver->instBigNum;

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

	// increment counter for number of frames since the player ended the race
	driver->framesSinceRaceEnded_forThisDriver++;
	framesElapsed = driver->framesSinceRaceEnded_forThisDriver;

	if (
		// if player ended race less than 110 frames ago
		(framesElapsed < FPS_DOUBLE(110)) &&

		// If you press Cross or Circle
		((sdata->AnyPlayerTap & 0x50) != 0) &&

		// only one player
		(numPlyr == 1))
	{
		// Assume race ended 110 frames ago
		framesElapsed = FPS_DOUBLE(110);
		sdata->framesSinceRaceEnded = framesElapsed;
		driver->framesSinceRaceEnded_forThisDriver = framesElapsed;

		sdata->numIconsEOR = numPlyr + gGT->numBotsNextGame;

		// clear gamepad input (for menus)
		RECTMENU_ClearInput();
	}

	tenseconds = (framesElapsed + param_2 > FPS_DOUBLE(300));

	// === Draw BigNum ===

	// Player 2
	lerpEndY = 0x41;

	// Player 1
	#ifdef USE_NEW2P
	if(numPlyr == 1)
	#endif
		if (driverId == 0)
			lerpEndY = -0x3d;

	// If race ended more than 10 seconds ago.
	if (tenseconds)
	{
		currFrame = framesElapsed + param_2 - FPS_DOUBLE(300);
		endFrame = FPS_DOUBLE(0xf);

		lerpStartX = -0xae;
		lerpEndX = DECOMP_UI_ConvertX_2(-100, hud[2].z);
		lerpStartY = lerpEndY;

		#ifdef USE_NEW2P
		if(driverId == 1)
		{
			lerpStartX = 0xae;
			lerpEndX = 0x200 - lerpEndX;
		}
		#endif
	}

	// If not
	else
	{
		currFrame = framesElapsed;
		endFrame = FPS_DOUBLE(0x1e);

		lerpStartX = DECOMP_UI_ConvertX_2(hud[2].x, hud[2].z);
		lerpStartY = DECOMP_UI_ConvertY_2(hud[2].y, hud[2].z);
		lerpEndX = -0xae;

		#ifdef USE_NEW2P
		if(driverId == 1)
			lerpEndX = 0xae;
		#endif
	}

	// interpolate fly-in positionXY
	DECOMP_UI_Lerp2D_Linear(
		&posXY[0],
		lerpStartX, lerpStartY,
		lerpEndX, lerpEndY,
		currFrame, endFrame);

	bigNum->matrix.t[0] = posXY[0];
	bigNum->matrix.t[1] = posXY[1];

	// interpolate scale to 0x1e00
	DECOMP_UI_Lerp2D_Linear(
		&posXY[0],
		hud[2].scale, 0,
		0x1e00, 0,
		framesElapsed, FPS_DOUBLE(30));

	bigNum->scale[0] = posXY[0];
	bigNum->scale[1] = posXY[0];
	bigNum->scale[2] = posXY[0];

	// === Draw Suffix ===

	// Player 2
	lerpEndY = 0x89;

	// Player 1
	#ifdef USE_NEW2P
	if(numPlyr == 1)
	#endif
		if (driverId == 0)
			lerpEndY = 9;

	if (tenseconds)
	{
		lerpStartX = 0x78;
		lerpStartY = lerpEndY;
		lerpEndX = -0x3c;

		#ifdef USE_NEW2P
		if (driverId == 1)
		{
			lerpStartX = 0x1d0;
			lerpEndX = 0x260;
		}
		#endif
	}
	else
	{
		lerpStartX = hud[5].x;
		lerpStartY = hud[5].y;
		lerpEndX = 0x78;

		#ifdef USE_NEW2P
		if (driverId == 1)
			lerpEndX = 0x1d0;
		#endif
	}

	DECOMP_UI_Lerp2D_Linear(
		&posXY[0],
		lerpStartX, lerpStartY,
		lerpEndX, lerpEndY,
		currFrame, endFrame);

	DECOMP_UI_DrawPosSuffix(posXY[0], posXY[1], driver, 0);

	// === DrawRaceClock ===

	// default
	#ifdef USE_NEW2P
	if(numPlyr == 1)
	{
	#endif

		lerpEndY = 0xc3;
		if (driverId == 0)
			lerpEndY = 0x3e;

		if (tenseconds)
		{
			lerpStartX = 0x150;
			lerpEndX = 0x27c;
		}

		else
		{
			lerpStartX = 0x218;
			lerpEndX = 0x150;
		}

	// new
	#ifdef USE_NEW2P
	}

	else
	{
		lerpEndY = 0x3e;

		if (tenseconds)
		{
			currFrame = framesElapsed + param_2 - FPS_DOUBLE(300);
			endFrame = FPS_DOUBLE(0xf);

			lerpStartX = gGT->pushBuffer[driverId].rect.x + 0x70;

			lerpEndX = 0x268;
			if (driverId == 0)
				lerpEndX = -0x90;
		}

		else
		{
			currFrame = framesElapsed;
			endFrame = FPS_DOUBLE(0x1e);

			lerpStartX = 0x268;
			if (driverId == 0)
				lerpStartX = -0x90;

			lerpEndX = gGT->pushBuffer[driverId].rect.x + 0x70;
		}
	}
	#endif

	DECOMP_UI_Lerp2D_Linear(
		&posXY[0],
		lerpStartX, lerpEndY,
		lerpEndX, lerpEndY,
		currFrame, endFrame);

	DECOMP_UI_DrawRaceClock(posXY[0], posXY[1], 1, driver);

	// "TOTAL"
	width = DECOMP_DecalFont_GetLineWidth(sdata->lngStrings[0xc4], 1);

	r.x = (posXY[0] - width) + -6;
	r.y = (posXY[1] - r.h) + 0xd;
	r.w = width + WIDE_34(0x94);
	r.h += 6;

	// Draw 2D Menu rectangle background
	RECTMENU_DrawInnerRect(&r, 4, gGT->backBuffer->otMem.startPlusFour);
	return;
}

struct MenuRow rows222[5] =
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
	}
};

struct RectMenu menu222 =
{
	.stringIndexTitle = 0xFFFF,
	.posX_curr = 256,
	.posY_curr = 170,
	.unk1 = 0,
	.state = (0x800 | USE_SMALL_FONT | CENTER_ON_COORDS), // 0x883
	.rows = rows222,
	.funcPtr = DECOMP_UI_RaceEnd_MenuProc,
	.drawStyle = 4,
	// rest of variables all default zero
};