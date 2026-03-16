#include <namespace_gte.h>

void RotateVector(SVec3 * out, const SVec3 * in)
{
    #ifndef REBUILD_PC
	struct ScratchpadFrustum* scpf = (struct ScratchpadFrustum*)0x1f800000;
    gte_ldv0(in);
    gte_rtv0();
    gte_stlvnl(scpf);
	
	out->x = scpf->pos.x;
	out->y = scpf->pos.y;
	out->z = scpf->pos.z;
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
