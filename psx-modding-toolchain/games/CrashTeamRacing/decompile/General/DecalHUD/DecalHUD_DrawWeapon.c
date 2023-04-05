#include <common.h>

void DECOMP_DecalHUD_DrawWeapon(struct Icon* icon, int posX, int posY, struct PrimMem* primMem, u_long* ot, char semitransparencyEnabled, short scale, u_short param_8)
{
	u_int uVar1;
	u_int bitshiftPosY;
	u_int uVar3;
	POLY_FT4 *p;
	u_int topRightCornerAndPageXY;
	u_int topLeftCornerAndPaletteXY;
	u_int bottomMargin;
	int iVar8;
	int iVar9;

	if (icon != 0)
	{
		topRightCornerAndPageXY = *(u_int*)&icon->texLayout.u1;
		topLeftCornerAndPaletteXY = *(u_int*)&icon->texLayout.u0;

		// posY, bitshifted 2 u_chars
		bitshiftPosY = posY * 0x10000;

		iVar9 = (int)(((topRightCornerAndPageXY & 0xff) - (topLeftCornerAndPaletteXY & 0xff)) * (int)scale) >> 0xc;

		// X and Y of the two bottom corners
		bottomMargin = *(u_int*)&icon->texLayout.u2;

		p = (POLY_FT4*)primMem->curr;

		iVar8 = (int)(((u_int)icon->texLayout.v2 - ((int)topLeftCornerAndPaletteXY >> 8 & 0xffU)) * (int)scale) >> 0xc;

		if (semitransparencyEnabled == 0)
		{
			p->code = 0x2d;

			// set top right corner UVs and texpage of primitive to the ones the icon has
			*(int*)&p->u1 = topRightCornerAndPageXY;
		}

		else
		{
			p->code = 0x2f;

			// set top right corner UVs and texpage of primitive, and alter the blending mode bits of the texpage from 11 (Mode 3, which is no blending) to 00 (Mode 0, equivalent to regular 50% opacity)
			*(int*)&p->u1 = topRightCornerAndPageXY & 0xff9fffff | ((u_int)semitransparencyEnabled - 1) * 0x200000;
		}

		// set top left corner UVs and CLUT of primitive to the ones the icon has
		*(int*)&p->u0 = topLeftCornerAndPaletteXY;

		// set UVs of bottom left corner
		*(short*)&p->u2 = (short)bottomMargin;

		// set UVs of bottom right corner
		*(u_short *)&p->u3 = *(u_short *)&icon->texLayout.u3;

		topRightCornerAndPageXY = posX + iVar8;

		if ((param_8 & 1) == 0)
		{
			topLeftCornerAndPaletteXY = posX + iVar9;
			topRightCornerAndPageXY = bitshiftPosY + iVar8 * 0x10000;
			uVar1 = posX | topRightCornerAndPageXY;
			topLeftCornerAndPaletteXY |= bitshiftPosY;

			// same as below
			topRightCornerAndPageXY |= topLeftCornerAndPaletteXY;

			if (param_8 == 0)
			{
				*(int*)&p->x0 = posX | bitshiftPosY;
				*(int*)&p->x1 = topLeftCornerAndPaletteXY;
				*(int*)&p->x2 = uVar1;
				*(int*)&p->x3 = topRightCornerAndPageXY;
			}

			else
			{
				// we go the other way around
				*(int*)&p->x3 = posX | bitshiftPosY;
				*(int*)&p->x2 = topLeftCornerAndPaletteXY;
				*(int*)&p->x1 = uVar1;
				*(int*)&p->x0 = topRightCornerAndPageXY;
			}
		}

		else
		{
			topLeftCornerAndPaletteXY = bitshiftPosY + iVar9 * 0x10000;
			uVar3 = topRightCornerAndPageXY | bitshiftPosY;
			uVar1 = posX | topLeftCornerAndPaletteXY;

			// same as above
			topRightCornerAndPageXY |= topLeftCornerAndPaletteXY;

			if (param_8 == 1)
			{
				*(int*)&p->x1 = posX | bitshiftPosY;
				*(int*)&p->x3 = uVar3;
				*(int*)&p->x0 = uVar1;
				*(int*)&p->x2 = topRightCornerAndPageXY;
			}

			else
			{
				*(int*)&p->x2 = posX | bitshiftPosY;
				*(int*)&p->x0 = uVar3;
				*(int*)&p->x3 = uVar1;
				*(int*)&p->x1 = topRightCornerAndPageXY;
			}
		}

		// link prim and OT together
		*(int*)p = *ot | 0x9000000;
		*ot = (u_int)p & 0xffffff;

		// POLY_FT4 is 0x28 bytes large
		primMem->curr = p + 1;
	}
	return;
}
