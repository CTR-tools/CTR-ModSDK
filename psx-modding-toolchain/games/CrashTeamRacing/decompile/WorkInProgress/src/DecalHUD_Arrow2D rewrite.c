#include <common.h>

void DECOMP_DecalHUD_Arrow2D(struct Icon* icon, u_int posX, int posY, struct PrimMem* primMem, u_long *otMemPtr, u_int color1, u_int color2, u_int color3, u_int color4, char transparency, short scale, u_short rot)
{
	u_char y2;
	u_int code;
	int bitshiftTopRightCorner;
	u_int topRightCornerAndPageXY;
	int bitshiftPosY;
	int iVar6;
	int iVar7;
	int sVar8;
	u_int bottomMargin;
	int iVar10;
	u_int topLeftCornerAndPaletteXY;
	int iVar12;
	int iVar13;

	#if BUILD > SepReview
		if (!icon) return;
	#endif

	POLY_GT4 *p;

	width = icon->X2 - icon->X1;
	height = icon->Y3 - icon->Y1;

	setPolyGT4(p);
	setRGB0(p, color0 & 0xff, (color0 & 0xff00) >> 8, (color0 & 0xff0000) >> 16);
	setRGB1(p, color1 & 0xff, (color1 & 0xff00) >> 8, (color1 & 0xff0000) >> 16);
	setRGB2(p, color2 & 0xff, (color2 & 0xff00) >> 8, (color2 & 0xff0000) >> 16);
	setRGB3(p, color3 & 0xff, (color3 & 0xff00) >> 8, (color3 & 0xff0000) >> 16);
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

	bitshiftPosY = width * scale / 0x2000;
	
	bitshiftTopRightCorner = height * scale / 0x2000;

	// stuff for rotation of primitive
	iVar13 = *(int *)(&data.trigApprox[(rot & 0x3ff) * 4]) >> 16;
	sVar8 = *(int *)(&data.trigApprox[(rot & 0x3ff) * 4]);

	if ((rot & 0x400) == 0)
	{
		iVar10 = sVar8;
		if ((rot & 0x800) == 0) goto LAB_800232d8;
		iVar12 = -iVar13;
	}
	else
	{
		iVar12 = sVar8;
		iVar10 = iVar13;
		if ((rot & 0x800) == 0)
		{
			iVar13 = -iVar12;
			goto LAB_800232d8;
		}
	}
	iVar10 = -iVar10;
	iVar13 = iVar12;
	
LAB_800232d8:
	iVar12 = -bitshiftPosY;
	bitshiftPosY++;
	iVar6 = iVar12 * iVar10 / 0x1000;
	iVar12 = posY + (iVar12 * iVar13 / 0x1000);

	*(int*)&p->x0 = posX + (-bitshiftTopRightCorner * iVar13 / 0x1000) + iVar6 & 0xffff | (iVar12 - (-bitshiftTopRightCorner * iVar10 / 0x1000)) << 16;
	
	iVar7 = bitshiftPosY * iVar10 / 0x1000;
	
	*(int*)&p->x1 = posX + ((bitshiftTopRightCorner + 1) * iVar13 / 0x1000) + iVar6 & 0xffff | (iVar12 - ((bitshiftTopRightCorner + 1) * iVar10 / 0x1000)) << 16;
	
	posY = posY + (bitshiftPosY * iVar13 / 0x1000);
	
	*(int*)&p->x2 = posX + (-bitshiftTopRightCorner * iVar13 / 0x1000) + iVar7 & 0xffff | (posY - (-bitshiftTopRightCorner * iVar10 / 0x1000)) << 16;
	*(int*)&p->x3 = posX + ((bitshiftTopRightCorner + 1) * iVar13 / 0x1000) + iVar7 & 0xffff | (posY - ((bitshiftTopRightCorner + 1) * iVar10 / 0x1000)) << 16;

	addPrim(ot, p);

	// POLY_GT4 is 0x34 bytes large
	primMem->curr = p + 1;
	return;
}