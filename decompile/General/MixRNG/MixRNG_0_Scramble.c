#include <common.h>

int DECOMP_MixRNG_Scramble()
{
	// random algorithm for seemingly-random numbers
	sdata->randomNumber = sdata->randomNumber * 0x6255 + 0x3619 & 0xffff;
	return sdata->randomNumber;
}