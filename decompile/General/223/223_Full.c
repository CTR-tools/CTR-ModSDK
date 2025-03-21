#include <common.h>

// copy/paste from GameProg
#define NO_ADV_BIT(rewards, bitIndex) \
	((rewards[bitIndex >> 5] >> (bitIndex & 0x1f)) & 1) != 0

// this goes to footer
static int str_number = 0x20; // " \0"

// required to start on 8009f71c until we rewrite MainGameEnd_Initialize
void JunkPadding223()
{
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
}
void DECOMP_RR_EndEvent_UnlockAward()
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
		relicTime = data.RelicTime[levelID*3 + i];

		// if driver did not beat relic time, check next relic
		if (raceTime > relicTime)
			continue;

		bitIndex = 0x16 + 0x12*i + levelID;

		// if relic already unlocked, check next relic
		if (CHECK_ADV_BIT(adv->rewards, bitIndex) != 0)
			continue;

		// == beat relic, and unlocked relic ==

		// unlock
		UNLOCK_ADV_BIT(adv->rewards, bitIndex);

		// relic model
		gGT->podiumRewardID = 0x61;

		// won relic
		gGT->gameModeEnd |= NEW_RELIC;

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
		sdata->relicTime_1min = relicTime / 0xe100;
		sdata->relicTime_10sec = (relicTime / 0x2580) % 6;
		sdata->relicTime_1sec = (relicTime / 0x3c0) % 10;
		sdata->relicTime_1ms = ((relicTime * 100) / 0x3c0) % 10;

		// [Not Done]
		sdata->relicTime_10ms = 0;
	}
}

void DECOMP_RR_EndEvent_DrawMenu(void)
{
	struct GameTracker *gGT;
	struct AdvProgress *adv;
	struct Driver *d;
	struct Instance *relic;

	char boolEarly;
	short pos[2];
	u_int elapsedFrames;
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
	int uVar11;
	char auStack72[16];

	gGT = sdata->gGT;
	d = gGT->drivers[0];
	relic = sdata->ptrRelic;
	adv = &sdata->advProgress;

	// testing
	//d->numTimeCrates = gGT->timeCratesInLEV;

	// change color
	txtColor = (gGT->timer & FPS_DOUBLE(1)) 
		? 0xffff8000 
		: 0xffff8004;

	// 0x3a is the bit index of where platinum
	// relics start in adventure progress
	bitIndex = gGT->levelID + 0x3a;

	// set color of relic in Instance
	relic->colorRGBA =

		// check if platinum is unlocked, set platinum color
		(CHECK_ADV_BIT(adv->rewards, bitIndex)) ? 0xffede90 :

		// check if gold is unlocked, set gold color
		(CHECK_ADV_BIT(adv->rewards, (bitIndex - 0x12) )) ? 0xd8d2090 :

		// if sapphire, keep original color
		relic->colorRGBA;

	sdata->ptrTimebox1->scale[0] = 0x300;
	sdata->ptrTimebox1->scale[1] = 0x300;
	sdata->ptrTimebox1->scale[2] = 0x300;

	// If race ended less than 900 seconds ago (30 seconds)
	if (sdata->framesSinceRaceEnded < FPS_DOUBLE(900))
	{
		// increment frame counter
		sdata->framesSinceRaceEnded++;
	}

	if (sdata->framesSinceRaceEnded > FPS_DOUBLE(509))
	{
		// start drawing the high score menu that shows the top 5 best times
		gGT->gameModeEnd |= DRAW_HIGH_SCORES;
	}



	// Did not get all crates, prepare skips in the menus
	if(d->numTimeCrates != gGT->timeCratesInLEV)
	{
		// if race ended 59-80 frames ago
		if ((u_int)(sdata->framesSinceRaceEnded - FPS_DOUBLE(21)) < FPS_DOUBLE(59))
		{
			// advance timer to 140 frames, since we can skip the amount of time
			// that would have been taken to draw "PERFECT" text
			sdata->framesSinceRaceEnded = FPS_DOUBLE(140);
		}

		// if race ended 229-250 frames ago, and if WON relic
		if (
				((gGT->gameModeEnd & NEW_RELIC) == 0) &&
				((u_int)(sdata->framesSinceRaceEnded - FPS_DOUBLE(21)) < FPS_DOUBLE(229))
			)
		{
			// advance timer to 370 frames, since we can skip the amount of time
			// that would have been taken to draw the animation
			// to deduct 10 seconds from the relic timer
			sdata->framesSinceRaceEnded = FPS_DOUBLE(370);
		}
	}



	// Draw Race Clock,
	// Reset local frame counter
	elapsedFrames = sdata->framesSinceRaceEnded;
	{
		if (elapsedFrames >= FPS_DOUBLE(490))
		{
			elapsedFrames -= FPS_DOUBLE(490);
			
			startX = 0x100;
			endY = -0x32;
		}
		
		// 0 - 489
		else
		{
			startX = -0x96;
			endY = 0x32;
		}
	
	
		// interpolate fly-in
		DECOMP_UI_Lerp2D_Linear(
			&pos[0],
			startX, 0x32,
			0x100, endY,
			elapsedFrames, FPS_DOUBLE(0x14));
	
		DECOMP_UI_DrawRaceClock(pos[0], pos[1] - 8, 1, d);
	}
	
	
	
	// Draw Relic,
	// Reset local frame counter
	elapsedFrames = sdata->framesSinceRaceEnded;
	
	if ((gGT->gameModeEnd & NEW_RELIC) != 0)
	{
		// default
		pos[0] = 0x100;
		
		if (elapsedFrames >= FPS_DOUBLE(490))
		{
			elapsedFrames -= FPS_DOUBLE(490);
			
			DECOMP_UI_Lerp2D_Linear(
				&pos[0],
				0x100, 0,
				-0x64, 0,
				elapsedFrames, FPS_DOUBLE(0x14));
		}
		
		else if (elapsedFrames >= FPS_DOUBLE(250))
		{
			// on exactly the 251st frame after race ends
			if (elapsedFrames == FPS_DOUBLE(251))
			{
				// play sound of unlocking relic
				OtherFX_Play(0x67, 1);
			}
	
			// if relic has not fully grown
			if (relic->scale[0] < 0xc00)
			{
				// make relic grow on x axis, y axis, and z axis
				relic->scale[0] += FPS_HALF(0x80);
				relic->scale[1] += FPS_HALF(0x80);
				relic->scale[2] += FPS_HALF(0x80);
			}
		}
	
		relic->matrix.t[0] = DECOMP_UI_ConvertX_2(pos[0], 0x100);
		relic->matrix.t[1] = DECOMP_UI_ConvertY_2(0xa2, 0x100);
	}
	

	// Draw Time Crates
	// Reset local frame counter
	elapsedFrames = sdata->framesSinceRaceEnded;
	{
		if (elapsedFrames >= FPS_DOUBLE(490))
		{
			elapsedFrames -= FPS_DOUBLE(490);
			
			// interpolate fly-in
			DECOMP_UI_Lerp2D_Linear(
				&pos[0],
				200,   0x79,
				0x264, 0x79,
				elapsedFrames, FPS_DOUBLE(0x14));
		}
	
		else
		{
			pos[0] = 200;
		}
	
		pos[1] = 0x79;
	
		sdata->ptrTimebox1->matrix.t[0] = DECOMP_UI_ConvertX_2(pos[0], 0x100);
		sdata->ptrTimebox1->matrix.t[1] = DECOMP_UI_ConvertY_2(pos[1], 0x100);
	
		// Draw 'x' before number of crates
		DecalFont_DrawLine("x", pos[0] + 0x14, pos[1] - 10, 2, 0);
	
		// %2.02d/%ld: Amount of crates you collected / Total number of crates
		sprintf(auStack72, "%2.02d/%ld", d->numTimeCrates, gGT->timeCratesInLEV);
	
		// Draw amount of crates collected
		DecalFont_DrawLine(auStack72, pos[0] + 0x21, pos[1] - 0xe, 1, 0);
	}
	
	
	
	// if collected all time boxes in level
	if(d->numTimeCrates == gGT->timeCratesInLEV)
	{
		// copy to local frame counter
		elapsedFrames = sdata->framesSinceRaceEnded;
		
		// PERFECT text, fade-in and fade-out
		if (elapsedFrames >= FPS_DOUBLE(80))
		{
			elapsedFrames -= FPS_DOUBLE(80);

			// fade-out PERFECT
			// 170 frames after the first 80
			if (elapsedFrames >= FPS_DOUBLE(170))
			{
				startX = 0x100;
				endX = 0x296;
			}
				
			// === fade-in PERFECT >=80 ===
			else
			{
				startX = -0x96;
				endX = 0x100;
	
				// 0 frames after the first 80
				if (elapsedFrames == 0)
				{
					OtherFX_Play(0x65, 1);
				}
			}

			DECOMP_UI_Lerp2D_Linear(
				&pos[0],
				startX, 0,
				endX, 0,
				elapsedFrames, FPS_DOUBLE(0x14));
	
			// "PERFECT"
			DecalFont_DrawLine(
				sdata->lngStrings[0x162], pos[0], 0x8a, 1, txtColor);
		}

		// copy to local frame counter
		elapsedFrames = sdata->framesSinceRaceEnded;

		// fade-in COUNTDOWN (-10, -9, -8...)
		if (elapsedFrames >= FPS_DOUBLE(140))
		{
			elapsedFrames -= FPS_DOUBLE(140);
			
			// -10
			char* str = (char*)0x1f800000;
			str[0] = '-';
			str[1] = '1';
			str[2] = '0';
			str[3] = 0;
			
			// interpolate fly-in
			DECOMP_UI_Lerp2D_Linear(
				&pos[0],
				0x296, 0,
				0x199, 0,
				elapsedFrames, FPS_DOUBLE(0x14));
			
			// 20 frames after fly-in starts, do the countdown
			if (elapsedFrames >= FPS_DOUBLE(20))
			{
				elapsedFrames -= FPS_DOUBLE(20);
				
				// 10, 9, 8, 7...
				// changes once every 5 frames
				int minusSeconds = elapsedFrames / FPS_DOUBLE(5);
		
				// -3, -2, -1, -0... (dont go past 0)
				if (minusSeconds > 10)
					minusSeconds = 10;
		
				// "if != 0" means 
				// "if text is not -10"
				else if (minusSeconds != 0)
				{
					// on every 5th frame, except the first frame
					if (elapsedFrames % FPS_DOUBLE(5) == 0)
					{
						// subtract a second
						d->timeElapsedInRace -= 960;
						OtherFX_Play(99, 1);
					}
					
					// change string to match new -X
					str[1] = '0' + (10-minusSeconds);
					str[2] = 0;
				}
			}
			
			// Draw String
			DecalFont_DrawLine(str, pos[0], 0x2a, 1, txtColor);
		}
	}



	// Draw RELIC AWARDED
	// copy to local frame counter
	elapsedFrames = sdata->framesSinceRaceEnded;
	
	if (
			(elapsedFrames >= FPS_DOUBLE(250)) &&
			((gGT->gameModeEnd & NEW_RELIC) != 0)
		)
	{	
		// Fade-out early, so "NEW HIGH SCORE" can fade-in
		if (elapsedFrames >= FPS_DOUBLE(370))
		{
			elapsedFrames -= FPS_DOUBLE(370);
			
			startX = 0x100;
			endX = 0x296;
		}
	
		// Fade-In
		else
		{
			elapsedFrames -= FPS_DOUBLE(250);
			
			startX = -0x96;
			endX = 0x100;
		}
		
		// interpolate fly-in
		DECOMP_UI_Lerp2D_Linear(
			&pos[0],
			startX, 0x50,
			endX, 0x50,
			elapsedFrames, FPS_DOUBLE(0x14));
	
		// "RELIC AWARDED!"
		DecalFont_DrawLine(
			sdata->lngStrings[0x160], pos[0], pos[1], 1, txtColor);
	}
	
	
	

	// copy to local frame counter
	elapsedFrames = sdata->framesSinceRaceEnded;

	if (
			(elapsedFrames >= FPS_DOUBLE(370)) &&
			((gGT->gameModeEnd & NEW_HIGH_SCORE) != 0)
		)
	{
		elapsedFrames -= FPS_DOUBLE(370);
		
		// 120 frames after the 370 initial frames
		if (elapsedFrames >= FPS_DOUBLE(120))
		{
			elapsedFrames -= FPS_DOUBLE(120);
			
			startX = 0x100;
			endX = 0x296;
		}
		
		else
		{
			startX = -0x96;
			endX = 0x100;
		}
		
		// Interpolate fly-in
		DECOMP_UI_Lerp2D_Linear(
			&pos[0],
			startX, 0x50,
			endX, 0x50,
			elapsedFrames, FPS_DOUBLE(0x14));

		// "NEW HIGH SCORE!"
		DecalFont_DrawLine(
			sdata->lngStrings[0x161], pos[0], pos[1], 1, txtColor);
	}




	// copy to local frame counter
	elapsedFrames = sdata->framesSinceRaceEnded;
	
	pos[1] = 0xc;

	// if race ended more than 490 frames ago
	if (elapsedFrames >= FPS_DOUBLE(490))
	{
		elapsedFrames -= FPS_DOUBLE(490);
		
		// Interpolate, vertical fly-out
		DECOMP_UI_Lerp2D_Linear(
			&pos[0],
			-0xa, 0xc,
			-0xa, -0x58,
			elapsedFrames, FPS_DOUBLE(0x14));
	}
	
	
	

	// This is actually a RECT on the stack
	box.x = -0xa;
	box.y = pos[1];
	box.w = 0x214;
	box.h = 0x3b;

	// Draw 2D Menu rectangle background
	RECTMENU_DrawInnerRect(
		&box, 0, gGT->backBuffer->otMem.startPlusFour);



	if ( 	// If you have not pressed X to continue
			((sdata->menuReadyToPass & 1) == 0) &&

			(sdata->framesSinceRaceEnded >= 510) &&
		 
			((gGT->gameModeEnd & NEW_HIGH_SCORE) == 0)
		)
	{
		DECOMP_RR_EndEvent_DrawHighScore(0x100, 10);

		// PRESS * TO CONTINUE
		DecalFont_DrawLine(sdata->lngStrings[0xc9], 0x100, 0xbe, 1, 0xffff8000);

		if ((sdata->AnyPlayerTap & (BTN_CROSS | BTN_CIRCLE)) != 0)
		{
			RECTMENU_ClearInput();
			RECTMENU_Show(&data.menuRetryExit);

			// record that you have pressed X to continue
			sdata->menuReadyToPass |= 1;
		}
	}
}

// same in TT and RR, but not the same in Main Menu
void DECOMP_RR_EndEvent_DrawHighScore(short startX, int startY)
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
	u_short currRowY;
	RECT box;

	gGT = sdata->gGT;
	timebox_X = startX - 0x1f;
	currRowY = 0;

	// 12 entries per track, 6 for Time Trial and 6 for Relic Race
	scoreEntry = &sdata->gameProgress.highScoreTracks[gGT->levelID].scoreEntry[6];

	// === Naughty Dog Bug ===
	// Start and End are the same

	// interpolate fly-in
	DECOMP_UI_Lerp2D_Linear(
		&pos[0],
		startX, startY,
		startX, startY,
		sdata->framesSinceRaceEnded, FPS_DOUBLE(0x14));

	// "BEST TIMES"
	DecalFont_DrawLine(sdata->lngStrings[0x171], pos[0], pos[1], 1, 0xffff8000);

	// Draw icon, name, and time of the
	// 5 best times in Time Trial
	for (i = 0; i < 5; i++)
	{
		// default color, not flashing
		timeColor = 0;
		nameColor = scoreEntry[i+1].characterID + 5;

		// If this loop index is a new high score
		if (gGT->newHighScoreIndex == i)
		{
			// make name color flash every odd frame
			nameColor = (gGT->timer & FPS_DOUBLE(2)) ? 4 : nameColor;

			// flash color of time
			timeColor = ((gGT->timer & FPS_DOUBLE(2)) << FPS_LEFTSHIFT(1));
		}

		timebox_Y = startY + 0x11 + currRowY;

		// Make a rank on the high score list ('1', '2', '3', '4', '5')
		// by taking the binary value of the rank (0, 1, 2, 3, 4),
		// and adding the ascii value of '1'
		str_number = (char)i + '1';

		// Draw String for Rank ('1', '2', '3', '4', '5')
		DecalFont_DrawLine((char*)&str_number, startX - 0x32, timebox_Y - 1, 2, 4);

		u_int iconColor = 0x808080;

		// Draw Character Icon
		RECTMENU_DrawPolyGT4(gGT->ptrIcons[data.MetaDataCharacters[scoreEntry[i+1].characterID].iconID],
							startX - 0x52, timebox_Y,

							// pointer to PrimMem struct
							&gGT->backBuffer->primMem,

							// pointer to OT mem
							gGT->pushBuffer_UI.ptrOT,

							// color of each corner
							iconColor, iconColor,
							iconColor, iconColor,

							1, 0x1000);

		// Draw Name
		DecalFont_DrawLine(scoreEntry[i+1].name, timebox_X, timebox_Y, 3, nameColor);

		// Draw time
		DecalFont_DrawLine(RECTMENU_DrawTime(scoreEntry[i+1].time), timebox_X, timebox_Y + 0x11, 2, timeColor);

		// If this loop index is a new high score
		if (gGT->newHighScoreIndex == i)
		{
			box.x = startX - 0x56;
			box.y = timebox_Y - 1;
			box.w = 0xab;
			box.h = 0x1a;

			// Draw a rectangle to highlight your time on the "Best Times" list
			DECOMP_CTR_Box_DrawClearBox(
				&box, &sdata->menuRowHighlight_Normal, TRANS_50_DECAL,
				gGT->pushBuffer_UI.ptrOT);
		}
		currRowY += 0x1a;
	}

	// IF RR
	{
		// "YOUR TIME"
		DecalFont_DrawLine(sdata->lngStrings[0xC5], startX, startY + 0x95, 1, 0xffff8000);

		// make a string for your current track time
		timeString = RECTMENU_DrawTime(gGT->drivers[0]->timeElapsedInRace);

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
	RECTMENU_DrawInnerRect(&box, 4, gGT->backBuffer->otMem.startPlusFour);
}
