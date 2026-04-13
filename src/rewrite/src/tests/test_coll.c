#include <ctr/test.h>

#ifdef TEST_COLL_IMPL

#pragma region COLL_ProjectPointToEdge
void TEST_COLL_ProjectPointToEdge(const SVec3* v1, const SVec3* v2, const SVec3* point, const SVec3* ret)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_COLL_ProjectPointToEdge), "COLL_ProjectPointToEdge");
    SVec3 expected;
    typedef void (*Func)(SVec3* out, const SVec3* v1, const SVec3* v2, const SVec3* point);
    Func func = (Func) TEST_WRAPPER;
    func(&expected, v1, v2, point);
    TEST_PrintSVectorDiff(&expected, ret);
    PatchFunction_End(index);
}
#pragma endregion

#pragma region COLL_CalculateTrianglePlane
void TEST_COLL_CalculateTrianglePlane(const CollDCache* cache, CollVertex* v1, const CollVertex* v2, const CollVertex* v3, const CollVertex* ret)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_COLL_CalculateTrianglePlane), "COLL_CalculateTrianglePlane");
    typedef void (*Func)(const CollDCache* cache, CollVertex* v1, const CollVertex* v2, const CollVertex* v3);
    Func func = (Func) TEST_WRAPPER;
    func(cache, v1, v2, v3);
	TEST_PrintSVectorDiff(&v1->triNormal, &ret->triNormal);
    if (v1->planeDist != ret->planeDist) { ND_printf("[%s] Test Failed:\nDist: %d\nResult: %d\n", s_nameTestedFunc, v1->planeDist, ret->planeDist); }
    if (v1->normalDominantAxis != ret->normalDominantAxis) { ND_printf("[%s] Test Failed:\nAxis: %d\nResult: %d\n", s_nameTestedFunc, v1->normalDominantAxis, ret->normalDominantAxis); }
    PatchFunction_End(index);
}
#pragma endregion

#pragma region COLL_LoadVerticeData
void TEST_COLL_LoadVerticeData(CollDCache* cache)
{
    CollVertex vertices[NUM_VERTICES_QUADBLOCK];
    for (u32 i = 0; i < NUM_VERTICES_QUADBLOCK; i++)
    {
        vertices[i] = cache->quadblockCollVertices[i];
    }
    const u16 thirdIndex = cache->quadblockThirdIndex;
    const u16 fourthIndex = cache->quadblockFourthIndex;
    const u32 index = PatchFunction_Beg((u32*)(&ND_COLL_LoadVerticeData), "COLL_LoadVerticeData");

    const u32 quadblock = (u32) cache->currQuadblock;
    const u32 levVertices = (u32) cache->meshInfo->vertices;
    __asm__ volatile("move $t9, %0" : : "r"(quadblock));
    __asm__ volatile("move $t8, %0" : : "r"(levVertices));

    typedef void (*Func)(CollDCache* cache);
    Func func = (Func) TEST_WRAPPER;
    func(cache);
    for (u32 i = 0; i < NUM_VERTICES_QUADBLOCK; i++)
    {
		TEST_PrintSVectorDiff(&cache->quadblockCollVertices[i].pos, &vertices[i].pos);
        if (cache->quadblockCollVertices[i].levVertex != vertices[i].levVertex)
        {
            ND_printf("[%s] Test Failed: levVertex at index %d\n", s_nameTestedFunc, i);
        }
    }
    if (cache->quadblockThirdIndex != thirdIndex) { ND_printf("[%s] Test Failed:\nthirdIndex: %d\nResult:%d\n", s_nameTestedFunc, cache->quadblockThirdIndex, thirdIndex); }
    if (cache->quadblockFourthIndex != fourthIndex) { ND_printf("[%s] Test Failed:\nfourthIndex: %d\nResult:%d\n", s_nameTestedFunc, cache->quadblockFourthIndex, fourthIndex);}
    PatchFunction_End(index);
}
#pragma endregion

#pragma region COLL_LoadQuadblockData_LowLOD
void BACKUP_COLL_LoadQuadblockData_LowLOD(CollDCache* cache)
{
	BDATA_COLL_LoadQuadblockData_LowLOD backup = {};
	backup.cache = *cache;
	BACKUP_PUSH(&backup, sizeof(backup));
}

void RESTORE_COLL_LoadQuadblockData_LowLOD(BDATA_COLL_LoadQuadblockData_LowLOD* restore, CollDCache* cache)
{
	*cache = restore->cache;
}

void TEST_COLL_LoadQuadblockData_LowLOD(const Quadblock* quadblock, CollDCache* cache)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_COLL_LoadQuadblockData_LowLOD), "COLL_LoadQuadblockData_LowLOD");

	BDATA_COLL_LoadQuadblockData_LowLOD* before = (BDATA_COLL_LoadQuadblockData_LowLOD*)BACKUP_PEEK(1, NULL);
	BDATA_COLL_LoadQuadblockData_LowLOD* resultFromDecomp = (BDATA_COLL_LoadQuadblockData_LowLOD*)BACKUP_PEEK(0, NULL);
	RESTORE_COLL_LoadQuadblockData_LowLOD(before, cache);
    typedef void (*Func)(CollDCache* cache, const Quadblock* quadblock);
    Func func = (Func) TEST_WRAPPER;
    func(cache, quadblock);
	BACKUP_COLL_LoadQuadblockData_LowLOD(cache);
	BDATA_COLL_LoadQuadblockData_LowLOD* resultFromND = (BDATA_COLL_LoadQuadblockData_LowLOD*)BACKUP_PEEK(0, NULL);

	BACKUP_POP_MULTIPLE(3);

	TEST_Memcmp(&resultFromND->cache, &resultFromDecomp->cache, sizeof(resultFromND->cache));
    PatchFunction_End(index);
}
#pragma endregion

#pragma region COLL_LoadQuadblockData_HighLOD
void BACKUP_COLL_LoadQuadblockData_HighLOD(CollDCache* cache)
{
	BDATA_COLL_LoadQuadblockData_HighLOD backup = {};
	backup.cache = *cache;
	BACKUP_PUSH(&backup, sizeof(backup));
}

void RESTORE_COLL_LoadQuadblockData_HighLOD(BDATA_COLL_LoadQuadblockData_HighLOD* restore, CollDCache* cache)
{
	*cache = restore->cache;
}

void TEST_COLL_LoadQuadblockData_HighLOD(const Quadblock* quadblock, CollDCache* cache)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_COLL_LoadQuadblockData_HighLOD), "COLL_LoadQuadblockData_HighLOD");

	BDATA_COLL_LoadQuadblockData_HighLOD* before = (BDATA_COLL_LoadQuadblockData_HighLOD*)BACKUP_PEEK(1, NULL);
	BDATA_COLL_LoadQuadblockData_HighLOD* resultFromDecomp = (BDATA_COLL_LoadQuadblockData_HighLOD*)BACKUP_PEEK(0, NULL);
	RESTORE_COLL_LoadQuadblockData_HighLOD(before, cache);
    typedef void (*Func)(CollDCache* cache, const Quadblock* quadblock);
    Func func = (Func) TEST_WRAPPER;
    func(cache, quadblock);
	BACKUP_COLL_LoadQuadblockData_HighLOD(cache);
	BDATA_COLL_LoadQuadblockData_HighLOD* resultFromND = (BDATA_COLL_LoadQuadblockData_HighLOD*)BACKUP_PEEK(0, NULL);

	BACKUP_POP_MULTIPLE(3);

	TEST_Memcmp(&resultFromND->cache, &resultFromDecomp->cache, sizeof(resultFromND->cache));
    PatchFunction_End(index);
}
#pragma endregion

#pragma region COLL_BarycentricTest
void TEST_COLL_BarycentricTest(TestVertex* t, const CollVertex* v1, const CollVertex* v2, const CollVertex* v3, const SVec3* pos, s32 ret)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_COLL_BarycentricTest), "COLL_BarycentricTest");
    typedef s32 (*Func)(TestVertex* t, const CollVertex* v1, const CollVertex* v2, const CollVertex* v3);
    Func func = (Func) TEST_WRAPPER;
    const s32 expected = func(t, v1, v2, v3);
	TEST_PrintSVectorDiff(&t->pos, pos);
    if (expected != ret) { ND_printf("[%s] Test Failed:\nExpected: %d\nResult: %d\n", s_nameTestedFunc, expected, ret); }
    PatchFunction_End(index);
}
#pragma endregion

#pragma region COLL_TestTriangle
void BACKUP_COLL_TestTriangle(CollDCache* cache)
{
	BDATA_COLL_TestTriangle backup = {};
	backup.cache = *cache;
	BACKUP_PUSH(&backup, sizeof(backup));
}

void RESTORE_COLL_TestTriangle(BDATA_COLL_TestTriangle* restore, CollDCache* cache)
{
	*cache = restore->cache;
}

void TEST_COLL_TestTriangle(const CollVertex* v1, const CollVertex* v2, const CollVertex* v3, CollDCache* cache)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_COLL_TestTriangle), "COLL_TestTriangle");

	BDATA_COLL_TestTriangle* before = (BDATA_COLL_TestTriangle*)BACKUP_PEEK(1, NULL);
	BDATA_COLL_TestTriangle* resultFromDecomp = (BDATA_COLL_TestTriangle*)BACKUP_PEEK(0, NULL);
	RESTORE_COLL_TestTriangle(before, cache);
    typedef void (*Func)(CollDCache* cache, const CollVertex* v1, const CollVertex* v2, const CollVertex* v3);
    Func func = (Func) TEST_WRAPPER;
    func(cache, v1, v2, v3);
	BACKUP_COLL_TestTriangle(cache);
	BDATA_COLL_TestTriangle* resultFromND = (BDATA_COLL_TestTriangle*)BACKUP_PEEK(0, NULL);

	BACKUP_POP_MULTIPLE(3);

	TEST_Memcmp(&resultFromND->cache, &resultFromDecomp->cache, sizeof(resultFromND->cache));
    PatchFunction_End(index);
}
#pragma endregion

#pragma region COLL_TestLeaf_Quadblock
void BACKUP_COLL_TestLeaf_Quadblock(CollDCache* cache)
{
	BDATA_COLL_TestLeaf_Quadblock backup = {};
	backup.cache = *cache;
	BACKUP_PUSH(&backup, sizeof(backup));
}

void RESTORE_COLL_TestLeaf_Quadblock(BDATA_COLL_TestLeaf_Quadblock* restore, CollDCache* cache)
{
	*cache = restore->cache;
}

void TEST_COLL_TestLeaf_Quadblock(const Quadblock* quadblock, CollDCache* cache)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_COLL_TestLeaf_Quadblock), "COLL_TestLeaf_Quadblock");

	BDATA_COLL_TestLeaf_Quadblock* before = (BDATA_COLL_TestLeaf_Quadblock*)BACKUP_PEEK(1, NULL);
	BDATA_COLL_TestLeaf_Quadblock* resultFromDecomp = (BDATA_COLL_TestLeaf_Quadblock*)BACKUP_PEEK(0, NULL);
	RESTORE_COLL_TestLeaf_Quadblock(before, cache);
    typedef void (*Func)(const Quadblock* quadblock, CollDCache* cache);
    Func func = (Func) TEST_WRAPPER;
    func(quadblock, cache);
	BACKUP_COLL_TestLeaf_Quadblock(cache);
	BDATA_COLL_TestLeaf_Quadblock* resultFromND = (BDATA_COLL_TestLeaf_Quadblock*)BACKUP_PEEK(0, NULL);

	BACKUP_POP_MULTIPLE(3);

	TEST_Memcmp(&resultFromND->cache, &resultFromDecomp->cache, sizeof(resultFromND->cache));
    PatchFunction_End(index);
}
#pragma endregion

#endif // TEST_COLL_IMPL