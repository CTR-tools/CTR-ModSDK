#include <common.h>
#include "RaceOptions.h"

u_char RO_numLaps[4] = {1, 3, 5, 7};
u_int RO_numLapsIndex = 1;
extern u_int RF_blueFireMode;
extern u_int RaceOptionsIsOpen;

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

	if (buttonsTapped & (BTN_CROSS | BTN_CIRCLE))
	{
		switch (mb->rowSelected)
		{
			case 0:
				if (!(gGT->gameMode1 & TIME_TRIAL))
				{
					OtherFX_Play(1, 1);
					RO_numLapsIndex = (RO_numLapsIndex + 1) % 4;
					gGT->numLaps = RO_numLaps[RO_numLapsIndex];
				}
				else
				{
					OtherFX_Play(5, 1);
				}
				break;
			case 1:
				RF_blueFireMode = (RF_blueFireMode + 1) % 3;
				OtherFX_Play(1, 1);
				break;
			case 2:
				OtherFX_Play(5, 1);
				break;
			case 3:
				OtherFX_Play(1, 1);
				RaceOptionsIsOpen = false;
				break;
		}
	}

	if (buttonsTapped & (BTN_SQUARE | BTN_TRIANGLE | BTN_START))
	{
		if (buttonsTapped & (BTN_SQUARE | BTN_TRIANGLE)) OtherFX_Play(2, 1);
		else                                             OtherFX_Play(1, 1);
		
		RaceOptionsIsOpen = false;
	}
}

force_inline void DisplayMenuBox(struct GameTracker* gGT, struct MenuBox* mb)
{
	u_int firstRowY = ((MenuBoxBG_y + 4) + 26);
	u_int optionTextPosX = (glowingcursor.x + glowingcursor.w) - 2;

	glowingcursor.y = firstRowY + (10 * mb->rowSelected);

	// "RACE OPTIONS"
	DecalFont_DrawLine(sdata->lngStrings[593], SCREEN_WIDTH/2, MenuBoxBG_y + 4, FONT_BIG, (JUSTIFY_CENTER | ORANGE));

	// "LAPS"
	DecalFont_DrawLine(sdata->lngStrings[594], glowingcursor.x + 2, firstRowY + (10 * 0) + 1, FONT_SMALL, ORANGE);
	// "BLUE FIRE"
	DecalFont_DrawLine(sdata->lngStrings[595], glowingcursor.x + 2, firstRowY + (10 * 1) + 1, FONT_SMALL, ORANGE);
	// "MIRROR MODE"
	DecalFont_DrawLine(sdata->lngStrings[596], glowingcursor.x + 2, firstRowY + (10 * 2) + 1, FONT_SMALL, ORANGE);
	// "EXIT"
	DecalFont_DrawLine(sdata->lngStrings[331], glowingcursor.x + 2, firstRowY + (10 * 3) + 1, FONT_SMALL, ORANGE);

	// Laps:
	DecalFont_DrawLine(sdata->lngStrings[600 + RO_numLapsIndex], optionTextPosX, firstRowY + (10 * 0) + 1, FONT_SMALL, WHITE | JUSTIFY_RIGHT);
	// Blue Fire:
	DecalFont_DrawLine(sdata->lngStrings[597 + RF_blueFireMode], optionTextPosX, firstRowY + (10 * 1) + 1, FONT_SMALL, WHITE | JUSTIFY_RIGHT);
	// Mirror Mode: "OFF"
	DecalFont_DrawLine(sdata->lngStrings[597], optionTextPosX, firstRowY + (10 * 2) + 1, FONT_SMALL, WHITE | JUSTIFY_RIGHT);

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