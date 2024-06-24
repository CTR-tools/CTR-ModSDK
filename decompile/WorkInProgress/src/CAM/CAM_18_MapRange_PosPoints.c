#include <common.h>

// get percentage [0 to 0x1000] of Driver between pos1 and pos2
int DECOMP_CAM_MapRange_PosPoints(short *pos1, short *pos2, short *currPos)
{
    int percent;
    int vectorDistMax;
    int vectorDistCurr;
    short distY;

    // vector distance between position1 and position2.
    vectorDistMax = CONCAT22(pos1[1] - pos2[1], pos1[0] - pos2[0]);

    distY = pos1[2] - pos2[2];

    MATH_VectorNormalize(&vectorDistMax);

    // vector distance between position1 and currentPosition.
    vectorDistCurr = CONCAT22(currPos[1] - pos1[1], currPos[0] - pos1[0]);

    gte_ldR11R12(vectorDistMax);
    gte_ldR13R21((int)distY);
    gte_ldVXY0(vectorDistCurr);
    gte_ldVZ0((int)(short)(currPos[2] - pos1[2]));
    gte_mvmva(0, 0, 0, 3, 0);
    percent = gte_stMAC1();

    // Shift by 12 bits to get the percentage between 0 and 0x1000.
    return percent >> 0xc;
}