#include <common.h>

#ifdef USE_ONLINE
#include "statsbarData.c"
extern unsigned int barColors[7];
extern short barLen[NUM_STATS];
extern short barStat[NUM_STATS * NUM_CLASS];
#endif

void DrawStatsBox(short posX, short posY, u_int engineID)
{
    int i;
    short *length;
    struct GameTracker* gGT = sdata->gGT;
    struct PrimMem *primMem = &gGT->backBuffer->primMem;
    RECT r;
    
    // "Intermediate" (longest class name)
    short classMaxLen = DECOMP_DecalFont_GetLineWidth(sdata->lngStrings[0x249], 1);

    // animate growth of all three stat bars
    for (i = 0; i < NUM_STATS; i++)
    {
        length = &barLen[i];
        short stat = barStat[engineID * 3 + i];

#ifdef USE_16BY9
        stat = WIDE_34(stat);
#endif

// half bar length, half speed per frame, just add 1
#if (defined(USE_60FPS) && defined(USE_16BY9))
#define BAR_RATE 1
#else
#define BAR_RATE 3
#endif

        if (*length < stat)
            *length = *length + BAR_RATE;
        if (stat < *length)
            *length = stat;
    }
    
    #ifdef USE_ONLINE
    short statNamePosX = posX + 60;
    short statBarPosX = statNamePosX + 10;
    
    short statNamePosY = posY + 5;

    short statBarStart_Y = statNamePosY;
    short statBarEnd_Y = statBarStart_Y + 5;
    short statBarShadows_Y = statBarStart_Y + 1;
    #else
    short classNamePosX = ((posX + 6) + (classMaxLen >> 1));
    short statNamePosX = classNamePosX - 1;
    short statBarPosX = statNamePosX + 10;

    short classNamePosY = posY + 4;
    short statNamePosY = classNamePosY + 15;

    short statBarStart_Y = statNamePosY + 3;
    short statBarEnd_Y = statBarStart_Y + 7;
    short statBarShadows_Y = statBarStart_Y + 1;
    #endif

    // "Speed", "Accel" and "Turn"
    for (i = 0; i < NUM_STATS; i++)
    {
        DECOMP_DecalFont_DrawLine(sdata->lngStrings[0x245 + i], statNamePosX, statNamePosY, FONT_SMALL, JUSTIFY_RIGHT | (ORANGE_RED - i));
        statNamePosY += 8;
    }
    
#ifndef USE_ONLINE

    // 0x248 - Beginner
    // EngineID == 3
    i = 0;

    // 0x24A - Advanced
    if (engineID == 2)
        i = 2;

    // 0x249 - Intermediate
    if (engineID < 2)
        i = 1;

    // Draw class name
    DECOMP_DecalFont_DrawLine(sdata->lngStrings[0x248 + i], classNamePosX, classNamePosY, FONT_BIG, (JUSTIFY_CENTER | ORANGE));

#endif

    // bar length (animated)

    for (i = 0; i < NUM_STATS; i++)
    {
        length = &barLen[i];

        // bar outline
        r.x = statBarPosX;
        r.y = statBarStart_Y;
        r.w = *length;
        #ifdef USE_ONLINE
        r.h = 5;
        #else
        r.h = 7;
        #endif

        // outline color white at 0x800b7780
        u_int outlineColor = 0xFFFFFF;

        DECOMP_CTR_Box_DrawWireBox(
            &r, &outlineColor,
            gGT->pushBuffer_UI.ptrOT, primMem);

        // bar shadows
        r.x = statBarPosX + 1;
        r.y = statBarShadows_Y;
        r.w = *length - 2;
        #ifdef USE_ONLINE
        r.h = 3;
        #else
        r.h = 5;
        #endif

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
            u_int* barColor = &barColors[segmentIndex];
            short currSegmentLen = (short)segmentLen;

            if (*length <= segmentEnd)
            {
                currSegmentLen = *length - segmentStart;
            }

            if ((int)currSegmentLen << 0x10 < 0)
            {
                currSegmentLen = 0;
            }

            if (segmentStart + currSegmentLen <= *length)
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
        #ifdef USE_ONLINE
        statBarStart_Y += 8;
        statBarEnd_Y += 8;
        statBarShadows_Y += 8;
        #else
        // 15 pixels lower Y axis
        statBarStart_Y += 15;
        statBarEnd_Y += 15;
        statBarShadows_Y += 15;
        #endif
    }

    // Stats box
    r.x = posX;
    r.y = posY;

    #ifdef USE_ONLINE
    r.w = classMaxLen;
    r.h = 34;
    #else
    r.w = classMaxLen + 12;
    r.h = 68;
    #endif

    // Draw 2D Menu rectangle background
    DECOMP_RECTMENU_DrawInnerRect(&r, 4, gGT->backBuffer->otMem.startPlusFour);
}
