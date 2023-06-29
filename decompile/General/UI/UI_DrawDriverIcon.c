#include <common.h>

void DECOMP_UI_DrawDriverIcon(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, char transparency, short scale, u_int color)
{
	POLY_FT4* p = (POLY_FT4*)primMem->curr;
	addPolyFT4(ot, p);

	unsigned int width = icon->texLayout.u1 - icon->texLayout.u0;
	unsigned int height = icon->texLayout.v2 - icon->texLayout.v0;
	unsigned int rightX = posX + FP_Mult(width, scale);
	#if BUILD != EurRetail
		unsigned int topY = (posY < 166) ? posY : 165;
		unsigned int bottomY = ((posY + FP_Mult(height, scale)) < 166) ? (posY + FP_Mult(height, scale)) : 165;
	#else
		unsigned int topY = (posY < 176) ? posY : 175;
		unsigned int bottomY = ((posY + FP_Mult(height, scale)) < 176) ? (posY + FP_Mult(height, scale)) : 175;
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