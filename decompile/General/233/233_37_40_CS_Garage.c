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
    } while (
        // character has unlock condition
        (curr >= 8) &&

        (
            // locked
            (
                sdata->gameProgress.unlocks[0] &
                (1 << OXIDE_GarageUnlockFlags[curr - 8])) == 0));

    return curr;
}
#endif

void DECOMP_CS_Garage_MenuProc(void)
{
    short garageFrames;
    short *barLen;
    u_short classNamePosX;
    int i;
    u_int statNamePosX;
    u_int statBarPosX;
    
    u_int currSelectIndex = sdata->advCharSelectIndex_curr;
    struct GameTracker *gGT = sdata->gGT;
    struct PrimMem *primMem = &gGT->backBuffer->primMem;
    struct MetaDataCHAR *MDC = &data.MetaDataCharacters[currSelectIndex];
    int nameIndex = MDC->name_LNG_long;
    RECT r;

#ifdef USE_OXIDE
    if (
        // if Crash selected
        (charSelectIndex == 0) &&
        (gGarage.numFramesCurr_GarageMove == 0) &&

        // if at least one character unlocked
        ((sdata->gameProgress.unlocks[0] & 0x1FE0) != 0))
    {
        // button
        int buttonTap = sdata->AnyPlayerTap;

        // left
        if ((buttonTap & BTN_L1) == BTN_L1)
            gGarage.unusedFrameCount =
                OXIDE_GarageGetNext(
                    gGarage.unusedFrameCount, -1);

        // right
        else if ((buttonTap & BTN_R1) == BTN_R1)
            gGarage.unusedFrameCount =
                OXIDE_GarageGetNext(
                    gGarage.unusedFrameCount, 1);

        MDC = &data.MetaDataCharacters[gGarage.unusedFrameCount];
        nameIndex = MDC->name_LNG_long;

        DECOMP_DecalFont_DrawLine(
            "PRESS L1 OR R1 TO SWAP",
            0x100,                    // midpoint
            0xc8,                     // near bottom
            FONT_SMALL,               // small text
            (JUSTIFY_CENTER | ORANGE) // center
        );
    }
#endif

    // CameraDC, freecam mode
    gGT->cameraDC[0].cameraMode = 3;

#ifdef USE_60FPS
    if ((gGT->timer & 1) == 0)
        sVar4 = gGarage.numFramesCurr_GarageMove;
    else
#endif

        // subtract transition timer by one frame
		garageFrames = gGarage.numFramesCurr_GarageMove - 1;

    // if mid-transition, skip some code
    if (gGarage.numFramesCurr_GarageMove != 0)
        goto SKIP_CONTROLS;

        // At this point, there must not be a transition
        // between drivers, so start drawing the UI

#if 0
	// count frames in garage?
    gGarage.unusedFrameCount++;
#endif

#ifndef USE_ENGINESWAP
    // animate growth of all three stat bars
    for (i = 0; i < 3; i++)
    {
        barLen = &gGarage.barLen[i];
        short stat = gGarage.barStat[MDC->engineID * 3 + i];

#ifdef USE_16BY9
        stat = WIDE_34(stat);
#endif

// half bar length, half speed per frame, just add 1
#if (defined(USE_60FPS) && defined(USE_16BY9))
#define BAR_RATE 1
#else
#define BAR_RATE 3
#endif

        if (*barLen < stat)
            *barLen = *barLen + BAR_RATE;
        if (stat < *barLen)
            *barLen = stat;
    }

    if (
        // Tiny Tiger
        (nameIndex == 46) ||

        (statNamePosX = 383,

         // Pura
         nameIndex == 51))
    {
        statNamePosX = 129;
        classNamePosX = 128;
        statBarPosX = 139;
    }
    else
    {
        classNamePosX = 384;
        statBarPosX = 393;
    }

    // "Speed"
    DECOMP_DecalFont_DrawLine(sdata->lngStrings[0x245], statNamePosX, 30, FONT_BIG, JUSTIFY_RIGHT | ORANGE_RED);

    // "Accel"
    DECOMP_DecalFont_DrawLine(sdata->lngStrings[0x246], statNamePosX, 45, FONT_BIG, JUSTIFY_RIGHT | LIME_GREEN);

    // "Turn"
    DECOMP_DecalFont_DrawLine(sdata->lngStrings[0x247], statNamePosX, 60, FONT_BIG, JUSTIFY_RIGHT | BLUE);

    int engineID = MDC->engineID;

    // 0x248 - Beginner
    // EngineID == 3
    i = 0;

    // 0x24A - Advanced
    if (engineID == 2)
        i = 2;

    // 0x249 - Intermediate
    if (engineID < 2)
        i = 1;

    // 7 pixels tall
    u_short statBarStart_Y = 33;
    u_short statBarEnd_Y = 40;

    u_short statBarShadows_Y = 34;

#if 0
	// remove array at 800b85f0,
	// it's 0x248, 0x249, 0x24A,
	// instead just do 0x248 + index
#endif

    // Draw class name
    DECOMP_DecalFont_DrawLine(sdata->lngStrings[0x248 + i], classNamePosX, 15, FONT_BIG, (JUSTIFY_CENTER | ORANGE));

    // bar length (animated)

    for (i = 0; i < 3; i++)
    {
        barLen = &gGarage.barLen[i];

        // bar outline
        r.x = statBarPosX;
        r.y = statBarStart_Y;
        r.w = *barLen;
        r.h = 7;

        // outline color white at 0x800b7780
        u_int outlineColor = 0xFFFFFF;

        DECOMP_CTR_Box_DrawWireBox(
            &r, &outlineColor,
            gGT->pushBuffer_UI.ptrOT, primMem);

        // bar shadows
        r.x = statBarPosX + 1;
        r.y = statBarShadows_Y;
        r.w = *barLen - 2;
        r.h = 5;

        // outline color black (shadows)
        outlineColor &= 0xff000000;

        DECOMP_CTR_Box_DrawWireBox(
            &r, &outlineColor,
            gGT->pushBuffer_UI.ptrOT, primMem);

        int segmentLen = WIDE_PICK(13, 10);
        int segmentStart = 0;
        int segmentEnd = segmentLen;

        for (int segmentIndex = 0; segmentIndex < 7; segmentIndex++)
        {
            // color data of bars (blue green yellow red)
            u_int *barColor = &gGarage.barColors[segmentIndex];
            short currSegmentLen = (short)segmentLen;

            if (*barLen <= segmentEnd)
            {
                currSegmentLen = *barLen - segmentStart;
            }

            if ((int)currSegmentLen << 0x10 < 0)
            {
                currSegmentLen = 0;
            }

            if (segmentStart + currSegmentLen <= *barLen)
            {
                // primMem curr
                POLY_G4 *p = primMem->curr;

                // quit if prim mem runs out
                if (p + 2 >= primMem->end)
                    return;

                primMem->curr = p + 1;

                // color data
                *(int *)&p->r0 = barColor[0] | 0x38000000;
                *(int *)&p->r1 = barColor[1] | 0x38000000;
                *(int *)&p->r2 = barColor[0] | 0x38000000;
                *(int *)&p->r3 = barColor[1] | 0x38000000;

                short segmentX = statBarPosX + segmentStart;

                // top left
                p->x0 = segmentX;
                p->y0 = statBarStart_Y;

                // top right
                p->x1 = segmentX + currSegmentLen;
                p->y1 = statBarStart_Y;

                // bottom left
                p->x2 = segmentX;
                p->y2 = statBarEnd_Y;

                // bottom right
                p->x3 = segmentX + currSegmentLen;
                p->y3 = statBarEnd_Y;

                // pointer to OT memory
                void *ot = gGT->pushBuffer_UI.ptrOT;

                *(int *)p = (*(int *)ot & 0xffffff) | 0x8000000;
                *(int *)ot = (int)p & 0xffffff;
            }

            segmentStart += segmentLen;
            segmentEnd += segmentLen;
        }

        // 15 pixels lower Y axis
        statBarStart_Y += 15;
        statBarEnd_Y += 15;
        statBarShadows_Y += 15;
    }

    // "Intermediate" (longest class name)
    short classMaxLen = DECOMP_DecalFont_GetLineWidth(sdata->lngStrings[0x249], 1);

    // Stats box
    r.x = (classNamePosX - (classMaxLen >> 1)) - 6;
    r.y = 11;
    r.w = classMaxLen + 12;
    r.h = 68;

    // Draw 2D Menu rectangle background
    DECOMP_RECTMENU_DrawInnerRect(&r, 4, gGT->backBuffer->otMem.startPlusFour);

#endif

#if 0
	// Original game uses array at 800b85d8,
	// we remove the usage cause it's just 0,1,2,3,4,5,6,7,
	// this array is used in Oxide Fix (Garage_Init+0x80),
	// so we can adjust the mod to fit the new code
	
	// otherwise would be
	// lngStrings[metadata[800b85d8[charSelectIndex]].nameLNG]
#endif

    char *name = sdata->lngStrings[nameIndex];

    // Draw character name
    DECOMP_DecalFont_DrawLine(name, 0x100, 0xb4, 1, 0xffff8000);

    char arrowColor = ORANGE;

    // blink arrows
    if ((sdata->frameCounter & FPS_DOUBLE(4)) == 0)
    {
        arrowColor = RED;
    }

    // Color data
    int *arrowColors = data.ptrColor[arrowColor];

    int nameLen = DECOMP_DecalFont_GetLineWidth(name, 1) >> 1;

    int arrowPos[2] = {236 - nameLen, nameLen + 274};
    int arrowRot[2] = {0x800, 0};

    struct Icon **iconPtrArray =
        ICONGROUP_GETICONS(gGT->iconGroup[4]);

    for (i = 0; i < 2; i++)
    {
        DECOMP_DecalHUD_Arrow2D(
            iconPtrArray[0x38],
            arrowPos[i],
            187,

            primMem,
            gGT->pushBuffer_UI.ptrOT,

            arrowColors[0], arrowColors[1],
            arrowColors[2], arrowColors[3],

            0, 0x1000, arrowRot[i]);
    }

    garageFrames = gGarage.numFramesCurr_GarageMove;

    if (((gGT->renderFlags & 0x1000) != 0) ||

        (
            // If you dont press Triangle, Cross, Circle, or Square
            ((sdata->AnyPlayerTap & 0x40070) == 0) &&

            // If you dont press D-pad
            ((sdata->AnyPlayerHold & 0xc) == 0)))

        goto SKIP_CONTROLS;

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

                garageFrames = gGarage.numFramesCurr_ZoomIn;
                if (gGarage.boolSelected == 1)
                {
                    gGarage.boolSelected = 0;
                    gGT->gameMode2 &= ~GARAGE_OSK;

                    if (garageFrames < gGarage.numFramesMax_Zoom)
                    {
                        gGarage.numFramesCurr_ZoomOut = gGarage.numFramesMax_Zoom - garageFrames;
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

                    data.characterIDs[0] = currSelectIndex;
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
#ifndef USE_ENGINESWAP
        // erase animated bars
        for (i = 2; i > -1; i--)
        {
            barLen = &gGarage.barLen[i];
            *barLen = 0;
        }
#endif
        // Play Sound
        DECOMP_OtherFX_Play(0, 1);

        // If you dont press Left
        if ((sdata->AnyPlayerHold & 4) == 0)
        {
            // If you dont press Right
            if ((sdata->AnyPlayerHold & 8) != 0)
            {
                currSelectIndex++;
                goto LAB_800b8084;
            }
        }

        // If you press Left
        else
        {
            currSelectIndex--;

        LAB_800b8084:

            // previous equals current
            sdata->advCharSelectIndex_prev = sdata->advCharSelectIndex_curr;

            // clamp 0-7
            currSelectIndex &= 7;
            sdata->advCharSelectIndex_curr = currSelectIndex;

#ifndef REBUILD_PS1
            Garage_MoveLR(currSelectIndex);
#endif
        }

        // reset frame counter to max number of frames
        gGarage.numFramesCurr_GarageMove = gGarage.numFramesMax_GarageMove;

        if (gGarage.numFramesCurr_ZoomIn < gGarage.numFramesMax_Zoom)
        {
            gGarage.numFramesCurr_ZoomOut = gGarage.numFramesMax_Zoom - gGarage.numFramesCurr_ZoomIn;
        }

        gGarage.boolSelected = 0;
        gGT->gameMode2 &= ~GARAGE_OSK;
    }

    // clear gamepad input (for menus)
    DECOMP_RECTMENU_ClearInput();

    garageFrames = gGarage.numFramesCurr_GarageMove;
SKIP_CONTROLS:
    gGarage.numFramesCurr_GarageMove = garageFrames;

    // if frames remaing for zoom camera
    if (0 < gGarage.numFramesCurr_ZoomIn)
    {
#ifdef USE_60FPS
        if (gGT->timer & 1)
#endif

            // decrease zoom frame timer
            gGarage.numFramesCurr_ZoomIn--;
    }

    // if pressed X once, and waited for countdown clock
    if ((gGarage.boolSelected == 1) && (gGarage.numFramesCurr_ZoomIn == 0))
    {
        if (
            // frames remaining for animation
            (FPS_DOUBLE(59) < gGarage.delayOneSecond) ||
            ((gGT->gameMode2 & GARAGE_OSK) != 0))
        {
            #ifdef USE_ENGINESWAP
            sdata->ptrDesiredMenu = &garageEngineSelect;
            #else
            // set desiredMenu to OSK (on-screen keyboard)
            sdata->ptrDesiredMenu = &data.menuSubmitName;
            #endif

            data.characterIDs[0] = currSelectIndex;
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

        else
        {
#ifdef USE_60FPS
            if (gGT->timer & 1)
#endif
                gGarage.delayOneSecond++;
        }
    }

#ifdef REBUILD_PC
    if (sdata->ptrDesiredMenu == &data.menuSubmitName)
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
        if (gGT->timer & 1)
#endif
            gGarage.numFramesCurr_ZoomOut--;
    }

    u_int prevSelectIndex = sdata->advCharSelectIndex_prev;

    // Pura->Crash
    if ((currSelectIndex == 0) && (prevSelectIndex == 7))
        garageFrames = 240 - gGarage.numFramesCurr_GarageMove;

    // Crash->Pura
    else if ((currSelectIndex == 7) && (prevSelectIndex == 0))
		garageFrames = gGarage.numFramesCurr_GarageMove + 210;

    // Move Right
    else if (prevSelectIndex < currSelectIndex)
        garageFrames = currSelectIndex * 30 - gGarage.numFramesCurr_GarageMove;

    // Move Left
    else
        garageFrames = currSelectIndex * 30 + gGarage.numFramesCurr_GarageMove;

    // animation frame index,
    // pointer to position,
    // pointer to rotation

    int getPath;
    short camPos[3];
    short camRot[3];
    DECOMP_CAM_Path_Move((int)garageFrames, &camPos[0], &camRot[0], &getPath);

#ifdef USE_60FPS

    // if transitioning
    if (gGarage.numFramesCurr_GarageMove != 0)
    {
        // if counter wasn't moved this frame
        if ((gGT->timer & 1) == 0)
        {
            // Pura->Crash
			if ((sdata->advCharSelectIndex_curr == 0) && (sdata->advCharSelectIndex_prev == 7))
				sVar4 = 240 - (gGarage.numFramesCurr_GarageMove-1);

            // Crash->Pura
			else if ((sdata->advCharSelectIndex_curr == 7) && (sdata->advCharSelectIndex_prev == 0))
				sVar4 = (gGarage.numFramesCurr_GarageMove-1) + 210;

            // Move Right
			else if (sdata->advCharSelectIndex_prev < sdata->advCharSelectIndex_curr)
				sVar4 = sdata->advCharSelectIndex_curr * 30 - (gGarage.numFramesCurr_GarageMove-1);

            // Move Left
            else
				sVar4 = sdata->advCharSelectIndex_curr * 30 + (gGarage.numFramesCurr_GarageMove-1);

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
            if (diff < 0x800)
            {
                rot[0] = (rot[0] + rot2[0]) / 2;
                rot[1] = (rot[1] + rot2[1]) / 2;
                rot[2] = (rot[2] + rot2[2]) / 2;
            }
        }
    }

#endif

    // set position and rotation to pushBuffer
    gGT->pushBuffer[0].pos[0] = camPos[0];
    gGT->pushBuffer[0].pos[1] = camPos[1];
    gGT->pushBuffer[0].pos[2] = camPos[2];

    gGT->pushBuffer[0].rot[0] = camRot[0];
    gGT->pushBuffer[0].rot[1] = camRot[1];
    gGT->pushBuffer[0].rot[2] = camRot[2];

    int zoom = gGarage.numFramesCurr_ZoomOut;
    if (zoom == 0)
    {
        zoom = (gGarage.numFramesMax_Zoom - gGarage.numFramesCurr_ZoomIn) *
                (gGarage.fovMax - gGarage.fovMin);
    }
    else
    {
        zoom = zoom * (gGarage.fovMax - gGarage.fovMin);
    }

    zoom = gGarage.fovMin + zoom / gGarage.numFramesMax_Zoom;

    gGT->pushBuffer[0].distanceToScreen_CURR = zoom;
    gGT->pushBuffer[0].distanceToScreen_PREV = zoom;
}

struct RectMenu *DECOMP_CS_Garage_GetMenuPtr(void)
{
    return &gGarage.menuGarage;
}

void DECOMP_CS_Garage_Init(void)
{
    // go to 3D character selection
    sdata->ptrActiveMenu = &gGarage.menuGarage;

    gGarage.menuGarage.state &= ~(ONLY_DRAW_TITLE);

    // 0 = just entered garage
    DECOMP_CS_Garage_ZoomOut(0);
}