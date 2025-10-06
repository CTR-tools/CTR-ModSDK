#include <ctr/test.h>

#ifdef TEST_RNG_IMPL

void BACKUP_RNG_Rand()
{
	BDATA_RNG_Rand backup = {
		.e_seed = e_seed
	};
	BACKUP_PUSH(&backup, sizeof(backup));
}

void RESTORE_RNG_Rand(BDATA_RNG_Rand* restore)
{
	e_seed = restore->e_seed;
}

void TEST_RNG_Rand()
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_RNG_Rand), "RNG_Rand");

	BDATA_RNG_Rand* before = (BDATA_RNG_Rand*)BACKUP_PEEK(1, NULL);
	BDATA_RNG_Rand* resultFromDecomp = (BDATA_RNG_Rand*)BACKUP_PEEK(0, NULL);
	RESTORE_RNG_Rand(before);
    ND_RNG_Rand();
	BACKUP_RNG_Rand();
	BDATA_RNG_Rand* resultFromND = (BDATA_RNG_Rand*)BACKUP_PEEK(0, NULL);

	bool failedGlobalState = TEST_Memcmp(resultFromDecomp, resultFromND, sizeof(BDATA_RNG_Rand));

	BACKUP_POP_MULTIPLE(3);

	if (failedGlobalState) { ND_printf("[%s] Test Failed (global state mismatch)\n", s_nameTestedFunc); }
    if (resultFromND->e_seed != resultFromDecomp->e_seed) { ND_printf("[%s] Test Failed:\nExpected: %d\nResult: %d\n", s_nameTestedFunc, resultFromND->e_seed, resultFromDecomp->e_seed); }
    PatchFunction_End(index);
}

void BACKUP_RNG_RandInt()
{
	BDATA_RNG_RandInt backup = {
		.e_gameTracker_seed = e_gameTracker->seed
	};
	BACKUP_PUSH(&backup, sizeof(backup));
}

void RESTORE_RNG_RandInt(BDATA_RNG_RandInt* restore)
{
	e_gameTracker->seed = restore->e_gameTracker_seed;
}

void TEST_RNG_RandInt(u32 n, s32 ret)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_RNG_RandInt), "RNG_RandInt");

	BDATA_RNG_RandInt* before = (BDATA_RNG_RandInt*)BACKUP_PEEK(1, NULL);
	BDATA_RNG_RandInt* resultFromDecomp = (BDATA_RNG_RandInt*)BACKUP_PEEK(0, NULL);
	RESTORE_RNG_RandInt(before);
    const s32 expected = ND_RNG_RandInt(n);
	BACKUP_RNG_RandInt();
	BDATA_RNG_RandInt* resultFromND = (BDATA_RNG_RandInt*)BACKUP_PEEK(0, NULL);

	bool failedGlobalState = TEST_Memcmp(resultFromDecomp, resultFromND, sizeof(BDATA_RNG_RandInt));

	BACKUP_POP_MULTIPLE(3);

	if (failedGlobalState) { ND_printf("[%s] Test Failed (global state mismatch)\n", s_nameTestedFunc); }
    if (expected != ret) { ND_printf("[%s] Test Failed:\nExpected: %d\nResult: %d\n", s_nameTestedFunc, expected, ret); }
    PatchFunction_End(index);
}

void TEST_RNG_PseudoRand(u16 n, u16 ret)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_RNG_PseudoRand), "RNG_PseudoRand");
    const u16 expected = ND_RNG_PseudoRand(n);
    if (expected != ret) { ND_printf("[%s] Test Failed:\nExpected: %d\nResult: %d\n", s_nameTestedFunc, expected, ret); }
    PatchFunction_End(index);
}

void TEST_RNG_Random(RNGSeed* seed, const RNGSeed* ret)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_RNG_Random), "RNG_Random");
    const u32 expected = ND_RNG_Random(seed);
    if (seed->a != ret->a) { ND_printf("[%s] Test Failed:\nseed->a: %d\nret->a: %d\n", s_nameTestedFunc, seed->a, ret->a); }
    if (seed->b != ret->b) { ND_printf("[%s] Test Failed:\nseed->b: %d\nret->b: %d\n", s_nameTestedFunc, seed->b, ret->b); }
    if (expected != ret->b) { ND_printf("[%s] Test Failed:\nExpected: %d\nret: %d\n", s_nameTestedFunc, expected, ret->b); }
    PatchFunction_End(index);
}

#endif // TEST_RNG_IMPL