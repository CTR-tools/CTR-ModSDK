#pragma once

#include <ctr/macros.h>
#include <ctr/redux.h>
#include <ctr/nd.h>
#include <ctr/game_tracker.h>
#include <ctr/math.h>
#include <ctr/rng.h>
#include <ctr/coll.h>

void TEST_WRAPPER();
void LoadTestPatches();
u32 PatchFunction_Beg(u32* index);
void PatchFunction_End(u32 index);
u32 PrintSVectorDiff(const char* name, const SVec3* expected, const SVec3* ret);
u32 PrintMatrixDiff(const char* name, const Matrix* expected, const Matrix* ret, u32 cmpTrans);

force_inline void FlushCache()
{
    register int n asm("t1") = 0x44;
    __asm__ volatile("" : "=r"(n) : "r"(n));
    ((void (*)())0xa0)();
}

#define BACKUP_ADDR 0x80400000

//#define TEST_MATH_IMPL
//#define TEST_RNG_IMPL
//#define TEST_COLL_IMPL

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
    void BACKUP_RNG_Rand();
    void TEST_RNG_Rand();
    void BACKUP_RNG_RandInt();
    void TEST_RNG_RandInt(u32 n, s32 ret);
    void TEST_RNG_PseudoRand(u16 n, u16 ret);
    void TEST_RNG_Random(RNGSeed* seed, const RNGSeed* ret);
#else
    #define BACKUP_RNG_Rand()
    #define TEST_RNG_Rand()
    #define BACKUP_RNG_RandInt()
    #define TEST_RNG_RandInt(n, ret)
    #define TEST_RNG_PseudoRand(n, ret)
    #define TEST_RNG_Random(seed, ret)
#endif

#ifdef TEST_COLL_IMPL
    void TEST_COLL_ProjectPointToEdge(const SVec3* v1, const SVec3* v2, const SVec3* point, const SVec3* ret);
    void TEST_COLL_CalculateTrianglePlane(const CollDCache* cache, CollVertex* v1, const CollVertex* v2, const CollVertex* v3, const CollVertex* ret);
    void TEST_COLL_LoadVerticeData(CollDCache* cache);
    void TEST_COLL_BarycentricTest(TestVertex* t, const CollVertex* v1, const CollVertex* v2, const CollVertex* v3, const SVec3* pos, s32 ret);
#else
    #define TEST_COLL_ProjectPointToEdge(out, v1, v2, point)
    #define TEST_COLL_CalculateTrianglePlane(cache, v1, v2, v3, ret)
    #define TEST_COLL_LoadVerticeData(cache)
    #define TEST_COLL_BarycentricTest(t, v1, v2, v3, pos, ret)
#endif