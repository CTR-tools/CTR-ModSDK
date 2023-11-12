#include <common.h>
#include "RaceOptions.h"

force_inline void ProcessInputs(struct GameTracker* gGT, struct MenuBox* mb, u_int buttonsTapped)
{
	if (buttonsTapped & (BTN_L1 | BTN_R1 | BTN_L2 | BTN_R2 | BTN_UP | BTN_DOWN)) OtherFX_Play(0, 1);

	if (buttonsTapped & (BTN_UP | BTN_DOWN))
	{
		if (buttonsTapped & BTN_UP)
		{
			mb->rowSelected = (mb->rowSelected + (NUM_ROWS - 1)) % NUM_ROWS;
		}

		if (buttonsTapped & BTN_DOWN)
		{
			mb->rowSelected = (mb->rowSelected + 1) % NUM_ROWS;
		}
	}
}

force_inline void DisplayMenuBox(struct GameTracker* gGT, struct MenuBox* mb)
{
	u_int firstRowY = ((MenuBoxBG_y + 4) + 26);

	glowingcursor.y = firstRowY + (10 * mb->rowSelected);

	// "OPTIONS"
	DecalFont_DrawLine(sdata->lngStrings[324], SCREEN_WIDTH/2, MenuBoxBG_y + 4, FONT_BIG, (JUSTIFY_CENTER | ORANGE));

	// "FALL GUY"
	DecalFont_DrawLine(sdata->lngStrings[451], glowingcursor.x + 2, firstRowY + (10 * 0) + 1, FONT_SMALL, ORANGE);
	// idk
	DecalFont_DrawLine(sdata->lngStrings[452], glowingcursor.x + 2, firstRowY + (10 * 1) + 1, FONT_SMALL, ORANGE);
	DecalFont_DrawLine(sdata->lngStrings[452], glowingcursor.x + 2, firstRowY + (10 * 2) + 1, FONT_SMALL, ORANGE);
	// "EXIT"
	DecalFont_DrawLine(sdata->lngStrings[331], glowingcursor.x + 2, firstRowY + (10 * 3) + 1, FONT_SMALL, ORANGE);

	MENUBOX_DrawInnerRect(&titleSeparatorLine, 4, (u_long *)(gGT->backBuffer->otMem).startPlusFour);
	CTR_Box_DrawClearBox(&glowingcursor, &sdata->menuRowHighlight_Normal, 1, (u_long *)(gGT->backBuffer->otMem).startPlusFour, &gGT->backBuffer->primMem); // draw glowing cursor
	MENUBOX_DrawInnerRect(&menuBoxBG, 4, (u_long *)(gGT->backBuffer->otMem).startPlusFour); // draw the actual menubox background
}

// the MenuBox function
void RaceOptions_FuncPtr(struct MenuBox* mb)
{
	ProcessInputs(sdata->gGT, mb, sdata->gGamepads->gamepad[0].buttonsTapped);
	DisplayMenuBox(sdata->gGT, mb);
}