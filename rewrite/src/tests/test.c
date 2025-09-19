#include <ctr/test.h>
#include <ctr/nd.h>

#define JMP(dest) ((((u32)dest) & 0x3FFFFFF) >> 2 | 0x8000000)
#define NOP 0x0

typedef struct FunctionPatch
{
    u32* address;
    u32* decomp;
    u32 firstInst;
    u32 secondInst;
    u32 firstNewInst;
    u32 secondNewInst;
} FunctionPatch;

#define TEST_FUNC(f) { .address = (u32*)(&ND_##f), .decomp = (u32*)(&f) }

FunctionPatch s_functions[] =
{
    TEST_FUNC(MATH_Sin),
    TEST_FUNC(MATH_Cos),
    TEST_FUNC(MATH_Sqrt),
    TEST_FUNC(MATH_GetInverseMatrixTransformation),
    TEST_FUNC(MATH_VectorLength),
    TEST_FUNC(MATH_VectorNormalize),
    TEST_FUNC(MATH_CombineMatrixTransformation),
    TEST_FUNC(MATH_MatrixMultiplication),
    TEST_FUNC(RNG_Rand),
    TEST_FUNC(RNG_RandInt),
    TEST_FUNC(RNG_PseudoRand),
    TEST_FUNC(RNG_Random),
};

void LoadTestPatches()
{
    const u32 funcCount = ARR_LEN(s_functions);
    for (u32 i = 0; i < funcCount; i++)
    {
        s_functions[i].firstInst = *(s_functions[i].address);
        s_functions[i].secondInst = *(s_functions[i].address + 1);
        s_functions[i].firstNewInst = JMP(s_functions[i].decomp);
        s_functions[i].secondNewInst = NOP;
        *(s_functions[i].address) = s_functions[i].firstNewInst;
        *(s_functions[i].address + 1) = s_functions[i].secondNewInst;
    }
}

static u32 PatchFunction_Beg(u32* address)
{
    u32 index = 0;
    const u32 funcCount = ARR_LEN(s_functions);
    for (u32 i = 0; i < funcCount; i++)
    {
        if (address == s_functions[i].address)
        {
            index = i;
            *(s_functions[i].address) = s_functions[i].firstInst;
            *(s_functions[i].address + 1) = s_functions[i].secondInst;
            break;
        }
    }
    return index;
}

static u32 PatchFunction_End(u32 index)
{
    *(s_functions[index].address) = s_functions[index].firstNewInst;
    *(s_functions[index].address + 1) = s_functions[index].secondNewInst;
}

static u32 PrintSVectorDiff(const char* name, const SVec3* expected, const SVec3* ret)
{
    u32 failed = 0;
    for (u32 i = 0; i < 3; i++)
    {
        if (expected->v[i] != ret->v[i])
        {
            failed = 1;
            ND_printf("[%s] Test Failed:\nv[%d] = %d, got %d\n", name, i, expected->v[i], ret->v[i]);
        }
    }
    return failed;
}

static u32 PrintMatrixDiff(const char* name, const Matrix* expected, const Matrix* ret, u32 cmpTrans)
{
    u32 failed = 0;
    for (u32 i = 0; i < 3; i++)
    {
        for (u32 j = 0; j < 3; j++)
        {
            if (expected->m[i][j] != ret->m[i][j])
            {
                failed = 1;
                ND_printf("[%s] Test Failed:\nm[%d][%d] = %d, got %d\n", name, i, j, expected->m[i][j], ret->m[i][j]);
            }
        }
        if ((cmpTrans) && (expected->t.v[i] != ret->t.v[i]))
        {
            failed = 1;
            ND_printf("[%s] Test Failed:\nt[%d] = %d, got %d\n", name, i, expected->t.v[i], ret->t.v[i]);
        }
    }
    return failed;
}

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

#ifdef TEST_RNG_IMPL

void BACKUP_RNG_Rand()
{
    u32* seedAddr = (u32*) BACKUP_ADDR;
    *seedAddr = e_seed;
}

void TEST_RNG_Rand()
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_RNG_Rand));
    const u32 ret = e_seed;
    e_seed = *(u32*) BACKUP_ADDR;
    ND_RNG_Rand();
    if (e_seed != ret) { ND_printf("[RNG_Rand] Test Failed:\nExpected: %d\nResult: %d\n", e_seed, ret); }
    PatchFunction_End(index);
}

void BACKUP_RNG_RandInt()
{
    RNGSeed* seedAddr = (RNGSeed*) BACKUP_ADDR;
    *seedAddr = e_gameTrackerSeed;
}

void TEST_RNG_RandInt(u32 n, s32 ret)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_RNG_RandInt));
    e_gameTrackerSeed = *(RNGSeed*) BACKUP_ADDR;
    const s32 expected = ND_RNG_RandInt(n);
    if (expected != ret) { ND_printf("[RNG_RandInt] Test Failed:\nExpected: %d\nResult: %d\n", expected, ret); }
    PatchFunction_End(index);
}

void TEST_RNG_PseudoRand(u16 n, u16 ret)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_RNG_PseudoRand));
    const u16 expected = ND_RNG_PseudoRand(n);
    if (expected != ret) { ND_printf("[RNG_PseudoRand] Test Failed:\nExpected: %d\nResult: %d\n", expected, ret); }
    PatchFunction_End(index);
}

void TEST_RNG_Random(RNGSeed* seed, const RNGSeed* ret)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_RNG_Random));
    const u32 expected = ND_RNG_Random(seed);
    if (seed->a != ret->a) { ND_printf("[RNG_Random] Test Failed:\nseed->a: %d\nret->a: %d\n", seed->a, ret->a); }
    if (seed->b != ret->b) { ND_printf("[RNG_Random] Test Failed:\nseed->b: %d\nret->b: %d\n", seed->b, ret->b); }
    if (expected != ret->b) { ND_printf("[RNG_Random] Test Failed:\nExpected: %d\nret: %d\n", expected, ret->b); }
    PatchFunction_End(index);
}

#endif // TEST_RNG_IMPL
