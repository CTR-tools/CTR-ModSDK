#include <common.h>

void DECOMP_RECTMENU_DrawOuterRect_Edge(RECT* r, Color color, u_int param_3, u_long * otMem)
{
	param_3 & 0x20 ?
	DECOMP_CTR_Box_DrawClearBox(r, color, TRANS_50_DECAL, otMem) :
	DECOMP_CTR_Box_DrawSolidBox(r, color, otMem);
}