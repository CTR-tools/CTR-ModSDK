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

    Vec3 coords;
    gte_interpolate(coords.v, GTE_INTERPOLATE_FLOATING_POINT);
    out->x = coords.x;
    out->y = coords.y;
    out->z = coords.z;
    TEST_COLL_ProjectPointToEdge(v1, v2, point, out);
#ifdef TEST_COLL_IMPL
    __asm__ volatile("move $a0, %0" : : "r"((u32)out));
    __asm__ volatile("move $a1, %0" : : "r"((u32)v1));
    __asm__ volatile("move $a2, %0" : : "r"((u32)v2));
    __asm__ volatile("move $a3, %0" : : "r"((u32)point));
#endif
}

/* Address: 0x8001f928 */
static s32 _COLL_BarycentricTest(TestVertex* t, const CollVertex* v1, const CollVertex* v2, const CollVertex* v3)
{
    Vec2 deltaT;
    Vec2 deltaTri[2];
    const SVec3* edgeV2;
    const SVec3* edgeV3;
    u32 firstAxis, secondAxis;

    if (t->normalDominantAxis == AXIS_X)
    {
        firstAxis = 1; // y
        secondAxis = 2; // z
    }
    else if (t->normalDominantAxis == AXIS_Y)
    {
        firstAxis = 2; // z
        secondAxis = 0; // x
    }
    else
    {
        firstAxis = 0; // x
        secondAxis = 1; // y
    }

    deltaTri[0].x = v2->pos.v[firstAxis] - v1->pos.v[firstAxis];
    deltaTri[0].y = v3->pos.v[firstAxis] - v1->pos.v[firstAxis];
    deltaT.x = t->interpolationPoint.v[firstAxis] - v1->pos.v[firstAxis];
    edgeV2 = &v2->pos;
    edgeV3 = &v3->pos;
    if (abs(deltaTri[0].x) < abs(deltaTri[0].y))
    {
        edgeV2 = &v3->pos;
        edgeV3 = &v2->pos;
        s32 temp = deltaTri[0].x;
        deltaTri[0].x = deltaTri[0].y;
        deltaTri[0].y = temp;
    }
    deltaTri[1].x = edgeV2->v[secondAxis] - v1->pos.v[secondAxis];
    deltaTri[1].y = edgeV3->v[secondAxis] - v1->pos.v[secondAxis];
    deltaT.y = t->interpolationPoint.v[secondAxis] - v1->pos.v[secondAxis];

    s32 beta = FP(-1);
    s32 gamma = FP(-1);
    if (deltaTri[0].x != 0)
    {
        s32 dem = ((deltaTri[1].y * deltaTri[0].x) - (deltaTri[0].y * deltaTri[1].x)) >> 6;
        if (dem != 0)
        {
            beta = (((deltaT.y * deltaTri[0].x) - (deltaT.x * deltaTri[1].x)) << 6) / dem;
            gamma = ((deltaT.x * FP_ONE) - (beta * deltaTri[0].y)) / deltaTri[0].x;
        }
    }
    else
    {
        if ((deltaTri[0].y != 0) && (deltaTri[1].x != 0))
        {
            beta = FP_DIV(deltaT.y, deltaTri[0].y);
            gamma = ((deltaT.y * FP_ONE) - (beta * deltaTri[1].y)) / deltaTri[1].x;
        }
    }

    /* Naughty Dog bug: their hand written assembly code
    forgets to check beta == -1, creating false collisions */
#ifdef FIX_CTR_BUGS
    if ((beta == FP(-1)) || (gamma == FP(-1))) { return BARYCENTRIC_TEST_INVALID; }
#else
    if (gamma == FP(-1)) { return BARYCENTRIC_TEST_INVALID; }
#endif

    s32 alpha = beta + gamma + FP(-1);
    if (gamma < 0)
    {
        if (beta < 0)
        {
            t->pos = v1->pos;
            return BARYCENTRIC_TEST_SNAP_V1;
        }
        if (alpha < 0)
        {
            COLL_ProjectPointToEdge(&t->pos, &v1->pos, edgeV3, &t->interpolationPoint);
            return BARYCENTRIC_TEST_EDGE_V1_V3;
        }
        t->pos = *edgeV3;
        return BARYCENTRIC_TEST_SNAP_V3;
    }
    if (beta < 0)
    {
        if (alpha < 0)
        {
            COLL_ProjectPointToEdge(&t->pos, &v1->pos, edgeV2, &t->interpolationPoint);
            return BARYCENTRIC_TEST_EDGE_V1_V2;
        }
        t->pos = *edgeV2;
        return BARYCENTRIC_TEST_SNAP_V2;
    }
    if (alpha > 0)
    {
        COLL_ProjectPointToEdge(&t->pos, edgeV2, edgeV3, &t->interpolationPoint);
        return BARYCENTRIC_TEST_EDGE_V2_V3;
    }
    t->pos = t->interpolationPoint;
    return BARYCENTRIC_TEST_INSIDE_TRIANGLE;
}

s32 COLL_BarycentricTest(TestVertex* t, const CollVertex* v1, const CollVertex* v2, const CollVertex* v3)
{
#ifdef TEST_COLL_IMPL
    TestVertex input = *t;
#endif
    const s32 ret = _COLL_BarycentricTest(t, v1, v2, v3);
    TEST_COLL_BarycentricTest(&input, v1, v2, v3, &t->pos, ret);
    return ret;
}