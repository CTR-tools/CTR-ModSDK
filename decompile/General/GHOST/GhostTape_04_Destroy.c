#include <common.h>

void DECOMP_GhostTape_Destroy()
{
	if(sdata->ptrGhostTapePlaying != 0)
	{
		sdata->ptrGhostTapePlaying = 0;
		DECOMP_MEMPACK_ClearHighMem();
	}
}