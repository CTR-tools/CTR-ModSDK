#include <ctr/test.h>
#include <ctr/test_backup.h>

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
    TEST_FUNC(COLL_TestLeaf_Quadblock),
};

const char* s_nameTestedFunc = nullptr;

void TEST_Init()
{
	BACKUP_INIT();
	TEST_LoadPatches();
}

bool TEST_Memcmp(const void* expected, const void* actual, u32 n)
{
	bool failed = false;
	const u8* pExpected = (const u8*)expected;
	const u8* pActual = (const u8*)actual;
	for (u32 i = 0; i < n; i++)
	{
		if (pExpected[i] != pActual[i]) { ND_printf("[%s] Test Failed:\nOffset %x: %d, got: %d\n", s_nameTestedFunc, i, (u32)pExpected[i], (u32)pActual[i]); failed = true; }
	}
	return failed;
}

void TEST_LoadPatches()
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
    FlushCache();
}

u32 PatchFunction_Beg(u32* address, const char* funcName)
{
    u32 addr = (u32)address;
    s_nameTestedFunc = funcName;
    __asm__ volatile("move $k1, %0" : : "r"(addr));

    u32 index = U32_MAX;
    const u32 funcCount = ARR_LEN(s_functions);
    for (u32 i = 0; i < funcCount; i++)
    {
        if (address == s_functions[i].address)
        {
            index = i;
            *(s_functions[i].address) = s_functions[i].firstInst;
            *(s_functions[i].address + 1) = s_functions[i].secondInst;
            FlushCache();
            break;
        }
    }
    return index;
}

void PatchFunction_End(u32 index)
{
    if (index == U32_MAX) { return; }
    *(s_functions[index].address) = s_functions[index].firstNewInst;
    *(s_functions[index].address + 1) = s_functions[index].secondNewInst;
    FlushCache();
}

u32 TEST_PrintSVectorDiff(const SVec3* expected, const SVec3* ret)
{
    u32 failed = 0;
    for (u32 i = 0; i < 3; i++)
    {
        if (expected->v[i] != ret->v[i])
        {
            failed = 1;
            ND_printf("[%s] Test Failed:\nv[%d] = %d, got %d\n", s_nameTestedFunc, i, expected->v[i], ret->v[i]);
        }
    }
    return failed;
}

u32 TEST_PrintMatrixDiff(const Matrix* expected, const Matrix* ret, u32 cmpTrans)
{
    u32 failed = 0;
    for (u32 i = 0; i < 3; i++)
    {
        for (u32 j = 0; j < 3; j++)
        {
            if (expected->m[i][j] != ret->m[i][j])
            {
                failed = 1;
                ND_printf("[%s] Test Failed:\nm[%d][%d] = %d, got %d\n", s_nameTestedFunc, i, j, expected->m[i][j], ret->m[i][j]);
            }
        }
        if ((cmpTrans) && (expected->t.v[i] != ret->t.v[i]))
        {
            failed = 1;
            ND_printf("[%s] Test Failed:\nt[%d] = %d, got %d\n", s_nameTestedFunc, i, expected->t.v[i], ret->t.v[i]);
        }
    }
    return failed;
}