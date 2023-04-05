#include <common.h>

void DECOMP_DecalHUD_DrawWeapon(struct Icon* icon, int posX, int posY, struct PrimMem* primMem, u_long* ot, char transparency, short scale, short rot)
{
	short width;
	short height;
	short rightX;
	short bottomY;
	short sidewaysX;
	short sidewaysY;
	POLY_FT4* p;

	#if BUILD > SepReview
		if (!icon) return;
	#endif

	p = (POLY_FT4*)primMem->curr;

	width = icon->texLayout.u1 - icon->texLayout.u0;
	height = icon->texLayout.v2 - icon->texLayout.v0;
	rightX = posX + (width * scale / 0x1000);
	bottomY = posY + (height * scale / 0x1000);
	sidewaysX = posX + (height * scale / 0x1000);
	sidewaysY = posY + (width * scale / 0x1000);

	setPolyFT4(p);
	setShadeTex(p, true);

	if (!(rot & 1))
	{
		if (rot == 0)
			setXY4(p, posX, posY, rightX, posY, posX, bottomY, rightX, bottomY);
		else
			setXY4(p, rightX, bottomY, posX, bottomY, rightX, posY, posX, posY);
	}
	else
	{
		if (rot == 1)
			setXY4(p, posX, sidewaysY, posX, posY, sidewaysX, sidewaysY, sidewaysX, posY);
		else
			setXY4(p, sidewaysX, posY, sidewaysX, sidewaysY, posX, posY, posX, sidewaysY);
	}

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

	// POLY_FT4 is 0x28 bytes large
	primMem->curr = p + 1;
	return;
}