#include <common.h>

void DECOMP_CS_Garage_MenuBoxFuncPtr(void)
{
    char bVar1;
    short sVar3;
    short sVar4;
    int iVar5;
    short *puVar6;
    int iVar7;
    u_int uVar9;
    u_int *puVar11;
    int iVar12;
    u_int *puVar13;
    int iVar14;
    int iVar15;
    int iVar16;
    int iVar17;
    int* ptrColor;
    int uVar19;
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
    u_short local_40;
    int local_30;
    int local_2c;

    struct GameTracker *gGT = sdata->gGT;
	struct PrimMem* primMem = &gGT->backBuffer->primMem;
	struct MetaDataCHAR* MDC = &data.MetaDataCharacters[sdata->advCharSelectIndex_curr];
	int nameIndex = MDC->name_LNG_long;
	RECT r;

    // CameraDC, freecam mode
    gGT->cameraDC[0].cameraMode = 3;

    // subtract transition timer by one frame
    sVar4 = *(short*)0x800b8638 - 1;

    // if mid-transition, skip some code
    if (*(short*)0x800b8638 != 0)
        goto LAB_800b821c;

    // At this point, there must not be a transition
    // between drivers, so start drawing the UI

    iVar7 = (int)(short)sdata->advCharSelectIndex_curr;
	
	#if 0
	// count frames in garage?
    *(short*)0x800b85ee = *(short*)0x800b85ee + 1;
	#endif

    // animate growth of all three stat bars
    for (iVar7 = 0; iVar7 < 3; iVar7++)
    {
		short* bar = (unsigned int)0x800b85e8 + 2 * iVar7;
		short stat = *(short *)((unsigned int)0x800b85f8 + MDC->engineID*6 + iVar7*2);
		
        if (*bar < stat)	*bar = *bar + 3;
        if (stat < *bar)	*bar = stat;
    }

    if (
			// Tiny Tiger
			(nameIndex == 0x2e) ||
        
			(
				uVar19 = 0x17f,
				
				// Pura
				nameIndex == 0x33
			)
		)
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

	int engineID = MDC->engineID;

    // 0x248 - Beginner
	// EngineID == 3
	iVar7 = 0;
	
	// 0x24A - Advanced
	if (engineID == 2) iVar7 = 2;
	
	// 0x249 - Intermediate
    if (engineID < 2) iVar7 = 1;

    iVar17 = 0;
    uVar21 = 0x21;
    local_2c = 0x28;
    local_30 = 0x22;

	#if 0
	// remove array at 800b85f0,
	// it's 0x248, 0x249, 0x24A,
	// instead just do 0x248 + iVar1
	#endif

    // Draw a string
    DecalFont_DrawLine(sdata->lngStrings[0x248+iVar7], (u_int)local_40, 0xf, 1, 0xffff8000);

    // bar length (animated)
    short* puVar20 = 0x800b85e8;

    do
    {		
		r.x = uVar22;
		r.y = uVar21;
		r.w = *puVar20;
		r.h = 7;
		
		// outline color white
        local_60 = *(int*)0x800b7780;

        CTR_Box_DrawWireBox(&r, &local_60,

                            // pointer to OT memory
                            gGT->tileView_UI.ptrOT,

                            // pointer to PrimMem struct
                            &gGT->backBuffer->primMem);

		r.x = uVar22 + 1;
		r.y = local_30;
        r.w = *puVar20 - 2;
		r.h = 5;

		// outline color black
		local_60 = local_60 & 0xff000000;

        CTR_Box_DrawWireBox(&r, &local_60,

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
                POLY_G4* p = primMem->curr;

                // quit if prim mem runs out
                if (p+2 >= primMem->end)
					return;
				
				primMem->curr = p + 1;

                // color data
                *(int*)&p->r0 = puVar13[0] | 0x38000000;
                *(int*)&p->r1 = puVar13[1] | 0x38000000;
                *(int*)&p->r2 = puVar13[0] | 0x38000000;
				*(int*)&p->r3 = puVar13[1] | 0x38000000;

                sVar3 = (short)uVar22 + (short)iVar7;
                p->x0 = sVar3;
                p->y0 = uVar21;
                p->x1 = sVar3 + sVar4;
                p->y1 = uVar21;
                p->x2 = sVar3;
                p->y2 = (short)local_2c;
                p->x3 = sVar3 + sVar4;
                p->y3 = (short)local_2c;

                // pointer to OT memory
                void* ot = gGT->tileView_UI.ptrOT;

				*(int*)p = (*(int*)ot & 0xffffff) | 0x8000000;
				*(int*)ot = (int)p & 0xffffff;
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

    r.x = (local_40 - (sVar4 >> 1)) + -6;
    r.y = 0xb;
    r.w = sVar4 + 0xc;
    r.h = 0x44;

    // Draw 2D Menu rectangle background
    MENUBOX_DrawInnerRect(&r, 4, gGT->backBuffer->otMem.startPlusFour);

	#if 0
	// Original game uses array at 800b85d8,
	// we remove the usage cause it's just 0,1,2,3,4,5,6,7,
	// this array is used in Oxide Fix (Garage_Init+0x80),
	// so we can adjust the mod to fit the new code
	
	// otherwise would be
	// lngStrings[metadata[800b85d8[charSelectIndex]].nameLNG]
	#endif

	char* name = sdata->lngStrings[nameIndex];

    DecalFont_DrawLine(name, 0x100, 0xb4, 1, 0xffff8000);
    
	iVar7 = 0;
    if ((sdata->frameCounter & 4) == 0)
    {
        iVar7 = 3;
    }
	
    iVar17 = DecalFont_GetLineWidth(name, 1) >> 1;

    // Color data
    ptrColor = data.ptrColor[iVar7];

	struct Icon** iconPtrArray =
		ICONGROUP_GETICONS(gGT->iconGroup[4]);

    // Draw arrow pointing Left
    DecalHUD_Arrow2D(
        iconPtrArray[0x38],
        0xec - iVar17,
        0xbb,

        primMem,
        gGT->tileView_UI.ptrOT,

        ptrColor[0], ptrColor[1], 
		ptrColor[2], ptrColor[3],
		
		0, 0x1000, 0x800);

    // Draw arrow pointing Right
    DecalHUD_Arrow2D(
        iconPtrArray[0x38],
        iVar17 + 0x112,
        0xbb,

        primMem,
		gGT->tileView_UI.ptrOT,

        ptrColor[0], ptrColor[1], 
		ptrColor[2], ptrColor[3],
		
		0, 0x1000, 0);

    sVar4 = *(short*)0x800b8638;

    if (
        ((gGT->renderFlags & 0x1000) != 0) ||

        (
            // If you dont press Triangle, Cross, Circle, or Square
            ((sdata->AnyPlayerTap & 0x40070) == 0) &&

             // If you dont press D-pad
             ((sdata->AnyPlayerHold & 0xc) == 0)
		)
	   )
        goto LAB_800b821c;

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
                    bVar1 = *(short*)0x800b863a < *(int*)0x800b85cc;
                    gGT->gameMode2 &= ~GARAGE_OSK;
                    if (bVar1)
                    {
                        *(short*)0x800b863c = *(int*)0x800b85cc - sVar4;
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
				// if pressed X twice quickly
                if (*(int*)0x800b8640 == 1)
                {
                    // set desiredMenuBox to OSK (on-screen keyboard)
                    sdata->ptrDesiredMenuBox = &data.menuBox_OSK;

                    data.characterIDs[0] = sdata->advCharSelectIndex_curr;
                    sdata->advProgress.characterID = data.characterIDs[0];

                    TitleOSK_RestoreName(0);

                    // Play Sound
                    OtherFX_Play(1, 1);
                }
            }
        }
    }
	
	// if using D-pad
    else
    {
		// erase animated bars
		iVar7 = 2;
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

			// clamp 0-7
			uVar21 = uVar21 & 7;

            sdata->advCharSelectIndex_curr = uVar21;

            Garage_MoveLR(uVar21);
        }
		
        *(short*)0x800b8638 =  *(short*)0x800b85c4;
        if (*(short*)0x800b863a < *(int*)0x800b85cc)
        {
            *(short*)0x800b863c = *(int*)0x800b85cc - *(short*)0x800b863a;
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
        *(short*)0x800b863a = *(short*)0x800b863a - 1;
    }

	// if pressed X once, and waited for countdown clock
    sVar4 = *(short*)0x800b863e;
    if (
        ((*(int*)0x800b8640 == 1) && (*(short*)0x800b863a == 0)) &&

        ((
            (0x3b < *(short*)0x800b863e) ||
            (
				sVar4 = *(short*)0x800b863e + 1,

				(gGT->gameMode2 & GARAGE_OSK) != 0
			)
		))
	   )
    {
        // set desiredMenuBox to OSK (on-screen keyboard)
        sdata->ptrDesiredMenuBox = &data.menuBox_OSK;

        data.characterIDs[0] = sdata->advCharSelectIndex_curr;
        sdata->advProgress.characterID = data.characterIDs[0];

        TitleOSK_RestoreName(0);

        // Play Sound
        OtherFX_Play(1, 1);

        sVar4 = *(short*)0x800b863e;
    }
	
    *(short*)0x800b863e = sVar4;

    if (*(int*)0x800b8640 == 0)
    {
        *(short*)0x800b863a = *(int*)0x800b85cc;
    }
	
    if (*(short*)0x800b863c != 0)
    {
        *(short*)0x800b863c = *(short*)0x800b863c - 1;
    }
    
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

    int getPath;
	short pos[3];
	short rot[3];
    CAM_Path_Move((int)sVar4, &pos[0], &rot[0], &getPath);

    // set position and rotation to tileView
    gGT->tileView[0].pos[0] = pos[0];
    gGT->tileView[0].pos[1] = pos[1];
    gGT->tileView[0].pos[2] = pos[2];
	
    gGT->tileView[0].rot[0] = rot[0];
    gGT->tileView[0].rot[1] = rot[1];
    gGT->tileView[0].rot[2] = rot[2];

	iVar7 = *(short*)0x800b863c;
    if (iVar7 == 0)
    {
        iVar7 = (*(int*)0x800b85cc - *(short*)0x800b863a) *
                (*(int*)0x800b85d4 - *(int*)0x800b85d0);
		
		#if 0
        if (DAT_800b85cc == 0) trap(0x1c00);
        if ((DAT_800b85cc == -1) && (iVar7 == -0x80000000)) trap(0x1800);
		#endif
	}
    else
    {
        iVar7 = iVar7 * (*(int*)0x800b85d4 - *(int*)0x800b85d0);
		
		#if 0
        if (DAT_800b85cc == 0) trap(0x1c00);
        if ((DAT_800b85cc == -1) && (iVar7 == -0x80000000)) trap(0x1800);
		#endif
    }
	
    iVar7 = *(int*)0x800b85d0 + iVar7 / *(int*)0x800b85cc;
    
	gGT->tileView[1].distanceToScreen_CURR = iVar7;
    gGT->tileView[0].distanceToScreen_PREV = iVar7;
}