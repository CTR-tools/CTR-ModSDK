#include <common.h>

void DECOMP_MM_CupSelect_MenuBox(struct MenuBox *param_1)
{
    struct GameTracker *gGT = sdata->gGT;
    short elapsedFrames;
    u_int txtColor;
    u_int uVar4;
    int iVar5;
    u_int uVar6;
    int *piVar7;
    int iVar8;
    int iVar9;
    int iVar10;
    int iVar11;
    u_int uVar12;
    int iVar13;
    RECT cupBox;

    if (param_1->unk1e == 0)
    {
        OVR_230.cupSel_postTransition_boolStart = (param_1->rowSelected != -1);
        OVR_230.cupSel_transitionState = 2;
        OVR_230.menubox_cupSelect.state &= 0xfffffbff | DISABLE_INPUT_ALLOW_FUNCPTRS;
        return;
    }

    elapsedFrames = OVR_230.cupSel_transitionFrames;

    // if not stationary
    if (OVR_230.cupSel_transitionState != 1)
    {
        // if transitioning in
        if (OVR_230.cupSel_transitionState == 0)
        {
            // Ghidra said it has another param of "1", when it only accepts 3 params.
            MM_TransitionInOut(&OVR_230.transitionMeta_cupSel[0], elapsedFrames, 8);

            // reduce frame count
            elapsedFrames--;

            // if no more frames
            if (elapsedFrames == 0)
            {
                // menu is now in focus
                OVR_230.cupSel_transitionState = 1;
                OVR_230.menubox_cupSelect.state &= 0xffffffdf | BIG_TEXT_IN_TITLE;
            }
        }
        // if transitioning out
        else if (OVR_230.cupSel_transitionState == 2)
        {
            MM_TransitionInOut(&OVR_230.transitionMeta_cupSel[0], elapsedFrames, 8);

            // increase frame count
            elapsedFrames++;

            // if more than 12 frames pass
            if (0xc < elapsedFrames)
            {
                // if cup selected
                if (OVR_230.cupSel_postTransition_boolStart != 0)
                {
                    // set cupID to the cup selected
                    gGT->cup.cupID = param_1->rowSelected;

                    // set track index to zero, to go to first track
                    gGT->cup.trackIndex = 0;

                    // loop through 8 drivers
                    for (iVar8 = 0; iVar8 < 8; iVar8++)
                    {
                        // set all points for all 8 drivers to zero
                        gGT->cup.points[iVar8] = 0;
                    }

                    // passthrough MenuBox for the function
                    sdata->ptrDesiredMenuBox = &data.menuBox_TitleBeginTrack;

                    // set current level
                    gGT->currLEV = data.ArcadeCups[gGT->cup.cupID].CupTrack[gGT->cup.trackIndex].trackID;
                    return;
                }

                // return to character selection
                sdata->ptrDesiredMenuBox = &OVR_230.menubox_characterSelect;

                MM_Characters_RestoreIDs();
                return;
            }
        }
    }

    OVR_230.cupSel_transitionFrames = elapsedFrames;

    // "SELECT CUP RACE"
    DecalFont_DrawLine(sdata->lngStrings[0x2fc],
                       (OVR_230.transitionMeta_cupSel[4].currX + 0x100),
                       (OVR_230.transitionMeta_cupSel[4].currY + 0x10), 1, 0xffff8000);
    // Loop through all four cups
    for (uVar4 = 0; uVar4 < 4; uVar4++)
    {
        // If this cup is the one you selected
        if (iVar11 == param_1->rowSelected)
        {
            // Make text flash

            txtColor = 0xffff8000;
            if ((sdata->frameCounter & 2) == 0)
            {
                txtColor = 0xffff8004;
            }
        }

        // If this is not the cup you're highlighting
        else
        {
            // Use solid color
            txtColor = 0xffff8000;
        }

        // draw the name of the cup
        DecalFont_DrawLine(sdata->lngStrings[(short)data.ArcadeCups[uVar4].lngIndex_CupName],
                           ((u_int)OVR_230.transitionMeta_cupSel[uVar4].currX + (uVar4 & 1) * 200 + 0xa2),
                           ((u_int)OVR_230.transitionMeta_cupSel[uVar4].currY +
                                 (iVar11 - (iVar8 >> 0x1f) >> 1) * 0x54 + 0x44),
                           3, txtColor);

        iVar8 = uVar4 * 0x10000;
    }

    // Loop through all four cups
    for (uVar4 = 0; uVar4 < 4; uVar4++)
    {
        iVar8 = (int)(uVar4 << 0x10) >> 0x10;
        iVar10 = (u_int)OVR_230.transitionMeta_cupSel[iVar8].currX + (uVar4 & 1) * 200 + 0x4e;
        iVar13 = (u_int)OVR_230.transitionMeta_cupSel[iVar8].currY +
                 (iVar8 - ((int)(uVar4 << 0x10) >> 0x1f) >> 1) * 0x54 + 0x29;
        iVar11 = 0;

        // loop through 3 stars to draw
        for (iVar5 = 0; iVar5 < 3; iVar5++)
        {
            uVar6 = *(short *)((int)OVR_230.cupSel_StarUnlockFlag[iVar11 >> 0xf]) + iVar8;
            if ((sdata->gameProgress.unlocks[(int)uVar6 >> 5] >> uVar6 & 1) != 0)
            {
                iVar9 = 0;
                if ((iVar8 != 0) && (iVar8 != 2))
                {
                    iVar9 = 0xca;
                }

                // &DAT_800b562c
                // array of colorIDs
                // 0x11: driver_C (tropy) (blue)
                // 0x0E: driver_9 (papu) (yellow)
                // 0x16: silver

                // Color data
                piVar7 = data.ptrColor[((int)(((int)OVR_230.cupSel_StarColorIndex[iVar11 >> 0xf]) << 0x10) >> 0xe)];

                DecalHUD_DrawPolyGT4(gGT->iconGroup[5]->icons[7],
                                     (iVar10 * 0x10000 >> 0x10) + iVar9 + -0x16,
                                     (iVar13 * 0x10000 >> 0x10) + ((iVar5 << 0x10) >> 0xc) + 0x10,

                                     // pointer to PrimMem struct
                                     &gGT->backBuffer->primMem,

                                     // pointer to OT mem
                                     gGT->tileView_UI.ptrOT,

                                     // color data
                                     piVar7[0], piVar7[1],
                                     piVar7[2], piVar7[3],

                                     0, 0x1000);
            }
            iVar11 = iVar5 * 0x10000;
        }

        // even or odd,
        // left or right side of screen
        uVar6 = 0;

        // loop through all four track icons in one cup
        for (uVar12 = 0; uVar12 < 4; uVar12++)
        {
            // Draw Icon of each track
            MENUBOX_DrawPolyGT4(gGT->ptrIcons[data.ArcadeCups[uVar4].CupTrack[uVar12].trackID],
                                (iVar10 + uVar6 * 0x54),
                                (iVar13 + (uVar12 - ((int)(uVar12 << 0x10) >> 0x1f) >> 1) * 0x23),

                                // pointer to PrimMem struct
                                &gGT->backBuffer->primMem,

                                // pointer to OT mem
                                gGT->tileView_UI.ptrOT,

                                OVR_230.cupSel_Color,
                                OVR_230.cupSel_Color,
                                OVR_230.cupSel_Color,
                                OVR_230.cupSel_Color,
                                0, 0x800);

            // determine if loop iteration is even or odd
            uVar6 = uVar12 & 1;
        }
        if ((short)uVar4 == param_1->rowSelected)
        {
            cupBox.h = (short)iVar10 - 3;
            cupBox.w = (short)iVar13 - 2;
            cupBox.y = 0xae;
            cupBox.x = 0x4a;

            CTR_Box_DrawClearBox(&cupBox, &sdata->menuRowHighlight_Normal, 1,
                                 gGT->backBuffer->otMem.startPlusFour,
                                 &gGT->backBuffer->primMem);
        }
        cupBox.h = (short)iVar10 - 6;
        cupBox.w = (short)iVar13 - 4;
        cupBox.y = 0xb4;
        cupBox.x = 0x4e;

        // Draw 2D Menu rectangle background
        MENUBOX_DrawInnerRect(&cupBox, 0, gGT->backBuffer->otMem.startPlusFour);
    }
    return;
}