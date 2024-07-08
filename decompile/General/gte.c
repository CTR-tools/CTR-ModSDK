#include <ctr_gte.h>

void RotateVector(SVec3 * out, const SVec3 * in)
{
    #ifndef REBUILD_PC
    gte_ldv0(in);
    gte_rtv0();
    gte_stlvnl0(&out->x);
    gte_stlvnl1(&out->y);
    gte_stlvnl2(&out->z);
    #endif
}

void MulMatrixVec(Vec3 * out, const Matrix * m, const SVec3 * in)
{
    #ifndef REBUILD_PC
    gte_SetColorMatrix(m);
    gte_ldv0(in);
    gte_lcv0();
    gte_stlvnl(out);
    #endif
}
