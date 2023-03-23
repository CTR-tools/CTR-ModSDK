#include <common.h>

void CTR_Box_DrawSolidBox(RECT* r, u_int rgb, u_long* otMem, struct PrimMem* primMem);
void CTR_Box_DrawClearBox(RECT* r, u_int rgb, int param_3, u_long* otMem, struct PrimMem* primMem);

void DECOMP_MenuBox_DrawOuterRect_Edge(RECT* r, u_int rgb, u_int param_3, u_long* otMem)
{
	if ((param_3 & 0x20) == 0)
	{
		// solid border
		CTR_Box_DrawSolidBox(r, rgb, otMem, &sdata->gGT->backBuffer->primMem);
	}
	else
	{
		// transparent border
		CTR_Box_DrawClearBox(r, rgb, 1, otMem, &sdata->gGT->backBuffer->primMem);
	}
	return;
}