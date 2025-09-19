#ifndef TEST_H
#define TEST_H

#include <ctr/macros.h>
#include <ctr/redux.h>
#include <ctr/math.h>
#include <ctr/rng.h>

void LoadTestPatches();

#define BACKUP_ADDR 0x80400000

#define TEST_MATH_IMPL
#define TEST_RNG_IMPL

#ifdef TEST_MATH_IMPL
    void TEST_MATH_Sin(u32 angle, s32 res);
    void TEST_MATH_Cos(u32 angle, s32 res);
    void TEST_MATH_Sqrt(u32 n, u32 shift, u32 res);
    void TEST_MATH_GetInverseMatrixTransformation(const Matrix* matrix, const Matrix* res);
    void TEST_MATH_VectorLength(const SVec3* vector, s32 res);
    void TEST_MATH_VectorNormalize(SVec3* vector, const SVec3* res);
    void TEST_MATH_CombineMatrixTransformation(const Matrix* m, const Matrix* n, const Matrix* res);
    void TEST_MATH_MatrixMultiplication(const Matrix* m, const Matrix* n, const Matrix* res);
#else
    #define TEST_MATH_Sin(angle, res)
    #define TEST_MATH_Cos(angle, res)
    #define TEST_MATH_Sqrt(n, shift, res)
    #define TEST_MATH_GetInverseMatrixTransformation(matrix, res)
    #define TEST_MATH_VectorLength(vector, res)
    #define TEST_MATH_VectorNormalize(vector, res)
    #define TEST_MATH_CombineMatrixTransformation(m, n, res)
    #define TEST_MATH_MatrixMultiplication(m, n, res)
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

#endif