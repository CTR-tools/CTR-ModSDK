#include <common.h>

// To do: add a header
void SaveLapTime(int lapID, int time, int driverID);

// used for both finished lap time and current race time
void DECOMP_DrawRaceClock(u_short paramX, u_short paramY, u_int flags, struct Driver* driver)
{
	// flag parameter bits
	// despite being a u_int only 6 bits are ever used
	// 0: Display in-race time (if 0) / Display time trial results (if 1)
	// 1: Enable or disable flashing
	// 2: Only used to check if you're in a relic race
	// 3: Only used to check if lap 1 should flash (which is when it's the fastest lap)
	// 4: Only used to check if lap 2 should flash (which is when it's the fastest lap)
	// 5: Only used to check if lap 3 should flash (which is when it's the fastest lap)

	short sVar1;
	int stringColor;
	u_int lapIndex;
	u_int uVar3;
	u_char *totalTimeString;
	int iVar5;
	int numParamY;
	int iVar7;
	u_int fontType;
	
	int msElapsed;
	int str;
	int posX;
	int numLaps;
	int levID;
	
	int strOffset;
	
	char msOnes;
	u_short uVar11;
	short *lapTextHeight;
	char msTens;
	char secondsOnes;
	int lapFontType;
	char secondsTens;
	short strFlags_but_its_also_posY;
	u_short stringColor_but_its_also_relicColor;
	char minutesOnes;
	char minutesTens;
	char acStack80 [8];
	
	u_short textPosX;
	u_short textPosY;
	
	char *local_38;
	int unbitshiftTextPosX;
	int bitshiftTextPosX;

	minutesTens = '\0';

	// if pointer is nullptr
	if (driver == 0)
	{
		// quit the function
		return;
	}

	// set default time to 99:59:99
	minutesTens = 9;
	minutesOnes = 9;
	secondsTens = 5;
	secondsOnes = 9;
	msTens = 9;
	msOnes = 9;
	
	// milliseconds elapsed in race
	msElapsed = driver->timeElapsedInRace;

	// if number of laps is 7
	if (sdata->gGT->numLaps == '\a')
	{
		// less than 99:59:99
		if ((char)(msElapsed / 0x8ca00) < 10)
		{
			minutesTens = (char)(msElapsed / 0x8ca00) % 10;
			
			goto setRestOfTime;
		}
	}

	// if numLaps is not 7
	else
	{
		// less than 9:59:99
		if ((char)(msElapsed / 0xe100) < 10)
		{
			setRestOfTime:
			minutesOnes = (char)(msElapsed / 0xe100) % 10;
			secondsTens = (char)((msElapsed / 0x2580) % 6);
			secondsOnes = (char)((msElapsed / 0x3c0) % 10);
			msTens = (char)(((msElapsed * 10) / 0x3c0) % 10);
			msOnes = (char)(((msElapsed * 100) / 0x3c0) % 10);
		}
	}

	if ((flags & 1) == 0)
	{
		// TIME
		str = 0x12;

		// If you're in Time Trial
		if ((sdata->gGT->gameMode1 & 0x20000) != 0)
		{
			// TIME TRIAL
			str = 0x4d;
		}

		// Draw small string
		fontType = 2;

		strFlags_but_its_also_posY = 0;
	}

	else
	{
		// TOTAL
		str = 0xc4;

		// If you're in a Relic Race
		if ((sdata->gGT->gameMode1 & 0x4000000) != 0)
		{
			// YOUR TIME
			str = 0xc5;
		}

		// Draw big string
		fontType = 1;

		// this particular snippet is for drawing the TOTAL text in the time trial lap results screen before it flashes, at which point it moves from the left to the center of the screen
		// if global game timer is on an odd number (in which case this condition doesn't execute) then set string to end at posX of next DrawLine and use data.ptrColor[4], which is a flat white
		if (((flags & 4) == 0) || (strFlags_but_its_also_posY = 0x4004, (sdata->gGT->timer & 2) != 0))
		{
			strFlags_but_its_also_posY = 0x4000;
		}
	}

	textPosX = paramX;
	textPosY = paramY;

	// str = 0x12: TIME
	// str = 0x4d: TIME TRIAL
	// str = 0xc4: TOTAL
	// str = 0xc5: YOUR TIME
	DecalFont_DrawLine(sdata->lngStrings[str], (int)(short)paramX, (int)(short)paramY, fontType, (int)strFlags_but_its_also_posY);

	// set string to use data.ptrColor[1], which is the blue-ish gray gradient seen in the LAP text on the HUD (is this correct???)
	// particularly used for relic race when the time is frozen
	strFlags_but_its_also_posY = 1;

	if
	(
		// if time isn't frozen or we're not in relic race
		(sdata->gGT->frozenTimeRemaining == 0) &&
		(
			// set color to orange if the string shouldn't flash
			strFlags_but_its_also_posY = 0,

			// if the string (which is probably the total time text in the time trial lap results screen) should flash
			(flags & 4) != 0
		)
	)
	{
		// use timer to change color on even and odd frames
		// strFlags_but_its_also_posY equals either 4 (white) or 0 (orange)
		strFlags_but_its_also_posY = (u_short)((sdata->gGT->timer & 2) == 0) << 2;
	}

	// if number of laps is 7
	if (sdata->gGT->numLaps == '\a')
	{
		// String for amount of time in total race
		totalTimeString = &rdata.s_timeString_empty[0];

		// Convert each number from the binary version of the number to the ascii version of the number by adding ascii value of '0'
		totalTimeString[0] = minutesTens + '0';
		
		strOffset = 1;
	}

	// if number of laps is not 7
	else
	{
		// String for amount of time in lap
		totalTimeString = &sdata->raceClockStr[0];

		strOffset = 0;
	}
	
	// Convert each number from the binary version of the number to the ascii version of the number by adding ascii value of '0'
	totalTimeString[strOffset+0] = minutesOnes + '0';
	totalTimeString[strOffset+2] = secondsTens + '0';
	totalTimeString[strOffset+3] = secondsOnes + '0';
	totalTimeString[strOffset+5] = msTens + '0';
	totalTimeString[strOffset+6] = msOnes + '0';

	// If in-race, reuse X and Y positions used for the TIME/TIME TRIAL text in the top left corner of the HUD for the actual time itself
	// Except set the Y position to be lower
	if ((flags & 1) == 0)
	{
		posX = (int)(short)textPosX;
		numParamY = ((u_int)textPosY + 8) * 0x10000;
	}

	// If in the time trial results screen, reuse X and Y positions used for the rightmost margin of the "TOTAL" text used for displaying the total time, and then adjust them accordingly
	else
	{
		posX = (int)(((u_int)textPosX + 0x11) * 0x10000) >> 0x10;
		numParamY = (u_int)textPosY << 0x10;
	}

	// Draw String
	DecalFont_DrawLine(totalTimeString, posX, numParamY >> 0x10, 1, (int)strFlags_but_its_also_posY);

	if
	(
		// If you're not in a Relic Race
		((sdata->gGT->gameMode1 & 0x4000000) == 0) ||
		((flags & 2) != 0)
	)
	{
		// If you're not in Arcade mode,
		// nor Time Trial, nor adventure mode
		if ((sdata->gGT->gameMode1 & 0x4a0000) == 0)
		{
			return;
		}

		lapIndex = (u_int)driver->lapIndex;
		numLaps = 0;

		if (lapIndex == 0xffffffff)
		{
			return;
		}

		local_38 = acStack80;
		numParamY = 1;
		bitshiftTextPosX = (u_int)textPosX << 0x10;
		unbitshiftTextPosX = bitshiftTextPosX >> 0x10;
		do
		{
			if ((numLaps <= (int)lapIndex) && (numLaps < (char)sdata->gGT->numLaps))
			{
				SaveLapTime(lapIndex, sdata->gGT->elapsedEventTime - driver->lapTime, (u_int)driver->driverID);

				// custom code for optimization using this unrelated variable
				iVar5 = (u_int)driver->driverID * 7 + numLaps;

				// set slot for the tens place of a minute to nothing
				rdata.s_timeString_empty[0] = ' ';

				// Convert each number from the binary version of the number to the ascii version of the number by adding ascii value of '0'
				// This is dynamically programmed to handle time for more than one player, see SaveLapTime

				rdata.s_timeString_empty[1] = sdata->LapTimes.p1_Min1s[iVar5] + '0';
				rdata.s_timeString_empty[3] = sdata->LapTimes.p1_Sec10s[iVar5] + '0';
				rdata.s_timeString_empty[4] = sdata->LapTimes.p1_Sec1s[iVar5] + '0';
				rdata.s_timeString_empty[6] = sdata->LapTimes.p1_Ms10s[iVar5] + '0';
				rdata.s_timeString_empty[7] = sdata->LapTimes.p1_Ms1s[iVar5] + '0';

				if
				(
					(
						// if this is lap 1, and if lap 1 should flash
						((numLaps == 0) && ((flags & 8) != 0)) ||

						// if this is lap 2, and if lap 2 should flash
						((numLaps == 1 && ((flags & 0x10) != 0)))
					) ||

					// if this is lap 3, and if lap 3 should flash
					((stringColor_but_its_also_relicColor = 1, numLaps == 2 && ((flags & 0x20) != 0)))
				)
				{
					// Change color based on frame counter
					stringColor_but_its_also_relicColor = ((u_short)(sdata->gGT->timer >> 1) ^ 1) & 1;
				}

				// Otherwise, color is white by default, you can see that in "stringColor_but_its_also_relicColor = 1" near lap 3 check

				if ((flags & 1) == 0)
				{
					// If you're in Arcade Mode
					if ((sdata->gGT->gameMode1 & 0x400000) != 0) goto LAB_8004f84c;

					// Set lap number in "Ln" string
					sdata->s_Ln[1] = (char)numLaps + '1';

					iVar7 = (int)(((u_int)textPosY + numParamY * 8 + 0x10) * 0x10000) >> 0x10;

					// draw "Ln" string
					DecalFont_DrawLine(&sdata->s_Ln[0], bitshiftTextPosX >> 0x10, iVar7, 2, 3);

					lapFontType = 2;
					stringColor = 1;
					iVar5 = (int)(((u_int)textPosX + 0x1a) * 0x10000) >> 0x10;
				}
				else
				{
					// draw big text for time in each lap
					lapFontType = 1;

					// if number of laps is more than 3
					if ('\x03' < (char)sdata->gGT->numLaps)
					{
						// draw small text for time in each lap
						lapFontType = 2;
					}

					// DAT_8008d510
					// %d

					sprintf(local_38, &sdata->s_int[0], numParamY);
					lapTextHeight = (short *)(&data.font_charPixHeight[lapFontType]);

					// draw string
					DecalFont_DrawLine(local_38, unbitshiftTextPosX, (int)(((u_int)textPosY - ((char)sdata->gGT->numLaps - numLaps) * (int)*lapTextHeight) * 0x10000) >> 0x10, lapFontType, 0x4003);

					// LAP
					DecalFont_DrawLine(sdata->lngStrings[0x18], (int)(((u_int)textPosX - (u_int)data.font_charPixWidth[lapFontType])), (int)(((u_int)textPosY - ((char)sdata->gGT->numLaps - numLaps) * (int)*lapTextHeight) * 0x10000) >> 0x10, lapFontType, 0x4003);

					stringColor = (int)(short)stringColor_but_its_also_relicColor;
					iVar7 = (int)(((u_int)textPosY - ((char)sdata->gGT->numLaps - numLaps) * (int)*lapTextHeight) * 0x10000) >> 0x10;
					iVar5 = unbitshiftTextPosX;
				}

				// draw string for total amount of time in race
				DecalFont_DrawLine(&rdata.s_timeString_empty[0], iVar5, iVar7, lapFontType, stringColor);
			}
LAB_8004f84c:
			// lap counter
			lapIndex = (u_int)driver->lapIndex;

			numLaps = numLaps + 1;
			numParamY = numParamY + 1;
			if ((int)(lapIndex + 1) <= numLaps)
			{
				return;
			}
		} while( 1 );
	}

	if ((sdata->gGT->unknownFlags_1d44 & 0x2000000) == 0)
	{
		// Level ID
		levID = sdata->gGT->levelID;

		// 3a is bit index for unlocking plat relics
		// 28 is bit index for unlocking gold relics

		if
		(
			//If you have unlocked a platinum relic on this track
			(((u_int)sdata->advProgress.rewards[(int)(levID + 0x3aU) >> 5] >> (levID + 0x3aU & 0x1f) & 1) != 0) ||

			//If you have unlocked a gold relic on this track
			(((u_int)&sdata->advProgress.rewards[(int)(levID + 0x28U) >> 5] >> (levID + 0x28U & 0x1f) & 1) != 0)
		)
		{
LAB_8004f338:
			str = 200;
			stringColor_but_its_also_relicColor = 0x16;
			goto LAB_8004f378;
		}

		// If you have not unlocked Gold or Plat relic on this track

		// 16 is bit index for unlocking blue relics

		// Check if you unlocked a Blue relic
		lapIndex = (u_int)sdata->advProgress.rewards[(int)(levID + 0x16U) >> 5] >> (levID + 0x16U & 0x1f);
	}

	else
	{
		// Level ID = PTR_DAT_8008d2ac + 0x1a10
		// uVar3 is bit index for unlocking platinum relic on this track
		// lapIndex is bit index for unlocking gold relic on this track
		uVar3 = sdata->gGT->levelID + 0x3a;
		lapIndex = sdata->gGT->levelID + 0x28;


		// 0x8fba4 is where the adventure profile (currently loaded) begins
		if (((u_int)sdata->advProgress.rewards[(int)uVar3 >> 5] >> (uVar3 & 0x1f) & 1) != 0) goto LAB_8004f338;

		// Check if you unlocked a gold relic
		lapIndex = (u_int)sdata->advProgress.rewards[(int)lapIndex >> 5] >> (lapIndex & 0x1f);
	}

	if ((lapIndex & 1) == 0)
	{
		// SAPPHIRE
		str = 0xc6;

		// blue color
		stringColor_but_its_also_relicColor = 0x11;
	}

	else
	{
		// GOLD
		str = 199;

		// yellow color
		stringColor_but_its_also_relicColor = 0xe;
	}

LAB_8004f378:
	fontType = 1;
	if ((flags & 1) == 0)
	{
		fontType = 2;
		sVar1 = textPosY + 0x18;
		strFlags_but_its_also_posY = textPosY + 0x20;
		uVar11 = textPosX;
	}

	else
	{
		stringColor_but_its_also_relicColor = stringColor_but_its_also_relicColor | 0x4000;
		sVar1 = textPosY - 0x11;
		strFlags_but_its_also_posY = sVar1;
		uVar11 = textPosX + 0x11;
	}

	// str 0xc6: SAPPHIRE
	// str 199 (c7): GOLD
	// str 0xc8: PLATINUM
	DecalFont_DrawLine(sdata->lngStrings[str], (int)(short)textPosX, (int)sVar1, fontType, (int)(short)stringColor_but_its_also_relicColor);

	// Convert each number from the binary
	// version of Relic Time to the ascii version
	// of the number by adding ascii value of '0'
	sdata->raceClockStr[0] = sdata->relicTime_1min + '0';
	sdata->raceClockStr[2] = sdata->relicTime_10sec + '0';
	sdata->raceClockStr[3] = sdata->relicTime_1sec + '0';
	sdata->raceClockStr[5] = sdata->relicTime_10ms + '0';
	sdata->raceClockStr[6] = sdata->relicTime_1ms + '0';
	DecalFont_DrawLine(sdata->raceClockStr, (int)(short)uVar11, (int)strFlags_but_its_also_posY, 1, (int)(short)(stringColor_but_its_also_relicColor & 0xbfff));
	return;
}