#include <common.h>

/*
Ghidra name: FUN_8009fdc8
Status: In-Progress (OVER BUDGET)
Byte budget: 1196/1040
Called in:
  - 224.c
  - MAIN.c
*/

void TT_EndEvent_DrawMenu(void)
{
    int framesSinceRaceEnded;
    struct MenuBox *ptrMenuBox; // TODO: Map Region. Curr: using raw mem addr
    int startX_also_strFlags;   // TODO: Verify type
    short endX;
    short pos[2];
	char** lngStrings;
	u_int unknownFlags_1d44;
    struct GameTracker *gGT;
	
	gGT = sdata->gGT;
	lngStrings = sdata->lngStrings;
	unknownFlags_1d44 = gGT->unknownFlags_1d44;

    sdata->flags_timeTrialEndOfRace |= 1;

    // If you just beat N Tropy && N Tropy was beaten on all tracks
    if (
			((unknownFlags_1d44 & 0x10000000) != 0) && 
			((GAMEPROG_CheckGhostsBeaten(1) & 0xffff) != 0)
		)
    {
        sdata->gameProgress.unlocks[0] |= 0x20; // Unlock N Tropy
    }

	// control the flow of the menu...

    if (sdata->framesSinceRaceEnded < 900)
    {
AddStuff:
        sdata->framesSinceRaceEnded++;
    }
    else
    {
		// if dont need to show high scores,
		// then dont increment framesSinceRaceEnded,
		// and then the later "if > 900" wont happen
        if ((unknownFlags_1d44 & 0x8000000) == 0)
        {
			// between 1001 and 1018, frame counter is paused until &0x10,
			// that's 15 frames between lerp high score off-screen, and showing MenuBox
            if ((sdata->framesSinceRaceEnded < 1018) && ((sdata->menuReadyToPass & 0x10) != 0)) goto AddStuff;
            if (sdata->framesSinceRaceEnded < 1001) goto AddStuff;
        }
    }

    // copy the frame counter variable
    framesSinceRaceEnded = sdata->framesSinceRaceEnded;

	if (sdata->framesSinceRaceEnded < 91)
    {
		// no lerp, just sit on-screen
        startX_also_strFlags = 0x14;
			
        if (sdata->framesSinceRaceEnded > 65)
        {
            startX_also_strFlags = -0x96;
            framesSinceRaceEnded = sdata->framesSinceRaceEnded - 65;
        }
		
		// draw race clock in top-left corner
        UI_Lerp2D_Linear(&pos[0], 0x14, 8, startX_also_strFlags, 8, framesSinceRaceEnded, 0x14);
        UI_DrawRaceClock((int)pos[0], (int)pos[1], 0, gGT->drivers[0]);
    }

	// between 91 and 900 frames (3-30)
	else if (sdata->framesSinceRaceEnded < 901)
	{
		// Blink Orange/White
		startX_also_strFlags = (gGT->timer & 1) ? 0xffff8000 : 0xffff8004;
	
		framesSinceRaceEnded = sdata->framesSinceRaceEnded;
	
		// If the race ended more than 120 frames ago (4 seconds)
		// Start moving "new high score" onto the screen, if necessary
		if ((framesSinceRaceEnded > 120) &&
	
			(UI_Lerp2D_Linear(&pos[0], 0x264, 0x7a, 0x100, 0x7a, framesSinceRaceEnded - 120, 0x14),
	
			// if there is a new high score
			gGT->newHighScoreIndex > -1))
		{
			// "NEW HIGH SCORE!"
			DecalFont_DrawLine(lngStrings[353], (int)pos[0], (int)pos[1], 1, startX_also_strFlags);
	
			// Total time should flash
			sdata->flags_timeTrialEndOfRace |= (1<<2);
		}
	
		// If race ended more than 150 frames ago (5 seconds)
		// Start moving "New Best Lap" onto the screen, if necessary
		if (framesSinceRaceEnded > 150)
		{
			// Fly-in Interpolation
			UI_Lerp2D_Linear(&pos[0], 0xffffff9c, 0x8e, 0x100, 0x8e, framesSinceRaceEnded + -0x96, 0x14);
	
			if ((unknownFlags_1d44 & 0x4000000) != 0)
			{
				// NEW BEST LAP!
				DecalFont_DrawLine(lngStrings[370], (int)pos[0], (int)pos[1], 1, startX_also_strFlags);
	
				// Check which of 3 laps was fastest
				// Make that row flash
				sdata->flags_timeTrialEndOfRace |= (gGT->lapIndexNewBest + 1) << 3;
			}
		}
	
		// if did not just open, or beat, n tropy
		if ((unknownFlags_1d44 & 0x10008000) != 0)
		{
			// Start moving "You Beat N Tropy" onto the screen, if necessary
			if (framesSinceRaceEnded > 180) // 6 seconds
			{
				UI_Lerp2D_Linear(&pos[0], 0x264, 0xa2, 0x100, 0xa2, framesSinceRaceEnded + -0xb4, 0x14);
		
				char *nTropyString;
		
				// default, N Tropy Opened
				nTropyString = lngStrings[371];
		
				// search "18000000"
				// if just beat n tropy, YOU BEAT N. TROPY!
				if ((unknownFlags_1d44 & 0x10000000) != 0)
					nTropyString = lngStrings[372];
				
				// Draw the "N Tropy" related string
				DecalFont_DrawLine(nTropyString, (int)pos[0], (int)pos[1], 1, startX_also_strFlags);
			}
		}

		UI_Lerp2D_Linear(&pos[0], 0xffffff9c, 0x5a, 0x100, 0x5a, framesSinceRaceEnded + -0x5a, 0x14);
	
		TT_EndEvent_DisplayTime((int)pos[0], pos[1], sdata->flags_timeTrialEndOfRace);
	
		// PRESS * TO CONTINUE
		DecalFont_DrawLine(lngStrings[201], 0x100, 0xbe, 1, 0xffff8000);
	
		// If you press Cross or Circle
		if ((sdata->AnyPlayerTap & 0x50) != 0)
		{
			// advance timer, quickly skip to see high scores
			sdata->framesSinceRaceEnded = 901; // 30 seconds
		}
	}

	// 901 or more (30 secs)
    else
    {
        // start drawing the high score menu that shows the top 5 best times
        gGT->unknownFlags_1d44 |= 2;

        if (framesSinceRaceEnded < 1017)
        {
			if ((unknownFlags_1d44 & 0x8000000) == 0)
			{
	
				// ====== Draw High Score ===========
				
				// 900-1002
				if (framesSinceRaceEnded < 1002)
				{
					startX_also_strFlags = -0x96;
					endX = 0x80;
					framesSinceRaceEnded -= 0x385;
				}
				
				// 1002-1017
				else
				{
					startX_also_strFlags = 0x80;
					endX = -0x96;
					framesSinceRaceEnded -= 0x3e9;
				}
	
				UI_Lerp2D_Linear(&pos[0], startX_also_strFlags, 10, endX, 10, framesSinceRaceEnded, 0x14);
				TT_EndEvent_DrawHighScore(pos[0], (int)pos[1], 0);
	
	
				// ====== Draw Your Time ===========
	
	
				// 900-1002
				if (sdata->framesSinceRaceEnded < 1002)
				{
					startX_also_strFlags = 0x296;
					endX = 0x180;
				}
				
				// 1002-1017
				else
				{
					startX_also_strFlags = 0x180;
					endX = 0x296;
				}
	
				UI_Lerp2D_Linear(&pos[0], startX_also_strFlags, 0x82, endX, 0x82, framesSinceRaceEnded, 0x14);
				TT_EndEvent_DisplayTime((int)pos[0], pos[1], sdata->flags_timeTrialEndOfRace);
	
	
				// PRESS * TO CONTINUE
				DecalFont_DrawLine(lngStrings[201], 0x100, 0xbe, 1, 0xffff8000);
	
	
				// ==== Pause Timer until Press X =======
	
	
				// Cross or Circle, or if timer drags on too long
				if (((sdata->AnyPlayerTap & 0x50) != 0) && (sdata->framesSinceRaceEnded < 1002))
				{
					sdata->framesSinceRaceEnded = 1001;
					
					// unpause frame counter,
					// which then counts up to 1018 for transition-out
					sdata->menuReadyToPass |= 0x10;
				}
			}
    
			// let 0.5s pass before showing MenuBox
			return;
		}
    }
	
	// if not showing menu yet
	if ((sdata->menuReadyToPass & 1) == 0)
	{
		// start showing menubox
		sdata->menuReadyToPass = sdata->menuReadyToPass & 0xffffffef | 1;
		
		sdata->flags_timeTrialEndOfRace = 0;
		
		// If ghost is not too big to save
		if (!sdata->boolGhostTooBigToSave)
		{
			// Show end of race menu with "Save Ghost" option
			ptrMenuBox = (struct MenuBox *)0x800a0458;
		}
		
		// If ghost is too big to save
		else
		{
			// Show end of race menu without "Save Ghost" option
			ptrMenuBox = (struct MenuBox *)0x800a04a4;
		}
		
		// Draw end of race menu, see 221 and 222 for more info
		MENUBOX_Show(ptrMenuBox);
	}

    return;
}