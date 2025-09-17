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

#ifdef TEST_MATH_IMPL
void TEST_MATH_Sin(u32 angle, s32 res)
{
    u32 index = PatchFunction_Beg((u32*)(&ND_MATH_Sin));
    s32 expected = ND_MATH_Sin(angle);
    if (expected == res) { ND_printf("[MATH_Sin] Test Passed!\n"); }
    else { ND_printf("[MATH_Sin] Test Failed:\nExpected: %d\nResult  :%d\n"); }
    PatchFunction_End(index);
}
#endif // TEST_MATH_IMPL