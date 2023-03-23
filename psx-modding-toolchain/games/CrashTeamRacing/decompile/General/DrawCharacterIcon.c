#include <common.h>

void DECOMP_DrawCharacterIcon(struct Icon* icon, int posX, int posY, struct PrimMem* primMem, u_long* ot, char semitransparencyEnabled, short scale, u_int vcolorAndCode)
{
	short iVar6;
	short height;
	short width;
	POLY_FT4* p;

	p = (POLY_FT4*)primMem->curr;

	// vertex color and code
	*(u_int*)&p->r0 = vcolorAndCode;

	setPolyFT4(p);

	// UVs and CLUT
	*(u_int*)&p->u0 = *(u_int*)&icon->X1;

	// UVs and texpage
	*(u_int*)&p->u1 = *(u_int*)&icon->X2;

	width = icon->X2 - icon->X1;

	// UVs and... pad1?
	*(u_int*)&p->u2 = *(u_int*)&icon->X3;

	p->x0 = posX;
	p->u3 = icon->X4;

	height = icon->Y3 - icon->Y1;

	if (posY < 166)
		p->y0 = posY;
	else
		p->y0 = 165;

	p->x1 = posX + (short)(width * scale >> 12);

	if (posY < 166)
		p->y1 = posY;
	else
		p->y1 = 165;

	iVar6 = posY + (height * scale >> 12);
	p->x2 = posX;

	if (iVar6 < 166)
		p->y2 = iVar6;
	else
		p->y2 = 165;

	p->x3 = posX + (short)(width * scale >> 12);
	height = posY + (height * scale >> 12);

	if (height < 166)
		p->y3 = (short)height;
	else
		p->y3 = 165;

	p->v2 = (p->v0 + *(u_char*)&p->y2) - (char)posY;
	p->v3 = (p->v0 + *(u_char*)&p->y3) - (char)posY;

	if (semitransparencyEnabled != 0)
	{
		// disable blending mode bits of the texpage using AND, then set them using OR
		// blending mode bits on most Icon images are set to 11 (Mode 3, which is no blending)
		// this function is always called with this parameter set to 1 (which is Mode 0, equivalent to 50% transparency)
		// uh, I think so anyway, feel free to double check I guess

		// note that these blending modes are different from those used in Map_DrawMap
		p->tpage = p->tpage & 0xff9f | (semitransparencyEnabled - 1) << 5;
		p->code = p->code | 2;
	}

	// could also use the psn00bsdk macro, there is no difference
	AddPrim(ot, p);

	// POLY_FT4 is 0x28 bytes large
	primMem->curr = p + 1;

	return;
}
