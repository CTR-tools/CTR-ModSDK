#ifndef TEST_H
#define TEST_H

#include <ctr/macros.h>
#include <ctr/math.h>
#include <ctr/redux.h>

void LoadTestPatches();

#define TEST_MATH_IMPL

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

#endif