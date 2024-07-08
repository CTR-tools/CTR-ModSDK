#include <common.h>

void GTE_AudioLR_Inst(MATRIX *pushBuffer, VECTOR *returnVect)
{
    SVECTOR instVect;

    instVect.vx = returnVect->vx;
    instVect.vy = returnVect->vy;
    instVect.vz = returnVect->vz;
    SetRotMatrix(pushBuffer);
    gte_ldv0(&instVect);
    gte_rtv0();
    gte_stlvnl0(returnVect->vx);
    gte_stlvnl1(returnVect->vy);
    gte_stlvnl2(returnVect->vz);
}

void GTE_AudioLR_Driver(MATRIX *pushBuffer, struct Driver* d, VECTOR *returnVect)
{
    SVECTOR playerVect;

    playerVect.vx = (short)(d->posCurr.x >> 8) - pushBuffer->t[0];
    playerVect.vy = (short)(d->posCurr.y >> 8) - pushBuffer->t[1];
    playerVect.vz = (short)(d->posCurr.z >> 8) - pushBuffer->t[2];
    SetRotMatrix(pushBuffer);
    gte_ldv0(&playerVect);
    gte_rtv0();
    gte_stlvnl0(returnVect->vx);
    gte_stlvnl1(returnVect->vy);
    gte_stlvnl2(returnVect->vz);
}

// in: vec3, out: squared length
int GTE_GetSquaredLength(VECTOR *vec3)
{
    int r2;
    int r3;
    int r4; // param_1

    // vectorX
    gte_ldIR1(vec3->vx);

    // vectorY
    gte_ldIR2(vec3->vy);

    // vectorZ
    gte_ldIR3(vec3->vz);

    // square root
    gte_sqr0(0);

    // readback
    read_mt(r2, r3, r4);

    return r2 + r3 + r4;
}
