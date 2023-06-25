#include <common.h>

int DECOMP_LOAD_IsOpen_RacingOrBattle()
{
	return sdata->gGT->overlayIndex_Threads == 1;
}