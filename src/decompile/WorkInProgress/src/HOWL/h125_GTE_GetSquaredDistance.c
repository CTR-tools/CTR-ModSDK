#include <common.h>

// param1: vec3 pos1
// param2: vec3 pos2
int GTE_GetSquaredDistance(VECTOR *pos1, VECTOR *pos2)
{
    int sqrX;
    int sqrY;
    int sqrZ;
    u_int distX;
    u_int distY;
    u_int distZ;

    // distX
    gte_ldIR1(2, distX, pos1->vx - pos2->vx);

    // distY
    gte_ldIR2(2, distY, pos1->vy - pos2->vy);

    // distZ
    gte_ldIR3(2, distZ, pos1->vz - pos2->vz);

    // SQR(sf) - Square vector
    gte_sqr0(0);

    // x*x
    gte_stlvnl0(sqrX);

    // y*y
    gte_stlvnl1(sqrY);

    // z*z
    gte_stlvnl2(sqrZ);

    // (x*x) + (y*y) + (z*z)
    // squared distance
    return sqrX + sqrY + sqrZ;
}