#include <ctr/test.h>

#ifdef TEST_COLL_IMPL

static u32 PrintDCacheDiff(const char* name, const CollDCache* expected, const CollDCache* ret)
{
    u32 failed = false;
    const u8* pExpected = (const u8*) expected;
    const u8* pRet = (const u8*) ret;
    const u32 len = sizeof(CollDCache);
    for (u32 i = 0; i < len; i++)
    {
        if (pExpected[i] != pRet[i]) { ND_printf("[%s] Test Failed:\nOffset %x: %d, got: %d\n", name, i, (u32) pExpected[i], (u32) pRet[i]); failed = true; }
    }
    return failed;
}

void TEST_COLL_ProjectPointToEdge(const SVec3* v1, const SVec3* v2, const SVec3* point, const SVec3* ret)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_COLL_ProjectPointToEdge));
    SVec3 expected;
    typedef void (*Func)(SVec3* out, const SVec3* v1, const SVec3* v2, const SVec3* point);
    Func func = (Func) TEST_WRAPPER;
    func(&expected, v1, v2, point);
    PrintSVectorDiff("COLL_ProjectPointToEdge", &expected, ret);
    PatchFunction_End(index);
}

void TEST_COLL_CalculateTrianglePlane(const CollDCache* cache, CollVertex* v1, const CollVertex* v2, const CollVertex* v3, const CollVertex* ret)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_COLL_CalculateTrianglePlane));
    typedef void (*Func)(const CollDCache* cache, CollVertex* v1, const CollVertex* v2, const CollVertex* v3);
    Func func = (Func) TEST_WRAPPER;
    func(cache, v1, v2, v3);
    PrintSVectorDiff("COLL_CalculateTrianglePlane", &v1->triNormal, &ret->triNormal);
    if (v1->planeDist != ret->planeDist) { ND_printf("[COLL_CalculateTrianglePlane] Test Failed:\nDist: %d\nResult: %d\n", v1->planeDist, ret->planeDist); }
    if (v1->normalDominantAxis != ret->normalDominantAxis) { ND_printf("[COLL_CalculateTrianglePlane] Test Failed:\nAxis: %d\nResult: %d\n", v1->normalDominantAxis, ret->normalDominantAxis); }
    PatchFunction_End(index);
}

void TEST_COLL_LoadVerticeData(CollDCache* cache)
{
    CollVertex vertices[NUM_VERTICES_QUADBLOCK];
    for (u32 i = 0; i < NUM_VERTICES_QUADBLOCK; i++)
    {
        vertices[i] = cache->quadblockCollVertices[i];
    }
    const u16 thirdIndex = cache->quadblockThirdIndex;
    const u16 fourthIndex = cache->quadblockFourthIndex;
    const u32 index = PatchFunction_Beg((u32*)(&ND_COLL_LoadVerticeData));

    const u32 quadblock = (u32) cache->currQuadblock;
    const u32 levVertices = (u32) cache->meshInfo->vertices;
    __asm__ volatile("move $t9, %0" : : "r"(quadblock));
    __asm__ volatile("move $t8, %0" : : "r"(levVertices));

    typedef void (*Func)(CollDCache* cache);
    Func func = (Func) TEST_WRAPPER;
    func(cache);
    for (u32 i = 0; i < NUM_VERTICES_QUADBLOCK; i++)
    {
        PrintSVectorDiff("COLL_LoadVerticeData", &cache->quadblockCollVertices[i].pos, &vertices[i].pos);
        if (cache->quadblockCollVertices[i].levVertex != vertices[i].levVertex)
        {
            ND_printf("[COLL_LoadVerticeData] Test Failed: levVertex at index %d\n", i);
        }
    }
    if (cache->quadblockThirdIndex != thirdIndex) { ND_printf("[COLL_LoadVerticeData] Test Failed:\nthirdIndex: %d\nResult:%d\n", cache->quadblockThirdIndex, thirdIndex); }
    if (cache->quadblockFourthIndex != fourthIndex) { ND_printf("[COLL_LoadVerticeData] Test Failed:\nfourthIndex: %d\nResult:%d\n", cache->quadblockFourthIndex, fourthIndex);}
    PatchFunction_End(index);
}

void TEST_COLL_BarycentricTest(TestVertex* t, const CollVertex* v1, const CollVertex* v2, const CollVertex* v3, const SVec3* pos, s32 ret)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_COLL_BarycentricTest));
    typedef s32 (*Func)(TestVertex* t, const CollVertex* v1, const CollVertex* v2, const CollVertex* v3);
    Func func = (Func) TEST_WRAPPER;
    const s32 expected = func(t, v1, v2, v3);
    PrintSVectorDiff("COLL_BarycentricTest", &t->pos, pos);
    if (expected != ret) { ND_printf("[COLL_BarycentricTest] Test Failed:\nExpected: %d\nResult: %d\n", expected, ret); }
    PatchFunction_End(index);
}

void TEST_COLL_TestTriangle(CollDCache* cache, const CollVertex* v1, const CollVertex* v2, const CollVertex* v3, const CollDCache* ret)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_COLL_TestTriangle));
    typedef void (*Func)(CollDCache* cache, const CollVertex* v1, const CollVertex* v2, const CollVertex* v3);
    Func func = (Func) TEST_WRAPPER;
    func(cache, v1, v2, v3);
    PrintDCacheDiff("COLL_TestTriangle", cache, ret);
    PatchFunction_End(index);
}

#endif // TEST_COLL_IMPL