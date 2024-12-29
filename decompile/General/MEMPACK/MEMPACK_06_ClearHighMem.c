#include <common.h>

void DECOMP_MEMPACK_ClearHighMem()
{
	// reset end-side allocation
	sdata->PtrMempack->lastFreeByte = sdata->PtrMempack->endOfAllocator;
}