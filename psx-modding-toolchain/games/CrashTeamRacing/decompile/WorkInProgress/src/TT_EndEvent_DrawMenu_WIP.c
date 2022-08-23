void TT_EndEvent_DrawMenu()
{
	u_int tropyBeat;
	int frameCounterCopy;
	u_char *puVar2;
	u_int startX_but_its_also_strFlags;
	u_int endX_but_its_also_a_string;
	short posX;
	short posY;
	
	sdata.flags_timeTrialEndOfRace |= 1;
	
	if
	(
		// If you just beat. N Tropy
		((sdata.gGT->unknownFlags_1d44 & 0x10000000) != 0) &&
		 
		(
			// Check to see if N. Tropy was beaten on all tracks
			tropyBeat = GAMEPROG_CheckGhostsBeaten(1), 
			
			// if N. Tropy's ghosts are beaten on all tracks
			(tropyBeat & 0xffff) != 0
		)
	)
	{
		// Unlock N. Tropy
		sdata.gameProgress.Unlocks.characters_tracks |= 0x20;
	}
	
	// If the race ended less than 900 frames ago (30 seconds) 
	if (sdata.framesSinceRaceEnded < 900) 
	{
		addFrame:

		// add to frame counter
		sdata.framesSinceRaceEnded++;
	}
	
	// If the race ended 900 frames ago or more (30 seconds) 
	else 
	{
		if ((sdata.gGT->unknownFlags_1d44 & 0x8000000) == 0)
		{
			if ((sdata.framesSinceRaceEnded < 0x3fa) && ((sdata.menuReadyToPass & 0x10) != 0)) goto addFrame;
			if (sdata.framesSinceRaceEnded < 0x3e9)
			{
				// add to frame counter
				sdata.framesSinceRaceEnded++;
			}
		}
	}
	
	// copy the frame counter variable
	frameCounterCopy = sdata.framesSinceRaceEnded;
	
	// If the race ended more than 900 frames ago (30 seconds) 
	if (900 < sdata.framesSinceRaceEnded) 
	{
		// start drawing the high score menu that shows the top 5 best times
		tropyBeat = sdata.gGT->unknownFlags_1d44;
		sdata.gGT->unknownFlags_1d44 = tropyBeat | 2;
	
		if ((frameCounterCopy < 0x3f9) && ((tropyBeat & 0x8000000) == 0))
		{
			if (frameCounterCopy < 0x3ea)
			{
				startX_but_its_also_strFlags = 0xffffff6a;
				endX_but_its_also_a_string = 0x80;
				frameCounterCopy = frameCounterCopy - 0x385;
			}
			else
			{
				startX_but_its_also_strFlags = 0x80;
				endX_but_its_also_a_string = 0xffffff6a;
				frameCounterCopy = frameCounterCopy - 0x3e9;
			}
		
			InterpolatePosition2D_Linear(&posX, startX_but_its_also_strFlags, 10, endX_but_its_also_a_string, 10, frameCounterCopy, 0x14);
			
			TT_EndEvent_DrawHighScore((int)posX, (int)posY, 0);
		
			if (sdata.framesSinceRaceEnded < 0x3ea)
			{
				startX_but_its_also_strFlags = 0x296;
				endX_but_its_also_a_string = 0x180;
				frameCounterCopy = sdata.framesSinceRaceEnded - 0x385;
			}
			else
			{
				startX_but_its_also_strFlags = 0x180;
				endX_but_its_also_a_string = 0x296;
				frameCounterCopy = sdata.framesSinceRaceEnded - 0x3e9;
			}
		
			// Fly-in Interpolation
			InterpolatePosition2D_Linear(&posX, startX_but_its_also_strFlags, 0x82, endX_but_its_also_a_string, 0x82, frameCounterCopy, 0x14);
			
			TT_EndEvent_DisplayTime((int)posX, (int)posY, sdata.flags_timeTrialEndOfRace);
				
			// PRESS * TO CONTINUE
			DecalFont_DrawLine(sdata.lngStrings[0x324], 0x100, 0xbe, 1, 0xffff8000);
				
			// Cross or Circle, or if timer drags on too long
			if (((sdata.AnyPlayerTap & 0x50) != 0) && (sdata.framesSinceRaceEnded < 0x3ea))
			{
				sdata.framesSinceRaceEnded = 0x3e9;
				sdata.menuReadyToPass = sdata.menuReadyToPass | 0x10;
			}
		}
		goto LAB_800a03c0;
	}
	
	// If the race ended less than 90 frames ago
	if (sdata.framesSinceRaceEnded < 0x5b) 
	{
		// If race ended less than 66 frames ago
		if (sdata.framesSinceRaceEnded < 0x42)
		{
			startX_but_its_also_strFlags = 0x14;
		}
	
		// If race ended 66 frames ago or more
		else
		{
			startX_but_its_also_strFlags = 0xffffff6a;
			frameCounterCopy = sdata.framesSinceRaceEnded + -0x41;
		}
	
		// These next two functions are related to drawing "TIME" and "TIME TRIAL" in the top-left corner of screen
	
		// Fly-in Interpolation
		InterpolatePosition2D_Linear(&posX, 0x14, 8, startX_but_its_also_strFlags, 8, frameCounterCopy, 0x14);
	
		DrawRaceClock((int)posX, (int)posY, 0, sdata.gGT->drivers[0]);
		goto LAB_800a03c0;
	}
	
	// If the race ended more than 120 frames ago (4 seconds)
	// Start moving "new high score" onto the screen, if necessary
	if 
	(
		(0x78 < sdata.framesSinceRaceEnded) &&
	
		// Fly-in Interpolation
		(InterpolatePosition2D_Linear(&posX, 0x264, 0x7a, 0x100, 0x7a, sdata.framesSinceRaceEnded - 0x78, 0x14),
	 
		// if there is a new high score
		-1 < sdata.newHighScoreIndex)
	)
	{
		// Change color of text every frame to make it blink
	
		// Default orange color
		startX_but_its_also_strFlags = 0xffff8000;

		// if the frame you are on, has an even number
		if ((sdata.gGT->timer & 1) == 0) 
		{
			// New white color
			startX_but_its_also_strFlags = 0xffff8004;
		}

		// "NEW HIGH SCORE!"
		DecalFont_DrawLine(sdata.lngStrings[0x584], (int)posX, (int)posY, 1, startX_but_its_also_strFlags);
	
		// Total time should flash
		sdata.flags_timeTrialEndOfRace = sdata.flags_timeTrialEndOfRace | 4;
	}

	// If race ended more than 150 frames ago (5 seconds)
	// Start moving "New Best Lap" onto the screen, if necessary
	if
	(
		(0x96 < sdata.framesSinceRaceEnded) &&

		// Fly-in Interpolation
		(InterpolatePosition2D_Linear(&posX, 0xffffff9c, 0x8e, 0x100, 0x8e, sdata.framesSinceRaceEnded - 0x96, 0x14),

		(sdata.gGT->unknownFlags_1d44 & 0x4000000) != 0)
	)
	{
		// Change color of text every frame to make it blink
	
		// Default orange color
		startX_but_its_also_strFlags = 0xffff8000;

		// if the frame you are on, has an even number
		if ((sdata.gGT->timer & 1) == 0) 
		{
			// New white color
			startX_but_its_also_strFlags = 0xffff8004;
		}

		// NEW BEST LAP!
		DecalFont_DrawLine(sdata.lngStrings[0x5c8], (int)posX, (int)posY, 1, startX_but_its_also_strFlags);
	
		// If first lap is the new fastest lap
		if (sdata.gGT->lapIndexNewBest == 0) 
		{
			// make first row flash
			sdata.flags_timeTrialEndOfRace = sdata.flags_timeTrialEndOfRace | 8;
		}
	
		// if new fastest lap was not your first lap
		else 
		{
			// if second lap is the new fastest lap
			if (sdata.gGT->lapIndexNewBest == 1) 
			{
				// make second row flash
				sdata.flags_timeTrialEndOfRace = sdata.flags_timeTrialEndOfRace | 0x10;
			}
		}

		// if third lap is the new fastest lap
		if (sdata.gGT->lapIndexNewBest == 2) 
		{
			// make third row flash
			sdata.flags_timeTrialEndOfRace = sdata.flags_timeTrialEndOfRace | 0x20;
		}
	}
	
	// If race ended more than 180 frames ago (6 seconds)
	// Start moving "YOU BEAT N. TROPY" onto the screen, if necessary
	if (0xb4 < sdata.framesSinceRaceEnded) 
	{
		// Fly-in Interpolation
		InterpolatePosition2D_Linear(&posX, 0x264, 0xa2, 0x100, 0xa2, sdata.framesSinceRaceEnded - 0xb4, 0x14);
	
		if ((sdata.gGT->unknownFlags_1d44 & 0x8000) == 0) 
		{
			// If you did not just beat N Tropy
			if ((sdata.gGT->unknownFlags_1d44 & 0x10000000) == 0) goto LAB_800a016c;
			
			// The next block of code only happens if you just beat N Tropy
	
			// Change color of text every frame to make it blink
		
			// Default orange color
			startX_but_its_also_strFlags = 0xffff8000;
		
			// if the frame you are on, has an even number
			if ((sdata.gGT->timer & 1) == 0) 
			{
				// New white color
				startX_but_its_also_strFlags = 0xffff8004;
			}
		
			// YOU BEAT N. TROPY!
			endX_but_its_also_a_string = sdata.lngStrings[0x5d0];
		}
		else 
		{
			// Change color of text every frame to make it blink
		
			// Default orange color
			startX_but_its_also_strFlags = 0xffff8000;
		
			// if the frame you are on, has an even number
			if ((sdata.gGT->timer & 1) == 0) 
			{
				// New white color
				startX_but_its_also_strFlags = 0xffff8004;
			}
		
			// N. TROPY OPENED!
			endX_but_its_also_a_string = sdata.lngStrings[0x5cc];
		}
	
		// Draw the N. Tropy-related string
		DecalFont_DrawLine(endX_but_its_also_a_string, (int)posX, (int)posY, 1, startX_but_its_also_strFlags);
	}
	
LAB_800a016c:

	// fly-in interpolation
	InterpolatePosition2D_Linear(&posX, 0xffffff9c, 0x5a, 0x100, 0x5a, sdata.framesSinceRaceEnded + -0x5a, 0x14);
	
	TT_EndEvent_DisplayTime((int)posX, (int)posY, sdata.flags_timeTrialEndOfRace);
	
	// PRESS * TO CONTINUE
	DecalFont_DrawLine(sdata.lngStrings[0x324],0x100,0xbe,1,0xffff8000);
	
	// If you press Cross or Circle
	if ((sdata.AnyPlayerTap & 0x50) != 0) 
	{
		// Advance the timer to 900 (30 seconds), 
		// so that you quickly skip to see high scores
		sdata.framesSinceRaceEnded = 0x385;
	}
	
LAB_800a03c0:
	if (((sdata.menuReadyToPass & 1) == 0) && (0x3f8 < sdata.framesSinceRaceEnded)) 
	{
		// Start drawing high scores
		sdata.menuReadyToPass = sdata.menuReadyToPass & 0xffffffef | 1;
	
		sdata.flags_timeTrialEndOfRace = 0;
	
		// If ghost is not too big to save
		if (data.boolGhostTooBigToSave == 0) 
		{
			// Show end of race menu with "Save Ghost" option
			puVar2 = &DAT_800a0458;
		}
	
		// If ghost is too big to save
		else 
		{
			// Show end of race menu without "Save Ghost" option
			puVar2 = &DAT_800a04a4;
		}
	
		// Draw end of race menu, see 221 and 222 for more info
		MenuBox_Show(puVar2);
	}
	return;
}