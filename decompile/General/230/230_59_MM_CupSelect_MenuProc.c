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

            Color color;
            color.self = sdata->menuRowHighlight_Normal;
            DECOMP_CTR_Box_DrawClearBox(&cupBox, color, TRANS_50_DECAL, gGT->backBuffer->otMem.startPlusFour);
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
#include "../AltMods/MM_CustomCups.c"
#endif