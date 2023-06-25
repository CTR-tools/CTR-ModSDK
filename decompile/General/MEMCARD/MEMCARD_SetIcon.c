#include <common.h>

void DECOMP_MEMCARD_SetIcon(int icon)
{
	int* dst;
	int* src;
	int i;
	
	// overwrite psyqHand
	dst = &data.memcardIcon_PsyqHand[0];
	
	// if ghost
	if(icon == 0)
	{
		src = &data.memcardIcon_Ghost[0];
	}
	
	// if crash head
	else
	{
		src = &data.memcardIcon_CrashHead[0];
	}
	
	// aligned copy, reduce loop jumps
	for(i = 0; i < 0x40; i+= 4)
	{
		dst[i+0] = src[i+0];
		dst[i+1] = src[i+1];
		dst[i+2] = src[i+2];
		dst[i+3] = src[i+3];
	}
}