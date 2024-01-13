#include <common.h>

#define EDUCATIONAL_BUG_IF 0

void DECOMP_DecalHUD_DrawPolyGT4(
	struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, 
	u_int color0, u_int color1, u_int color2, u_int color3, char transparency, short scale)
{
	#ifdef USE_16BY9
	void ui16BY9_DrawPolyGT4(
	struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, 
	u_int color0, u_int color1, u_int color2, u_int color3, char transparency, short scale);
	ui16BY9_DrawPolyGT4(icon, posX, posY, primMem, ot, color0, color1, color2, color3, transparency, scale);
	return;
	#endif
	
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
	
	#if EDUCATIONAL_BUG_IF
		// The original compiled version of DecalHUD_DrawPolyGT4 has a bug where the Y coordinate of the top
		// right vertex of the primitive (henceforth referred to as y1) can overflow by 1 if the X offset of
		// the primitive (centered on the top left vertex of the primitive, henceforth referred to as x0) is
		// set to a negative value. This is due to an optimization in the code: with x0 being a 32-bit value
		// truncated to 16 bits, the value for the X coordinate of the top right vertex (henceforth referred to
		// as x1), itself the offset of x0 by the width of the texture, is stored in a 32-bit variable; as the
		// function sets the primitive's X and Y coordinate values by dereferencing both of them as a singular
		// 32-bit integer, with x1 and y1's bits being added together using bitwise OR, the bottom 16 bits of
		// x1 are added onto y1's bits, resulting in y1's value being altered by x1's overflow.
		// This also affects the bottom right vertex.

		unsigned int rightX = (u_short)posX + FP_Mult(width, scale);
		setXY4CompilerHack(p, (u_short)posX, posY, rightX, posY, (u_short)posX, bottomY, rightX, bottomY);
	#else
		unsigned int rightX = posX + FP_Mult(width, scale);
		setXY4(p, posX, posY, rightX, posY, posX, bottomY, rightX, bottomY);
	#endif
	setIconUV(p, icon);

	if (transparency)
	{
		setTransparency(p, transparency);
	}

	primMem->curr = p + 1;
}