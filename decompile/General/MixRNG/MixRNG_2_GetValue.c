#include <common.h>

u_int MixRNG_GetValue(int param_1)
{
	//this decomp and/or MixRNG_1_Particles.c is buggy
	//I'm pretty sure this one is fine.
	return param_1 * 0x6255 + 0x3619U & 0xffff;
}