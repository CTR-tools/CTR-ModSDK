#include <common.h>

int DECOMP_MixRNG_Particles(int param_1)
{
	//this decomp and/or MixRNG_2_GetValue.c is buggy
	u_int uVar1;

	uVar1 = SquareRoot0_stub(sdata->gGT->deadcoed_struct.unk1);
	return (int)((uVar1 & 0xffff) * param_1) >> 0x10;
}