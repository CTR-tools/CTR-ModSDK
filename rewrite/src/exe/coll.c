#include <ctr/coll.h>
#include <ctr/gte.h>
#include <ctr/test.h>

/* Address: 0x8001ede4 */
void COLL_ProjectPointToEdge(SVec3* out, const SVec3* v1, const SVec3* v2, const SVec3* point)
{
    const SVec3 edge = { v2->x - v1->x, v2->y - v1->y, v2->z - v1->z };
    const Matrix m =
    {
        .m[0][0] = edge.x, .m[0][1] = edge.y, .m[0][2] = edge.z,
        .m[1][0] = point->x - v1->x, .m[1][1] = point->y - v1->y, .m[1][2] = point->z - v1->z,
    };
    gte_SetRotMatrix(m.m);
    gte_loadSVec(edge.v, GTE_VECTOR_0);
    s32 edgeDot, pointDot;
    gte_dotProduct(&edgeDot, GTE_ROW_INDEX_0, GTE_MATRIX_ROT, GTE_VECTOR_0);
    gte_readMac(&pointDot, GTE_MAC_2);
    s32 leadingZeroes;
    gte_leadingZeroes(&leadingZeroes, pointDot);

    const s32 shift = clamp(leadingZeroes - 2, 0, FRACTIONAL_BITS);
    if (shift < FRACTIONAL_BITS) { edgeDot >>= (FRACTIONAL_BITS - shift); }

    s32 barycentricFactor = 0;
    if (edgeDot != 0) { barycentricFactor = clamp((pointDot << shift) / edgeDot, 0, FP_ONE); }

    const Vec3 V1 = { .x = v1->x, .y = v1->y, .z = v1->z };
    gte_loadIR(barycentricFactor, GTE_IR_0);
    gte_loadSVec(edge.v, GTE_VECTOR_IR);
    gte_loadVec(V1.v, GTE_VECTOR_MAC);
    gte_interpolate(GTE_INTERPOLATE_FLOATING_POINT);
    Vec3 coords;
    gte_readMac(coords.v, GTE_VECTOR_MAC);
    out->x = coords.x;
    out->y = coords.y;
    out->z = coords.z;
    TEST_COLL_ProjectPointToEdge(v1, v2, point, out);
}