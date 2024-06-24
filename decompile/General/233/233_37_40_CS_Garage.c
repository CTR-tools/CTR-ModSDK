#include <common.h>

extern struct OVR233_Garage gGarage;

void DECOMP_CS_Garage_ZoomOut(char zoomState)
{
    // if just entered garage
    if (zoomState == 0)
    {
        gGarage.numFramesCurr_ZoomOut = 0;

#ifndef REBUILD_PS1
		// both howl
        Garage_Init();
        Garage_Enter(sdata->advCharSelectIndex_curr);
#endif

        DECOMP_Audio_SetState_Safe(8);
    }
    else
    {
        // number of frames to zoom in, or out,
        // when selecting or cancelling OSK
        gGarage.numFramesCurr_ZoomOut = gGarage.numFramesMax_Zoom;
    }

    gGarage.numFramesCurr_GarageMove = 0;
    gGarage.delayOneSecond = 0;
    gGarage.boolSelected = 0;

    gGarage.numFramesCurr_ZoomIn = gGarage.numFramesCurr_ZoomOut;

    sdata->gGT->gameMode2 &= ~(GARAGE_OSK);
}

#ifdef USE_OXIDE
char OXIDE_GarageUnlockFlags[] =
{
	// [x] = y
	// [characterID-8] = unlockFlag (unlocks[0] & 1<<self)

	0x0A,
	0x08,
	0x07,
	0x09,
	0x05,
	0x06,
	0x0B,
	0x0C,

};

int OXIDE_GarageGetNext(int curr, int dir)
{
	do
	{
		// go to next
		curr += dir;
		curr &= 0xf;

	// repeat search if new character is locked
	} while(
			// character has unlock condition
			(curr >= 8) &&

			(
				// locked
				(
					sdata->gameProgress.unlocks[0] &
					(1 << OXIDE_GarageUnlockFlags[curr-8])
				) == 0
			)
		   );

	return curr;
}
#endif

void DECOMP_CS_Garage_MenuProc(void)
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

	#ifdef USE_OXIDE
	if(
		// if Crash selected
		(sdata->advCharSelectIndex_curr == 0) &&
		(gGarage.numFramesCurr_GarageMove == 0) &&

		// if at least one character unlocked
		((sdata->gameProgress.unlocks[0] & 0x1FE0) != 0)
	  )
	{
		// button
		int buttonTap = sdata->AnyPlayerTap;

		// left
		if((buttonTap & BTN_L1) == BTN_L1)
			gGarage.unusedFrameCount =
				OXIDE_GarageGetNext(
					gGarage.unusedFrameCount, -1);

		// right
		else if((buttonTap & BTN_R1) == BTN_R1)
			gGarage.unusedFrameCount =
				OXIDE_GarageGetNext(
					gGarage.unusedFrameCount, 1);

		MDC = &data.MetaDataCharacters[gGarage.unusedFrameCount];
		nameIndex = MDC->name_LNG_long;

		DECOMP_DecalFont_DrawLine
		(
			"PRESS L1 OR R1 TO SWAP",
			0x100,					// midpoint
			0xc8,					// near bottom
			FONT_SMALL,				// small text
			(JUSTIFY_CENTER | ORANGE)	// center
		);
	}
	#endif

    // CameraDC, freecam mode
    gGT->cameraDC[0].cameraMode = 3;

	#ifdef USE_60FPS
	if( (gGT->timer & 1) == 0)
		sVar4 = gGarage.numFramesCurr_GarageMove;
	else
	#endif

		// subtract transition timer by one frame
		sVar4 = gGarage.numFramesCurr_GarageMove - 1;

    // if mid-transition, skip some code
    if (gGarage.numFramesCurr_GarageMove != 0)
        goto LAB_800b821c;

    // At this point, there must not be a transition
    // between drivers, so start drawing the UI

	#if 0
	// count frames in garage?
    gGarage.unusedFrameCount++;
	#endif

    // animate growth of all three stat bars
    for (iVar7 = 0; iVar7 < 3; iVar7++)
    {
		short* bar = &gGarage.barLen[iVar7];
		short stat = gGarage.barStat[MDC->engineID*3 + iVar7];

		#ifdef USE_16BY9
		stat = WIDE_34(stat);
		#endif

		// half bar length, half speed per frame, just add 1
		#if (defined(USE_60FPS) && defined(USE_16BY9))
			#define BAR_RATE 1
		#else
			#define BAR_RATE 3
		#endif

        if (*bar < stat)	*bar = *bar + BAR_RATE;
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
    DECOMP_DecalFont_DrawLine(sdata->lngStrings[0x245], uVar19, 0x1e, 1, 0x4022);

    // "Accel"
    DECOMP_DecalFont_DrawLine(sdata->lngStrings[0x246], uVar19, 0x2d, 1, 0x4021);

    // "Turn"
    DECOMP_DecalFont_DrawLine(sdata->lngStrings[0x247], uVar19, 0x3c, 1, 0x4020);

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
    DECOMP_DecalFont_DrawLine(sdata->lngStrings[0x248+iVar7], (u_int)local_40, 0xf, 1, 0xffff8000);

    // bar length (animated)
    short* puVar20 = &gGarage.barLen[0];

    do
    {
		r.x = uVar22;
		r.y = uVar21;
		r.w = *puVar20;
		r.h = 7;

		// outline color white
        //local_60 = *(int*)0x800b7780;
		local_60 = 0xFFFFFF;

        DECOMP_CTR_Box_DrawWireBox(
			&r, MakeColor(255, 255, 255),
			gGT->pushBuffer_UI.ptrOT);

		r.x = uVar22 + 1;
		r.y = local_30;
        r.w = *puVar20 - 2;
		r.h = 5;

		// outline color black
		local_60 = local_60 & 0xff000000;

        DECOMP_CTR_Box_DrawWireBox(
			&r, MakeColor(0, 0, 0),
            gGT->pushBuffer_UI.ptrOT);

        iVar16 = 0;

        // color data of bars (blue green yellow red)
        puVar13 = &gGarage.barColors[0];

		int segmentLength = WIDE_PICK(13, 10);

        iVar7 = 0;
        iVar14 = segmentLength;
        do
        {
            iVar12 = segmentLength;
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
                void* ot = gGT->pushBuffer_UI.ptrOT;

				*(int*)p = (*(int*)ot & 0xffffff) | 0x8000000;
				*(int*)ot = (int)p & 0xffffff;
            }

			// color index
            puVar13 = puVar13 + 1;

			// segment index
            iVar16 = iVar16 + 1;

            iVar7 = iVar7 + segmentLength;
            iVar14 = iVar14 + segmentLength;

		} while (iVar16 < 6);

		// 15 pixels lower Y axis
        uVar21 = uVar21 + 0xf;
        local_2c = local_2c + 0xf;
        local_30 = local_30 + 0xf;

        puVar20 = puVar20 + 1;
        iVar17 = iVar17 + 1;

    } while (iVar17 < 3);

    // "Intermediate"
    sVar4 = DECOMP_DecalFont_GetLineWidth(sdata->lngStrings[0x249], 1);

    r.x = (local_40 - (sVar4 >> 1)) + -6;
    r.y = 0xb;
    r.w = sVar4 + 0xc;
    r.h = 0x44;

    // Draw 2D Menu rectangle background
    DECOMP_RECTMENU_DrawInnerRect(&r, 4, gGT->backBuffer->otMem.startPlusFour);

	#if 0
	// Original game uses array at 800b85d8,
	// we remove the usage cause it's just 0,1,2,3,4,5,6,7,
	// this array is used in Oxide Fix (Garage_Init+0x80),
	// so we can adjust the mod to fit the new code

	// otherwise would be
	// lngStrings[metadata[800b85d8[charSelectIndex]].nameLNG]
	#endif

	char* name = sdata->lngStrings[nameIndex];

    DECOMP_DecalFont_DrawLine(name, 0x100, 0xb4, 1, 0xffff8000);

	iVar7 = 0;
    if ((sdata->frameCounter & FPS_DOUBLE(4)) == 0)
    {
        iVar7 = 3;
    }

    iVar17 = DECOMP_DecalFont_GetLineWidth(name, 1) >> 1;

    // Color data
    ptrColor = data.ptrColor[iVar7];

	struct Icon** iconPtrArray =
		ICONGROUP_GETICONS(gGT->iconGroup[4]);

    // Draw arrow pointing Left
    DECOMP_DecalHUD_Arrow2D(
        iconPtrArray[0x38],
        0xec - iVar17,
        0xbb,

        primMem,
        gGT->pushBuffer_UI.ptrOT,

        ptrColor[0], ptrColor[1],
		ptrColor[2], ptrColor[3],

		0, 0x1000, 0x800);

    // Draw arrow pointing Right
    DECOMP_DecalHUD_Arrow2D(
        iconPtrArray[0x38],
        iVar17 + 0x112,
        0xbb,

        primMem,
		gGT->pushBuffer_UI.ptrOT,

        ptrColor[0], ptrColor[1],
		ptrColor[2], ptrColor[3],

		0, 0x1000, 0);

    sVar4 = gGarage.numFramesCurr_GarageMove;

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
                DECOMP_OtherFX_Play(2, 1);

                sVar4 = gGarage.numFramesCurr_ZoomIn;
                if (gGarage.boolSelected == 1)
                {
                    gGarage.boolSelected = 0;
                    bVar1 = gGarage.numFramesCurr_ZoomIn < gGarage.numFramesMax_Zoom;
                    gGT->gameMode2 &= ~GARAGE_OSK;
                    if (bVar1)
                    {
                        gGarage.numFramesCurr_ZoomOut = gGarage.numFramesMax_Zoom - sVar4;
                    }
                }
                else
                {
                    // return to main menu
                    sdata->mainMenuState = 0;

#ifndef REBUILD_PS1
                    Garage_Leave();
#endif

                    // load main menu LEV
                    DECOMP_MainRaceTrack_RequestLoad(0x27);
                }
            }
        }

        // If you press Cross or Circle
        else
        {
            // "Have you selected character?"
            // If true, it will show an animation, and then show the
            // OSK (keyboard) screen. If set to 0 after in that screen,
            // the screen does not disappear

            // if false
            if (gGarage.boolSelected == 0)
            {
                // make it true
                gGarage.boolSelected = 1;
            }

            // if true
            else
            {
				// if pressed X twice quickly
                if (gGarage.boolSelected == 1)
                {
                    // set desiredMenu to OSK (on-screen keyboard)
                    sdata->ptrDesiredMenu = &data.menuSubmitName;

                    data.characterIDs[0] = sdata->advCharSelectIndex_curr;
                    sdata->advProgress.characterID = data.characterIDs[0];

					#ifdef USE_OXIDE
					if (data.characterIDs[0] == 0)
					{
						data.characterIDs[0] = gGarage.unusedFrameCount;
						sdata->advProgress.characterID = data.characterIDs[0];
					}
					#endif

                    DECOMP_SubmitName_RestoreName(0);
                    DECOMP_OtherFX_Play(1, 1);
                }
            }
        }
    }

	// if using D-pad
    else
    {
		// erase animated bars
		iVar7 = 2;
        puVar6 = &gGarage.barLen[2];
        do
        {
            *puVar6 = 0;
            puVar6 -= 1;
            iVar7--;
        } while (-1 < iVar7);

        // Play Sound
        DECOMP_OtherFX_Play(0, 1);

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

#ifndef REBUILD_PS1
            Garage_MoveLR(uVar21);
#endif
        }

		// reset frame counter to max number of frames
        gGarage.numFramesCurr_GarageMove =  gGarage.numFramesMax_GarageMove;

        if (gGarage.numFramesCurr_ZoomIn < gGarage.numFramesMax_Zoom)
        {
            gGarage.numFramesCurr_ZoomOut = gGarage.numFramesMax_Zoom - gGarage.numFramesCurr_ZoomIn;
        }

        gGarage.boolSelected = 0;
        gGT->gameMode2 &= ~GARAGE_OSK;
    }

    // clear gamepad input (for menus)
    DECOMP_RECTMENU_ClearInput();

    sVar4 = gGarage.numFramesCurr_GarageMove;
LAB_800b821c:
    gGarage.numFramesCurr_GarageMove = sVar4;

    // if frames remaing for zoom camera
    if (0 < gGarage.numFramesCurr_ZoomIn)
    {
		#ifdef USE_60FPS
		if(gGT->timer & 1)
		#endif

			// decrease zoom frame timer
			gGarage.numFramesCurr_ZoomIn--;
    }

	// if pressed X once, and waited for countdown clock
    if ((gGarage.boolSelected == 1) && (gGarage.numFramesCurr_ZoomIn == 0))
	{
		if(
				// frames remaining for animation
				(0x3b < gGarage.delayOneSecond) ||
				((gGT->gameMode2 & GARAGE_OSK) != 0)
		  )
		{
			// set desiredMenu to OSK (on-screen keyboard)
			sdata->ptrDesiredMenu = &data.menuSubmitName;

			data.characterIDs[0] = sdata->advCharSelectIndex_curr;
			sdata->advProgress.characterID = data.characterIDs[0];

			#ifdef USE_OXIDE
			if(data.characterIDs[0] == 0)
			{
				data.characterIDs[0] = gGarage.unusedFrameCount;
				sdata->advProgress.characterID = data.characterIDs[0];
			}
			#endif

			DECOMP_SubmitName_RestoreName(0);
			DECOMP_OtherFX_Play(1, 1);
		}

		else
		{
			#ifdef USE_60FPS
			if(gGT->timer & 1)
			#endif
				gGarage.delayOneSecond++;
		}
	}

	#ifdef REBUILD_PC
	if(sdata->ptrDesiredMenu == &data.menuSubmitName)
	{
		// flush async key state buffer, otherwise
		// tapping Enter "before" picking a garage
		// character, then picking character, will
		// immediately warp you to the adv hub, with
		// no time to type the name
		int NikoGetEnterKey();
		NikoGetEnterKey();
	}
	#endif

    if (gGarage.boolSelected == 0)
    {
        gGarage.numFramesCurr_ZoomIn = gGarage.numFramesMax_Zoom;
    }

    if (gGarage.numFramesCurr_ZoomOut != 0)
    {
		#ifdef USE_60FPS
		if(gGT->timer & 1)
		#endif
			gGarage.numFramesCurr_ZoomOut--;
    }

    // Pura->Crash
    if ((sdata->advCharSelectIndex_curr == 0) && (sdata->advCharSelectIndex_prev == 7))
        sVar4 = 0xf0 - gGarage.numFramesCurr_GarageMove;

    // Crash->Pura
    else if ((sdata->advCharSelectIndex_curr == 7) && (sdata->advCharSelectIndex_prev == 0))
		sVar4 = gGarage.numFramesCurr_GarageMove + 0xd2;

    // Move Right
    else if (sdata->advCharSelectIndex_prev < sdata->advCharSelectIndex_curr)
        sVar4 = sdata->advCharSelectIndex_curr * 0x1e - gGarage.numFramesCurr_GarageMove;

    // Move Left
    else
        sVar4 = sdata->advCharSelectIndex_curr * 0x1e + gGarage.numFramesCurr_GarageMove;

    // animation frame index,
    // pointer to position,
    // pointer to rotation

    int getPath;
	short pos[3];
	short rot[3];
    DECOMP_CAM_Path_Move((int)sVar4, &pos[0], &rot[0], &getPath);

	#ifdef USE_60FPS

	// if transitioning
	if(gGarage.numFramesCurr_GarageMove != 0)
	{
		// if counter wasn't moved this frame
		if((gGT->timer & 1) == 0)
		{
			// Pura->Crash
			if ((sdata->advCharSelectIndex_curr == 0) && (sdata->advCharSelectIndex_prev == 7))
				sVar4 = 0xf0 - (gGarage.numFramesCurr_GarageMove-1);

			// Crash->Pura
			else if ((sdata->advCharSelectIndex_curr == 7) && (sdata->advCharSelectIndex_prev == 0))
				sVar4 = (gGarage.numFramesCurr_GarageMove-1) + 0xd2;

			// Move Right
			else if (sdata->advCharSelectIndex_prev < sdata->advCharSelectIndex_curr)
				sVar4 = sdata->advCharSelectIndex_curr * 0x1e - (gGarage.numFramesCurr_GarageMove-1);

			// Move Left
			else
				sVar4 = sdata->advCharSelectIndex_curr * 0x1e + (gGarage.numFramesCurr_GarageMove-1);

			short pos2[3];
			short rot2[3];
			DECOMP_CAM_Path_Move((int)sVar4, &pos2[0], &rot2[0], &getPath);

			pos[0] = (pos[0] + pos2[0]) / 2;
			pos[1] = (pos[1] + pos2[1]) / 2;
			pos[2] = (pos[2] + pos2[2]) / 2;

			int diff = rot[1] - rot2[1];
			if(diff < 0) diff = -diff;

			// on the one frame that jumps from
			// 359 degrees -> 1 degree, just ignore
			// interpolation. Nobody will notice a one-frame
			// gap between Polar and Pura where it reuses the
			// old frame's rotation, with lerp'd position
			if(diff < 0x800)
			{
				rot[0] = (rot[0] + rot2[0]) / 2;
				rot[1] = (rot[1] + rot2[1]) / 2;
				rot[2] = (rot[2] + rot2[2]) / 2;
			}
		}
	}

	#endif

    // set position and rotation to pushBuffer
    gGT->pushBuffer[0].pos[0] = pos[0];
    gGT->pushBuffer[0].pos[1] = pos[1];
    gGT->pushBuffer[0].pos[2] = pos[2];

    gGT->pushBuffer[0].rot[0] = rot[0];
    gGT->pushBuffer[0].rot[1] = rot[1];
    gGT->pushBuffer[0].rot[2] = rot[2];

	iVar7 = gGarage.numFramesCurr_ZoomOut;
    if (iVar7 == 0)
    {
        iVar7 = (gGarage.numFramesMax_Zoom - gGarage.numFramesCurr_ZoomIn) *
                (gGarage.fovMax - gGarage.fovMin);
	}
    else
    {
        iVar7 = iVar7 * (gGarage.fovMax - gGarage.fovMin);
    }

    iVar7 = gGarage.fovMin + iVar7 / gGarage.numFramesMax_Zoom;

	gGT->pushBuffer[0].distanceToScreen_CURR = iVar7;
    gGT->pushBuffer[0].distanceToScreen_PREV = iVar7;
}

struct RectMenu* DECOMP_CS_Garage_GetMenuPtr(void)
{
  return &gGarage.menuGarage;
}

void DECOMP_CS_Garage_Init(void)
{
  // go to 3D character selection
  sdata->ptrActiveMenu = &gGarage.menuGarage;

  gGarage.menuGarage.state &= 0xfffffffb;

  // 0 = just entered garage
  DECOMP_CS_Garage_ZoomOut(0);
}