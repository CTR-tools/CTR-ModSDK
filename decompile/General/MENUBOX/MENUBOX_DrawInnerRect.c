#include <common.h>

/**
 * @brief Draws an inner rectangle for a menu box with various styles depending on the tileViewType.
 *        This function is part of the UI system for drawing menu boxes and allows for different 
 *        styles like transparent or solid black, as well as additional customizations.
 *        The function adjusts the dimensions and style of the rectangle based on tileViewType 
 *        and then draws it using specific graphical functions.
 * Byte budget: 508/572
 * Function Identifier: FUN_800457b0
 *
 * @author aalhendi
 *
 * @param r Pointer to a RECT structure that specifies the initial position and size of the rectangle.
 * @param tileViewType An integer that determines the style of the tile view:
 *                     0 for transparent (like main menu), 1 for solid black (like "gamepad unplugged"), etc.
 * @param ot Pointer to a rendering structure or object, used internally in the drawing functions.
 */
void DECOMP_MENUBOX_DrawInnerRect(RECT *r, int tileViewType, void *ot)
{
	int *colorDataNormal;  // TODO(aalhendi): colorData1?
	int *colorDataSpecial; // TODO(aalhendi): colorData2?
	int drawMode;          // TODO(aalhendi): Check type?
	RECT adjustedRect; // Using a single RECT for adjustments

	colorDataNormal = &sdata->battleSetup_Color_UI_1;
	if ((tileViewType & 0x10) != 0)
	{
		colorDataNormal = &sdata->battleSetup_Color_UI_2;
	}

	if ((tileViewType & 2) == 0)
	{
		DECOMP_MENUBOX_DrawOuterRect_HighLevel
		(
			r, colorDataNormal,
			(int)(short)(tileViewType | 0x20), ot
		);
	}

	adjustedRect.x = r->x;
	adjustedRect.y = r->y;
	adjustedRect.w = r->w;
	adjustedRect.h = r->h;

	if ((tileViewType & 8) == 0) 
	{
		if ((tileViewType & 2) == 0) 
		{
			// Modify RECT components directly
			adjustedRect.x += 3;
			adjustedRect.y += 2;
			adjustedRect.w -= 6;
			adjustedRect.h -= 4;
		}

		if ((tileViewType & 1) == 0) 
		{
			drawMode = ((tileViewType & 0x100) != 0) ? 2 : 0;
			colorDataSpecial = ((tileViewType & 0x100) != 0) ? &sdata->DrawSolidBoxData[1] : &sdata->DrawSolidBoxData[2];

			DECOMP_CTR_Box_DrawClearBox
			(
				&adjustedRect, colorDataSpecial, drawMode, ot,
				&sdata->gGT->backBuffer->primMem
			);
		} 
		else 
		{
			DECOMP_CTR_Box_DrawSolidBox
			(
				&adjustedRect, &sdata->DrawSolidBoxData[0], ot,
				&sdata->gGT->backBuffer->primMem
			);
		}
	}

	if ((tileViewType & 4) == 0) 
	{
		short horizontalOffset = ((tileViewType & 0x80) != 0) ? 4 : 0xc;
		short verticalOffset = ((tileViewType & 0x40) != 0) ? 2 : 6;

		adjustedRect.x = r->x + r->w;
		adjustedRect.y = r->y + verticalOffset;	
		adjustedRect.w = horizontalOffset;
		adjustedRect.h = r->h;

		// Adjust and draw the box
		DECOMP_CTR_Box_DrawClearBox
		(
			&adjustedRect, &sdata->DrawSolidBoxData[0], 0, ot,
			&sdata->gGT->backBuffer->primMem
		);

		adjustedRect.x = r->x + horizontalOffset;
		adjustedRect.y = r->y + r->h;	
		adjustedRect.w = r->w - horizontalOffset;
		adjustedRect.h = verticalOffset;

		// Draw the box again
		DECOMP_CTR_Box_DrawClearBox
		(
			&adjustedRect, &sdata->DrawSolidBoxData[0], 0, ot,
			&sdata->gGT->backBuffer->primMem
		);
	}

	return;
}