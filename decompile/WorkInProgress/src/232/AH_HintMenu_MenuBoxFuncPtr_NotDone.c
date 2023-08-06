#include <common.h>

void AH_HintMenu_MenuBoxFuncPtr(struct MenuBox *mb)
{

    struct GameTracker *gGT;
    struct Instance *inst;

    u_int *puVar1;
    u_short uVar2;
    char bVar3;
    short sVar5;
    uint uVar6;
    int iVar7;
    int *puVar8;
    short sVar9;
    int iVar10;
    int iVar11;
    short sVar12;
    char local_70[64];
    RECT box;

    gGT = sdata->gGT;
    bVar3 = false;
    iVar11 = 0;
    MainFreeze_SafeAdvDestroy();
    iVar10 = 0;
    sdata->advProgress.rewards[3] |= 0x400000;
    sVar9 = DAT_800b54f4;
    while (sVar5 = (short)iVar11, -1 < sVar9)
    {
        uVar6 = ((int)*(short *)((int)&DAT_800b54f4 + ((iVar10 << 0x10) >> 0xf)) + -0x17b) / 2 +
                0x76;

        // 0x8fba4 is where the adventure profile (currently loaded) begins
        if (CHECK_ADV_BIT(sdata->advProgress.rewards, uVar6) != 0)
        {
            iVar11 = iVar11 + 1;
            local_70[sVar5] = (char)iVar10;
        }
        iVar10 = iVar10 + 1;
        sVar9 = *(short *)((int)&DAT_800b54f4 + (iVar10 * 0x10000 >> 0xf));
    }
    sVar9 = (short)(iVar11 + 1);
    if (sVar5 < mb->rowSelected)
    {
        mb->rowSelected = sVar5;
    }
    if ((((iVar11 + 1)) + -5 < *(short *)0x800b5664) &&
        (*(short *)0x800b5664 = (short)(iVar11 + -4), (iVar11 + -4) * 0x10000 < 0))
    {
        *(short *)0x800b5664 = 0;
    }

    // if viewing a hint
    if (*(char *)0x800b5660 != 0)
    {
        uVar2 = (&DAT_800b54f4)[local_70[mb->rowSelected]];

        AH_HintMenu_MaskPosRot();

        if (0 < *(short *)0x800b51ee)
        {
            *(short *)0x800b51ee --;
        }

        // If you press Cross, Square, Triangle, or Circle
        if (((sdata->buttonTapPerPlayer[0] & 0x40070) != 0) &&

            // if no XA is playing anymore
            ((uVar6 = TalkingMask_boolNotTalking(), (uVar6 & 0xffff) != 0 || (*(short *)0x800b51ee == 0))))
        {
            // not viewing hint anymore
            *(char *)0x800b5660 = 0;

            MENUBOX_ClearInput();

            TalkingMask_End();
        }
        iVar11 = uVar2;

        DecalFont_DrawLine(sdata->lngStrings[iVar11], 0x100, 0x2c, 1, 0xffff8000);

        iVar11 = DecalFont_DrawMultiLine(sdata->lngStrings[iVar11 + 1], 0x96, 0x3f, 0x14e, 2, 0);

        // "EXIT"
        DecalFont_DrawLine(sdata->lngStrings[0x17a], 0x100, iVar11 + 0x4f, 1, 0xffff8000);

        // "EXIT"
        iVar10 = DecalFont_GetLineWidth(sdata->lngStrings[0x17a], 1);

        iVar7 = (iVar10 + 6) * 0x10000;
        box.x = 0xff - (short)((iVar7 >> 0x10) - (iVar7 >> 0x1f) >> 1);
        box.w = (short)(iVar10 + 6);
        box.y = (short)iVar11 + 0x4e;
        box.h = 0x11;

        CTR_Box_DrawClearBox(&box, &sdata->menuRowHighlight_Normal, 1, gGT->backBuffer->otMem.startPlusFour,

                             // pointer to PrimMem struct
                             &gGT->backBuffer->primMem);
        box.y = 0x3c;
        box.x = -0xe;
        box.w = 0x21c;
        box.h = 2;

        // MENUBOX_DrawOuterRect_Edge (transparent)
        MENUBOX_DrawOuterRect_Edge(&box, &sdata->battleSetup_Color_UI_1, 0x20, gGT->backBuffer->otMem.startPlusFour);

        box.y = 0x28;
        box.h = (short)iVar11 + 0x3b;
        box.x = -0xe;
        box.w = 0x21c;

        // Draw 2D Menu rectangle background
        MENUBOX_DrawInnerRect(&box, 4, gGT->backBuffer->otMem.startPlusFour + 0xc);

        return;
    }

    // If you press Up, Down, Cross, Square, Triangle, Circle
    if ((sdata->buttonTapPerPlayer[0] & 0x40073) == 0)
    {
        goto LAB_800b38cc;
    }

    // If you dont press Up
    if ((sdata->buttonTapPerPlayer[0] & 1) == 0)
    {

        // If you dont press Down
        if ((sdata->buttonTapPerPlayer[0] & 2) == 0)
        {

            // If you dont press Cross or Circle
            if ((sdata->buttonTapPerPlayer[0] & 0x50) == 0)
            {

                // If you press Triangle or Square
                if ((sdata->buttonTapPerPlayer[0] & 0x40020) != 0)
                {
                    // Play sound
                    OtherFX_Play(2, 1);
                    goto LAB_800b38c0;
                }
            }

            // If you press Cross or Circle
            else
            {
                // Play Sound
                OtherFX_Play(1, 1);

                if (mb->rowSelected == sVar5)
                {
                LAB_800b38c0:
                    bVar3 = true;
                }
                else
                {
                    // If there is no loading in progress
                    if ((sdata->load_inProgress == 0) && (sdata->XA_State == 0))
                    {

                        sdata->instMaskHints3D = TalkingMask_Init();

                        *(short *)0x800b51ee = 0x1e;

                        TalkingMask_PlayXA(sdata->instMaskHints3D,
                                           (((int)(short)(&DAT_800b54f4)[local_70[mb->rowSelected]] + -0x17b) -
                                            ((int)(short)(&DAT_800b54f4)[local_70[mb->rowSelected]] + -0x17b >> 0x1f)) *
                                                   0x8000 >>
                                               0x10);

                        AH_HintMenu_MaskPosRot();

                        // talking mask instance
                        inst = sdata->instMaskHints3D;

                        inst->idpp[0].tileView = gGT->tileView_UI;

                        inst->flags |= 0x400;

                        iVar10 = 1;

                        // if more than 1 screen
                        if (1 < gGT->numPlyrCurrGame)
                        {
                            // loop through Instance DPPs
                            do
                            {
                                // clear instance->tileView per player
                                inst->idpp[iVar10].tileView = NULL;
                                iVar10++;

                            } while (iVar10 < gGT->numPlyrCurrGame);
                        }

                        // now viewing a hint
                        *(char *)0x800b5660 = 1;
                    }
                }
            }
        }

        // If you press Down
        else
        {
            // if you are not on the bottom row
            if (mb->rowSelected < sVar5)
            {
                // Play Sound
                OtherFX_Play(0, 1);

                // change which row is selected
                mb->rowSelected = mb->rowSelected + 1;
            }
        }
    }

    // If you press Up
    else
    {
        // if you are not on the top row
        if (0 < mb->rowSelected)
        {
            // Play Sound
            OtherFX_Play(0, 1);

            // change the row selected
            mb->rowSelected--;
        }
    }

    // clear gamepad input (for menus)
    MENUBOX_ClearInput();

LAB_800b38cc:

    uVar6 = Weapon_Mask_boolGoodGuy(gGT->drivers[0]);

    // If they use Uka
    if ((uVar6 & 0xffff) == 0)
    {
        // "UKA UKA HINTS"
        puVar8 = sdata->lngStrings[0x179];
    }

    // If they use Aku
    else
    {
        // "AKU AKU HINTS"
        puVar8 = sdata->lngStrings[0x178];
    }

    // Draw the "Hints" string
    DecalFont_DrawLine(*puVar8, 0x100, 0x2c, 1, 0xffff8000);

    if (*(short *)0x800b5664 + 5 <= mb->rowSelected)
    {
        *(short *)0x800b5664 = mb->rowSelected - 4;
    }
    if (mb->rowSelected < *(short *)0x800b5664)
    {
        *(short *)0x800b5664 = mb->rowSelected;
    }
    sVar12 = 5;
    if (sVar9 < *(short *)0x800b5664 + 5)
    {
        sVar12 = sVar9;
    }

    // if scroll bar is not on top
    if (0 <*(short *)0x800b5664)
    {
        AH_HintMenu_FiveArrows(0x3f, 0);
    }

    iVar10 = 0x10;
    iVar11 = 0;
    if (0 < sVar12)
    {
        do
        {
            iVar7 = *(short *)0x800b5664 + (int)(short)iVar11;
            if (iVar7 < sVar5)
            {
                uVar6 = (uint)(ushort)(&DAT_800b54f4)[local_70[iVar7]];
            }
            else
            {
                uVar6 = 0x17a;
            }
            iVar7 = iVar10 + 0x40;
            iVar10 = iVar10 + 0x10;

            // "EXIT"
            DecalFont_DrawLine(sdata->lngStrings[uVar6], 0x100, iVar7, 1, 0xffff8000);

            iVar11 = iVar11 + 1;
        } while (iVar11 < sVar12);
    }

    // if scroll bar is not on bottom
    if ((int)*(short *)0x800b5664 + (int)sVar12 < (int)sVar9)
    {
        AH_HintMenu_FiveArrows((iVar10 + 0x40), 0x800);
    }
    box.x = -0xe;
    box.w = 0x21c;
    box.y = (mb->rowSelected - *(short *)0x800b5664) * 0x10 + 0x4f;
    box.h = 0x11;

    CTR_Box_DrawClearBox(&box, &sdata->menuRowHighlight_Normal, 1,
                         gGT->backBuffer->otMem.startPlusFour,

                         // pointer to PrimMem struct
                         &gGT->backBuffer->primMem);

    box.y = 0x3c;
    box.h = 2;
    box.x = -0x14;
    box.w = 0x228;

    MENUBOX_DrawOuterRect_Edge(&box, &sdata->battleSetup_Color_UI_1, 0x20, gGT->backBuffer->otMem.startPlusFour);
    box.y = 0x28;
    box.h = (short)iVar10 + 0x2b;
    box.x = -0x14;
    box.w = 0x228;

    MENUBOX_DrawInnerRect(&box, 4, gGT->backBuffer->otMem.startPlusFour);

    if (
        (bVar3) ||

        // If you dont press Start, Square, or Triangle
        ((sdata->buttonTapPerPlayer[0] & 0x41020) != 0))
    {
        // clear gamepad input (for menus)
        MENUBOX_ClearInput();

        // set desired MenuBox to pause MenuBox
        sdata->ptrDesiredMenuBox = MainFreeze_GetMenuBox();
    }
    return;
}
