#include <common.h>

void DECOMP_UI_DrawDriverIcon(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, char transparency, int scale, u_int color)
{
	POLY_FT4* p = (POLY_FT4*)primMem->curr;
	addPolyFT4(ot, p);

	unsigned int width = icon->texLayout.u1 - icon->texLayout.u0;
	unsigned int height = icon->texLayout.v2 - icon->texLayout.v0;
	unsigned int rightX = posX + (width * scale / 0x1000);
	#if BUILD != EurRetail
		unsigned int topY = (posY < 166) ? posY : 165;
		unsigned int bottomY = ((posY + (height * scale / 0x1000)) < 166) ? (posY + (height * scale / 0x1000)) : 165;
	#else
		unsigned int topY = (posY < 176) ? posY : 175;
		unsigned int bottomY = ((posY + (height * scale / 0x1000)) < 176) ? (posY + (height * scale / 0x1000)) : 175;
	#endif
	unsigned int bottomV = (icon->texLayout.v0 + bottomY) - posY;

	setXY4(p, posX, topY, rightX, topY, posX, bottomY, rightX, bottomY);
	setUV4(p, icon->texLayout.u0, icon->texLayout.v0, icon->texLayout.u1, icon->texLayout.v1, icon->texLayout.u2, bottomV, icon->texLayout.u3, bottomV);
	p->clut = icon->texLayout.clut;
	p->tpage = icon->texLayout.tpage;
	setColor0(p, color);

	if (transparency)
	{
		setTransparency(p, transparency);
	}
	
	primMem->curr = p + 1;

	return;
}