#include <common.h>

int LOAD_IsOpen_RacingOrBattle()
{
	return sdata->gGT->overlayIndex_Threads == 1;
}