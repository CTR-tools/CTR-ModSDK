// TT_EndEvent_DrawHighScore
void FUN_8009f8c0(short param_1, int param_2, short param_3)
{
	// This is different from High Score in Main Menu because Main Menu
	// does not show the rank icons '1', '2', '3', '4', '5'
	
	short sVar1;
	u_int uVar2;
	int iVar3;
	int local_88;
	u_int *trackTime;
	short UI_DrawRaceClockFlags;
	short UI_DrawRaceClockFlagsAgain;
	int loop;
	int bestTimeIndex;
	short local_68;
	short local_66;
	short local_60;
	short local_5e;
	u_short local_5c;
	u_short local_5a;
	short local_58;
	short local_50;
	int driver;
	u_int *trackHighScore;
	u_short local_40;
	int local_38;
	int local_34;
	u_int local_30;
	
	local_40 = param_1 - 0x52;
	local_88 = param_2 + 0x11;
	sVar1 = (short)param_2;
	local_30 = 0;
	
	// pointer to player structure (8009900C)
	driver = sdata->gGT->drivers[0];
	
	// loop counter
	loop = 0;
	
	// 8008e6f4 is where all high scores are saved
	// 0x49*4 = 0x124, size of each HighScoreTrack
	// 0x24*4 = sizeof(highScoreEntry)*6, which changes from Time Trial to Relic
	trackHighScore = &sdata->gameProgress->highScoreTracks[0] + (int)param_3 * 0x24 + sdata->gGT->levelID * 0x49;
	
	local_58 = param_1;
	local_50 = param_3;
	
	// Fly-in Interpolation
	UI_Lerp2D_Linear(&local_68, (int)param_1, (int)sVar1, (int)param_1, (int)sVar1, sdata->framesSinceRaceEnded, 0x14);
	
	bestTimeIndex = 1;
	
	// "BEST TIMES"
	UI_DrawRaceClock(sdata->lngStrings[0x5c4], (int)local_68, (int)local_66, 1, 0xffff8000);
	
	local_38 = local_88 * 0x10000 >> 0x10;
	local_34 = (int)(short)(param_1 - 0x1f);
	
	// for loop = 0; loop < 5; loop++
	do 
	{
		// Draw icon, name, and time of the 
		// 5 best times in Time Trial
	
		// pointer to the track time of this high score
		trackTime = &trackHighScore->scoreEntry[bestTimeIndex];
	
		// If this loop index is a new high score
		if ((int)sdata->gGT->newHighScoreIndex == loop) 
		{
			// make name color flash every odd frame
			UI_DrawRaceClockFlags = 4;
		
			// if timer on clock is an even number
			if ((sdata->gGT->timer & 2) == 0) 
			{
				// use default color
				UI_DrawRaceClockFlags = *(short *)((int)trackTime + 0x16) + 5;
			}
		
			// flash color of time
			UI_DrawRaceClockFlagsAgain = (short)((sdata->gGT->timer & 2) << 1);
		}
	
		// If your current time is not on "best times" list
		else 
		{
			// dont flash color of time
			UI_DrawRaceClockFlagsAgain = 0;
		
			// dont flash color of name, stick with default
			UI_DrawRaceClockFlags = *(short *)((int)trackTime + 0x16) + 5;
		}
		iVar3 = local_88 + (local_30 & 0xffff);
	
		// Make a rank on the high score list ('1', '2', '3', '4', '5')
		// by taking the binary value of the rank (0, 1, 2, 3, 4),
		// and adding the ascii value of '1'
		DAT_8009f700 = (char)loop + '1';
	
		// Draw String for Rank ('1', '2', '3', '4', '5')
		UI_DrawRaceClock(&DAT_8009f700, (int)(((u_int)local_40 + 0x20) * 0x10000) >> 0x10, (iVar3 - 1) * 0x10000 >> 0x10, 2, 4);
				 
		// Draw Character Icon
		MENUBOX_DrawPolyGT4
		(
			sdata->gGT + (int)(*(short *)(&DAT_80086d8c + (int)*(short *)((int)trackTime + 0x16) * 0x10) * 4 + 0x1eec),
			(int)(short)local_40, local_38 + (short)local_30,
					
			// pointer to PrimMem struct
			*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,
				 
			// pointer to OT mem
			*(u_int *)(PTR_DAT_8008d2ac + 0x147c),

			uRam800a04d0,uRam800a04d0,uRam800a04d0,uRam800a04d0,
			TRANS_50_DECAL, FP(1.0)
		);
				 
	// Draw Name, which is 4 bytes after pointer to Time (puVar6)
		UI_DrawRaceClock(trackTime + 1,local_34,iVar3 * 0x10000 >> 0x10,3,(int)UI_DrawRaceClockFlags);
	
	// make a string for time
		uVar2 = FUN_80044ff8(*trackTime);
	
	// Draw time
		UI_DrawRaceClock(uVar2,local_34,(iVar3 + 0x11) * 0x10000 >> 0x10,2,(int)UI_DrawRaceClockFlagsAgain);
	
	// If this loop index is a new high score
		if ((int)(char)PTR_DAT_8008d2ac[0x1d49] == loop) 
	{
		// Check the order that variables are declared on stack
		// These four variables are actually a RECT starting at local_60
			local_60 = local_40 - 4;
			local_5e = (short)local_88 + (short)local_30 + -1;
			local_5c = 0xab;
			local_5a = 0x1a;
		
		// Draw a rectangle to highlight your time on the "Best Times" list
		// CTR_Box_DrawClearBox
			FUN_8002177c(&local_60,&DAT_8008d94c,1,
		
					// pointer to OT mem
					*(u_int *)(PTR_DAT_8008d2ac + 0x147c),
		
					// pointer to PrimMem struct
									 *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);
		}
	
		UI_DrawRaceClockFlags = local_58;
		
	bestTimeIndex++;
		
	// loop counter
	loop = loop + 1;
	
		local_30 = local_30 + 0x1a;
	} while (loop < 5);
	
	// If this is Time Trial Mode
	if (local_50 == 0) 
	{
	// Change the way text flickers
		UI_DrawRaceClockFlagsAgain = -0x8000;
	
	// If you got a new best lap
		if (((*(u_int *)(PTR_DAT_8008d2ac + 0x1d44) & 0x4000000) != 0) &&
	
		// Same logic to make text flicker as earlier in the function, but different colors
			 (UI_DrawRaceClockFlagsAgain = -0x8000, (*(u_int *)(PTR_DAT_8008d2ac + 0x1cec) & 2) != 0)) {
			UI_DrawRaceClockFlagsAgain = -0x7ffc;
		}
	
		// DAT_8008d878 + 0x5c0
		// "BEST LAP"
		UI_DrawRaceClock(*(u_int *)(DAT_8008d878 + 0x5c0),(int)local_58,(int)(short)(sVar1 + 0x95),1,
								 0xffff8000);
	
	// make a string for best lap	
		uVar2 = FUN_80044ff8(*trackHighScore);
	
	// color
		local_88 = (int)UI_DrawRaceClockFlagsAgain;
	}
	
	// If this is Relic Mode
	else 
	{
		// DAT_8008d878 + 0x314
		// "YOUR TIME"
		UI_DrawRaceClock(*(u_int *)(DAT_8008d878 + 0x314),(int)local_58,
								 (param_2 + 0x95) * 0x10000 >> 0x10,1,0xffff8000);
	
	// make a string for your current track time
		uVar2 = FUN_80044ff8(*(u_int *)(driver + 0x514));
	
	// color
		local_88 = -0x8000;
	}

	// Print amount of time, for whichever purpose
	UI_DrawRaceClock(uVar2,(int)UI_DrawRaceClockFlags,(param_2 + 0xa6) * 0x10000 >> 0x10,2,local_88);
	
	local_5c = 0xc0;
	local_5a = 0xb4;
	local_60 = local_68 + -0x60;
	local_5e = local_66 + -4;
	
	// Draw 2D Menu rectangle background
	FUN_800457b0(&local_60,4,*(u_int *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
	
	return;
}