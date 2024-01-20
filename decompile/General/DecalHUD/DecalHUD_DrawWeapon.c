#include <common.h>

#define EDUCATIONAL_BUG_IF 0

void DECOMP_DecalHUD_DrawWeapon(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, char transparency, short scale, char rot)
{
	#ifdef USE_16BY9
	void ui16BY9_DrawWeapon(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, char transparency, short scale, char rot);
	ui16BY9_DrawWeapon(icon,posX,posY,primMem,ot,transparency,scale,rot);
	return;
	#endif
	
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

	// instead of psn00bsdk's setXY4, this function uses a custom-made macro that resembles the compiler optimization used in the original code
	// the X and Y fields of the primitive will be dereferenced as combined 32-bit integers for each vertex
	// from this, the X and Y coordinates will be added onto these integers using bitwise OR
	// this originally caused a bug where if X is higher than 0xFFFF (by not being cast as unsigned 16-bits) it will overflow onto Y
	// for the sake of making this compile under the original file size of the function (0x190 bytes) this macro will be used with the proper variable casts
	// the bugged version of the code is still intact as a compiler macro
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

	// this function doesn't support coloring the primitives
	setShadeTex(p, true);

	if (transparency)
	{
		setTransparency(p, transparency);
	}

	primMem->curr = p + 1;
}