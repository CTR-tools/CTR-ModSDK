#include <common.h>

void DECOMP_RefreshCard_Unknown1(void)
{
	sdata->memcardUnk1 = sdata->memcardUnk1 & 0xfffffff7 | 6;
}