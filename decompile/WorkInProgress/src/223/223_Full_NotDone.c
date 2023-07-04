#include <common.h>

// copy/paste from GameProg
#define NO_ADV_BIT(rewards, bitIndex) \
	((rewards[bitIndex >> 5] >> (bitIndex & 0x1f)) & 1) != 0

// 8009f700
int str_number;

// 8009f704
int str_x;

// 8009f708
char str_format[0xC];

// 8009f714
int str_negInt;

// 8009f718
int str_posInt;

// 8009f71c
void RR_EndEvent_UnlockAward()
{
	int i;
	struct Driver *driver;
	struct GameTracker *gGT;
	int raceTime;
	int timeDeduct;
	int bitIndex;
	struct AdvProgress *adv;
	int levelID;
	int relicTime;

	gGT = sdata->gGT;
	driver = gGT->drivers[0];
	raceTime = driver->timeElapsedInRace;
	adv = &sdata->advProgress;
	levelID = gGT->levelID;

	// 10 seconds for getting all crates
	if (driver->numTimeCrates == gGT->timeCratesInLEV)
		raceTime -= 0x2580;

	for (i = 0; i < 3; i++)
	{
		relicTime = data.RelicTime[levelID * 3 + i];

		// if driver did not beat relic time, check next relic
		if (raceTime > relicTime)
			continue;

		bitIndex = 0x16 + 0x12 * i;

		// if relic already unlocked, check next relic
		if (CHECK_ADV_BIT(adv->rewards, bitIndex) != 0)
			continue;

		// == beat relic, and unlocked relic ==

		// unlock
		UNLOCK_ADV_BIT(adv->rewards, bitIndex);

		// relic model
		gGT->podiumRewardID = 0x61;

		gGT->unknownFlags_1d44 |= 0x2000000;

		// unlocked sapphire
		// do not make this an AND (&&) if statement
		if (i == 0)
		{
			if (gGT->levelID == TURBO_TRACK)
			{
				// unlock turbo track
				sdata->gameProgress.unlocks[0] |= 2;
			}

			continue;
		}

		// == Gold or Platinum ==

		// store globally... 8008d9b0
		data.relicTime_1min = relicTime / 0xe100;
		data.relicTime_10sec = (relicTime / 0x2580) % 6;
		data.relicTime_1sec = (relicTime / 0x3c0) % 10;
		data.relicTime_1ms = ((relicTime * 100) / 0x3c0) % 10;

		// [Not Done]
		data.relicTime_10ms = 0;
	}
}

void RR_EndEvent_DrawHighScore(short startX, int startY, short mode)
{
	// This is different from High Score in Main Menu because Main Menu
	// does not show the rank icons '1', '2', '3', '4', '5'
	struct GameTracker *gGT;
	struct HighScoreEntry *scoreEntry;

	char i;
	char *timeString;
	short nameColor;
	u_int timeColor;
	short pos[2];
	short timebox_X;
	short timebox_Y;
	ushort currRowY;
	RECT box;

	gGT = sdata->gGT;
	timebox_X = startX - 0x1f;
	currRowY = 0;

	// 8008e6f4 is where all high scores are saved
	// 0x49*4 = 0x124, size of each HighScoreTrack
	// 0x24*4 = sizeof(highScoreEntry)*6, which changes from Time Trial to Relic
	scoreEntry = &sdata->gameProgress->highScoreTracks[gGT->levelID].scoreEntry[mode];

	// interpolate fly-in
	UI_Lerp2D_HUD(&pos, startX, startY, startX, startY, sdata->framesSinceRaceEnded, 0x14);

	// "BEST TIMES"
	DecalFont_DrawLine(sdata->lngStrings[0x171], pos[0], pos[1], 1, 0xffff8000);

	// Draw icon, name, and time of the
	// 5 best times in Time Trial
	for (i = 0; i < 5; i++)
	{
		// default color, not flashing
		timeColor = 0;
		nameColor = scoreEntry->characterID + 5;

		// If this loop index is a new high score
		if (gGT->newHighScoreIndex == i)
		{
			// make name color flash every odd frame
			nameColor = (gGT->timer & 2) ? 4 : scoreEntry->characterID + 5;
			// flash color of time
			timeColor = ((gGT->timer & 2) << 1);
		}

		timebox_Y = startY + 0x11 + currRowY;

		// Make a rank on the high score list ('1', '2', '3', '4', '5')
		// by taking the binary value of the rank (0, 1, 2, 3, 4),
		// and adding the ascii value of '1'
		str_number = (char)i + '1';

		// Draw String for Rank ('1', '2', '3', '4', '5')
		DecalFont_DrawLine(str_number, startX - 0x32, timebox_Y - 1, 2, 4);

		u_int *iconColor = 0x800a0cb4;

		// Draw Character Icon
		MENUBOX_DrawPolyGT4(gGT->ptrIcons[data.MetaDataCharacters[data.characterIDs[gGT->drivers[i]->driverID]].iconID],
							startX - 0x52, timebox_Y,

							// pointer to PrimMem struct
							&gGT->backBuffer->primMem,

							// pointer to OT mem
							gGT->tileView_UI.ptrOT,
							iconColor, iconColor, iconColor, iconColor, 1, 0x1000);

		// Draw Name
		DecalFont_DrawLine(scoreEntry->name, timebox_X, timebox_Y, 3, nameColor);

		// Draw time
		DecalFont_DrawLine(MENUBOX_DrawTime(scoreEntry->time), timebox_X, timebox_Y + 0x11, 2, timeColor);

		// If this loop index is a new high score
		if (gGT->newHighScoreIndex == i)
		{
			box.x = startX - 0x56;
			box.y = timebox_Y - 1;
			box.w = 0xab;
			box.h = 0x1a;

			// Draw a rectangle to highlight your time on the "Best Times" list
			CTR_Box_DrawClearBox(&box, &sdata->menuRowHighlight_Normal, 1,
								 // pointer to OT mem
								 gGT->tileView_UI.ptrOT,
								 // pointer to PrimMem struct
								 &gGT->backBuffer->primMem);
		}
		currRowY += 0x1a;
	}

	// If this is Time Trial Mode
	if (mode == 0)
	{
		// "BEST LAP"
		DecalFont_DrawLine(sdata->lngStrings[0x170], startX, startY + 0x95, 1, 0xffff8000);
		// Change the way text flickers
		timeColor = 0xffff8000;
		// If you got a new best lap
		if (((gGT->unknownFlags_1d44 & 0x4000000) != 0) &&
			((gGT->timer & 2) != 0))
		{
			timeColor = 0xffff8004;
		}
		// make a string for best lap
		timeString = MENUBOX_DrawTime(scoreEntry->time);
	}
	// If this is Relic Mode
	else
	{
		// "YOUR TIME"
		DecalFont_DrawLine(sdata->lngStrings[0xC5], startX, startY + 0x95, 1, 0xffff8000);
		// make a string for your current track time
		timeString = MENUBOX_DrawTime(gGT->drivers[0].timeElapsedInRace);
		// color
		timeColor = 0xffff8000;
	}

	// Print amount of time, for whichever purpose
	DecalFont_DrawLine(timeString, startX, startY + 0xa6, 2, timeColor);

	box.x = pos[0] - 0x60;
	box.y = pos[1] - 4;
	box.w = 0xc0;
	box.h = 0xb4;

	// Draw 2D Menu rectangle background
	MENUBOX_DrawInnerRect(&box, 4, gGT->backBuffer->otMem.startPlusFour);
}

void RR_EndEvent_DrawMenu(void)
{
	struct GameTracker *gGT;
	struct AdvProgress *adv;
	struct Driver *d;
	struct Instance *relic;

	char boolEarly;
	short pos[2];
	u_int framesElapsed;
	u_int bitIndex;
	u_int txtColor;
	RECT box;

	int iVar2;
	short sVar3;
	short startY;
	short endX;
	short sVar6;
	int startX;
	int endY;
	int startFrame;
	int uVar11;
	undefined auStack72[16];
	undefined auStack56[24];

	// pointer to player structure
	d = gGT->drivers[0];
	relic = sdata->ptrRelic;

	// swap color of text depending on if timer
	// has an even or odd number, sVar10 is used
	// to draw "PERFECT" string

	// change color
	txtColor = (gGT->timer & 1) ? 0xffff8000 : 0xffff8004;

	// 0x3a is the bit index of where platinum
	// relics start in adventure progress
	bitIndex = gGT->levelID + 0x3a;

	// set color of relic in Instance
	relic->colorRGBA =
		// check if platinum is unlocked
		(CHECK_ADV_BIT(adv->rewards, bitIndex)) ? 0xffede90 :
												// check if gold is unlocked
			((CHECK_ADV_BIT(adv->rewards, bitIndex - 0x12)) ? 0xd8d2090 : 0);

	sdata->ptrTimebox1->scale[0] = 0x300;
	sdata->ptrTimebox1->scale[1] = 0x300;
	sdata->ptrTimebox1->scale[2] = 0x300;

	// If race ended less than 900 seconds ago (30 seconds)
	if (sdata->framesSinceRaceEnded < 900)
	{
		// increment frame counter
		sdata->framesSinceRaceEnded++;
	}
	// copy to local frame counter
	framesElapsed = sdata->framesSinceRaceEnded;

	if (509 < framesElapsed)
	{
		// start drawing the high score menu that shows the top 5 best times
		gGT->unknownFlags_1d44 |= 2;
	}

	// if race ended less than 80 frames ago
	if ((framesElapsed - 21 < 59) &&

		// If the amount of time crates you collected is not equal to
		(d->numTimeCrates !=

		 // the amount of time crates in this level
		 gGT->timeCratesInLEV))
	{
		// advance timer to 140 frames, since we can skip the amount of time
		// that would have been taken to draw "PERFECT" text
		framesElapsed = 140;
	}

	// if race ended less than 250 frames ago
	if ((framesElapsed - 21 < 229) && ((gGT->unknownFlags_1d44 & 0x2000000) == 0) &&

		// If the amount of time crates you collected is not equal to
		(d->numTimeCrates !=

		 // the amount of time crates in this level
		 gGT->timeCratesInLEV))
	{
		// advance timer to 370 frames, since we can skip the amount of time
		// that would have been taken to draw the animation
		// to deduct 10 seconds from the relic timer
		framesElapsed = 370;
	}

	// if 16.333 sec hasn't passed yet
	boolEarly = framesElapsed < 491;

	if (boolEarly)
	{
		startX = -0x96;
		endY = 0x32;
		startFrame = framesElapsed;
	}
	else
	{
		startX = 0x100;
		endY = -0x32;
		startFrame = framesElapsed - 490;
	}

	// interpolate fly-in
	UI_Lerp2D_HUD(&pos, startX, 0x32, 0x100, endY, startFrame, 0x14);

	UI_DrawRaceClock(pos[0], pos[1] - 8, 1, d);
	if ((gGT->unknownFlags_1d44 & 0x2000000) != 0)
	{
		// if race ended less than 491 frames ago
		if (boolEarly)
		{
			// if race ended less than 251 frames ago
			if (framesElapsed < 251)
				goto LAB_800a0594;

			// on exactly the 251st frame after race ends
			if (framesElapsed == 251)
			{
				// play sound of unlocking relic
				OtherFX_Play(0x67, 1);
			}

			// if relic has not fully grown
			if (relic->scale[0] < 0xc00)
			{
				// make relic grow on x axis, y axis, and z axis
				relic->scale[0] += 0x80;
				relic->scale[1] += 0x80;
				relic->scale[2] += 0x80;
			}
			startX = UI_ConvertX_2(0x100, 0x100);
			endX = UI_ConvertX_2(0x100, 0x100);
			startFrame = framesElapsed - 250;
		}
		else
		{
			startX = UI_ConvertX_2(0x100, 0x100);
			endX = UI_ConvertX_2(-0x64, 0x100);
			startFrame = framesElapsed - 490;
		}
		startY = UI_ConvertY_2(0xa2, 0x100);

		UI_Lerp2D_HUD(&pos, startX, startY, endX, startY, startFrame, 0x14);
	}

LAB_800a0594:
	relic->matrix.t[0] = pos[0];
	relic->matrix.t[1] = pos[1];

	if (boolEarly)
	{
		startX = 0x28a;
		endY = 0x20;
	}
	else
	{
		// start moving all current menus off the screen,
		// then the high scores will replace it
		startX = 0x100;
		endY = -0x44;
		startFrame = framesElapsed - 490;
	}

	// interpolate fly-in
	UI_Lerp2D_HUD(&pos, startX, 0x20, 0x100, endY, startFrame, 0x14);

	// if race ended less than 16.333 seconds ago
	if (boolEarly)
	{
		endX = 200;
		startFrame = framesElapsed;
	}
	// if race ended 16.333 seconds ago or more
	else
	{
		// start moving all current menus off the screen,
		// then the high scores will replace it
		endX = 0x264;
		startFrame = framesElapsed - 490;
	}

	// interpolate fly-in
	UI_Lerp2D_HUD(&pos, 200, 0x79, endX, 0x79, startFrame, 0x14);

	sdata->ptrTimebox1->matrix.t[0] = UI_ConvertX_2(pos[0], 0x100);
	sdata->ptrTimebox1->matrix.t[1] = UI_ConvertY_2(pos[1], 0x100);

	// Draw 'x' before number of crates
	DecalFont_DrawLine(str_x, pos[0] + 0x14, pos[1] - 10, 2, 0);

	// %2.02d/%ld: Amount of crates you collected / Total number of crates
	sprintf(auStack72, str_format, d->numTimeCrates, gGT->timeCratesInLEV);

	// Draw amount of crates collected
	DecalFont_DrawLine(auStack72, pos[0] + 0x21, pos[1] - 0xe, 1, 0);

	// If the amount of time crates you collected is equal to
	if // If the amount of time crates you collected is equal to
		(d->numTimeCrates ==

		 // the amount of time crates in this level
		 gGT->timeCratesInLEV)
	{
		// -%d
		// print negative sign in front of integer

		sprintf(auStack56, str_negInt);

		if (framesElapsed < 249)
		{
			if (79 < framesElapsed)
			{
				// interpolate fly-in
				UI_Lerp2D_HUD(&pos, -0x96, 0x8a, 0x100, 0x8a, framesElapsed - 80, 0x14);

				if (framesElapsed == 0x50)
				{
					// Play sound
					OtherFX_Play(0x65, 1);
				}
				goto LAB_800a07f8;
			}
		}

		// if race ended more than 249 frames ago
		else
		{
			// interpolate fly-in
			UI_Lerp2D_HUD(&pos, 0x100, 0x8a, 0x296, 0x8a, framesElapsed - 250, 0x14);

		LAB_800a07f8:
			// "PERFECT"
			DecalFont_DrawLine(sdata->lngStrings[0x162], pos[0], pos[1], 1, txtColor);
		}

		if (framesElapsed < 490)
		{
			// if race ended, not within range of 0x8c and 0x8c+0x6d,
			// if not within range of 140-249
			if (109 < framesElapsed - 140)
				goto LAB_800a096c;

			if (framesElapsed > 159)
			{
				startFrame = (160 - framesElapsed) / 5;
				if (startFrame < 0)
					startFrame = 0;
				else if (startFrame != 10 && (160 - framesElapsed) % 5 == 0)
				{
					// reduce the number of frames it took for the player to finish the race
					// by 0x3c0, which is 960, which is 30fps * 32ms, or one full second
					d->timeElapsedInRace -= 960;
					OtherFX_Play(99, 1);
				}
				sprintf(auStack56, &str_posInt, startFrame);
			}

			startX = 0x296;
			uVar11 = 0x2a;
			endY = 0x2a;
		}
		// if race ended 490 frames ago or more
		else
		{
			startX = 0x199;
			uVar11 = 0x32;
			endY = -0x32;
		}

		// interpolate fly-in
		UI_Lerp2D_HUD(&pos, startX, uVar11, 0x199, endY, framesElapsed - 140, 0x14);

		// Draw String
		DecalFont_DrawLine(auStack56, pos[0], pos[1], 1, txtColor);
	}

LAB_800a096c:
	if (
		((gGT->unknownFlags_1d44 & 0xa000000) == 0x2000000) &&

		// race ended more than 489 frames ago
		(489 < framesElapsed))
	{
		startX = 0x100;
		sVar6 = 0x296;
		startFrame = framesElapsed - 490;

	LAB_800a0a64:
		// interpolate fly-in
		UI_Lerp2D_HUD(&pos, startX, 0x50, sVar6, 0x50, startFrame, 0x14);
		// "RELIC AWARDED!"
		DecalFont_DrawLine(sdata->lngStrings[0x160], pos[0], pos[1], 1, txtColor);
	}

	// race ended than 489 frames ago or less
	else
	{
		if (((gGT->unknownFlags_1d44 & 0xa000000) == 0xa000000) &&

			(369 < framesElapsed))
		{
			startX = 0x100;
			sVar6 = 0x296;
			startFrame = framesElapsed - 370;
			goto LAB_800a0a64;
		}

		if (((gGT->unknownFlags_1d44 & 0x2000000) != 0) &&

			(249 < framesElapsed))
		{
			startX = -0x96;
			sVar6 = 0x100;
			startFrame = framesElapsed - 250;
			goto LAB_800a0a64;
		}
	}

	if ((gGT->unknownFlags_1d44 & 0x8000000) != 0)
	{
		// if race ended less than 490 frames ago
		if (framesElapsed < 490)
		{
			// if race ended less than 370 frames ago
			if (framesElapsed < 370)
				goto LAB_800a0b58;

			// if race ended 370 frames ago or more
			startX = -0x96;
			sVar6 = 0x100;
			startFrame = framesElapsed - 370;
		}

		// if race ended 490 frames ago or more
		else
		{
			startX = 0x100;
			sVar6 = 0x296;
			startFrame = framesElapsed - 490;
		}

		// Interpolate fly-in
		UI_Lerp2D_HUD(&pos, startX, 0x50, sVar6, 0x50, startFrame, 0x14);

		// "NEW HIGH SCORE!"
		DecalFont_DrawLine(sdata->lngStrings[0x161], pos[0], pos[1], 1, txtColor);
	}

LAB_800a0b58:
	pos[0] = 0;
	pos[1] = 0xc;

	// if race ended more than 490 frames ago
	if (490 < framesElapsed)
	{
		// Interpolate, vertical fly-out??
		UI_Lerp2D_HUD(&pos, -0xa, 0xc, -0xa, -0x58, framesElapsed - 490, 0x14);
	}

	// This is actually a RECT on the stack
	box.x = 0xfff6;
	box.y = pos[1];
	box.w = 0x214;
	bow.h = 0x3b;

	// Draw 2D Menu rectangle background
	MENUBOX_DrawInnerRect(&box, 0, gGT->backBuffer->otMem.startPlusFour);

	if ( // If you have not pressed X to continue
		(((sdata->menuReadyToPass & 1) == 0) &&

		 // if race ended more than 509 frames ago
		 (509 < sdata->framesSinceRaceEnded)) &&
		((gGT->unknownFlags_1d44 & 0x8000000) == 0))
	{
		RR_EndEvent_DrawHighScore(0x100, 10, 1);

		// PRESS * TO CONTINUE
		DecalFont_DrawLine(sdata->lngStrings[0xc9], 0x100, 0xbe, 1, 0xffff8000);

		if ((sdata->AnyPlayerTap & (BTN_CROSS | BTN_CIRCLE)) != 0)
		{
			// clear gamepad input (for menus)
			MENUBOX_ClearInput();

			// Draw end of race menu (see 221 and 222)
			MENUBOX_Show(&data.menuBox_Retry_ExitToMap);

			// record that you have pressed X to continue
			sdata->menuReadyToPass |= 1;
		}
	}
	sdata->framesSinceRaceEnded = framesElapsed;
}