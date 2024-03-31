#include <common.h>

void NewDrawPolyFT4(struct Icon* icon, u_int posX, int posY, struct PrimMem* primMem, u_long* ot, u_char semitransparencyEnabled, short scale)
{
	u_char y2;
	u_short bottomRightCorner;
	u_int topRightCornerAndPageXY;
	u_int topLeftCornerAndPaletteXY;
	POLY_FT4 *p;
	u_int bitshiftPosY;
	u_int bottomMargin;

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

		//printf("pointer: 0x%p\n",icon);
		//printf("index: 0x%p\n",icon->global_IconArray_Index);
		printf("name: %s\n",icon->name);
		//printf("clut: 0x%x\n",icon->texLayout.clut);
		printf("original texpage: 0x%04x\n",icon->texLayout.tpage);
		printf("current texpage: 0x%04x\n",p->tpage);

		// link prim and OT together
		*(int*)p = *ot | 0x9000000;
		*ot = (u_int)p & 0xffffff;

		// POLY_FT4 is 0x28 bytes large
		primMem->curr = p + 1;
	}
	return;
}

void KeepDrawingIcon()
{
	NewDrawPolyFT4(sdata->gGT->ptrIcons[0x0],0x54,0x22,

	// gGT->backBuffer->primMem
	&sdata->gGT->backBuffer->primMem,

	// pointer to OT mem
	sdata->gGT->pushBuffer_UI.ptrOT,

	1, 0x1000);

	NewDrawPolyFT4(sdata->gGT->ptrIcons[0x1],0x54,0x44,

	// gGT->backBuffer->primMem
	&sdata->gGT->backBuffer->primMem,

	// pointer to OT mem
	sdata->gGT->pushBuffer_UI.ptrOT,

	1, 0x1000);/*

	NewDrawPolyFT4(sdata->gGT->ptrIcons[0x18],0xa8,0x22,

	// gGT->backBuffer->primMem
	&sdata->gGT->backBuffer->primMem,

	// pointer to OT mem
	sdata->gGT->pushBuffer_UI.ptrOT,

	0, 0x1000);

	NewDrawPolyFT4(sdata->gGT->ptrIcons[0x1d],0xa8,0x44,

	// gGT->backBuffer->primMem
	&sdata->gGT->backBuffer->primMem,

	// pointer to OT mem
	sdata->gGT->pushBuffer_UI.ptrOT,

	0, 0x1000);

	NewDrawPolyFT4(sdata->gGT->ptrIcons[0x1e],0x102,0x22,

	// gGT->backBuffer->primMem
	&sdata->gGT->backBuffer->primMem,

	// pointer to OT mem
	sdata->gGT->pushBuffer_UI.ptrOT,

	0, 0x1000);

	NewDrawPolyFT4(sdata->gGT->ptrIcons[0x1f],0x102,0x44,

	// gGT->backBuffer->primMem
	&sdata->gGT->backBuffer->primMem,

	// pointer to OT mem
	sdata->gGT->pushBuffer_UI.ptrOT,

	0, 0x1000);

	NewDrawPolyFT4(sdata->gGT->ptrIcons[0x2e],0x154,0x22,

	// gGT->backBuffer->primMem
	&sdata->gGT->backBuffer->primMem,

	// pointer to OT mem
	sdata->gGT->pushBuffer_UI.ptrOT,

	0, 0x1000);

	NewDrawPolyFT4(sdata->gGT->ptrIcons[0x30],0x154,0x44,

	// gGT->backBuffer->primMem
	&sdata->gGT->backBuffer->primMem,

	// pointer to OT mem
	sdata->gGT->pushBuffer_UI.ptrOT,

	0, 0x1000);*/

	return;
}