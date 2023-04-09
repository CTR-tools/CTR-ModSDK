#include <common.h>

void DECOMP_DecalHUD_DrawPolyFT4(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, char transparency, int scale)
{
	if (!icon) return;

	POLY_FT4* p = (POLY_FT4*)primMem->curr;
	addPolyFT4(ot, p);

	// this function doesn't support coloring the primitives
	setShadeTex(p, true);

	unsigned int width = icon->texLayout.u1 - icon->texLayout.u0;
	unsigned int height = icon->texLayout.v2 - icon->texLayout.v0;
	unsigned int rightX = posX + (width * scale / 0x1000);
	unsigned int bottomY = posY + (height * scale / 0x1000);

	setXY4(p, posX, posY, rightX, posY, posX, bottomY, rightX, bottomY);
	setIconUV4(p, icon);
	if (transparency)
	{
		setTransparency(p, transparency);
	}

	primMem->curr = p + 1;
}