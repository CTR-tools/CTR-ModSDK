#include <common.h>

void DECOMP_DecalHUD_DrawPolyGT4(struct Icon* icon, u_int posX, int posY, struct PrimMem* primMem, u_int* ot, u_int topLeftColor, u_int topRightColor, u_int bottomLeftColor, u_int bottomRightColor, u_char semitransparencyEnabled, short scale)
{
	u_char y2;
	u_short bottomRightCorner;
	u_int code;
	u_int topRightCornerAndPageXY;
	u_int bitshiftPosY;

	POLY_GT4* p;

	u_int topLeftCornerAndPaletteXY;
	u_int bottomMargin;

	if (icon != 0)
	{
		topRightCornerAndPageXY = *(u_int*)&icon->X2;
		topLeftCornerAndPaletteXY = *(u_int*)&icon->X1;
		y2 = icon->Y3;

		posX = posX & 0xffff;

		// posY, bitshifted 2 bytes
		bitshiftPosY = posY << 16;

		bottomMargin = *(u_int*)&icon->X3;

		p = (POLY_GT4*)primMem->curr;

		// if semitransparencyEnabled == 0,
		// except made default...

		code = 0x3c000000;
		*(int*)&p->u1 = topRightCornerAndPageXY;

		if(semitransparencyEnabled != 0)
		{
			code = 0x3e000000;

			// disable blending mode bits of the texpage using AND, then set them using OR
			// blending mode bits on most Icon images are set to 11 (Mode 3, which is no blending)
			// this function is always called with this parameter set to 0 (disabled) or 1 (which is Mode 0, equivalent to 50% transparency)

			// note that these blending modes are different from those used in Map_DrawMap
			*(int*)&p->u1 =
				topRightCornerAndPageXY & 0xff9fffff |
				((u_int)semitransparencyEnabled - 1) << 21;
		}

		// set top left vertex color, and code in 7th byte of prim
		*(int*)&p->r0 = topLeftColor & 0xffffff | code;

		*(int*)&p->u0 = topLeftCornerAndPaletteXY;
		*(short*)&p->u2 = (short)bottomMargin;
		bottomRightCorner = *(u_short*)&icon->X4;

		// calculate final position of top right vertex of primitive
		// posX + (endX - startX) * scale / 0x1000
		topRightCornerAndPageXY =
		posX +
		(
			(int)
			(((topRightCornerAndPageXY & 0xff) - (topLeftCornerAndPaletteXY & 0xff)) * (int)scale)
			>> 12
		);

		*(int*)&p->x0 = posX | bitshiftPosY;
		*(int*)&p->x1 = topRightCornerAndPageXY | bitshiftPosY;

		// posY +=
		bitshiftPosY +=
		(
			(int)
			(((u_int)y2 - ((int)topLeftCornerAndPaletteXY >> 8 & 0xffU)) * (int)scale)
			>> 12
		) << 16;

		*(int*)&p->x2 = posX | bitshiftPosY;
		*(int*)&p->x3 = topRightCornerAndPageXY | bitshiftPosY;
		*(u_short *)&p->u3 = bottomRightCorner;

		// color data from parameters
		*(int*)&p->r1 = topRightColor;
		*(int*)&p->r2 = bottomLeftColor;
		*(int*)&p->r3 = bottomRightColor;

		// link prim and OT together
		*(int*)p = *ot | 0xc000000;
		*ot = (u_int)p & 0xffffff;

		// POLY_GT4 is 0x34 bytes large
		primMem->curr = p + 1;
	}
	return;
}