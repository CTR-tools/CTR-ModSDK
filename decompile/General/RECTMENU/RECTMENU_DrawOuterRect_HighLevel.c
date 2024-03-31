#include <common.h>

void DECOMP_RECTMENU_DrawOuterRect_HighLevel(RECT* r, u_int* rgb, short param_3, u_long* otMem)
{
	DECOMP_RECTMENU_DrawOuterRect_LowLevel(r, 3, 2, rgb, param_3, otMem);
	return;
}