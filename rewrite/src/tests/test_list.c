#include <ctr/test.h>

#ifdef TEST_LIST_IMPL

#pragma region LIST_Init
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

void BACKUP_LIST_Init(const void* source)
{

}

void RESTORE_LIST_Init(BDATA_LIST_Init* restore, void* destination)
{

}

void TEST_LIST_Init(LinkedList* list, Item* item, s32 itemSize, s32 numItems)
{
	const u32 index = PatchFunction_Beg((u32*)(&ND_LIST_Init), "LIST_Init");
}
#pragma endregion

#endif //TEST_LIST_IMPL