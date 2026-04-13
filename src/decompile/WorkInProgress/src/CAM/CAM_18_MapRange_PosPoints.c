#include <common.h>

// get percentage [0 to 0x1000] of Driver between pos1 and pos2
int DECOMP_CAM_MapRange_PosPoints(SVec3 *pos1, SVec3 *pos2, SVec3 *currPos)
{
    int percent;
    SVec3 vec1;
    SVec3 vec2;
    short distY;

    // vector distance between position1 and position2.
    vec1.x = pos1->x - pos2->x;
    vec1.y = pos1->y - pos2->y;
    vec1.z = pos1->z - pos2->z;

    MATH_VectorNormalize(&vec1);
    
    // vector distance between position1 and currentPosition.
    vec2.x = pos1->x - currPos->x;
    vec2.y = pos1->y - currPos->y;
    vec2.z = pos1->z - currPos->z;

    // replace R11R12 and R13R21
	gte_ldsvrtrow0(&vec1);
    gte_ldv0(&vec2);
    gte_mvmva(0, 0, 0, 3, 0);
    gte_stlvnl0(&percent);

    // Shift by 12 bits to get the percentage between 0 and 0x1000.
    return FP_INT(percent);
}