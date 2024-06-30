#include <common.h>

/**
 * @brief Draws an inner rectangle for a menu box with various styles depending on the type.
 *        This function is part of the UI system for drawing menu boxes and allows for different
 *        styles like transparent or solid black, as well as additional customizations.
 *        The function adjusts the dimensions and style of the rectangle based on type
 *        and then draws it using specific graphical functions.
 * Byte budget: 508/572
 * Function Identifier: FUN_800457b0
 *
 * @author aalhendi
 *
 * @param r Pointer to a RECT structure that specifies the initial position and size of the rectangle.
 * @param type An integer that determines the style of the tile view:
 *                     0 for transparent (like main menu), 1 for solid black (like "gamepad unplugged"), etc.
 * @param ot Pointer to a rendering structure or object, used internally in the drawing functions.
 */
void DECOMP_RECTMENU_DrawInnerRect(RECT *r, int type, void *ot)
{
	int *colorDataNormal;  // TODO(aalhendi): colorData1?
	int *colorDataSpecial; // TODO(aalhendi): colorData2?
	int drawMode;          // TODO(aalhendi): Check type?
	RECT adjustedRect; // Using a single RECT for adjustments

	colorDataNormal = &sdata->battleSetup_Color_UI_1;
	if ((type & 0x10) != 0)
	{
		colorDataNormal = &sdata->battleSetup_Color_UI_2;
	}

	if ((type & 2) == 0)
	{
		Color color;
		color.self = *colorDataNormal;
		DECOMP_RECTMENU_DrawOuterRect_HighLevel
		(
			r, color,
			(int)(short)(type | 0x20), ot
		);
	}

	adjustedRect.x = r->x;
	adjustedRect.y = r->y;
	adjustedRect.w = r->w;
	adjustedRect.h = r->h;

	if ((type & 8) == 0)
	{
		if ((type & 2) == 0)
		{
			// Modify RECT components directly
			adjustedRect.x += 3;
			adjustedRect.y += 2;
			adjustedRect.w -= 6;
			adjustedRect.h -= 4;
		}

		if ((type & 1) == 0)
		{
			drawMode = ((type & 0x100) != 0) ? 2 : 0;
			colorDataSpecial = ((type & 0x100) != 0) ? &sdata->DrawSolidBoxData[1] : &sdata->DrawSolidBoxData[2];

			Color color;
			color.self = *colorDataSpecial;
			DECOMP_CTR_Box_DrawClearBox(&adjustedRect, color, drawMode, ot);
		}
		else
		{
			Color color;
			color.self = sdata->DrawSolidBoxData[0];
			DECOMP_CTR_Box_DrawSolidBox(&adjustedRect, color, ot);
		}
	}

	// Draw shadow under the menu
	if ((type & 4) == 0)
	{
		short horizontalOffset = ((type & 0x80) != 0) ? WIDE_34(4) : WIDE_34(0xc);
		short verticalOffset = ((type & 0x40) != 0) ? 2 : 6;

		adjustedRect.x = r->x + r->w;
		adjustedRect.y = r->y + verticalOffset;
		adjustedRect.w = horizontalOffset;
		adjustedRect.h = r->h;

		Color color;
		color.self = sdata->DrawSolidBoxData[0];
		DECOMP_CTR_Box_DrawClearBox(&adjustedRect, color, 0, ot); // Adjust and draw the box

		adjustedRect.x = r->x + horizontalOffset;
		adjustedRect.y = r->y + r->h;
		adjustedRect.w = r->w - horizontalOffset;
		adjustedRect.h = verticalOffset;
		DECOMP_CTR_Box_DrawClearBox(&adjustedRect, color, 0, ot);
	}

	return;
}