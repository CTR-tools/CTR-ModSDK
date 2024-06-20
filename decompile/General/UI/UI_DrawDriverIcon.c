#include <common.h>

void DECOMP_UI_DrawDriverIcon(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, char transparency, short scale, u_int color)
{
	POLY_FT4* p = (POLY_FT4*)primMem->curr;
	addPolyFT4(ot, p);

	unsigned int width = icon->texLayout.u1 - icon->texLayout.u0;
	unsigned int height = icon->texLayout.v2 - icon->texLayout.v0;
	unsigned int rightX = posX + FP_Mult(width, scale);
	#ifdef USE_ONLINE
		unsigned int topY = posY;
		unsigned int bottomY = posY + FP_Mult(height, scale);
	#else
		#if BUILD != EurRetail
			unsigned int topY = (posY < 166) ? posY : 165;
			unsigned int bottomY = ((posY + FP_Mult(height, scale)) < 166) ? (posY + FP_Mult(height, scale)) : 165;
		#else
			unsigned int topY = (posY < 176) ? posY : 175;
			unsigned int bottomY = ((posY + FP_Mult(height, scale)) < 176) ? (posY + FP_Mult(height, scale)) : 175;
		#endif
	#endif

	setXY4(p, posX, topY, rightX, topY, posX, bottomY, rightX, bottomY);

	#ifdef USE_ONLINE
	setUV4(p, icon->texLayout.u0, icon->texLayout.v0, icon->texLayout.u1, icon->texLayout.v1, icon->texLayout.u2, icon->texLayout.v2, icon->texLayout.u3, icon->texLayout.v3);
	#else
	unsigned int bottomV = (icon->texLayout.v0 + bottomY) - posY;
	setUV4(p, icon->texLayout.u0, icon->texLayout.v0, icon->texLayout.u1, icon->texLayout.v1, icon->texLayout.u2, bottomV, icon->texLayout.u3, bottomV);
	#endif

	p->clut = icon->texLayout.clut;
	p->tpage = icon->texLayout.tpage;

	#ifdef REBUILD_PC
	*(int*)p->r0 = color;
	setPolyFT4(p);
	#else
	setColor0(p, color);
	#endif

	if (transparency)
	{
		setTransparency(p, transparency);
	}

	#ifdef USE_16BY9
	// widescreen, need to scale X by 75%,
	// so subtract 12% from left and 12% from right
	int len = ((p->x1 - p->x0) * 125) / 1000;
	p->x0 += len;
	p->x2 += len;
	p->x1 -= len;
	p->x3 -= len;
	#endif

	primMem->curr = p + 1;

	return;
}