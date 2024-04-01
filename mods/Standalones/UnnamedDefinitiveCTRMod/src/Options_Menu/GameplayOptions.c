#include <common.h>
#include "GameplayOptions.h"

extern u_int UDCTRM_OM_GameplayReservesMeter;
extern u_int UDCTRM_OM_GameplayTurboCount;

force_inline void ProcessInputs(struct RectMenu* menu, struct GameTracker* gGT, u_int buttonsTapped)
{
	int exitMenu = false;

	// change row
	if (buttonsTapped & (BTN_UP | BTN_DOWN))
	{
		// play sound for when you're moving around in the menu
		OtherFX_Play(0, 1);

		if (buttonsTapped & BTN_UP)
		{
			menu->rowSelected = (menu->rowSelected + (UDCTRM_OM_GameplayNumRows - 1)) % UDCTRM_OM_GameplayNumRows;
		}

		if (buttonsTapped & BTN_DOWN)
		{
			menu->rowSelected = (menu->rowSelected + 1) % UDCTRM_OM_GameplayNumRows;
		}
	}

	if (buttonsTapped & (BTN_CROSS | BTN_CIRCLE))
	{
		switch (menu->rowSelected)
		{
			// Reserves Meter
			case 0:
				UDCTRM_OM_GameplayReservesMeter ^= 1;
				OtherFX_Play(1, 1);
				break;
			// Turbo Counter
			case 1:
				if (!(gGT->gameMode2 & CHEAT_TURBOCOUNT))
				{
					gGT->gameMode2 |= CHEAT_TURBOCOUNT;
					UDCTRM_OM_GameplayTurboCount = true;
				}
				else
				{
					gGT->gameMode2 &= ~CHEAT_TURBOCOUNT;
					UDCTRM_OM_GameplayTurboCount = false;
				}
				OtherFX_Play(1, 1);
				break;
			case 2:
				OtherFX_Play(5, 1);
				break;
			case 3:
				OtherFX_Play(5, 1);
				break;
			case 4:
				// exit
				OtherFX_Play(2, 1);
				exitMenu = true;
				break;
		}
	}

	if (exitMenu || buttonsTapped & (BTN_SQUARE_one | BTN_TRIANGLE))
	{
		OtherFX_Play(2, 1); // back sound
		MM_JumpTo_Title_Returning();
	}
}

// draw menu
force_inline void DisplayMenu(struct RectMenu* menu, struct GameTracker* gGT)
{
	u_int firstRowY = ((UDCTRM_OM_GameplayMenuBG_y + 4) + 26);
	u_int optionTextPosX = (UDCTRM_OM_Gameplayglowingcursor.x + UDCTRM_OM_Gameplayglowingcursor.w) - 2;

	UDCTRM_OM_Gameplayglowingcursor.y = firstRowY + (10 * menu->rowSelected);

	// "GAMEPLAY OPTIONS"
	DecalFont_DrawLine(sdata->lngStrings[608], SCREEN_WIDTH/2, UDCTRM_OM_GameplayMenuBG_y + 4, FONT_BIG, (JUSTIFY_CENTER | ORANGE));

	// "RESERVES METER:"
	DecalFont_DrawLine(sdata->lngStrings[611], UDCTRM_OM_Gameplayglowingcursor.x + 2, firstRowY + (10 * 0) + 1, FONT_SMALL, ORANGE);
	// "TURBO COUNTER:"
	DecalFont_DrawLine(sdata->lngStrings[612], UDCTRM_OM_Gameplayglowingcursor.x + 2, firstRowY + (10 * 1) + 1, FONT_SMALL, ORANGE);
	// "CPU DRIVERS:"
	DecalFont_DrawLine(sdata->lngStrings[613], UDCTRM_OM_Gameplayglowingcursor.x + 2, firstRowY + (10 * 2) + 1, FONT_SMALL, ORANGE);
	// "CAMERA:"
	DecalFont_DrawLine(sdata->lngStrings[617], UDCTRM_OM_Gameplayglowingcursor.x + 2, firstRowY + (10 * 3) + 1, FONT_SMALL, ORANGE);
	// "EXIT"
	DecalFont_DrawLine(sdata->lngStrings[331], UDCTRM_OM_Gameplayglowingcursor.x + 2, firstRowY + (10 * 4) + 1, FONT_SMALL, ORANGE);

	// CORTEX_RED + 0 = CORTEX_RED
	// CORTEX_RED + 1 = TINY_GREEN
	// Reserves Meter: "OFF"
	DecalFont_DrawLine(sdata->lngStrings[597 + UDCTRM_OM_GameplayReservesMeter], optionTextPosX, firstRowY + (10 * 0) + 1, FONT_SMALL, CORTEX_RED + UDCTRM_OM_GameplayReservesMeter | JUSTIFY_RIGHT);
	// Turbo Counter: "OFF"
	DecalFont_DrawLine(sdata->lngStrings[597 + UDCTRM_OM_GameplayTurboCount], optionTextPosX, firstRowY + (10 * 1) + 1, FONT_SMALL, CORTEX_RED + UDCTRM_OM_GameplayTurboCount | JUSTIFY_RIGHT);
	// CPU Drivers: "ALL 15 + OXIDE"
	DecalFont_DrawLine(sdata->lngStrings[616], optionTextPosX, firstRowY + (10 * 2) + 1, FONT_SMALL, GRAY | JUSTIFY_RIGHT);
	// Camera: "ZOOMED IN"
	DecalFont_DrawLine(sdata->lngStrings[618], optionTextPosX, firstRowY + (10 * 3) + 1, FONT_SMALL, GRAY | JUSTIFY_RIGHT);

	RECTMENU_DrawInnerRect(&UDCTRM_OM_GameplaytitleSeparatorLine, 4, (u_long *)(gGT->backBuffer->otMem).startPlusFour); // draw the line that's below the title
	CTR_Box_DrawClearBox(&UDCTRM_OM_Gameplayglowingcursor, &sdata->menuRowHighlight_Normal, 1, (u_long *)(gGT->backBuffer->otMem).startPlusFour, &gGT->backBuffer->primMem); // draw glowing cursor
	RECTMENU_DrawInnerRect(&UDCTRM_OM_GameplaymenuBG, 4, (u_long *)(gGT->backBuffer->otMem).startPlusFour); // draw the actual menu background
}

// the Menu function
void UDCTRM_OM_GameplayFuncPtr(struct RectMenu* menu)
{
	ProcessInputs(mb, sdata->gGT, sdata->gGamepads->gamepad[0].buttonsTapped);
	DisplayMenu(mb, sdata->gGT);
}