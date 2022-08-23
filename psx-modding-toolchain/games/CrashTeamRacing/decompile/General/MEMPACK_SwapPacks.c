#include <common.h>

void DECOMP_MEMPACK_SwapPacks(int index)
{
	register struct sData* sdata asm("gp"); // r28
	sdata->PtrMempack = &sdata->mempack[index];
	return;
}