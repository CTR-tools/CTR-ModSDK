#include <common.h>

void DECOMP_MEMPACK_SwapPacks(int index)
{
	sdata->PtrMempack = &sdata->mempack[index];
	return;
}