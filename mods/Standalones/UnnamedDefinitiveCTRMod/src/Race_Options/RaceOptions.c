#include <common.h>
#include "RaceOptions.h"

u_int UDCTRM_RO_rowSelected = 0; // race options menu row, should start at 0
u_char UDCTRM_RO_numLaps[4] = {1, 3, 5, 7}; // accepted values for laps option, just the lap amounts from the og game
u_int UDCTRM_RO_numLapsIndex = 1; // number of laps should be 3 by default
extern u_int UDCTRM_RF_blueFireMode; // found in BlueFireInt.c
extern u_int UDCTRM_MI_mirrorMode; // found in MI_main.C
// extern u_int UDCTRM_IL_itemless;
extern u_int UDCTRM_RO_isOpen; // found in trackselect menu... for now?

force_inline void ProcessInputs(struct GameTracker* gGT, u_int buttonsTapped)
{
	// change row
	if (buttonsTapped & (BTN_UP | BTN_DOWN))
	{
		// play sound for when you're moving around in the menu
		OtherFX_Play(0, 1);

		if (buttonsTapped & BTN_UP)
		{
			UDCTRM_RO_rowSelected = (UDCTRM_RO_rowSelected + (UDCTRM_RO_NUM_ROWS - 1)) % UDCTRM_RO_NUM_ROWS;
		}

		if (buttonsTapped & BTN_DOWN)
		{
			UDCTRM_RO_rowSelected = (UDCTRM_RO_rowSelected + 1) % UDCTRM_RO_NUM_ROWS;
		}
	}

	if (buttonsTapped & (BTN_CROSS | BTN_CIRCLE))
	{
		switch (UDCTRM_RO_rowSelected)
		{
			case 0:
				// number of laps
				// we don't want players to change laps in time trial...
				if (!(gGT->gameMode1 & TIME_TRIAL))
				{
					OtherFX_Play(1, 1);
					UDCTRM_RO_numLapsIndex = (UDCTRM_RO_numLapsIndex + 1) % 4;
					gGT->numLaps = UDCTRM_RO_numLaps[UDCTRM_RO_numLapsIndex];
				}
				else
				{
					// denied!
					OtherFX_Play(5, 1);
				}
				break;
			case 1:
				// toggle blue fire mode
				UDCTRM_RF_blueFireMode = (UDCTRM_RF_blueFireMode + 1) % 3;
				OtherFX_Play(1, 1);
				break;
			case 2:
				// mirror mode -- not yet implemented
				UDCTRM_MI_mirrorMode = (UDCTRM_MI_mirrorMode + 1) % 2;
				OtherFX_Play(1, 1);
				break;
			case 3:
				// exit
				OtherFX_Play(1, 1);
				goto CLOSE_RO_MENU;
		}
	}

	if (buttonsTapped & (BTN_SQUARE | BTN_TRIANGLE | BTN_START))
	{
		if (buttonsTapped & (BTN_SQUARE | BTN_TRIANGLE)) OtherFX_Play(2, 1); // back sound
		else                                             OtherFX_Play(1, 1); // accept sound
		CLOSE_RO_MENU:
		// this variable controls when the track select menu function will draw the race options menu
		UDCTRM_RO_isOpen = false;
	}
}

// draw menu
force_inline void DisplayMenu(struct GameTracker* gGT)
{
	u_int firstRowY = ((UDCTRM_RO_MenuProcBG_y + 4) + 26);
	u_int optionTextPosX = (UDCTRM_RO_glowingcursor.x + UDCTRM_RO_glowingcursor.w) - 2;

	UDCTRM_RO_glowingcursor.y = firstRowY + (10 * UDCTRM_RO_rowSelected);

	// "RACE OPTIONS"
	DecalFont_DrawLine(sdata->lngStrings[593], SCREEN_WIDTH/2, UDCTRM_RO_MenuProcBG_y + 4, FONT_BIG, (JUSTIFY_CENTER | ORANGE));

	// "LAPS"
	DecalFont_DrawLine(sdata->lngStrings[594], UDCTRM_RO_glowingcursor.x + 2, firstRowY + (10 * 0) + 1, FONT_SMALL, ORANGE);
	// "BLUE FIRE"
	DecalFont_DrawLine(sdata->lngStrings[595], UDCTRM_RO_glowingcursor.x + 2, firstRowY + (10 * 1) + 1, FONT_SMALL, ORANGE);
	// "MIRROR MODE"
	DecalFont_DrawLine(sdata->lngStrings[596], UDCTRM_RO_glowingcursor.x + 2, firstRowY + (10 * 2) + 1, FONT_SMALL, ORANGE);
	// "EXIT"
	DecalFont_DrawLine(sdata->lngStrings[331], UDCTRM_RO_glowingcursor.x + 2, firstRowY + (10 * 3) + 1, FONT_SMALL, ORANGE);

	int lapsSettingColor = WHITE;
	if (gGT->gameMode1 & TIME_TRIAL) lapsSettingColor = GRAY;

	// Laps:
	DecalFont_DrawLine(sdata->lngStrings[600 + UDCTRM_RO_numLapsIndex], optionTextPosX, firstRowY + (10 * 0) + 1, FONT_SMALL, lapsSettingColor | JUSTIFY_RIGHT);

	int blueFireSettingColor = CORTEX_RED;
	if (UDCTRM_RF_blueFireMode == 1) blueFireSettingColor = TINY_GREEN;
	if (UDCTRM_RF_blueFireMode == 2) blueFireSettingColor = CRASH_BLUE;

	// Blue Fire:
	DecalFont_DrawLine(sdata->lngStrings[597 + UDCTRM_RF_blueFireMode], optionTextPosX, firstRowY + (10 * 1) + 1, FONT_SMALL, blueFireSettingColor | JUSTIFY_RIGHT);
	
	// Mirror Mode:
	int mirrorModeSettingColor = GRAY;
	if (UDCTRM_MI_mirrorMode == 1) mirrorModeSettingColor = TINY_GREEN;
	DecalFont_DrawLine(sdata->lngStrings[597 + UDCTRM_MI_mirrorMode], optionTextPosX, firstRowY + (10 * 2) + 1, FONT_SMALL, mirrorModeSettingColor | JUSTIFY_RIGHT);

	RECTMENU_DrawInnerRect(&UDCTRM_RO_titleSeparatorLine, 4, (u_long *)(gGT->backBuffer->otMem).startPlusFour); // draw the line that's below the title
	CTR_Box_DrawClearBox(&UDCTRM_RO_glowingcursor, &sdata->menuRowHighlight_Normal, 1, (u_long *)(gGT->backBuffer->otMem).startPlusFour, &gGT->backBuffer->primMem); // draw glowing cursor
	RECTMENU_DrawInnerRect(&UDCTRM_RO_menuBG, 4, (u_long *)(gGT->backBuffer->otMem).startPlusFour); // draw the actual menu background
}

// the Menu function
// remember: this is a fake menu. this doesn't make use of a menu struct at all
void UDCTRM_RaceOptions()
{
	ProcessInputs(sdata->gGT, sdata->gGamepads->gamepad[0].buttonsTapped);
	DisplayMenu(sdata->gGT);
}