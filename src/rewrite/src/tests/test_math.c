#include <ctr/test.h>

#ifdef TEST_MATH_IMPL

#pragma region MATH_Sin
void TEST_MATH_Sin(u32 angle, s32 ret)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_MATH_Sin), "MATH_Sin");
    const s32 expected = ND_MATH_Sin(angle);
    if (expected != ret) { ND_printf("[%s] Test Failed:\nInput: %d\nExpected: %d\nResult: %d\n", s_nameTestedFunc, angle, expected, ret); }
    PatchFunction_End(index);
}
#pragma endregion

#pragma region MATH_Cos
void TEST_MATH_Cos(u32 angle, s32 ret)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_MATH_Cos), "MATH_Cos");
    const s32 expected = ND_MATH_Cos(angle);
    if (expected != ret) { ND_printf("[%s] Test Failed:\nInput: %d\nExpected: %d\nResult: %d\n", s_nameTestedFunc, angle, expected, ret); }
    PatchFunction_End(index);
}
#pragma endregion

#pragma region MATH_Sqrt
void TEST_MATH_Sqrt(u32 n, u32 shift, u32 ret)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_MATH_Sqrt), "MATH_Sqrt");
    const u32 expected = ND_MATH_Sqrt(n, shift);
    if (expected != ret) { ND_printf("[%s] Test Failed:\nInput: %d %d\nExpected: %d\nResult: %d\n", s_nameTestedFunc, n, shift, expected, ret); }
    PatchFunction_End(index);
}
#pragma endregion

#pragma region MATH_GetInverseMatrixTransformation
void TEST_MATH_GetInverseMatrixTransformation(const Matrix* matrix, const Matrix* ret)
{
    Matrix out;
    const u32 index = PatchFunction_Beg((u32*)(&ND_MATH_GetInverseMatrixTransformation), "MATH_GetInverseMatrixTransformation");
    ND_MATH_GetInverseMatrixTransformation(&out, matrix);
	TEST_PrintMatrixDiff(&out, ret, true);
    PatchFunction_End(index);
}
#pragma endregion

#pragma region MATH_VectorLength
void TEST_MATH_VectorLength(const SVec3* vector, s32 ret)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_MATH_VectorLength), "MATH_VectorLength");
    const s32 expected = ND_MATH_VectorLength(vector);
    if (expected != ret) { ND_printf("[%s] Test Failed:\nInput: %d %d %d\nExpected: %d\nResult: %d\n", s_nameTestedFunc, vector->x, vector->y, vector->z, expected, ret); }
    PatchFunction_End(index);
}
#pragma endregion

#pragma region MATH_VectorNormalize
void TEST_MATH_VectorNormalize(SVec3* vector, const SVec3* ret)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_MATH_VectorNormalize), "MATH_VectorNormalize");
    ND_MATH_VectorNormalize(vector);
	TEST_PrintSVectorDiff(vector, ret);
    PatchFunction_End(index);
}
#pragma endregion

#pragma region MATH_CombineMatrixTransformation
void TEST_MATH_CombineMatrixTransformation(const Matrix* m, const Matrix* n, const Matrix* ret)
{
    Matrix expected;
    const u32 index = PatchFunction_Beg((u32*)(&ND_MATH_CombineMatrixTransformation), "MATH_CombineMatrixTransformation");
    ND_MATH_CombineMatrixTransformation(&expected, m, n);
	TEST_PrintMatrixDiff(&expected, ret, true);
    PatchFunction_End(index);
}
#pragma endregion

#pragma region MATH_MatrixMultiplication
void TEST_MATH_MatrixMultiplication(const Matrix* m, const Matrix* n, const Matrix* ret)
{
    Matrix expected;
    const u32 index = PatchFunction_Beg((u32*)(&ND_MATH_MatrixMultiplication), "MATH_MatrixMultiplication");
    ND_MATH_MatrixMultiplication(&expected, m, n);
	TEST_PrintMatrixDiff(&expected, ret, false);
    PatchFunction_End(index);
}
#pragma endregion

#endif // TEST_MATH_IMPL