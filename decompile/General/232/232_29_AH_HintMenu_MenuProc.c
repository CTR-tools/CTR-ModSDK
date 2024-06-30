#include <common.h>

void DECOMP_AH_HintMenu_MenuProc(struct RectMenu* menu)
{
    struct GameTracker *gGT;
    struct Instance *inst;

    u_int *puVar1;
    u_short uVar2;
    char bVar3;
    u_int uVar6;
    int iVar7;
    int *puVar8;
    short sVar9;
    int iVar10;
    int iVar11;
    short sVar12;
    RECT box;
	char hintsFound[32];
    Color color;

    gGT = sdata->gGT;
    bVar3 = false;

	iVar11 = 0;
    DECOMP_MainFreeze_SafeAdvDestroy();

	iVar10 = 0;
    sdata->advProgress.rewards[3] |= 0x400000;

	int numHintsFound = 0;

	int i = 0;
    short* ptrLngID = &D232.hintMenu_lngIndexArr[0];

	for(/**/; *ptrLngID > -1; ptrLngID++, i++)
	{
		int hintID = (ptrLngID[0] - 0x17b)/2;
		int bitIndex = hintID + 0x76;

		if (CHECK_ADV_BIT(sdata->advProgress.rewards, bitIndex) != 0)
		{
			hintsFound[numHintsFound] = i;
			numHintsFound++;
		}
	}

	sVar9 = numHintsFound+1;

    if (menu->rowSelected > numHintsFound)
        menu->rowSelected = numHintsFound;

    if (
		(D232.hintMenu_scrollIndex > (numHintsFound + -4)) &&
        (
			D232.hintMenu_scrollIndex = (short)(numHintsFound + -4),
			D232.hintMenu_scrollIndex < 0
		)
	   )
    {
        D232.hintMenu_scrollIndex = 0;
    }

	int lngIndex =
		D232.hintMenu_lngIndexArr
		[
			hintsFound[menu->rowSelected]
		];

    // if viewing a hint
    if (D232.hintMenu_boolViewHint != 0)
    {
        DECOMP_AH_HintMenu_MaskPosRot();

        if (D232.maskCooldown > 0)
			D232.maskCooldown--;

        // If you press Cross, Square, Triangle, or Circle
        if (((sdata->buttonTapPerPlayer[0] & 0x40070) != 0) &&

            (
				(
					// if no XA is playing anymore
					uVar6 = DECOMP_VehTalkMask_boolNoXA(),
					(uVar6 & 0xffff) != 0 ||

					// allowed to leave hint
					(D232.maskCooldown == 0))
				)
			)
        {
            D232.hintMenu_boolViewHint = 0;

            DECOMP_RECTMENU_ClearInput();

            DECOMP_VehTalkMask_End();
        }

        DECOMP_DecalFont_DrawLine(
			sdata->lngStrings[lngIndex+0],
			0x100, 0x2c,
			1, 0xffff8000);

		// height of multiLine
		iVar11 = DECOMP_DecalFont_DrawMultiLine(
			sdata->lngStrings[lngIndex+1],
			0x96, 0x3f,
			0x14e, 2, 0);

        // "EXIT"
		char* strExit = sdata->lngStrings[0x17a];

		DECOMP_DecalFont_DrawLine(
			strExit,
			0x100, iVar11 + 0x4f,
			1, 0xffff8000);

		iVar10 = DECOMP_DecalFont_GetLineWidth(strExit, 1);

        iVar7 = (iVar10 + 6) * 0x10000;
        box.x = 0xff - (short)((iVar7 >> 0x10) - (iVar7 >> 0x1f) >> 1);
        box.w = (short)(iVar10 + 6);
        box.y = (short)iVar11 + 0x4e;
        box.h = 0x11;

        color.self = sdata->menuRowHighlight_Normal;
        DECOMP_CTR_Box_DrawClearBox(&box, color, TRANS_50_DECAL, gGT->backBuffer->otMem.startPlusFour);

		box.y = 0x3c;
        box.x = -0xe;
        box.w = 0x21c;
        box.h = 2;

        color.self = sdata->battleSetup_Color_UI_1;
        DECOMP_RECTMENU_DrawOuterRect_Edge(&box, color, 0x20, gGT->backBuffer->otMem.startPlusFour);

        box.y = 0x28;
        box.h = (short)iVar11 + 0x3b;
        box.x = -0xe;
        box.w = 0x21c;

        DECOMP_RECTMENU_DrawInnerRect(
			&box, 4, &gGT->backBuffer->otMem.startPlusFour[3]);

        return;
    }

	int tapP1 = sdata->buttonTapPerPlayer[0];

    // If you press Up, Down, Cross, Square, Triangle, Circle
    if ((tapP1 & 0x40073) == 0)
    {
        goto LAB_800b38cc;
    }

    // If you dont press Up
    if ((tapP1 & 1) == 0)
    {
        // If you dont press Down
        if ((tapP1 & 2) == 0)
        {
            // If you dont press Cross or Circle
            if ((tapP1 & 0x50) == 0)
            {
                // If you press Triangle or Square
                if ((tapP1 & 0x40020) != 0)
                {
                    // Play sound
                    DECOMP_OtherFX_Play(2, 1);
                    goto LAB_800b38c0;
                }
            }

            // If you press Cross or Circle
            else
            {
                // Play Sound
                DECOMP_OtherFX_Play(1, 1);

                if (menu->rowSelected == numHintsFound)
                {
                LAB_800b38c0:
                    bVar3 = true;
                }
                else
                {
                    // temporary until XA support is on PC,
                    // otherwise state is locked in 4, and menu bugs
                    #ifdef REBUILD_PC
                    sdata->XA_State = 0;
                    #endif

                    // If there is no loading in progress
                    if ((sdata->load_inProgress == 0) && (sdata->XA_State == 0))
                    {
                        sdata->instMaskHints3D =
							DECOMP_VehTalkMask_Init();

                        D232.maskCooldown = FPS_DOUBLE(30);

                        DECOMP_VehTalkMask_PlayXA(
							sdata->instMaskHints3D,
							(lngIndex + -0x17b)/2);

                        DECOMP_AH_HintMenu_MaskPosRot();

                        // talking mask instance
                        inst = sdata->instMaskHints3D;
                        inst->flags |= 0x400;

						struct InstDrawPerPlayer* idpp =
							INST_GETIDPP(inst);

						idpp[0].pushBuffer = &gGT->pushBuffer_UI;
						for(int j = 1; j < gGT->numPlyrCurrGame; j++)
							idpp[j].pushBuffer = 0;

                        // now viewing a hint
                        D232.hintMenu_boolViewHint = 1;
                    }
                }
            }
        }

        // If you press Down
        else
        {
            // if you are not on the bottom row
            if (menu->rowSelected < numHintsFound)
            {
                // Play Sound
                DECOMP_OtherFX_Play(0, 1);

                // change which row is selected
                menu->rowSelected = menu->rowSelected + 1;
            }
        }
    }

    // If you press Up
    else
    {
        // if you are not on the top row
        if (0 < menu->rowSelected)
        {
            // Play Sound
            DECOMP_OtherFX_Play(0, 1);

            // change the row selected
            menu->rowSelected--;
        }
    }

    // clear gamepad input (for menus)
    DECOMP_RECTMENU_ClearInput();

LAB_800b38cc:

    uVar6 = DECOMP_VehPickupItem_MaskBoolGoodGuy(gGT->drivers[0]);

    // Draw the "Hints" string
    DECOMP_DecalFont_DrawLine(
		sdata->lngStrings[0x178+(uVar6==0)],
		0x100, 0x2c, 1, 0xffff8000);

    if (D232.hintMenu_scrollIndex + 5 <= menu->rowSelected)
    {
        D232.hintMenu_scrollIndex = menu->rowSelected - 4;
    }
    if (menu->rowSelected < D232.hintMenu_scrollIndex)
    {
        D232.hintMenu_scrollIndex = menu->rowSelected;
    }
    sVar12 = 5;
    if (sVar9 < D232.hintMenu_scrollIndex + 5)
    {
        sVar12 = sVar9;
    }

    // if scroll bar is not on top
    if (0 < D232.hintMenu_scrollIndex)
    {
        DECOMP_AH_HintMenu_FiveArrows(0x3f, 0);
    }

    iVar10 = 0x10;
    iVar11 = 0;
    if (0 < sVar12)
    {
        do
        {
            iVar7 = D232.hintMenu_scrollIndex + (int)(short)iVar11;
            if (iVar7 < numHintsFound)
            {
                uVar6 = D232.hintMenu_lngIndexArr
						[
							hintsFound[iVar7]
						];
            }
            else
            {
				// EXIT
                uVar6 = 0x17a;
            }
            iVar7 = iVar10 + 0x40;
            iVar10 = iVar10 + 0x10;

            // "EXIT"
            DECOMP_DecalFont_DrawLine(sdata->lngStrings[uVar6], 0x100, iVar7, 1, 0xffff8000);

            iVar11 = iVar11 + 1;
        } while (iVar11 < sVar12);
    }

    // if scroll bar is not on bottom
    if (D232.hintMenu_scrollIndex + (int)sVar12 < (int)sVar9)
    {
        DECOMP_AH_HintMenu_FiveArrows((iVar10 + 0x40), 0x800);
    }
    box.x = -0xe;
    box.w = 0x21c;
    box.y = (menu->rowSelected - D232.hintMenu_scrollIndex) * 0x10 + 0x4f;
    box.h = 0x11;

    color.self = sdata->menuRowHighlight_Normal;
    DECOMP_CTR_Box_DrawClearBox(&box, color, TRANS_50_DECAL, gGT->backBuffer->otMem.startPlusFour);

    box.y = 0x3c;
    box.h = 2;
    box.x = -0x14;
    box.w = 0x228;

    color.self = sdata->battleSetup_Color_UI_1;
	DECOMP_RECTMENU_DrawOuterRect_Edge(&box, color, 0x20, gGT->backBuffer->otMem.startPlusFour);

    box.y = 0x28;
    box.h = (short)iVar10 + 0x2b;
    box.x = -0x14;
    box.w = 0x228;

	DECOMP_RECTMENU_DrawInnerRect(
		&box, 4, gGT->backBuffer->otMem.startPlusFour);

    if (
        (bVar3) ||

        // If you dont press Start, Square, or Triangle
        ((sdata->buttonTapPerPlayer[0] & 0x41020) != 0))
    {
        DECOMP_RECTMENU_ClearInput();
        sdata->ptrDesiredMenu = DECOMP_MainFreeze_GetMenuPtr();
    }
    return;
}
