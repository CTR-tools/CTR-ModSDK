#include <common.h>

void DECOMP_RECTMENU_DrawPolyGT4(
	struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, 
	u_int color0, u_int color1, u_int color2, u_int color3, char transparency, short scale)
{
	if(!icon) return;
	
	DECOMP_DecalHUD_DrawPolyGT4(
		icon, posX, posY, primMem, ot,
		color0, color1, color2, color3, transparency, scale);
}