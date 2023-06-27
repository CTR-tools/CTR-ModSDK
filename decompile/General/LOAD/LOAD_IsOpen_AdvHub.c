#include <common.h>

int DECOMP_LOAD_IsOpen_AdvHub()
{
	return sdata->gGT->overlayIndex_Threads == 2;
}