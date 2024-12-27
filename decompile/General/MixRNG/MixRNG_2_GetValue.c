#include <common.h>

u_int MixRNG_GetValue(int param_1)
{
	return param_1 * 0x6255 + 0x3619U & 0xffff;
}