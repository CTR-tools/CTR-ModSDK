#include <common.h>

void DecalHUD_DrawPolyGT4_Expanded(struct Icon* icon, u_int posX, int posY, struct PrimMem* primMem, u_int* ot, u_int topLeftColor, u_int topRightColor, u_int bottomLeftColor, u_int bottomRightColor, short scale, u_char scaleY)
{
	u_char y2;
	u_int topRightCornerAndPageXY;
	u_int bitshiftPosY;

	POLY_GT4 *p;

	u_int topLeftCornerAndPaletteXY;
	u_int bottomMargin;

	if (icon != 0)
	{
		topRightCornerAndPageXY = *(u_int*)&icon->texLayout.u1;
		topLeftCornerAndPaletteXY = *(u_int*)&icon->texLayout.u0;
		y2 = icon->texLayout.v2;

		posX = posX & 0xffff;

		// posY, bitshifted 2 bytes
		bitshiftPosY = posY * 0x10000;

		bottomMargin = *(u_int*)&icon->texLayout.u2;

		p = (POLY_GT4*)primMem->curr;

		*(int*)&p->u1 = topRightCornerAndPageXY;

		// set top left vertex color, and code in 7th byte of prim
		*(int*)&p->r0 = topLeftColor & 0xffffff | 0x3c000000;

		*(int*)&p->u0 = topLeftCornerAndPaletteXY;
		*(short*)&p->u2 = (short)bottomMargin;

		// calculate final position of top right vertex of primitive
		// posX + (endX - startX) * scale / 0x1000
		topRightCornerAndPageXY =
			posX + ((int)(((topRightCornerAndPageXY & 0xff) -
					(topLeftCornerAndPaletteXY & 0xff)) * (int)scale) >> 0xc);

		*(int*)&p->x0 = posX | bitshiftPosY;
		*(int*)&p->x1 = topRightCornerAndPageXY | bitshiftPosY;

		// posY +=
		bitshiftPosY += ((int)(
		(
			(u_int)y2 -

			((int)topLeftCornerAndPaletteXY >> 8 & 0xffU)) *

			(int)scale) >> 0xc
		) *

		// bitshift up 2 bytes
		0x10000;

		*(int*)&p->x2 = posX | bitshiftPosY;
		*(int*)&p->x3 = topRightCornerAndPageXY | bitshiftPosY;
		*(u_short *)&p->u3 = *(u_short *)&icon->texLayout.u3;

		// color data from parameters
		*(int*)&p->r1 = topRightColor;
		*(int*)&p->r2 = bottomLeftColor;
		*(int*)&p->r3 = bottomRightColor;

		if(scaleY)
		{
			p->y0 += scaleY;
			p->y1 += scaleY;
		}

		// link prim and OT together
		*(int*)p = *ot | 0xc000000;
		*ot = (u_int)p & 0xffffff;

		// POLY_GT4 is 0x34 bytes large
		primMem->curr = p + 1;
	}
	return;
}