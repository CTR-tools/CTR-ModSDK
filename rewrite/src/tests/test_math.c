#include <ctr/test.h>

#ifdef TEST_MATH_IMPL

void TEST_MATH_Sin(u32 angle, s32 ret)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_MATH_Sin));
    const s32 expected = ND_MATH_Sin(angle);
    if (expected != ret) { ND_printf("[MATH_Sin] Test Failed:\nInput: %d\nExpected: %d\nResult:%d\n", angle, expected, ret); }
    PatchFunction_End(index);
}

void TEST_MATH_Cos(u32 angle, s32 ret)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_MATH_Cos));
    const s32 expected = ND_MATH_Cos(angle);
    if (expected != ret) { ND_printf("[MATH_Cos] Test Failed:\nInput: %d\nExpected: %d\nResult:%d\n", angle, expected, ret); }
    PatchFunction_End(index);
}

void TEST_MATH_Sqrt(u32 n, u32 shift, u32 ret)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_MATH_Sqrt));
    const u32 expected = ND_MATH_Sqrt(n, shift);
    if (expected != ret) { ND_printf("[MATH_Sqrt] Test Failed:\nInput: %d %d\nExpected: %d\nResult:%d\n", n, shift, expected, ret); }
    PatchFunction_End(index);
}

void TEST_MATH_GetInverseMatrixTransformation(const Matrix* matrix, const Matrix* ret)
{
    Matrix out;
    const u32 index = PatchFunction_Beg((u32*)(&ND_MATH_GetInverseMatrixTransformation));
    ND_MATH_GetInverseMatrixTransformation(&out, matrix);
    PrintMatrixDiff("MATH_GetInverseMatrixTransformation", &out, ret, true);
    PatchFunction_End(index);
}

void TEST_MATH_VectorLength(const SVec3* vector, s32 ret)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_MATH_VectorLength));
    const s32 expected = ND_MATH_VectorLength(vector);
    if (expected != ret) { ND_printf("[MATH_VectorLength] Test Failed:\nInput: %d %d %d\nExpected: %d\nResult:%d\n", vector->x, vector->y, vector->z, expected, ret); }
    PatchFunction_End(index);
}

void TEST_MATH_VectorNormalize(SVec3* vector, const SVec3* ret)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_MATH_VectorNormalize));
    ND_MATH_VectorNormalize(vector);
    PrintSVectorDiff("MATH_VectorNormalize", vector, ret);
    PatchFunction_End(index);
}

void TEST_MATH_CombineMatrixTransformation(const Matrix* m, const Matrix* n, const Matrix* ret)
{
    Matrix expected;
    const u32 index = PatchFunction_Beg((u32*)(&ND_MATH_CombineMatrixTransformation));
    ND_MATH_CombineMatrixTransformation(&expected, m, n);
    PrintMatrixDiff("MATH_CombineMatrixTransformation", &expected, ret, true);
    PatchFunction_End(index);
}

void TEST_MATH_MatrixMultiplication(const Matrix* m, const Matrix* n, const Matrix* ret)
{
    Matrix expected;
    const u32 index = PatchFunction_Beg((u32*)(&ND_MATH_MatrixMultiplication));
    ND_MATH_MatrixMultiplication(&expected, m, n);
    PrintMatrixDiff("MATH_MatrixMultiplication", &expected, ret, false);
    PatchFunction_End(index);
}

#endif // TEST_MATH_IMPL