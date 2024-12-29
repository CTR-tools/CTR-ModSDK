#include <common.h>

int DECOMP_SelectProfile_UI_ConvertY(int param_1, int param_2)
{
	param_2 = (param_1 + -0x6c) * param_2;
	if (param_2 < 0) {
		param_2 = param_2 + 0xff;
	}
	return param_2 >> 8;
}