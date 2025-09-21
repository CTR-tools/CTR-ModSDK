#include <ctr/test.h>

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
    *seedAddr = e_gameTracker->seed;
}

void TEST_RNG_RandInt(u32 n, s32 ret)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_RNG_RandInt));
    e_gameTracker->seed = *(RNGSeed*) BACKUP_ADDR;
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