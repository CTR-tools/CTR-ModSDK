#include <common.h>

void DECOMP_DecalHUD_DrawPolyGT4(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, u_int color0, u_int color1, u_int color2, u_int color3, char transparency, int scale)
{
	short width;
	short height;
	short rightX;
	short bottomY;
	POLY_GT4* p;

	#if BUILD > SepReview
		if (!icon) return;
	#endif

	p = (POLY_GT4*)primMem->curr;

	width = icon->texLayout.u1 - icon->texLayout.u0;
	height = icon->texLayout.v2 - icon->texLayout.v0;
	rightX = posX + (width * scale / 0x1000);
	bottomY = posY + (height * scale / 0x1000);

	setPolyGT4(p);
	setRGB0(p, color0 & 0xff, (color0 & 0xff00) >> 8, (color0 & 0xff0000) >> 16);
	setRGB1(p, color1 & 0xff, (color1 & 0xff00) >> 8, (color1 & 0xff0000) >> 16);
	setRGB2(p, color2 & 0xff, (color2 & 0xff00) >> 8, (color2 & 0xff0000) >> 16);
	setRGB3(p, color3 & 0xff, (color3 & 0xff00) >> 8, (color3 & 0xff0000) >> 16);
	setXY4(p, posX, posY, rightX, posY, posX, bottomY, rightX, bottomY);
	setUV4(p, icon->texLayout.u0, icon->texLayout.v0, icon->texLayout.u1, icon->texLayout.v1, icon->texLayout.u2, icon->texLayout.v2, icon->texLayout.u3, icon->texLayout.v3);
	p->clut = icon->texLayout.clut;
	p->tpage = icon->texLayout.tpage;

	if (transparency != 0)
	{
		// disable blending mode bits of the texpage using AND, then set them using OR
		// then set image to use semi-transparent mode using the setSemiTrans macro

		p->tpage = p->tpage & 0xff9f | (transparency - 1) << 5;
		setSemiTrans(p, true);
	}

	addPrim(ot, p);

	// POLY_GT4 is 0x34 bytes large
	primMem->curr = p + 1;
	return;
}