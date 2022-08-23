#include <common.h>

void DECOMP_MEMPACK_ClearHighMem()
{
	register struct sData* sdata asm("gp"); // r28

	// reset end-side allocation
	sdata->PtrMempack->lastFreeByte = sdata->PtrMempack->endOfAllocator;
}