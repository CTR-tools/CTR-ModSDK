#include <common.h>

int LOAD_IsOpen_AdvHub()
{
	return sdata->gGT->overlayIndex_Threads == 2;
}