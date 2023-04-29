#include <common.h>

void DecalHUD_DrawPolyGT4_Expanded(struct Icon* icon, u_int posX, int posY, struct PrimMem* primMem, u_long* ot, u_int topLeftColor, u_int topRightColor, u_int bottomLeftColor, u_int bottomRightColor, short scale, u_char scaleX, u_char scaleY, u_short rot, u_char mirrorX)
{
	u_char y2;
	u_int topRightCornerAndPageXY;
	u_int bitshiftPosY;

	int bitshiftTopRightCorner;
	int iVar6;
	int iVar7;
	short sVar8;
	int iVar10;
	int iVar12;
	int iVar13;
	u_char isEurDrawLineStrlenIcon = 0;

	POLY_GT4 *p;

	u_int topLeftCornerAndPaletteXY;
	u_int bottomMargin;
	u_char u0Backup = 0;
	u_char u2Backup = 0;

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

		if(rot)
		{
			topRightCornerAndPageXY = *(u_int *)&icon->texLayout.u1;
			topLeftCornerAndPaletteXY = *(u_int *)&icon->texLayout.u0;
			bitshiftPosY = (int)(((u_int)y2 - ((int)topLeftCornerAndPaletteXY >> 8 & 0xffU)) * (int)scale) >> 0xd;
			bitshiftTopRightCorner = (int)(((topRightCornerAndPageXY & 0xff) - (topLeftCornerAndPaletteXY & 0xff)) * (int)scale) >> 0xd;

			// stuff for rotation of primitive
			iVar13 = *(int *)(&data.trigApprox[((u_int)rot & 0x3ff) * 4]) >> 0x10;
			sVar8 = (short)*(int *)(&data.trigApprox[((u_int)rot & 0x3ff) * 4]);

			if ((rot & 0x400) == 0)
			{
				iVar10 = (int)sVar8;
				if ((rot & 0x800) == 0) goto LAB_800232d8;
				iVar12 = -iVar13;
			}
			else
			{
				iVar12 = (int)sVar8;
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
			bitshiftPosY = bitshiftPosY + 1;
			iVar6 = iVar12 * iVar10 >> 0xc;
			iVar12 = posY + (iVar12 * iVar13 >> 0xc);

			*(int*)&p->x0 = posX + (-bitshiftTopRightCorner * iVar13 >> 0xc) + iVar6 & 0xffff | (iVar12 - (-bitshiftTopRightCorner * iVar10 >> 0xc)) * 0x10000;
			
			iVar7 = bitshiftPosY * iVar10 >> 0xc;
			
			*(int*)&p->x1 = posX + ((bitshiftTopRightCorner + 1) * iVar13 >> 0xc) + iVar6 & 0xffff | (iVar12 - ((bitshiftTopRightCorner + 1) * iVar10 >> 0xc)) * 0x10000;
			
			posY = posY + (bitshiftPosY * iVar13 >> 0xc);
			
			*(int*)&p->x2 = posX + (-bitshiftTopRightCorner * iVar13 >> 0xc) + iVar7 & 0xffff | (posY - (-bitshiftTopRightCorner * iVar10 >> 0xc)) * 0x10000;
			*(int*)&p->x3 = posX + ((bitshiftTopRightCorner + 1) * iVar13 >> 0xc) + iVar7 & 0xffff | (posY - ((bitshiftTopRightCorner + 1) * iVar10 >> 0xc)) * 0x10000;
		
			// fix color gradient when primitive is rotated 180 degrees
			if((rot & 0x800) == 0x800)
			{
				*(int*)&p->r0 = bottomRightColor & 0xffffff | 0x3c000000;
				*(int*)&p->r1 = bottomLeftColor;
				*(int*)&p->r2 = topRightColor;
				*(int*)&p->r3 = topLeftColor;
			}
		}

		if(scaleX)
		{
			if(rot == 0x800)
			{
				p->x0 -= scaleX;
				p->x2 -= scaleX;
			}
			else
			{
				p->x0 += scaleX;
				p->x2 += scaleX;
			}

		}
		if(scaleY)
		{
			if(rot == 0x800)
			{
				p->y0 -= scaleY;
				p->y1 -= scaleY;
			}
			else
			{
				p->y0 += scaleY;
				p->y1 += scaleY;
			}

		}

		if(mirrorX)
		{
			u0Backup = p->u0;
			u2Backup = p->u2;
			p->u0 = p->u1;
			p->u1 = u0Backup;
			p->u2 = p->u3;
			p->u3 = u2Backup;
		}

		// link prim and OT together
		*(int*)p = *ot | 0xc000000;
		*ot = (u_int)p & 0xffffff;

		// POLY_GT4 is 0x34 bytes large
		primMem->curr = p + 1;
	}
	return;
}