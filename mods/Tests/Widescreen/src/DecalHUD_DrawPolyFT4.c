#include <common.h>

void DECOMP_DecalHUD_DrawPolyFT4(struct Icon* icon, int posX, int posY, struct PrimMem* primMem, u_long* ot, char semitransparencyEnabled, short scale)
{
	u_char y2;
	u_short bottomRightCorner;
	u_int topRightCornerAndPageXY;
	u_int topLeftCornerAndPaletteXY;
	POLY_FT4 *p;
	u_int bitshiftPosY;
	u_int bottomMargin;
	int len;

	if (icon != 0)
	{
		topRightCornerAndPageXY = *(u_int*)&icon->texLayout.u1;
		topLeftCornerAndPaletteXY = *(u_int*)&icon->texLayout.u0;
		y2 = icon->texLayout.v2;

		// posY, bitshifted 2 bytes
		bitshiftPosY = posY * 0x10000;

		bottomMargin = *(u_int*)&icon->texLayout.u2;

		p = (POLY_FT4*)primMem->curr;

		// if semitransparencyEnabled == 0,
		// except made default...

		p->code = 0x2d;
		*(int*)&p->u1 = topRightCornerAndPageXY;

		if (semitransparencyEnabled != 0)
		{
			p->code = 0x2f;

			// set top right corner UVs and texpage of primitive, and alter the blending mode bits of the texpage from 11 (Mode 3, which is no blending) to 00 (Mode 0, equivalent to regular 50% opacity)
			// note that these blending modes are different from those used in UI_Map_DrawMap
			*(int*)&p->u1 =
				topRightCornerAndPageXY & 0xff9fffff |
				((u_int)semitransparencyEnabled - 1) * 0x200000;
		}

		*(int*)&p->u0 = topLeftCornerAndPaletteXY;
		*(short*)&p->u2 = (short)bottomMargin;
		bottomRightCorner = *(u_short*)&icon->texLayout.u3;

		// calculate final position of top right vertex of primitive
		// posX + (endX - startX) * scale / 0x1000
		topRightCornerAndPageXY =
			posX + ((int)(((topRightCornerAndPageXY & 0xff) -
					(topLeftCornerAndPaletteXY & 0xff)) * (int)scale) >> 0xc);
					
		// widescreen, need to scale X by 75%,
		// so subtract 12% from left and 12% from right
		len = ((topRightCornerAndPageXY - posX) * 125) / 1000;
		posX += len;
		topRightCornerAndPageXY -= len;

		*(int*)&p->x0 = posX | bitshiftPosY;
		*(int*)&p->x1 = topRightCornerAndPageXY | bitshiftPosY;

		// posY +=
		bitshiftPosY += ((int)(
		(
			(u_int)y2 -

			// top left Y
			((int)topLeftCornerAndPaletteXY >> 8 & 0xffU)) *

			// * scale / 0x1000
			(int)scale) >> 0xc
		) *

		// bitshift up 2 bytes
		0x10000;

		*(int*)&p->x2 = posX | bitshiftPosY;
		*(int*)&p->x3 = topRightCornerAndPageXY | bitshiftPosY;
		*(u_short *)&p->u3 = bottomRightCorner;

		// link prim and OT together
		*(int*)p = *ot | 0x9000000;
		*ot = (u_int)p & 0xffffff;

		// POLY_FT4 is 0x28 bytes large
		primMem->curr = p + 1;
	}
	return;
}
