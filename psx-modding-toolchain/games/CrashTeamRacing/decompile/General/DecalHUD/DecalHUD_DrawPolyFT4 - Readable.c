#include <common.h>

void DECOMP_DecalHUD_DrawPolyFT4(struct Icon* icon, int posX, int posY, struct PrimMem* primMem, u_long* ot, char transparency, short scale)
{
	short width;
	short height;
	short rightX;
	short bottomY;
	POLY_FT4* p;

	if (!icon) return;

	p = (POLY_FT4*)primMem->curr;

	width = icon->X2 - icon->X1;
	height = icon->Y3 - icon->Y1;
	rightX = posX + (width * scale / 0x1000);
	bottomY = posY + (height * scale / 0x1000);

	// this function doesn't support coloring the primitives
	setPolyFT4(p);
	setShadeTex(p, true);
	setXY4(p, posX, posY, rightX, posY, posX, bottomY, rightX, bottomY);
	setUV4(p, icon->X1, icon->Y1, icon->X2, icon->Y2, icon->X3, icon->Y3, icon->X4, icon->Y4);
	p->clut = icon->paletteXY;
	p->tpage = icon->pageXY;

	if (transparency != 0)
	{
		// disable blending mode bits of the texpage using AND, then set them using OR
		// then set image to use semi-transparent mode using the setSemiTrans macro

		p->tpage = p->tpage & 0xff9f | (transparency - 1) << 5;
		setSemiTrans(p, true);
	}

	addPrim(ot, p);

	// POLY_FT4 is 0x28 bytes large
	primMem->curr = p + 1;
	return;
}