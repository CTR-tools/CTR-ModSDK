// used for 16x9 (part 2)

#ifdef USE_16BY9
void ui16BY9_DrawPolyFT4(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, char transparency, short scale)
{
	if (!icon) return;

	POLY_FT4* p = (POLY_FT4*)primMem->curr;
	addPolyFT4(ot, p);

	unsigned int width = icon->texLayout.u1 - icon->texLayout.u0;
	unsigned int height = icon->texLayout.v2 - icon->texLayout.v0;
	unsigned int bottomY = posY + FP_Mult(height, scale);
	unsigned int rightX = posX + FP_Mult(width, scale);
	
	setXY4(p, posX, posY, rightX, posY, posX, bottomY, rightX, bottomY);
	setIconUV(p, icon);

	// this function doesn't support coloring the primitives
	setShadeTex(p, true);

	if (transparency)
	{
		setTransparency(p, transparency);
	}
	
	// widescreen, need to scale X by 75%,
	// so subtract 12% from left and 12% from right
	int len = ((p->x1 - p->x0) * 125) / 1000;
	p->x0 += len;
	p->x2 += len;
	p->x1 -= len;
	p->x3 -= len;

	primMem->curr = p + 1;
}

void ui16BY9_DrawWeapon(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, char transparency, short scale, char rot)
{
	#if BUILD > SepReview
		if (!icon) return;
	#endif

	POLY_FT4* p = (POLY_FT4*)primMem->curr;
	addPolyFT4(ot, p);

	unsigned int width = icon->texLayout.u1 - icon->texLayout.u0;
	unsigned int height = icon->texLayout.v2 - icon->texLayout.v0;
	unsigned int rightX = posX + FP_Mult(width, scale);
	unsigned int bottomY = posY + FP_Mult(height, scale);
	unsigned int sidewaysX = posX + FP_Mult(height, scale);
	unsigned int sidewaysY = posY + FP_Mult(width, scale);

	if (!(rot & 1))
	{
		if (rot == 0)
		{
			setXY4(p, (u_short)posX, posY, (u_short)rightX, posY, (u_short)posX, bottomY, (u_short)rightX, bottomY);
		}
		else
		{
			setXY4(p, (u_short)rightX, bottomY, (u_short)posX, bottomY, (u_short)rightX, posY, (u_short)posX, posY);
		}
	}
	else
	{
		if (rot == 1)
		{
			setXY4(p, (u_short)posX, sidewaysY, (u_short)posX, posY, (u_short)sidewaysX, sidewaysY, (u_short)sidewaysX, posY);
		}
		else
		{
			setXY4(p, (u_short)sidewaysX, posY, (u_short)sidewaysX, sidewaysY, (u_short)posX, posY, (u_short)posX, sidewaysY);
		}
	}

	
	setIconUV(p, icon);

	// this function doesn't support coloring the primitives
	setShadeTex(p, true);

	if (transparency)
	{
		setTransparency(p, transparency);
	}
	
	// widescreen, need to scale X by 75%,
	// so subtract 12% from left and 12% from right
	int len = ((p->x2 - p->x0) * 125) / 1000;
	p->x0 += len;
	p->x1 += len;
	p->x2 -= len;
	p->x3 -= len;

	primMem->curr = p + 1;
}

void ui16BY9_DrawPolyGT4(
	struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, 
	u_int color0, u_int color1, u_int color2, u_int color3, char transparency, short scale)
{
	#if BUILD > SepReview
		if (!icon) return;
	#endif

	// setInt32RGB4 needs to go before addPolyGT4
	// for more information check "include/gpu.h"
	POLY_GT4* p = (POLY_GT4*)primMem->curr;
	setInt32RGB4(p, color0, color1, color2, color3);
	addPolyGT4(ot, p);

	unsigned int width = icon->texLayout.u1 - icon->texLayout.u0;
	unsigned int height = icon->texLayout.v2 - icon->texLayout.v0;
	unsigned int bottomY = posY + FP_Mult(height, scale);
	unsigned int rightX = posX + FP_Mult(width, scale);
	
	setXY4(p, posX, posY, rightX, posY, posX, bottomY, rightX, bottomY);
	setIconUV(p, icon);

	if (transparency)
	{
		setTransparency(p, transparency);
	}
	
	// widescreen, need to scale X by 75%,
	// so subtract 12% from left and 12% from right
	int len = ((p->x1 - p->x0) * 125) / 1000;
	p->x0 += len;
	p->x2 += len;
	p->x1 -= len;
	p->x3 -= len;

	primMem->curr = p + 1;
}
#endif
