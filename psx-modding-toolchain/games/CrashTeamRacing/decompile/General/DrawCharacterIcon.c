#include <common.h>

void DECOMP_DrawCharacterIcon(struct Icon* icon, short posX, int posY, struct PrimMem* primMem, void *ot, u_char semitransparencyEnabled, short scale, u_int vcolorAndCode)
{
	u_char x1;
	u_char x0;
	u_char y2;
	u_char y0;
	u_short bottomRightCorner;
	int iVar6;
	int height;
	int width;
	POLY_FT4 *p;

	// PrimMem->curr
	p = (POLY_FT4*)primMem->curr;

	x1 = icon->X2;
	x0 = icon->X1;
	y2 = icon->Y3;
	y0 = icon->Y1;

	// vertex color and code
	*(u_int*)&p->r0 = vcolorAndCode;

	// UVs and CLUT
	*(u_int*)&p->u0 = *(u_int*)&icon->X1;

	// UVs and texpage
	*(u_int*)&p->u1 = *(u_int*)&icon->X2;

	width = (u_int)x1 - (u_int)x0;

	// UVs and... pad1?
	*(u_int*)&p->u2 = *(u_int*)&icon->X3;

	bottomRightCorner = *(u_short*)&icon->X4;
	p->x0 = posX;
	*(u_short*)&p->u3 = bottomRightCorner;

	height = (u_int)y2 - (u_int)y0;

	if (posY < 0xa6)
	{
		p->y0 = (short)posY;
	}

	else
	{
		p->y0 = 0xa5;
	}

	p->x1 = posX + (short)(width * scale >> 0xc);

	if (posY < 0xa6)
	{
		p->y1 = (short)posY;
	}

	else
	{
		p->y1 = 0xa5;
	}

	iVar6 = posY + (height * scale >> 0xc);
	p->x2 = posX;

	if (iVar6 < 0xa6)
	{
		p->y2 = (short)iVar6;
	}

	else
	{
		p->y2 = 0xa5;
	}

	p->x3 = posX + (short)(width * scale >> 0xc);
	height = posY + (height * scale >> 0xc);

	if (height < 0xa6)
	{
		p->y3 = (short)height;
	}

	else
	{
		p->y3 = 0xa5;
	}

	setPolyFT4(p);

	p->v2 = (p->v0 + *(u_char*)&p->y2) - (char)posY;
	p->v3 = (p->v0 + *(u_char*)&p->y3) - (char)posY;

	if (semitransparencyEnabled != 0)
	{
		p->tpage = p->tpage & 0xff9f | ((u_short)semitransparencyEnabled - 1) * 0x20;
		p->code = p->code | 2;
	}

	AddPrim(ot, p);

	// POLY_FT4 is 0x28 bytes large
	primMem->curr = p + 1;

	return;
}