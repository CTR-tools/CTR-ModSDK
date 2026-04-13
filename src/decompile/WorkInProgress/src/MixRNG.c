#include <common.h>

int DECOMP_MixRNG_Scramble()
{
	// random algorithm for seemingly-random numbers
	sdata->randomNumber = sdata->randomNumber * 0x6255 + 0x3619 & 0xffff;
	return sdata->randomNumber;
}
int DECOMP_MixRNG_Particles(int seed)
{
  return (int)((RngDeadCoed(sdata->gGT->deadcoed_struct.unk1 & 0xffff) * seed) >> 0x10);
}

u_int DECOMP_MixRNG_GetValue(int val)
{
  return val * 0x6255 + 0x3619U & 0xffff;
}