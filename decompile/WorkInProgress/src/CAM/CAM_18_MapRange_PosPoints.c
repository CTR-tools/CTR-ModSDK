#include <common.h>

// get percentage [0 to 0x1000] of Driver between pos1 and pos2
int DECOMP_CAM_MapRange_PosPoints(short *pos1, short *pos2, short *currPos)
{
    char i;
    int percent;
    SVECTOR vectorDistMax;
    SVECTOR vectorDistCurr;

    // vector distance between position1 and position2.
    for (i = 0; i < 3; i++)
        *(short*)&vectorDistMax[i] = pos1[i] - pos2[i];

    MATH_VectorNormalize(&vectorDistMax);

    // vector distance between position1 and currentPosition.
    for (i = 0; i < 3; i++)
        *(short*)&vectorDistMax[i] = currPos[i] - pos1[i];

    gte_ldR11R12(vectorDistMax[0]);
    gte_ldR13R21(vectorDistMax[1]);

    gte_ldv0(&vectorDistMax[0]);

    gte_mvmva(0, 0, 0, 3, 0);
    gte_stlvnl0(&percent);

    // Shift by 12 bits to get the percentage between 0 and 0x1000.
    return percent >> 12;
}