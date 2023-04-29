#include <common.h>

void DECOMP_UI_DrawDriverIcon(struct Icon* icon, int posX, int posY, struct PrimMem* primMem, u_long* ot, char transparency, short scale, u_int color)
{
	short width;
	short height;
	short rightX;
	short topY;
	short bottomY;
	char bottomV;
	POLY_FT4* p;

	p = (POLY_FT4*)primMem->curr;

	width = icon->texLayout.u1 - icon->texLayout.u0;
	height = icon->texLayout.v2 - icon->texLayout.v0;
	rightX = posX + (width * scale / 0x1000);
	#if BUILD != EurRetail
		topY = (posY < 166) ? posY : 165;
		bottomY = ((posY + (height * scale / 0x1000)) < 166) ? (posY + (height * scale / 0x1000)) : 165;
	#else
		topY = (posY < 176) ? posY : 175;
		bottomY = ((posY + (height * scale / 0x1000)) < 176) ? (posY + (height * scale / 0x1000)) : 175;
	#endif
	bottomV = (icon->texLayout.v0 + bottomY) - posY;

	setPolyFT4(p);
	setRGB0(p, color & 0xff, (color & 0xff00) >> 8, (color & 0xff0000) >> 16);
	setXY4(p, posX, topY, rightX, topY, posX, bottomY, rightX, bottomY);
	setUV4(p, icon->texLayout.u0, icon->texLayout.v0, icon->texLayout.u1, icon->texLayout.v1, icon->texLayout.u2, bottomV, icon->texLayout.u3, bottomV);
	p->clut = icon->texLayout.clut;
	p->tpage = icon->texLayout.tpage;

	if (transparency != 0)
	{
		// disable blending mode bits of the texpage using AND, then set them using OR
		// then set image to use semi-transparent mode using the setSemiTrans macro
		// this function is always called with this parameter set to 1 (which is Mode 0, equivalent to 50% transparency)

		p->tpage = p->tpage & 0xff9f | (transparency - 1) << 5;
		setSemiTrans(p, true);
	}

	// could also use the psn00bsdk macro, there is no difference
	AddPrim(ot, p);

	// POLY_FT4 is 0x28 bytes large
	primMem->curr = p + 1;

	return;
}