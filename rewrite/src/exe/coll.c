#include <ctr/coll.h>
#include <ctr/gte.h>
#include <ctr/driver.h>
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
    gte_dotProduct(&edgeDot, GTE_ROW_INDEX_0, GTE_MATRIX_ROT, GTE_VECTOR_0, GTE_CALC_INT);
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
    gte_interpolateBase(coords.v, GTE_CALC_FLOATING_POINT);
    out->x = coords.x;
    out->y = coords.y;
    out->z = coords.z;
    TEST_COLL_ProjectPointToEdge(v1, v2, point, out);
    /* This is a hand written assembly function that breaks the ABI,
    and some callers expect the argument registers to be untouched */
    __asm__ volatile("move $a0, %0" : : "r"((u32)out));
    __asm__ volatile("move $a1, %0" : : "r"((u32)v1));
    __asm__ volatile("move $a2, %0" : : "r"((u32)v2));
    __asm__ volatile("move $a3, %0" : : "r"((u32)point));
}

/* Address: 0x8001f2dc */
static void COLL_CalculateTrianglePlane(const CollDCache* cache, CollVertex* v1, const CollVertex* v2, const CollVertex* v3)
{
#ifdef TEST_COLL_IMPL
    CollVertex input = *v1;
#endif
    Vec3 cross;
    const Matrix m = { .m[0][0] = v3->pos.x - v1->pos.x, .m[1][1] = v3->pos.y - v1->pos.y, .m[2][2] = v3->pos.z - v1->pos.z };
    const SVec3 v = { .x = v2->pos.x - v1->pos.x, .y = v2->pos.y - v1->pos.y, .z = v2->pos.z - v1->pos.z };
    gte_crossProduct(cross.v, m.m, v.v);
    v1->triNormal.x = ((cross.x >> cache->lodShift) * cache->normalScale) >> cache->normalBitshift;
    v1->triNormal.y = ((cross.y >> cache->lodShift) * cache->normalScale) >> cache->normalBitshift;
    v1->triNormal.z = ((cross.z >> cache->lodShift) * cache->normalScale) >> cache->normalBitshift;

    s32 dot;
    gte_loadRowMatrix(v1->pos.v, GTE_ROW_INDEX_0, GTE_MATRIX_ROT);
    gte_loadSVec(v1->triNormal.v, GTE_VECTOR_IR);
    gte_dotProduct(&dot, GTE_ROW_INDEX_0, GTE_MATRIX_ROT, GTE_VECTOR_IR, GTE_CALC_FLOATING_POINT);
    v1->planeDist = dot >> 1;

    Vec3 absNormal = { .x = abs(v1->triNormal.x), .y = abs(v1->triNormal.y), .z = abs(v1->triNormal.z) };
    const s32 magnitude = max(max(absNormal.x, absNormal.y), absNormal.z);
    if (magnitude == absNormal.x) { v1->normalDominantAxis = AXIS_X; }
    else if (magnitude == absNormal.y) { v1->normalDominantAxis = AXIS_Y; }
    else { v1->normalDominantAxis = AXIS_Z; }
    TEST_COLL_CalculateTrianglePlane(cache, &input, v2, v3, v1);
}

/* Address: 0x8001f7f0 */
static void COLL_LoadVerticeData(CollDCache* cache)
{
    const Quadblock* quadblock = cache->currQuadblock;
    const Vertex* vertices = cache->meshInfo->vertices;
    for (u32 i = 0; i < NUM_VERTICES_QUADBLOCK; i++)
    {
        u16 index = quadblock->index[i];
        const Vertex* vertex = &vertices[index];
        cache->quadblockCollVertices[i].pos = vertex->pos;
        cache->quadblockCollVertices[i].levVertex = vertex;
    }
    cache->quadblockThirdIndex = quadblock->index[2];
    cache->quadblockFourthIndex = quadblock->index[3];
    TEST_COLL_LoadVerticeData(cache);
}

/* Address: 0x8001f67c */
void COLL_LoadQuadblockData_LowLOD(CollDCache* cache, Quadblock* quadblock)
{
    COLL_LoadVerticeData(cache);
    cache->lodShift = 2;
    cache->normalBitshift = quadblock->triNormalVecBitshift;
    if (cache->quadblockThirdIndex != cache->quadblockFourthIndex)
    {
        cache->normalScale = quadblock->triNormalVecDividend[9];
        COLL_CalculateTrianglePlane(cache, &cache->quadblockCollVertices[1], &cache->quadblockCollVertices[3], &cache->quadblockCollVertices[2]);
    }
    cache->normalScale = quadblock->triNormalVecDividend[8];
    COLL_CalculateTrianglePlane(cache, &cache->quadblockCollVertices[0], &cache->quadblockCollVertices[1], &cache->quadblockCollVertices[2]);
    /* This is a hand written assembly function that breaks the ABI,
    and some callers expect the argument registers to be untouched */
    __asm__ volatile("move $a0, %0" : : "r"((u32)cache));
    __asm__ volatile("move $t9, %0" : : "r"((u32)quadblock));
}

/* Address: 0x8001f6f0 */
void COLL_LoadQuadblockData_HighLOD(CollDCache* cache, Quadblock* quadblock)
{
    COLL_LoadVerticeData(cache);
    cache->lodShift = 0;
    cache->normalBitshift = quadblock->triNormalVecBitshift;
    if (cache->quadblockThirdIndex != cache->quadblockFourthIndex)
    {
        cache->normalScale = quadblock->triNormalVecDividend[4];
        COLL_CalculateTrianglePlane(cache, &cache->quadblockCollVertices[8], &cache->quadblockCollVertices[6], &cache->quadblockCollVertices[7]);
        cache->normalScale = quadblock->triNormalVecDividend[5];
        COLL_CalculateTrianglePlane(cache, &cache->quadblockCollVertices[7], &cache->quadblockCollVertices[3], &cache->quadblockCollVertices[8]);
        cache->normalScale = quadblock->triNormalVecDividend[6];
        COLL_CalculateTrianglePlane(cache, &cache->quadblockCollVertices[1], &cache->quadblockCollVertices[7], &cache->quadblockCollVertices[6]);
        cache->normalScale = quadblock->triNormalVecDividend[7];
        COLL_CalculateTrianglePlane(cache, &cache->quadblockCollVertices[2], &cache->quadblockCollVertices[6], &cache->quadblockCollVertices[8]);
    }
    cache->normalScale = quadblock->triNormalVecDividend[0];
    COLL_CalculateTrianglePlane(cache, &cache->quadblockCollVertices[0], &cache->quadblockCollVertices[4], &cache->quadblockCollVertices[5]);
    cache->normalScale = quadblock->triNormalVecDividend[1];
    COLL_CalculateTrianglePlane(cache, &cache->quadblockCollVertices[4], &cache->quadblockCollVertices[6], &cache->quadblockCollVertices[5]);
    cache->normalScale = quadblock->triNormalVecDividend[2];
    COLL_CalculateTrianglePlane(cache, &cache->quadblockCollVertices[6], &cache->quadblockCollVertices[4], &cache->quadblockCollVertices[1]);
    cache->normalScale = quadblock->triNormalVecDividend[3];
    COLL_CalculateTrianglePlane(cache, &cache->quadblockCollVertices[5], &cache->quadblockCollVertices[6], &cache->quadblockCollVertices[2]);
    /* This is a hand written assembly function that breaks the ABI,
    and some callers expect the argument registers to be untouched */
    __asm__ volatile("move $a0, %0" : : "r"((u32)cache));
    __asm__ volatile("move $t9, %0" : : "r"((u32)quadblock));
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

static s32 COLL_BarycentricTest(TestVertex* t, const CollVertex* v1, const CollVertex* v2, const CollVertex* v3)
{
#ifdef TEST_COLL_IMPL
    TestVertex input = *t;
#endif
    const s32 ret = _COLL_BarycentricTest(t, v1, v2, v3);
    TEST_COLL_BarycentricTest(&input, v1, v2, v3, &t->pos, ret);
    return ret;
}

static void _COLL_TestTriangle(CollDCache* cache, const CollVertex* v1, const CollVertex* v2, const CollVertex* v3)
{
    cache->numVerticesTested++;
    cache->collIntersection.triNormal = v1->triNormal;
    cache->collIntersection.planeDist = v1->planeDist;
    cache->collIntersection.normalDominantAxis = v1->normalDominantAxis;

    const u16 quadFlags = cache->currQuadblock->flags;
    if ((quadFlags & QUADFLAGS_TIGER_TEMPLE_DOOR) && (cache->currQuadblock->terrain & e_ignoreCollisionDoorFlagTerrain)) { return; }

    const u32 triggerScript = quadFlags & QUADFLAGS_TRIGGER_SCRIPT;
    const Matrix m = {
        .m[0][0] = cache->inputNextPos.x, .m[0][1] = cache->inputNextPos.y, .m[0][2] = cache->inputNextPos.z,
        .m[1][0] = cache->collInput.quadblock.driverPos.x, .m[1][1] = cache->collInput.quadblock.driverPos.y, .m[1][2] = cache->collInput.quadblock.driverPos.z,
    };
    s32 distTriNextPos, distTriCurrPos;
    gte_SetRotMatrix(m.m);
    gte_loadSVec(cache->collIntersection.triNormal.v, GTE_VECTOR_0);
    gte_dotProduct(&distTriNextPos, GTE_ROW_INDEX_0, GTE_MATRIX_ROT, GTE_VECTOR_0, GTE_CALC_FLOATING_POINT);
    gte_readMac(&distTriCurrPos, GTE_MAC_2);
    distTriNextPos = distTriNextPos + (cache->collIntersection.planeDist * -2);
    distTriCurrPos = distTriCurrPos + (cache->collIntersection.planeDist * -2);
    cache->numVerticesTested++;
    if (distTriCurrPos < 0)
    {
        if ((!triggerScript) && (cache->currQuadblock->drawOrderLow.doubleSided == 0)) { return; }
        distTriCurrPos = -distTriCurrPos;
        distTriNextPos = -distTriNextPos;
        cache->collIntersection.triNormal.x = -cache->collIntersection.triNormal.x;
        cache->collIntersection.triNormal.y = -cache->collIntersection.triNormal.y;
        cache->collIntersection.triNormal.z = -cache->collIntersection.triNormal.z;
        cache->collIntersection.planeDist = -cache->collIntersection.planeDist;
    }
    if ((distTriNextPos >= cache->inputHitRadius) || ((!triggerScript) && (distTriNextPos > distTriCurrPos))) { return; }

    u32 crossedPlane = false;
    const SVec3 deltaPos = {
        .x = cache->inputNextPos.x - cache->collInput.quadblock.driverPos.x,
        .y = cache->inputNextPos.y - cache->collInput.quadblock.driverPos.y,
        .z = cache->inputNextPos.z - cache->collInput.quadblock.driverPos.z
    };
    if (distTriNextPos < 0)
    {
        const s32 interpolationFactor = FP_DIV(-distTriNextPos, distTriCurrPos - distTriNextPos);
        gte_loadSVec(deltaPos.v, GTE_VECTOR_IR);
        gte_loadIR(interpolationFactor, GTE_IR_0);
        crossedPlane = true;
    }
    else
    {
        gte_loadSVec(cache->collIntersection.triNormal.v, GTE_VECTOR_IR);
        gte_loadIR(distTriNextPos, GTE_IR_0);
    }
    Vec3 interpolation;
    gte_interpolate(interpolation.v, GTE_CALC_FLOATING_POINT);
    cache->collIntersection.interpolationPoint.x = cache->inputNextPos.x - interpolation.x;
    cache->collIntersection.interpolationPoint.y = cache->inputNextPos.y - interpolation.y;
    cache->collIntersection.interpolationPoint.z = cache->inputNextPos.z - interpolation.z;
    cache->currTestVertices[0] = v1;
    cache->currTestVertices[1] = v2;
    cache->currTestVertices[2] = v3;
    const s32 barycentricTest = COLL_BarycentricTest(&cache->collIntersection, v1, v2, v3);
    if (barycentricTest == BARYCENTRIC_TEST_INVALID) { return; }

    if (crossedPlane)
    {
        cache->deltaInterpolationIntersection.x = cache->collIntersection.interpolationPoint.x - cache->collIntersection.pos.x;
        cache->deltaInterpolationIntersection.y = cache->collIntersection.interpolationPoint.y - cache->collIntersection.pos.y;
        cache->deltaInterpolationIntersection.z = cache->collIntersection.interpolationPoint.z - cache->collIntersection.pos.z;
    }
    else
    {
        cache->deltaInterpolationIntersection.x = cache->inputNextPos.x - cache->collIntersection.pos.x;
        cache->deltaInterpolationIntersection.y = cache->inputNextPos.y - cache->collIntersection.pos.y;
        cache->deltaInterpolationIntersection.z = cache->inputNextPos.z - cache->collIntersection.pos.z;
    }
    s32 distSquaredInterpolationIntersection;
    gte_loadRowMatrix(cache->deltaInterpolationIntersection.v, GTE_ROW_INDEX_0, GTE_MATRIX_ROT);
    gte_loadSVec(cache->deltaInterpolationIntersection.v, GTE_VECTOR_0);
    gte_dotProduct(&distSquaredInterpolationIntersection, GTE_ROW_INDEX_0, GTE_MATRIX_ROT, GTE_VECTOR_0, GTE_CALC_INT);
    if (distSquaredInterpolationIntersection > cache->inputHitRadiusSquared) { return; }

    if (triggerScript)
    {
        const u32 skip = (distTriNextPos >= 0) && (distTriNextPos >= cache->inputHitRadius) && (distTriCurrPos >= cache->inputHitRadius);
        if (!skip) { cache->stepFlags |= cache->currQuadblock->terrain; return; }
    }

    s32 deltaDist = distTriCurrPos - distTriNextPos;
    if (deltaDist != 0) { deltaDist = FP_ONE - FP_DIV(cache->inputHitRadius - distTriNextPos, deltaDist); }
    if (deltaDist >= cache->speedScale) { return; }

    if (quadFlags & QUADFLAGS_OUT_OF_BOUNDS)
    {
        if ((quadFlags & QUADFLAGS_MASK_GRAB) == 0) { return; }
        cache->stepFlags |= STEPFLAGS_OUT_OF_BOUNDS;
        return;
    }

    cache->speedScale = deltaDist;
    cache->collidedVertices[0] = cache->currTestVertices[0]->levVertex;
    cache->collidedVertices[1] = cache->currTestVertices[1]->levVertex;
    cache->collidedVertices[2] = cache->currTestVertices[2]->levVertex;
    cache->coll = cache->collIntersection;
    cache->collidedQuadblock = cache->currQuadblock;
    cache->collidedTriangleIndex = cache->currTriangleIndex;
    cache->barycentricTest = barycentricTest;
    if (deltaDist > 0)
    {
        Vec3 nextPos;
        gte_loadSVec(deltaPos.v, GTE_VECTOR_IR);
        gte_loadIR(deltaDist, GTE_IR_0);
        gte_interpolate(nextPos.v, GTE_CALC_FLOATING_POINT);
        cache->collInput.quadblock.driverNextPos.x = cache->collInput.quadblock.driverPos.x + nextPos.x;
        cache->collInput.quadblock.driverNextPos.y = cache->collInput.quadblock.driverPos.y + nextPos.y;
        cache->collInput.quadblock.driverNextPos.z = cache->collInput.quadblock.driverPos.z + nextPos.z;
    }
    else { cache->collInput.quadblock.driverNextPos = cache->collInput.quadblock.driverPos; }
    cache->numTrianglesCollided++;
}

void COLL_TestTriangle(CollDCache* cache, const CollVertex* v1, const CollVertex* v2, const CollVertex* v3)
{
#ifdef TEST_COLL_IMPL
    *(CollDCache*)(BACKUP_ADDR) = *cache;
#endif
    _COLL_TestTriangle(cache, v1, v2, v3);
    TEST_COLL_TestTriangle((CollDCache*)(BACKUP_ADDR), v1, v2, v3, cache);
    /* This is a hand written assembly function that breaks the ABI,
    and some callers expect the argument registers to be untouched */
    __asm__ volatile("move $a0, %0" : : "r"((u32)cache));
    __asm__ volatile("move $t9, %0" : : "r"((u32)cache->currQuadblock));
}