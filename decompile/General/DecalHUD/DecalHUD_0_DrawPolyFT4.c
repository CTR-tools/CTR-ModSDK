#include <common.h>

#define EDUCATIONAL_BUG_IF 0

void DECOMP_DecalHUD_DrawPolyFT4(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, char transparency, short scale)
{
	#ifdef USE_16BY9
	void ui16BY9_DrawPolyFT4(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, char transparency, short scale);
	ui16BY9_DrawPolyFT4(icon, posX, posY, primMem, ot, transparency, scale);
	return;
	#endif
	
	if (!icon) return;

	POLY_FT4* p = (POLY_FT4*)primMem->curr;
	addPolyFT4(ot, p);

	unsigned int width = icon->texLayout.u1 - icon->texLayout.u0;
	unsigned int height = icon->texLayout.v2 - icon->texLayout.v0;
	unsigned int bottomY = posY + FP_Mult(height, scale);
	unsigned int rightX = posX + FP_Mult(width, scale);
	
	#if EDUCATIONAL_BUG_IF
		// using custom-made macro that resembles the compiler optimization used in the original code
		// the X and Y fields of the primitive will be dereferenced as combined 32-bit integers for each vertex
		// from this, the X and Y coordinates will be added onto these integers using bitwise OR
		// this causes a bug where if X is higher than 0xFFFF (by not being cast as unsigned 16-bits) it will overflow onto Y
		setXY4CompilerHack(p, posX, posY, rightX, posY, posX, bottomY, rightX, bottomY);
	#else
		setXY4(p, posX, posY, rightX, posY, posX, bottomY, rightX, bottomY);
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
