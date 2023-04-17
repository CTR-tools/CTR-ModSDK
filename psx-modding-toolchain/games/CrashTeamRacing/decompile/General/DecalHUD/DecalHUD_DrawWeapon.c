#include <common.h>

#define EDUCATIONAL_BUG_IF 0

void DECOMP_DecalHUD_DrawWeapon(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, char transparency, int scale, char rot)
{
	#if BUILD > SepReview
		if (!icon) return;
	#endif

	POLY_FT4* p = (POLY_FT4*)primMem->curr;
	addPolyFT4(ot, p);

	// this function doesn't support coloring the primitives
	setShadeTex(p, true);

	unsigned int width = icon->texLayout.u1 - icon->texLayout.u0;
	unsigned int height = icon->texLayout.v2 - icon->texLayout.v0;
	unsigned int rightX = posX + (width * scale / 0x1000);
	unsigned int bottomY = posY + (height * scale / 0x1000);
	unsigned int sidewaysX = posX + (height * scale / 0x1000);
	unsigned int sidewaysY = posY + (width * scale / 0x1000);

	#if EDUCATIONAL_BUG_IF == 0
		if (!(rot & 1))
		{
			if (rot == 0)
			{
				setXY4CompilerHack(p, (u_short)posX, posY, (u_short)rightX, posY, (u_short)posX, bottomY, (u_short)rightX, bottomY);
			}
			else
			{
				setXY4CompilerHack(p, (u_short)rightX, bottomY, (u_short)posX, bottomY, (u_short)rightX, posY, (u_short)posX, posY);
			}
		}
		else
		{
			if (rot == 1)
			{
				setXY4CompilerHack(p, (u_short)posX, sidewaysY, (u_short)posX, posY, (u_short)sidewaysX, sidewaysY, (u_short)sidewaysX, posY);
			}
			else
			{
				setXY4CompilerHack(p, (u_short)sidewaysX, posY, (u_short)sidewaysX, sidewaysY, (u_short)posX, posY, (u_short)posX, sidewaysY);
			}
		}
	#else
		if (!(rot & 1))
		{
			if (rot == 0)
			{
				setXY4CompilerHack(p, posX, posY, rightX, posY, posX, bottomY, rightX, bottomY);
			}
			else
			{
				setXY4CompilerHack(p, rightX, bottomY, posX, bottomY, rightX, posY, posX, posY);
			}
		}
		else
		{
			if (rot == 1)
			{
				setXY4CompilerHack(p, posX, sidewaysY, posX, posY, sidewaysX, sidewaysY, sidewaysX, posY);
			}
			else
			{
				setXY4CompilerHack(p, sidewaysX, posY, sidewaysX, sidewaysY, posX, posY, posX, sidewaysY);
			}
		}
	#endif
	
	setIconUV(p, icon);

	if (transparency)
	{
		setTransparency(p, transparency);
	}

	primMem->curr = p + 1;
}