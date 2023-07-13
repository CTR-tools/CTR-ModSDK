#include <common.h>

void CS_Garage_MenuBoxFuncPtr(void)
{
    char bVar1;
    short sVar3;
    short sVar4;
    int iVar5;
    short *puVar6;
    int iVar7;
    u_int *puVar8;
    u_int uVar9;
    short *psVar10;
    u_int *puVar11;
    int iVar12;
    u_int *puVar13;
    int iVar14;
    int iVar15;
    int iVar16;
    int iVar17;
    undefined **ppuVar18;
    int uVar19;
    u_short *puVar20;
    u_short uVar21;
    u_int uVar22;
    short local_70;
    short local_6e;
    short local_6c;
    short local_6a;
    u_int local_68;
    int local_64;
    u_int local_60;
    int local_5c;
    short local_58;
    short local_56;
    short local_54;
    short local_50;
    short local_4e;
    short local_4c;
    undefined auStack72[8];
    u_short local_40;
    u_int *local_38;
    int local_30;
    int local_2c;

    struct GameTracker *gGT = sdata->gGT;

    // CameraDC, freecam mode
    gGT->cameraDC[0].cameraMode = 3;

    // subtract transition timer by one frame
    sVar4 = *(short*)0x800b8638--;

    // if mid-transition, skip some code
    if (*(short*)0x800b8638 != 0)
        goto LAB_800b821c;

    // At this point, there must not be a transition
    // between drivers, so start drawing the UI

    // bar length (animated) in adv character selection
    psVar10 = &DAT_800b85e8;

    iVar7 = (int)(short)sdata->advCharSelectIndex_curr;
    *(short*)0x800b85ee = *(short*)0x800b85ee + 1;

    // animate growth of all three stat bars
    for (iVar7 = 0; iVar7 < 3; iVar7++)
    {

        // if bar length is less than character stat
        if (*psVar10 <

            // array of engine-specific stats
            *(short *)(&DAT_800b85f8 +
                       iVar17 * 2 +

                       // engineID from MetaDataCharacters
                       *(int *)(&DAT_80086d90 + (int)*(short *)(&DAT_800b85d8 + iVar7 * 2) * 0x10) * 6))
        {
            // make bar grow
            *psVar10 = *psVar10 + 3;
        }

        // if bar length is more than character stat
        if (

            // array of engine-specific stats
            *(short *)(&DAT_800b85f8 +
                       iVar17 * 2 +

                       // engineID from MetaDataCharacters
                       *(int *)(&DAT_80086d90 + (int)*(short *)(&DAT_800b85d8 + iVar7 * 2) * 0x10) * 6) < *psVar10)
        {
            // set bar length to character stat
            *psVar10 =

                // array of engine-specific stats
                *(short *)(&DAT_800b85f8 +
                           iVar17 * 2 +

                           // engineID from MetaDataCharacters
                           *(int *)(&DAT_80086d90 +
                                    (int)*(short *)(&DAT_800b85d8 + iVar7 * 2) * 0x10) *
                               6);
        }

        // loop to next bar

        psVar10 = psVar10 + 1;
    }

    if ((*(short *)(&DAT_80086d88 +
                    (int)*(short *)(&DAT_800b85d8 + (int)(short)sdata->advCharSelectIndex_curr * 2) * 0x10) ==
         0x2e) ||
        (uVar19 = 0x17f,
         *(short *)(&DAT_80086d88 +
                    (int)*(short *)(&DAT_800b85d8 + (int)(short)sdata->advCharSelectIndex_curr * 2) * 0x10) == 0x33))
    {
        uVar19 = 0x81;
        local_40 = 0x80;
        uVar22 = 0x8b;
    }
    else
    {
        local_40 = 0x180;
        uVar22 = 0x189;
    }

    // "Speed"
    DecalFont_DrawLine(sdata->lngStrings[0x245], uVar19, 0x1e, 1, 0x4022);

    // "Accel"
    DecalFont_DrawLine(sdata->lngStrings[0x246], uVar19, 0x2d, 1, 0x4021);

    // "Turn"
    DecalFont_DrawLine(sdata->lngStrings[0x247], uVar19, 0x3c, 1, 0x4020);

    iVar7 = 0;
    if ((*(u_int *)(&DAT_80086d90 + (int)*(short *)(&DAT_800b85d8 + (int)(short)sdata->advCharSelectIndex_curr * 2) * 0x10) != 3) &&
        (iVar7 = 2,
         *(u_int *)(&DAT_80086d90 +
                   (int)*(short *)(&DAT_800b85d8 + (int)(short)sdata->advCharSelectIndex_curr * 2) * 0x10) < 2))
    {
        iVar7 = 1;
    }
    iVar17 = 0;
    local_38 = &local_68;
    uVar21 = 0x21;
    local_2c = 0x28;
    local_30 = 0x22;

    // Draw a string
    DecalFont_DrawLine(*(int *)((int)(short)(&DAT_800b85f0)[iVar7] * 4 + sdata->lngStrings), (u_int)local_40, 0xf, 1, 0xffff8000);

    // bar length (animated)
    puVar20 = &DAT_800b85e8;

    do
    {
        local_60 = uVar22 | (u_int)uVar21 << 0x10;
        local_5c = CONCAT22(7, *puVar20);
        local_68 = local_60;
        local_64 = local_5c;
        local_60 = *(int*)0x800b7780;

        CTR_Box_DrawWireBox(local_38, &local_60,

                            // pointer to OT memory
                            gGT->tileView_UI.ptrOT,

                            // pointer to PrimMem struct
                            &gGT->backBuffer->primMem);

        local_68 = CONCAT22((short)local_30, (short)uVar22 + 1);
        local_60 = local_60 & 0xff000000;
        local_64 = CONCAT22(5, *puVar20 - 2);

        //
        CTR_Box_DrawWireBox(local_38, &local_60,

                            // pointer to OT memory
                            gGT->tileView_UI.ptrOT,

                            // pointer to PrimMem struct
                            &gGT->backBuffer->primMem);
        iVar16 = 0;

        // color data of bars (blue green yellow red)
        puVar13 = (int*)0x800b861c;

        iVar15 = 4;
        iVar7 = 0;
        iVar14 = 0xd;
        do
        {
            iVar12 = 0xd;
            if ((short)*puVar20 <= iVar14)
            {
                iVar12 = (u_int)*puVar20 - iVar7;
            }
            sVar4 = (short)iVar12;
            iVar5 = (iVar12 << 0x10) >> 0x10;
            if (iVar12 << 0x10 < 0)
            {
                sVar4 = 0;
                iVar5 = 0;
            }
            if (iVar7 + iVar5 <= (int)(short)*puVar20)
            {
                // backbuffer
                iVar12 = gGT->backBuffer;

                // primMem curr
                puVar8 = *(u_int **)(iVar12 + 0x80);

                puVar11 = (u_int *)0x0;

                // near end of Prim mem
                if (puVar8 <= *(u_int **)(iVar12 + 0x84))
                {
                    *(u_int **)(iVar12 + 0x80) = puVar8 + 9;
                    puVar11 = puVar8;
                }

                // quit if prim mem runs out
                if (puVar11 == (u_int *)0x0)
                {
                    return;
                }

                // color data
                puVar11[1] = *puVar13 | 0x38000000;
                puVar11[3] = *(u_int *)((int)&DAT_800b861c + iVar15) | 0x38000000;
                puVar11[5] = *puVar13 | 0x38000000;
                uVar9 = *(u_int *)((int)&DAT_800b861c + iVar15);

                sVar3 = (short)uVar22 + (short)iVar7;
                *(short *)(puVar11 + 2) = sVar3;
                *(short *)(puVar11 + 6) = sVar3;
                *(short *)(puVar11 + 4) = sVar3 + sVar4;
                *(u_short *)((int)puVar11 + 10) = uVar21;
                *(u_short *)((int)puVar11 + 0x12) = uVar21;
                *(short *)((int)puVar11 + 0x1a) = (short)local_2c;
                *(short *)((int)puVar11 + 0x22) = (short)local_2c;
                puVar11[7] = uVar9 | 0x38000000;


                *(short *)(puVar11 + 8) = *(short *)(puVar11 + 6) + sVar4;

                // pointer to OT memory
                puVar8 = *(u_int **)(gGT + 0x147c);

                *puVar11 = *puVar8 | 0x8000000;
                *puVar8 = (u_int)puVar11 & 0xffffff;
            }
            puVar13 = puVar13 + 1;
            iVar15 = iVar15 + 4;
            iVar7 = iVar7 + 0xd;
            iVar16 = iVar16 + 1;
            iVar14 = iVar14 + 0xd;
        } while (iVar16 < 6);
        uVar21 = uVar21 + 0xf;
        puVar20 = puVar20 + 1;
        iVar17 = iVar17 + 1;
        local_2c = local_2c + 0xf;
        local_30 = local_30 + 0xf;
    } while (iVar17 < 3);

    // "Intermediate"

    sVar4 = DecalFont_GetLineWidth(sdata->lngStrings[0x249], 1);

    local_70 = (local_40 - (sVar4 >> 1)) + -6;
    local_6e = 0xb;

    // "Intermediate"

    local_6c = DecalFont_GetLineWidth(sdata->lngStrings[0x249], 1);

    local_6c = local_6c + 0xc;
    local_6a = 0x44;

    // Draw 2D Menu rectangle background
    MENUBOX_DrawInnerRect(&local_70, 4, gGT->backBuffer->otMem.startPlusFour);

    // Draw a string
    DecalFont_DrawLine(*(int *)((int)*(short *)(&DAT_80086d88 +
                                                       (int)*(short *)(&DAT_800b85d8 + (int)(short)sdata->advCharSelectIndex_curr * 2) * 0x10) *
                                           4 +
                                       sdata->lngStrings),
                       0x100, 0xb4, 1, 0xffff8000);
    iVar7 = 0;
    if ((sdata->frameCounter & 4) == 0)
    {
        iVar7 = 3;
    }
    iVar17 = DecalFont_GetLineWidth(*(int *)((int)*(short *)(&DAT_80086d88 +
                                                                    (int)*(short *)(&DAT_800b85d8 +
                                                                                    (int)(short)sdata->advCharSelectIndex_curr * 2) *
                                                                        0x10) *
                                                        4 +
                                                    sdata->lngStrings),
                                    1);

    iVar17 = ((iVar17 << 0x10) >> 0x10) - ((iVar17 << 0x10) >> 0x1f) >> 1;

    // Color data
    ppuVar18 = &data.ptrColor[iVar7];

    // Draw arrow pointing Left
    DecalHUD_Arrow2D(
        sdata->gGT->iconGroup[4]->icons[0x38],
        0xec - iVar17,
        0xbb,

        // pointer to PrimMem struct
        gGT->backBuffer->primMem,

        // pointer to OT memory
        gGT->tileView_UI.ptrOT,

        *(int *)*ppuVar18, *(int *)(*ppuVar18 + 4),
        *(int *)(*ppuVar18 + 8), *(int *)(*ppuVar18 + 0xc), 0, 0x1000, 0x800);

    // Draw arrow pointing Right
    DecalHUD_Arrow2D(
        sdata->gGT->iconGroup[4]->icons[0x38],
        iVar17 + 0x112,
        0xbb,

        // pointer to PrimMem struct
        gGT->backBuffer->primMem,

        // pointer to OT mem
        gGT->tileView_UI.ptrOT,

        *(int *)*ppuVar18, *(int *)(*ppuVar18 + 4),
        *(int *)(*ppuVar18 + 8), *(int *)(*ppuVar18 + 0xc), 0, 0x1000, 0);

    sVar4 = *(short*)0x800b8638;

    if (
        ((gGT->renderFlags & 0x1000) != 0) ||

        (
            // If you dont press Triangle, Cross, Circle, or Square
            ((sdata->AnyPlayerTap & 0x40070) == 0 &&

             // If you dont press D-pad
             ((sdata->AnyPlayerHold & 0xc) == 0))))
        goto LAB_800b821c;

    iVar7 = 2;

    // If you dont press D-pad
    if ((sdata->AnyPlayerHold & 0xc) == 0)
    {
        // If you do not press Cross or Circle
        if ((sdata->AnyPlayerTap & 0x50) == 0)
        {
            // If you press Triangle or Square
            if ((sdata->AnyPlayerTap & 0x40020) != 0)
            {
                // Play Sound
                OtherFX_Play(2, 1);

                sVar4 = *(short*)0x800b863a;
                if (*(int*)0x800b8640 == 1)
                {
                    *(int*)0x800b8640 = 0;
                    bVar1 = *(short*)0x800b863a < *(short*)0x800b85cc;
                    gGT->gameMode2 &= 0xfffdffff;
                    if (bVar1)
                    {
                        *(short*)0x800b863c = *(short*)0x800b85cc - sVar4;
                    }
                }
                else
                {
                    // return to main menu
                    sdata->mainMenuState = 0;

                    Garage_Leave();

                    // load main menu LEV
                    MainRaceTrack_RequestLoad(0x27);
                }
            }
        }

        // If you press Cross or Circle
        else
        {
            // 0x800b8640 is the boolean for "Have you selected character?"
            // If true, it will show an animation, and then show the
            // OSK (keyboard) screen. If set to 0 after in that screen,
            // the screen does not disappear

            // if false
            if (*(int*)0x800b8640 == 0)
            {
                // make it true
                *(int*)0x800b8640 = 1;
            }

            // if true
            else
            {
                if (*(int*)0x800b8640 == 1)
                {
                    // set desiredMenuBox to OSK (on-screen keyboard)
                    sdata->ptrDesiredMenuBox = &data.menuBox_OSK;

                    // set Character ID of P1 to the
                    // character you see in the
                    // 3D Character Selection screen

                    // Naughty Dog mistake:
                    // This line still works, but it is redundant,
                    // shouldn't need to pull characterID from array,
                    // should just be 80086e84 = sdata->advCharSelectIndex_curr
                    data.characterIDs[0] = sdata->advCharSelectIndex_curr;

                    // set icon ID to match Character ID
                    sdata->advProgress.characterID = data.characterIDs[0];

                    TitleOSK_RestoreName(0);

                    // Play Sound
                    OtherFX_Play(1, 1);
                }
            }
        }
    }
    else
    {
        puVar6 = (short*)0x800b85ec;
        do
        {
            *puVar6 = 0;
            puVar6 -= 1;
            iVar7--;
        } while (-1 < iVar7);

        // Play Sound
        OtherFX_Play(0, 1);

        // If you dont press Left
        if ((sdata->AnyPlayerHold & 4) == 0)
        {
            // If you dont press Right
            if ((sdata->AnyPlayerHold & 8) != 0)
            {
                uVar21 = sdata->advCharSelectIndex_curr + 1;
                goto LAB_800b8084;
            }
        }

        // If you press Left
        else
        {
            uVar21 = sdata->advCharSelectIndex_curr - 1;
        LAB_800b8084:

            // previous equals current
            sdata->advCharSelectIndex_prev = sdata->advCharSelectIndex_curr;

            // add one, then chop of all "bits" that come after 7,
            // that way, the number 8 turns into 0, so you stay in bounds
            sdata->advCharSelectIndex_curr = uVar21 & 7;

            Garage_MoveLR();
        }
        *(short*)0x800b8638 =  *(short*)0x800b85c4;
        if (*(short*)0x800b863a < *(short*)0x800b85cc)
        {
            *(short*)0x800b863c = *(short*)0x800b85cc - *(short*)0x800b863a;
        }
        *(int*)0x800b8640 = 0;
        gGT->gameMode2 &= ~GARAGE_OSK;
    }

    // clear gamepad input (for menus)
    MENUBOX_ClearInput();

    sVar4 = *(short*)0x800b8638;
LAB_800b821c:
    *(short*)0x800b8638 = sVar4;

    // if frames remain
    if (0 < *(short*)0x800b863a)
    {
        // decrease zoom frame timer
        *(short*)0x800b863a --;
    }

    sVar4 = *(int*)0x800b863e;
    if (
        ((*(int*)0x800b8640 == 1) && (*(short*)0x800b863a == 0)) &&

        ((
            0x3b < *(int*)0x800b863e ||
            (sVar4 = *(int*)0x800b863e + 1,

             (gGT->gameMode2 & 0x20000) != 0))))
    {
        // set desiredMenuBox to OSK (on-screen keyboard)
        sdata->ptrDesiredMenuBox = &data.menuBox_OSK;

        // set Character ID of P1 to the
        // character you see in the
        // 3D Character Selection screen

        // Naughty Dog mistake:
        // This line still works, but it is redundant,
        // shouldn't need to pull characterID from array,
        // should just be 80086e84 = sdata->advCharSelectIndex_curr
        data.characterIDs[0] = sdata->advCharSelectIndex_curr;

        // set Icon ID to match Character ID
        sdata->advProgress.characterID = data.characterIDs[0];

        TitleOSK_RestoreName(0);

        // Play Sound
        OtherFX_Play(1, 1);

        sVar4 = *(int*)0x800b863e;
    }
    *(int*)0x800b863e = sVar4;

    if (*(int*)0x800b8640 == 0)
    {
        *(short*)0x800b863a = (short)DAT_800b85cc;
    }
    if (DAT_800b863c != 0)
    {
        DAT_800b863c --;
    }
    puVar6 = gGT->tileView[0];

    // if current is zero, and previous is 7
    if ((sdata->advCharSelectIndex_curr == 0) && (sdata->advCharSelectIndex_prev == 7))
    {
        sVar4 = 0xf0 - *(short*)0x800b8638;
    }

    // if current is not zero, or if previous is not 7
    else
    {
        // if current is 7, and previous is 0
        if ((sdata->advCharSelectIndex_curr == 7) && (sdata->advCharSelectIndex_prev == 0))
        {
            sVar4 = *(short*)0x800b8638 + 0xd2;
        }

        // if current is not 7, or if previous is not zero
        else
        {
            // if current is less more previous (you move right)
            if (sdata->advCharSelectIndex_prev < sdata->advCharSelectIndex_curr)
            {
                sVar4 = sdata->advCharSelectIndex_curr * 0x1e - *(short*)0x800b8638;
            }

            // if current is less than previous (you move left)
            else
            {
                sVar4 = sdata->advCharSelectIndex_curr * 0x1e + *(short*)0x800b8638;
            }
        }
    }

    // animation frame index,
    // pointer to position,
    // pointer to rotation

    CAM_Path_Move((int)sVar4, &local_58, &local_50, auStack72);

    // set position and rotation to tileView
    *puVar6 = local_58;
    gGT->tileView[0].pos[1] = local_56;
    gGT->tileView[0].pos[2] = local_54;
    gGT->tileView[0].rot[0] = local_50;
    gGT->tileView[0].rot[1] = local_4e;
    iVar7 = DAT_800b863c;
    gGT->tileView[0].rot[2] = local_4c;

    if (iVar7 == 0)
    {
        iVar7 = (DAT_800b85cc - *(short*)0x800b863a) *
                (DAT_800b85d4 - DAT_800b85d0);
        if (DAT_800b85cc == 0)
        {
            trap(0x1c00);
        }
        if ((DAT_800b85cc == -1) && (iVar7 == -0x80000000))
        {
            trap(0x1800);
        }
    }
    else
    {
        iVar7 = iVar7 * (DAT_800b85d4 - DAT_800b85d0);
        if (DAT_800b85cc == 0)
        {
            trap(0x1c00);
        }
        if ((DAT_800b85cc == -1) && (iVar7 == -0x80000000))
        {
            trap(0x1800);
        }
    }
    iVar7 = DAT_800b85d0 + iVar7 / DAT_800b85cc;
    gGT->tileView[1].distanceToScreen_CURR = iVar7;
    gGT->tileView[0].distanceToScreen_PREV = iVar7;
}

struct MenuBox *CS_Garage_GetMenuBox(void)
{
    // this "MenuBox" is what displays the driver stats,
    // driver name, and arrows, before selecting the driver
    return 0x800b8598;
}