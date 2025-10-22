#pragma once

#include <ctr/macros.h>
#include <ctr/redux.h>
#include <ctr/nd.h>
#include <ctr/game_tracker.h>
#include <ctr/math.h>
#include <ctr/rng.h>
#include <ctr/coll.h>
#include <ctr/list.h>
#include <ctr/test_backup.h>

extern const char* s_nameTestedFunc;

void TEST_WRAPPER();
void TEST_LoadPatches();
void TEST_Init();
bool TEST_Memcmp(const void* expected, const void* actual, u32 n);
u32 PatchFunction_Beg(u32* index, const char* funcName);
void PatchFunction_End(u32 index);
u32 TEST_PrintSVectorDiff(const SVec3* expected, const SVec3* ret);
u32 TEST_PrintMatrixDiff(const Matrix* expected, const Matrix* ret, u32 cmpTrans);

force_inline void FlushCache()
{
    register int n asm("t1") = 0x44;
    __asm__ volatile("" : "=r"(n) : "r"(n));
    ((void (*)())0xa0)();
}

#define TEST

#if defined(TEST)
#define DYNAMIC_ASSERT(expected, actual, msg) //TODO
#else
#define DYNAMIC_ASSERT(expected, actual, msg)
#endif

#if defined(TEST)
#define STATIC_ASSERT //TODO
#else
#define STATIC_ASSERT
#endif

#if defined(TEST)
#define TEST_MATH_IMPL
#define TEST_RNG_IMPL
#define TEST_COLL_IMPL
#define TEST_LIST_IMPL
#endif

#ifdef TEST_MATH_IMPL
    void TEST_MATH_Sin(u32 angle, s32 ret);
    void TEST_MATH_Cos(u32 angle, s32 ret);
    void TEST_MATH_Sqrt(u32 n, u32 shift, u32 ret);
    void TEST_MATH_GetInverseMatrixTransformation(const Matrix* matrix, const Matrix* ret);
    void TEST_MATH_VectorLength(const SVec3* vector, s32 ret);
    void TEST_MATH_VectorNormalize(SVec3* vector, const SVec3* ret);
    void TEST_MATH_CombineMatrixTransformation(const Matrix* m, const Matrix* n, const Matrix* ret);
    void TEST_MATH_MatrixMultiplication(const Matrix* m, const Matrix* n, const Matrix* ret);
#else
    #define TEST_MATH_Sin(angle, ret)
    #define TEST_MATH_Cos(angle, ret)
    #define TEST_MATH_Sqrt(n, shift, ret)
    #define TEST_MATH_GetInverseMatrixTransformation(matrix, ret)
    #define TEST_MATH_VectorLength(vector, ret)
    #define TEST_MATH_VectorNormalize(vector, ret)
    #define TEST_MATH_CombineMatrixTransformation(m, n, ret)
    #define TEST_MATH_MatrixMultiplication(m, n, ret)
#endif

#ifdef TEST_RNG_IMPL
	typedef struct BDATA_RNG_Rand
	{
		u32 e_seed; //backup of 0x8008d424
	} BDATA_RNG_Rand;
    void BACKUP_RNG_Rand();
	void RESTORE_RNG_Rand(BDATA_RNG_Rand* restore);
    void TEST_RNG_Rand();

	typedef struct BDATA_RNG_RandInt
	{
		RNGSeed e_gameTracker_seed; //backup of e_gameTracker->seed
	} BDATA_RNG_RandInt;
    void BACKUP_RNG_RandInt();
	void RESTORE_RNG_RandInt(BDATA_RNG_RandInt* restore);
    void TEST_RNG_RandInt(u32 n, s32 ret);

    void TEST_RNG_PseudoRand(u16 n, u16 ret);
    void TEST_RNG_Random(RNGSeed* seed, const RNGSeed* ret);
#else
    #define BACKUP_RNG_Rand()
	#define RESTORE_RNG_Rand(restore)
    #define TEST_RNG_Rand()
    #define BACKUP_RNG_RandInt()
	#define RESTORE_RNG_RandInt(restore)
    #define TEST_RNG_RandInt(n, ret)
    #define TEST_RNG_PseudoRand(n, ret)
    #define TEST_RNG_Random(seed, ret)
#endif

#ifdef TEST_COLL_IMPL
    void TEST_COLL_ProjectPointToEdge(const SVec3* v1, const SVec3* v2, const SVec3* point, const SVec3* ret);
    void TEST_COLL_CalculateTrianglePlane(const CollDCache* cache, CollVertex* v1, const CollVertex* v2, const CollVertex* v3, const CollVertex* ret);
    void TEST_COLL_LoadVerticeData(CollDCache* cache);

	typedef struct BDATA_COLL_LoadQuadblockData_LowLOD
	{
		CollDCache cache; //backup of *cache
	} BDATA_COLL_LoadQuadblockData_LowLOD;
	void BACKUP_COLL_LoadQuadblockData_LowLOD(CollDCache* cache);
	void RESTORE_COLL_LoadQuadblockData_LowLOD(BDATA_COLL_LoadQuadblockData_LowLOD* restore, CollDCache* cache);
    void TEST_COLL_LoadQuadblockData_LowLOD(const Quadblock* quadblock, CollDCache* cache);

	typedef struct BDATA_COLL_LoadQuadblockData_HighLOD
	{
		CollDCache cache; //backup of *cache
	} BDATA_COLL_LoadQuadblockData_HighLOD;
	void BACKUP_COLL_LoadQuadblockData_HighLOD(CollDCache* cache);
	void RESTORE_COLL_LoadQuadblockData_HighLOD(BDATA_COLL_LoadQuadblockData_HighLOD* restore, CollDCache* cache);
    void TEST_COLL_LoadQuadblockData_HighLOD(const Quadblock* quadblock, CollDCache* cache);

    void TEST_COLL_BarycentricTest(TestVertex* t, const CollVertex* v1, const CollVertex* v2, const CollVertex* v3, const SVec3* pos, s32 ret);

	typedef struct BDATA_COLL_TestTriangle
	{
		CollDCache cache; //backup of *cache
	} BDATA_COLL_TestTriangle;
	void BACKUP_COLL_TestTriangle(CollDCache* cache);
	void RESTORE_COLL_TestTriangle(BDATA_COLL_TestTriangle* restore, CollDCache* cache);
    void TEST_COLL_TestTriangle(const CollVertex* v1, const CollVertex* v2, const CollVertex* v3, CollDCache* cache);

	typedef struct BDATA_COLL_TestLeaf_Quadblock
	{
		CollDCache cache; //backup of *cache
	} BDATA_COLL_TestLeaf_Quadblock;
	void BACKUP_COLL_TestLeaf_Quadblock(CollDCache* cache);
	void RESTORE_COLL_TestLeaf_Quadblock(BDATA_COLL_TestLeaf_Quadblock* restore, CollDCache* cache);
    void TEST_COLL_TestLeaf_Quadblock(const Quadblock* quadblock, CollDCache* cache);
#else
    #define TEST_COLL_ProjectPointToEdge(out, v1, v2, point)
    #define TEST_COLL_CalculateTrianglePlane(cache, v1, v2, v3, ret)
    #define TEST_COLL_LoadVerticeData(cache)
    #define TEST_COLL_LoadQuadblockData_LowLOD(cache, quadblock, ret)
    #define TEST_COLL_LoadQuadblockData_HighLOD(cache, quadblock, ret)
    #define TEST_COLL_BarycentricTest(t, v1, v2, v3, pos, ret)
    #define TEST_COLL_TestTriangle(cache, v1, v2, v3, ret)
    #define TEST_COLL_TestLeaf_Quadblock(quadblock, cache, ret)
#endif

#ifdef TEST_LIST_IMPL
	typedef struct BDATA_LIST_Init
	{
		void asdf;
	} BDATA_LIST_Init;
	void BACKUP_LIST_Init(const void* source);
	void RESTORE_LIST_Init(BDATA_LIST_Init* restore, void* destination);
	void TEST_LIST_Init(LinkedList* list, Item* item, s32 itemSize, s32 numItems);
#else
	#define TEST_LIST_Init(list, item, itemSize, numItems)
#endif