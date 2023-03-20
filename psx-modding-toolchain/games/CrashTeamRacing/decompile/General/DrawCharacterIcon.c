#include <common.h>

void DECOMP_DrawCharacterIcon(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, char semitransparencyEnabled, short scale, u_int color)
{
	short height;
	short width;
	short rightX;
	short topY;
	short bottomY;
	char bottomV;
	POLY_FT4* p;

	p = (POLY_FT4*)primMem->curr;

	width = icon->X2 - icon->X1;
	height = icon->Y3 - icon->Y1;
	rightX = posX + (width * scale >> 12);
	topY = posY;
	if (topY > 165) topY = 165;
	bottomY = posY + (height * scale >> 12);
	if (bottomY > 165) bottomY = 165;
	bottomV = (icon->Y1 + bottomY) - posY;

	setPolyFT4(p);
	setRGB0(p, color & 0xff, (color & 0xff00) >> 8, (color & 0xff0000) >> 16);
	setXY4(p, posX, topY, rightX, topY, posX, bottomY, rightX, bottomY);
	setUV4(p, icon->X1, icon->Y1, icon->X2, icon->Y2, icon->X3, bottomV, icon->X4, bottomV);
	p->clut = icon->paletteXY;
	p->tpage = icon->pageXY;

	if (semitransparencyEnabled != 0)
	{
		// disable blending mode bits of the texpage using AND, then set them using OR
		// then set image to use semi-transparent mode using the setSemiTrans macro
		// blending mode bits on most Icon images are set to 11 (Mode 3, which is no blending)
		// this function is always called with this parameter set to 1 (which is Mode 0, equivalent to 50% transparency)

		p->tpage = p->tpage & 0xff9f | (semitransparencyEnabled - 1) << 5;
		setSemiTrans(p, true);
	}

	// could also use the psn00bsdk macro, there is no difference
	AddPrim(ot, p);

	// POLY_FT4 is 0x28 bytes large
	primMem->curr = p + 1;

	return;
}