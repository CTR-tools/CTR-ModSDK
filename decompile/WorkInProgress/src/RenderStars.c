#include <common.h>

// WIP

void RenderStars(struct PushBuffer *pb, struct PrimMem *primMem, struct StarData *stars, char numPlayers)
{
    short starSpread;
    u_short randomSeed;
    int starX, starY, starZ;
    int absX, absY, absZ;
    int max, mid, min;
    int multiplier;
    u_int starColor;
    
    u_int flag;
    u_int sxy2;

    u_int rngSeed1;
    u_int rngSeed2;
    u_int rngTemp1, rngTemp2, rngTemp3;
    u_int rngPosX, rngPosY, rngPosZ;

    u_long *ot;

    // special POLY_G3?
    void *p;

    gte_ldtr(0, 0, 0);

    p = primMem->curr;

    for (int i = numPlayers; i > 0; i--)
    {
        gte_ldR11R12(*(u_int *)&pb->matrix_ViewProj.m[0][0]);
        gte_ldR13R21(*(u_int *)&pb->matrix_ViewProj.m[0][2]);
        gte_ldR22R23(*(u_int *)&pb->matrix_ViewProj.m[1][1]);
        gte_ldR31R32(*(u_int *)&pb->matrix_ViewProj.m[2][0]);
        gte_ldR33(pb->matrix_ViewProj.m[2][2]);

        gte_ldOFX(pb->rect.w << 15);
        gte_ldOFY(pb->rect.h << 15);

        gte_ldH(pb->distanceToScreen_PREV);

        gte_ldtr(0, 0, 0);

        int numStars = stars->numStars;
        starSpread = stars->spread;
        randomSeed = stars->seed;

        // OT depth based on distance
        ot = (u_int *)&pb->ptrOT[stars->distance];

        // RNG seed,
        // produces different random numbers for each iteration
        // of the loop, but will generate same random numbers each frame,
        // putting stars in the same place each frame
        rngSeed1 = 0x30125400;
        rngSeed2 = 0x493583fe;

        // loop for every star
        for (; numStars >= 0; numStars--)
        {
            rngTemp1 = rngSeed1 + (rngSeed2 >> 8);
            rngTemp2 = rngSeed1 >> 8 | rngTemp1;
            rngPosX = (rngTemp1 + (rngTemp2 >> 8)) << 24;

            rngTemp3 = (rngSeed2 >> 8 | rngPosX) >> 8;
            rngTemp1 = rngTemp2 >> 8 | rngPosX;
            rngPosY = (rngTemp2 + rngTemp3 + (rngTemp1 >> 8)) << 24;

            rngTemp3 = (rngTemp3 | rngPosY) >> 8;
            rngTemp2 = rngTemp1 >> 8 | rngPosX;
            rngPosZ = (rngTemp1 + rngTemp3 + (rngTemp2 >> 8)) << 24;

            // randomize position
            starX = (int)rngPosX >> 20;
            starY = (int)rngPosY >> (randomSeed + 20 & 0x1f);
            starZ = (int)rngPosZ >> 20;

            // absolute
            absX = (starX < 0) ? -starX : starX;

            absY = (starY < 0) ? -starY : starY;

            if ((starY < 0) && (absY = -starY, starSpread == 0))
            {
                starY = absY;
            }

            absZ = (starZ < 0) ? -starZ : starZ;

            // sort x,y,z
            max = absX;
            mid = absY;

            if (absX - absY < 1)
            {
                max = absY;
                mid = absX;
            }

            if (max - absZ < 1)
            {
                min = mid;
                mid = absZ;

                if (absZ >= max)
                {
                    max = absZ;
                }
            }
            else
            {
                min = absZ;
            }
            
            multiplier = 0x1000000 / (max + (mid >> 2) + (min >> 2));

            rngSeed1 = (starX * multiplier >> 12) & 0xFFFF |
                       ((starY * multiplier >> 12) << 16);

            gte_ldVXY0(rngSeed1);
            gte_ldVZ0(starZ * multiplier >> 12);            
            gte_rtps_b();

            // randomize color
            rngTemp1 = (rngTemp3 | rngTemp1) >> 8;
            rngSeed1 = rngTemp2 >> 8 | rngSeed1;
            rngSeed2 = rngTemp1 | (rngTemp2 + rngTemp1 + (rngSeed1 >> 8)) << 24;
            starColor = (rngTemp2 + rngTemp1 + (rngSeed1 >> 8)) & 0xFF | 0x40;

            // get output
            gte_stflg(&flag);
            gte_stsxy2(&sxy2);

            // if star is not off screen and clipped
            if ((-1 < flag << 13) &&
                // what's 0xd90200?
                (rngTemp2 = sxy2 - 0xd90200 | sxy2, 
                // check pos X
                (int)rngTemp2 < 0) &&
                // check pos Y 
                (-1 < (int)(~rngTemp2 << 16)))
            {
                *(u_int*)&p->r0 = starColor | (starColor << 8) | (starColor << 16) | 0x68000000;
                *(u_int*)&p->x0 = sxy2;

                *(int *)p = *ot | 0x2000000;
                *ot = (u_int)p & 0xffffff;
                p += 3;
            }
        }

        p->tpage = 0xe1000a20; 
        p->tag = 0;

        *(int *)p = *ot | 0x2000000;
        *ot = (u_int)p & 0xffffff;

        // advance to next primitive
        p += 3;
        // next pushBuffer
        pb += 1;
    }
    // new PrimMem curr
    primMem->curr = p;
}