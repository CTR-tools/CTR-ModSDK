#include <ctr_gte.h>

void RotateVector(SVec3 * out, const SVec3 * in)
{
    gte_ldv0(in);
    gte_rtv0();
    gte_stlvnl0(&out->x);
    gte_stlvnl1(&out->y);
    gte_stlvnl2(&out->z);
}