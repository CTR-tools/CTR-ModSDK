#include <common.h>

void DECOMP_MM_CupSelect_MenuProc(struct RectMenu* menu)
{
    char i;
    u_char cupIndex;
    u_char starIndex;
    u_char trackIndex;
    short elapsedFrames;
    u_int txtColor;
    u_int *starColor;
    int startX;
    int startY;
    struct GameTracker *gGT = sdata->gGT;
    RECT cupBox;

    if (menu->unk1e == 0)
    {
        D230.cupSel_postTransition_boolStart = (menu->rowSelected != -1);
        D230.cupSel_transitionState = 2;
        D230.menuCupSelect.state &= ~(EXECUTE_FUNCPTR);
		D230.menuCupSelect.state |= DISABLE_INPUT_ALLOW_FUNCPTRS;
        return;
    }

    elapsedFrames = D230.cupSel_transitionFrames;

    // if not stationary
    if (D230.cupSel_transitionState != 1)
    {
        // if transitioning in
        if (D230.cupSel_transitionState == 0)
        {
            DECOMP_MM_TransitionInOut(&D230.transitionMeta_cupSel[0], elapsedFrames, FPS_DOUBLE(8));

            // if no more frames
            if (elapsedFrames == 0)
            {
                // menu is now in focus
                D230.cupSel_transitionState = 1;
				D230.menuCupSelect.state &= ~(DISABLE_INPUT_ALLOW_FUNCPTRS);
				D230.menuCupSelect.state |= EXECUTE_FUNCPTR;
            }
			
			else
			{
				elapsedFrames--;
			}
        }
        // if transitioning out
        else if (D230.cupSel_transitionState == 2)
        {
            DECOMP_MM_TransitionInOut(&D230.transitionMeta_cupSel[0], elapsedFrames, FPS_DOUBLE(8));

            // increase frame count
            elapsedFrames++;

            // if more than 12 frames pass
            if (FPS_DOUBLE(12) < elapsedFrames)
            {
                // if cup selected
                if (D230.cupSel_postTransition_boolStart != 0)
                {
                    // loop through 8 drivers
                    for (i = 0; i < 8; i++)
                    {
                        // set all points for all 8 drivers to zero
                        gGT->cup.points[i] = 0;
                    }

                    // passthrough Menu for the function
                    sdata->ptrDesiredMenu = &data.menuQueueLoadTrack;

                    // set track index to zero, to go to first track
                    gGT->cup.trackIndex = 0;
					
                    // set cupID to the cup selected
                    gGT->cup.cupID = menu->rowSelected;

                    // set current level
                    gGT->currLEV = data.ArcadeCups[gGT->cup.cupID].CupTrack[0].trackID;
                    return;
                }

                // return to character selection
                sdata->ptrDesiredMenu = &D230.menuCharacterSelect;

                DECOMP_MM_Characters_RestoreIDs();
                return;
            }
        }
    }
	
	#ifdef USE_NEWCUPS
	if(D230.cupSel_transitionState != 2)
	{
		void CustomCups_MenuProc(struct RectMenu* menu);
		CustomCups_MenuProc(menu);
	}
	#endif

    D230.cupSel_transitionFrames = elapsedFrames;

    // "SELECT CUP RACE"
    DECOMP_DecalFont_DrawLine(
		sdata->lngStrings[0xBF],
		(D230.transitionMeta_cupSel[4].currX + 0x100),
		(D230.transitionMeta_cupSel[4].currY + 0x10), 
		1, 0xffff8000);
		
    // Loop through all four cups
    for (cupIndex = 0; cupIndex < 4; cupIndex++)
    {
        // Use solid color
        txtColor = 0xffff8000;
		
        // If this cup is the one you selected
        if (cupIndex == menu->rowSelected)
        {
            // Make text flash
			if ((sdata->frameCounter & FPS_DOUBLE(2)) != 0)
				txtColor |= 4;
        }

		startX = (short)D230.transitionMeta_cupSel[cupIndex].currX + (cupIndex &1) * 200;
		startY = (short)D230.transitionMeta_cupSel[cupIndex].currY + (cupIndex>>1) * 0x54;

        // draw the name of the cup
        DECOMP_DecalFont_DrawLine(
			sdata->lngStrings[data.ArcadeCups[cupIndex].lngIndex_CupName],                  
			startX + 0xa2, startY + 0x44, 3, txtColor);

        startX = startX + 0x4e;
        startY = startY + 0x29;

        // loop through 3 stars to draw
        for (starIndex = 0; starIndex < 3; starIndex++)
        {
			// assuming starUnlock is never more than 32,
			// otherwise you'd do [flag>>5] >> flag&0x1f
            int starUnlock = D230.cupSel_StarUnlockFlag[starIndex] + cupIndex;
            if (((sdata->gameProgress.unlocks[0] >> starUnlock) & 1) != 0)
            {
                // array of colorIDs
                // 0x11: driver_C (tropy) (blue)
                // 0x0E: driver_9 (papu) (yellow)
                // 0x16: silver

                starColor = data.ptrColor[D230.cupSel_StarColorIndex[starIndex]];

				struct Icon** iconPtrArray =
					ICONGROUP_GETICONS(gGT->iconGroup[5]);

                DECOMP_DecalHUD_DrawPolyGT4(
					iconPtrArray[0x37],
					(startX + (cupIndex & 1) * 0xCA - 0x16),
					(startY + ((starIndex * 0x10) + 0x10)),
					&gGT->backBuffer->primMem,
					gGT->pushBuffer_UI.ptrOT,
					starColor[0], starColor[1],
					starColor[2], starColor[3],
					0, FP(1.0));
            }
        }

        // loop through all four track icons in one cup
        for (trackIndex = 0; trackIndex < 4; trackIndex++)
        {
			int posX = (startX + (trackIndex &1) * 0x54);
			int posY = (startY + (trackIndex>>1) * 0x23);
			
			#ifdef USE_16BY9
			if (trackIndex &1)
			{
				// right icons move 12% of 0x54, to the left
				posX -= 10;
			}
			else
			{				
				// left icons move 12% of 0x54, to the right
				posX += 10;
			}
			#endif
			
            // Draw Icon of each track
            DECOMP_RECTMENU_DrawPolyGT4(
				gGT->ptrIcons[data.ArcadeCups[cupIndex].CupTrack[trackIndex].iconID],
				posX, posY,
				&gGT->backBuffer->primMem,
				gGT->pushBuffer_UI.ptrOT,
				D230.cupSel_Color,
				D230.cupSel_Color,
				D230.cupSel_Color,
				D230.cupSel_Color,
				0, FP(0.5));
        }
		
        if (cupIndex == menu->rowSelected)
        {
			// highlight box
            cupBox.x = startX - 3;
            cupBox.y = startY - 2;
            cupBox.w = 174;
            cupBox.h = 74;

            DECOMP_CTR_Box_DrawClearBox(
				&cupBox, &sdata->menuRowHighlight_Normal, TRANS_50_DECAL,
				gGT->backBuffer->otMem.startPlusFour,
				&gGT->backBuffer->primMem);
        }
		
		// background box
        cupBox.x = startX - 6;
        cupBox.y = startY - 4;
        cupBox.w = 180;
        cupBox.h = 78;
        
		DECOMP_RECTMENU_DrawInnerRect(
			&cupBox, 0, gGT->backBuffer->otMem.startPlusFour);
    }
}

#ifdef USE_NEWCUPS

// Transfer data from Single(SIN) menu to Cup(CUP) menu
#define CUP_TRACK(i, cup) data.ArcadeCups[cup].CupTrack[i].trackID
#define SIN_TRACK(i, cup) D230.arcadeTracks[cc->choiceX[cup][i]].levID
#define CUP_ICON(i, cup) data.ArcadeCups[cup].CupTrack[i].iconID
#define SIN_ICON(i, cup) D230.arcadeTracks[cc->choiceX[cup][i]].videoThumbnail

struct CustomCup
{
	char choiceX[4][4];

	char choiceY;
	char boolOpen;
};

struct CustomCup cc_static;
struct CustomCup* cc = &cc_static;

RECT windowSel[4] = 
{
	[0] = {0x100, 0x25, WIDE_PICK(0xE0, 0xC0), 0x4E}, // top right
	[1] = {0x20,  0x25, WIDE_PICK(0xE0, 0xC0), 0x4E}, // top left
	[2] = {0x100, 0x79, WIDE_PICK(0xE0, 0xC0), 0x4E}, // bottom right
	[3] = {0x20,  0x79, WIDE_PICK(0xE0, 0xC0), 0x4E}  // bottom left
};

RECT windowText = {0x40, 0, 0x180, 0x50};

static char CustomCups_boolRepeat(int numTracksSet, int currTrack, int cupIndex)
{
	int i;

	// check if track is taken
	// previously (<)
	// or by self (=)
	for (i = 0; i <= numTracksSet; i++)
		if (cc->choiceX[cupIndex][i] == currTrack)
			return 1;

	return 0;
}

void CustomCups_MenuProc(struct RectMenu* menu)
{
	int i;
	unsigned int buttonTap;
	int id;
	
	int CUP_SELECT = D230.menuCupSelect.rowSelected;

	DecalFont_DrawLine(
		"PRESS SELECT FOR CUSTOM CUPS",
		0x100,
		0x4,
		FONT_SMALL,
		(JUSTIFY_CENTER | ORANGE));

	buttonTap = sdata->gGamepads->gamepad[0].buttonsTapped;

	if (buttonTap & BTN_SELECT)
	{
		cc->boolOpen = !cc->boolOpen;
		cc->choiceY = 0;
	}

	if (cc->boolOpen)
	{		
		// prevent cup from changing selection
		// while in the custom cups config menu
		sdata->AnyPlayerTap &= ~(0xF);
		sdata->buttonTapPerPlayer[0] &= ~(0xF);
		
		if (buttonTap & BTN_UP) cc->choiceY--;
		if (buttonTap & BTN_DOWN) cc->choiceY++;
		cc->choiceY &= 3;
		
		if (buttonTap & BTN_LEFT)
			cc->choiceX[CUP_SELECT][cc->choiceY]--;
		if (buttonTap & BTN_RIGHT)
			cc->choiceX[CUP_SELECT][cc->choiceY]++;

		// pressing Left on Crash Cove goes to Turbo Track,
		// pressing Right on Turbo Track goes to Crash Cove
		if (cc->choiceX[CUP_SELECT][cc->choiceY] < 0)
			cc->choiceX[CUP_SELECT][cc->choiceY] = 17;
		else
			cc->choiceX[CUP_SELECT][cc->choiceY] = 
			cc->choiceX[CUP_SELECT][cc->choiceY] % 18;

		if ((buttonTap & BTN_R1) != 0)
		{
			i = 0;

			while (i < 4)
			{
				// random
				MixRNG_Scramble();

				id = (
						 // system clock
						 (Timer_GetTime_Total() & 0xf)

						 +

						 // from RNG
						 (sdata->randomNumber >> 8)

							 ) %
					 18; // 18 tracks

				// avoid repeats
				if (CustomCups_boolRepeat(i, id, CUP_SELECT))
					continue;

				// set value
				cc->choiceX[CUP_SELECT][i] = id;
				i++;
			}
		}

		int startX;
		int startY;

		int flipSide = 
			(CUP_SELECT & ~(1)) |
			(!(CUP_SELECT & 1));

		// copied from CupSelect_MenuProc
		startX = (short)D230.transitionMeta_cupSel[flipSide].currX + (flipSide &1) * 200;
		startY = (short)D230.transitionMeta_cupSel[flipSide].currY + (flipSide>>1) * 0x54;
		
		// copied from CupSelect_MenuProc
        startX = startX + 0x4e -3-3;
        startY = startY + 0x29 -2-2;
		
		windowSel[CUP_SELECT].x = startX;
		windowSel[CUP_SELECT].y = startY;
		
		startX += 8;
		startY += 11;

		// Draw arrow
		DecalFont_DrawLine(
			"-\0",
			startX,
			startY + 0x10 * cc->choiceY,
			FONT_SMALL,
			ORANGE);

		// set values of all cups
		for (i = 0; i < 4; i++)
		{
			// Set trackID
			CUP_TRACK(i, CUP_SELECT) = SIN_TRACK(i, CUP_SELECT);

			// set iconID
			CUP_ICON(i, CUP_SELECT) = SIN_ICON(i, CUP_SELECT);

			// Draw name of track
			DecalFont_DrawLine(
				sdata->lngStrings[CUP_TRACK(i, CUP_SELECT) + 0x6e],
				startX + 0x10,
				startY + 0x10 * i,
				FONT_SMALL,
				ORANGE);
		}

		windowText.y = 0x25;
		if(CUP_SELECT < 2)
			windowText.y = 0x79;

		DecalFont_DrawLine(
			"USE D-PAD TO CUSTOMIZE CUP",
			0x100,
			windowText.y + 0x18,
			FONT_SMALL,
			(JUSTIFY_CENTER | PERIWINKLE));

		DecalFont_DrawLine(
			"PRESS R1 TO RANDOMOMIZE",
			0x100,
			windowText.y + 0x30,
			FONT_SMALL,
			(JUSTIFY_CENTER | PERIWINKLE));

		struct DB *backBuffer = 
			sdata->gGT->backBuffer;

		RECTMENU_DrawInnerRect(
			&windowSel[CUP_SELECT], 1, 
			backBuffer->otMem.startPlusFour);

		RECTMENU_DrawInnerRect(
			&windowText, 1, 
			backBuffer->otMem.startPlusFour);
	}
}

void CustomCups_Init()
{
	// Start with default tracks,
	// each choiceX[x][y] is the index of D230.arcadeTracks
	// that matches data.ArcadeCups[x].CupTrack[y].trackID;
	cc->choiceX[0][0] = 0;
	cc->choiceX[0][1] = 2;
	cc->choiceX[0][2] = 5;
	cc->choiceX[0][3] = 3;
	cc->choiceX[1][0] = 1;
	cc->choiceX[1][1] = 7;
	cc->choiceX[1][2] = 9;
	cc->choiceX[1][3] = 6;
	cc->choiceX[2][0] = 4;
	cc->choiceX[2][1] = 8;
	cc->choiceX[2][2] = 11;
	cc->choiceX[2][3] = 12;
	cc->choiceX[3][0] = 10;
	cc->choiceX[3][1] = 14;
	cc->choiceX[3][2] = 13;
	cc->choiceX[3][3] = 16;
	
	// set values of all cups
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			// Set trackID
			CUP_TRACK(i, j) = SIN_TRACK(i, j);
	
			// set iconID
			CUP_ICON(i, j) = SIN_ICON(i, j);
		}
	}

	cc->choiceY = 0;
	cc->boolOpen = 0;
}
#endif