#include <common.h>

void DECOMP_DecalHUD_DrawPolyGT4(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, u_int color0, u_int color1, u_int color2, u_int color3, char transparency, int scale)
{
	#if BUILD > SepReview
		if (!icon) return;
	#endif

	// setInt32RGB4 needs to go before addPolyGT4
	// for more information check "temporaryrevampedgpuheader.h"
	POLY_GT4* p = (POLY_GT4*)primMem->curr;
	setInt32RGB4(p, color0, color1, color2, color3);
	addPolyGT4(ot, p);

	unsigned int width = icon->texLayout.u1 - icon->texLayout.u0;
	unsigned int height = icon->texLayout.v2 - icon->texLayout.v0;
	unsigned int rightX = posX + (width * scale / 0x1000);
	unsigned int bottomY = posY + (height * scale / 0x1000);

	setXY4(p, posX, posY, rightX, posY, posX, bottomY, rightX, bottomY);
	setIconUV(p, icon);
	if (transparency)
	{
		setTransparency(p, transparency);
	}

	primMem->curr = p + 1;
}