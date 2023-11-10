#include <common.h>

void DECOMP_howl_ErasePtrCseqHeader()
{
	// can not play a song anymore
	sdata->ptrCseqHeader = 0;
}