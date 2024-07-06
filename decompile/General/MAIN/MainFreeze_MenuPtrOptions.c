#include <common.h>

typedef struct
{
	int numGamepads;
	int numAnalogs;
	int gamepadId[4];
	int analogId[4];
	int isGamepadAnalog[4];
	int menuRowsToRemove;
} GAMEPAD_MainFreeze_MenuPtrOptions;

force_inline void IDENTIFYGAMEPADS_MainFreeze_MenuPtrOptions(struct RectMenu* menu, GAMEPAD_MainFreeze_MenuPtrOptions* gamepad)
{
	struct GameTracker* gGT = sdata->gGT;

	// get number of ordinary gamepads and/or "analog controllers" connected, and which players are using which

	for(int i = 0; i < gGT->numPlyrCurrGame; i++)
	{
		struct ControllerPacket* ptrControllerPacket = sdata->gGamepads->gamepad[i].ptrControllerPacket;

		// if gamepad is not an "analog controller", as CTR uses to refer to jogcons and negcons
		if
		(
			(
				(ptrControllerPacket == 0) ||
				(ptrControllerPacket->isControllerConnected != 0)
			) ||

			(
				(ptrControllerPacket->controllerData != ((PAD_ID_JOGCON << 4) | 3)) &&
				(ptrControllerPacket->controllerData != ((PAD_ID_NEGCON << 4) | 3))
			)
		)
		{
			gamepad->gamepadId[gamepad->numGamepads] = i;
			gamepad->isGamepadAnalog[i] = false;
			gamepad->numGamepads++;
		}
		else
		{
			gamepad->analogId[gamepad->numAnalogs] = i;
			gamepad->isGamepadAnalog[i] = true;
			gamepad->numAnalogs++;
		}
	}

	// the menu buttons for configuring dualshocks and analog controllers are accompanied by labels each
	// these labels can appear at once
	int areBothControllerLabelsNecessary = false;
	if (gamepad->numGamepads != 0) areBothControllerLabelsNecessary = (gamepad->numAnalogs != 0);

	// set amount of menu rows to hide/remove
	// used for the dualshock and/or "analog" rows which are variable

	// in singleplayer, regardless of gamepad, 2 of these rows are always visible
	// (dualshock label + 1 gamepad)

	// with 4 regular gamepads connected, in multiplayer, there's 5 rows visible
	// (dualshock label + 4 gamepads)

	// maximum amount of rows is 6, which happens if there's 4 controllers and one of them is analog
	// (dualshock label + analog label + 4 gamepads)

	// in the last scenario, menuRowsToRemove will equal -1
	gamepad->menuRowsToRemove = (4 - areBothControllerLabelsNecessary) - gGT->numPlyrCurrGame;
}

force_inline void PROCESSINPUTS_MainFreeze_MenuPtrOptions(struct RectMenu* menu, GAMEPAD_MainFreeze_MenuPtrOptions* gamepad)
{
	struct GameTracker* gGT = sdata->gGT;
	int exitMenu = false;

	if (sdata->AnyPlayerTap & (BTN_UP | BTN_DOWN))
	{
		// play sound for when you're moving around in the menu
		OtherFX_Play(0, 1);

		// there are only 9 rows total
		if (sdata->AnyPlayerTap & BTN_UP)
		{
			menu->rowSelected = (menu->rowSelected + (9 - 1)) % 9;
			if (menu->rowSelected == 7) menu->rowSelected = gGT->numPlyrCurrGame + 3;
		}
		if (sdata->AnyPlayerTap & BTN_DOWN)
		{
			menu->rowSelected = (menu->rowSelected + 1) % 9;
			if (menu->rowSelected > (gGT->numPlyrCurrGame + 3)) menu->rowSelected = 8;
		}
	}

	switch (menu->rowSelected)
	{
		// 0: FX slider
		// 1: Music slider
		// 2: Voice slider
		case 0:
		case 1:
		case 2:
			OptionsMenu_TestSound(menu->rowSelected, 1);
			if (sdata->AnyPlayerHold & (BTN_LEFT | BTN_RIGHT))
			{
				int volume = howl_VolumeGet(menu->rowSelected);

				if (sdata->AnyPlayerHold & BTN_LEFT)  volume -= FPS_HALF(4);
				if (sdata->AnyPlayerHold & BTN_RIGHT) volume += FPS_HALF(4);

				if(volume < 0) volume = 0;
				if(volume > 0xff) volume = 0xff;

				howl_VolumeSet(menu->rowSelected, volume);
			}
			break;

		// Mode	(Stereo/Mono)
		case 3:
			// clear test sound
			OptionsMenu_TestSound(0, 0);

			if (sdata->AnyPlayerTap & (BTN_CIRCLE | BTN_CROSS_one))
			{
				OtherFX_Play(1, 1);
				int mode = howl_ModeGet();
				howl_ModeSet(mode == 0);
			}
			break;

		// DualShock/"Analog controller" settings
		case 4:
		case 5:
		case 6:
		case 7:
			// clear test sound
			OptionsMenu_TestSound(0, 0);

			if (sdata->AnyPlayerTap & (BTN_CIRCLE | BTN_CROSS_one))
			{
				OtherFX_Play(1, 1);

				int gamepadRow = menu->rowSelected - 4;

				if (gamepadRow < gamepad->numGamepads)
				{
					// selecting dualshock row
					// toggle gamepad vibration
					gGT->gameMode1 ^= data.gGT_gameMode1_VibPerPlayer[gamepad->gamepadId[gamepadRow]];
				}
				else
				{
					// selecting "analog controller" row
					// this will open the analog controller config menu
					sdata->gamepadID_OwnerRaceWheelConfig = gamepad->analogId[gamepadRow - gamepad->numGamepads];
					sdata->boolOpenWheelConfig = true;
					sdata->raceWheelConfigPageIndex = 0;
				}
			}
			break;

		// Exit
		case 8:
			// clear test sound
			OptionsMenu_TestSound(0, 0);

			if (sdata->AnyPlayerTap & (BTN_CIRCLE | BTN_CROSS_one))
			{
				OtherFX_Play(1, 1);
				exitMenu = true;
			}
			break;
	}

	if (exitMenu || (sdata->AnyPlayerTap & (BTN_TRIANGLE | BTN_START | BTN_SQUARE_one)))
	{
		OtherFX_Play(1, 1);
		OptionsMenu_TestSound(0, 0);
		RECTMENU_ClearInput();
		sdata->ptrDesiredMenu = DECOMP_MainFreeze_GetMenuPtr();
	}
}

// stuff is drawn last to first
force_inline void DISPLAYRECTMENU_MainFreeze_MenuPtrOptions(struct RectMenu* menu, GAMEPAD_MainFreeze_MenuPtrOptions* gamepad)
{
	struct GameTracker* gGT = sdata->gGT;

	// note: multitap only works if it's connected to the P1 slot
	int isMultitap = (sdata->gGamepads->slotBuffer[0].controllerData == (PAD_ID_MULTITAP << 4));

	// a menu row is 10 pixels
	int menuRowsNegativePadding = gamepad->menuRowsToRemove * 10;

	int analogRowPosY = 0;
	if (gamepad->numGamepads != 0) analogRowPosY = (gamepad->numGamepads + 1) * 10;

	// cursor location for exit button, which will change depending on how many dualshock rows there need to be
	data.Options_HighlightBar[8].posY = gamepad->menuRowsToRemove * -10 + 119;

	// cursor location for dualshock rows
	if (gamepad->numGamepads > 0)
	{
		for(int i = 0; i < gamepad->numGamepads; i++)
		{
			data.Options_HighlightBar[i + 4].posY = (i * 10) + 79;
		}
	}

	// cursor location for "analog" rows
	if (gamepad->numAnalogs > 0)
	{
		for(int i = 0; i < gamepad->numAnalogs; i++)
		{
			int areBothControllerLabelsNecessary = false;
			if (gamepad->numGamepads != 0) areBothControllerLabelsNecessary = (gamepad->numAnalogs != 0);

			data.Options_HighlightBar[gamepad->numGamepads + i + 4].posY = ((gamepad->numGamepads + i + areBothControllerLabelsNecessary) * 10) + 79;
		}
	}

	// drawStyle needs research...
	menu->drawStyle &= 0xfeff;
	if (gGT->numPlyrCurrGame > 2)
		menu->drawStyle |= 0x100;

	int volumeSliderTriangleLeftMargin = 0;

	for(int i = 0; i < 3; i++)
	{
		//"FX:", "MUSIC:", "VOICE:"
		int lineWidth = DECOMP_DecalFont_GetLineWidth(sdata->lngStrings[data.Options_StringIDs_Audio[i]], FONT_SMALL);
		if (volumeSliderTriangleLeftMargin < lineWidth) volumeSliderTriangleLeftMargin = lineWidth;
	}

	// "OPTIONS"
	DecalFont_DrawLine(
		sdata->lngStrings[324],
		256,
		26 + (menuRowsNegativePadding / 2),
		FONT_BIG, (JUSTIFY_CENTER | ORANGE));

	int volumeSliderWidth = 380 - (30 + volumeSliderTriangleLeftMargin);

	struct OTMem* otMem = &gGT->backBuffer->otMem;
	struct PrimMem* primMem = &gGT->backBuffer->primMem;

	// draw volume sliders
	for(int i = 0; i <3; i++)
	{
		int volume = howl_VolumeGet(i) & 0xff;
		int volumeSliderValue = volume * (volumeSliderWidth - 5);

		short volumeSliderPosY = (menuRowsNegativePadding / 2) + (i * 10);

		if (volumeSliderValue < 0) volumeSliderValue += 0xff;

		int volumeSliderTriangleLeftPosX = 30 + volumeSliderTriangleLeftMargin;
		int volumeSliderBarPosX = 0x38 + volumeSliderTriangleLeftPosX + (short)((u_int)volumeSliderValue >> 8);

		short volumeSliderTriangle[8] =
		{
			// 0, 1
			volumeSliderTriangleLeftPosX + 56,
			volumeSliderPosY + 58,

			// 2, 3
			volumeSliderTriangleLeftPosX + volumeSliderWidth + 56,
			volumeSliderPosY + 48,

			// 4, 5
			0,0
		};

		volumeSliderTriangle[4] = volumeSliderTriangle[2];
		volumeSliderTriangle[5] = volumeSliderTriangle[1];

		RECT volumeSliderBar =
		{
			.x = volumeSliderBarPosX + 1,
			.y = volumeSliderPosY + 48,
			.w = 3,
			.h = 10
		};
		Color color = *(Color *)(data.Options_VolumeSlider_Colors + 0xc);
		DECOMP_CTR_Box_DrawSolidBox(
			&volumeSliderBar,
			color,
			otMem->startPlusFour);

		RECT volumeSliderBarOutline =
		{
			.x = volumeSliderBarPosX,
			.y = volumeSliderPosY + 47,
			.w = 5,
			.h = 12
		};

		color = *(Color *)(data.Options_VolumeSlider_Colors + 0x10);
		DECOMP_CTR_Box_DrawSolidBox(
			&volumeSliderBarOutline,
			color,
			otMem->startPlusFour);

		RECTMENU_DrawRwdTriangle(
			volumeSliderTriangle,
			data.Options_VolumeSlider_Colors,
			otMem->startPlusFour,
			primMem);

		// "FX:" "MUSIC:" "VOICE:"
		DecalFont_DrawLine(
			sdata->lngStrings[data.Options_StringIDs_Audio[i]],
			76,
			50 + (menuRowsNegativePadding / 2) + (i * 10),
			FONT_SMALL, ORANGE);
	}

	// "MODE:"
	DecalFont_DrawLine(
		sdata->lngStrings[332],
		76,
		80 + (menuRowsNegativePadding / 2),
		FONT_SMALL, ORANGE);

	// 333: MONO
	// 334: STEREO
	int mode = howl_ModeGet();

	// "MONO", "STEREO"
	DecalFont_DrawLine(
		sdata->lngStrings[333 + mode],
		436,
		80 + (menuRowsNegativePadding / 2),
		FONT_SMALL, (JUSTIFY_RIGHT | WHITE));

	if (gamepad->numGamepads != 0)
	{
		// "DUAL SHOCK:"
		DecalFont_DrawLine(
			sdata->lngStrings[330],
			76,
			90 + (menuRowsNegativePadding / 2),
			FONT_SMALL, ORANGE);

		int lineWidth_controller1A =
			DECOMP_DecalFont_GetLineWidth(sdata->lngStrings[data.Options_StringIDs_Gamepads[2]], FONT_SMALL);

		// width can change depending on language
		int lineWidth_vibrateOff = DECOMP_DecalFont_GetLineWidth(sdata->lngStrings[326], FONT_SMALL);
		int lineWidth_vibrateOn = DECOMP_DecalFont_GetLineWidth(sdata->lngStrings[325], FONT_SMALL);
		if (lineWidth_vibrateOn < lineWidth_vibrateOff) lineWidth_vibrateOn = lineWidth_vibrateOff;

		lineWidth_vibrateOn = (lineWidth_controller1A + lineWidth_vibrateOn + 10);
		lineWidth_vibrateOn = 256 - (lineWidth_vibrateOn >> 1);

		for(int i = 0; i < gamepad->numGamepads; i++)
		{
			int gamepadConnected = false;
			int dualShockRowColor = ORANGE;
			int currPad = gamepad->gamepadId[i];

			struct ControllerPacket* ptrControllerPacket =
				sdata->gGamepads->gamepad[currPad].ptrControllerPacket;

			if (ptrControllerPacket == 0 || ptrControllerPacket->isControllerConnected != 0)
			{
				gamepadConnected = true;
				dualShockRowColor = GRAY;
			}

			int rowY =
				100 + (menuRowsNegativePadding / 2) + (i * 10);

			// "CONTROLLER 1", "CONTROLLER 2",
			// "CONTROLLER 1A", "CONTROLLER 1B",
			// "CONTROLLER 1C", "CONTROLLER 1D"
			DecalFont_DrawLine
			(
				sdata->lngStrings[data.Options_StringIDs_Gamepads[currPad + isMultitap]],
				lineWidth_vibrateOn,
				rowY,
				FONT_SMALL, dualShockRowColor
			);

			// ON: 0
			// OFF: 1
			int boolDisabled =
				(gGT->gameMode1 & data.gGT_gameMode1_VibPerPlayer[currPad]) == 0;

			dualShockRowColor = GRAY;
			if (!gamepadConnected)
			{
				// RED: 3
				// WHITE: 4
				dualShockRowColor = RED + boolDisabled;
			}

			// 325: "VIBRATE ON"
			// 326: "VIBRATE OFF"

			DecalFont_DrawLine(
				sdata->lngStrings[325 + boolDisabled],
				lineWidth_vibrateOn + lineWidth_controller1A + 10,
				rowY,
				FONT_SMALL, dualShockRowColor);
		}
	}

	if (gamepad->numAnalogs != 0)
	{
		// "CONFIGURE ANALOG:"
		DecalFont_DrawLine(
			sdata->lngStrings[336],
			76,
			90 + (menuRowsNegativePadding / 2) + analogRowPosY,
			FONT_SMALL, ORANGE);

		for(int i = 0; i < gamepad->numAnalogs; i++)
		{
			DecalFont_DrawLine
			(
				sdata->lngStrings[
					data.Options_StringIDs_Gamepads[
						gamepad->analogId[i] + isMultitap]],
				256,
				100 + (menuRowsNegativePadding / 2) + analogRowPosY + (i * 10),
				FONT_SMALL, (JUSTIFY_CENTER | ORANGE)
			);
		}
	}

	// "EXIT"
	DecalFont_DrawLine(
		sdata->lngStrings[331],
		76,
		140 - (menuRowsNegativePadding / 2),
		FONT_SMALL, ORANGE);

	RECT cursor =
	{
		.x = 74,
		.y = data.Options_HighlightBar[menu->rowSelected].posY + (menuRowsNegativePadding / 2) + 20,
		.w = 364,
		.h = data.Options_HighlightBar[menu->rowSelected].sizeY
	};

	Color color;
	color.self = sdata->menuRowHighlight_Normal;
	DECOMP_CTR_Box_DrawClearBox(
		&cursor, color,
		TRANS_50_DECAL, otMem->startPlusFour);

	RECT titleSeparatorLine =
	{
		.x = 66,
		.y = (menuRowsNegativePadding / 2) + 43,
		.w = 380,
		.h = 2
	};

	color.self = sdata->battleSetup_Color_UI_1;
	DECOMP_RECTMENU_DrawOuterRect_Edge(
		&titleSeparatorLine,
		color,
		0x20, otMem->startPlusFour);

	RECT menuBG =
	{
		.x = 56,
		.y = (menuRowsNegativePadding / 2) + 20,
		.w = 400,
		.h = 135 - menuRowsNegativePadding
	};

	RECTMENU_DrawInnerRect(
		&menuBG, 4, otMem->startPlusFour);
}

void DECOMP_MainFreeze_MenuPtrOptions(struct RectMenu* menu)
{
	DECOMP_MainFreeze_SafeAdvDestroy();

	// open racing wheel config menu instead
	if (sdata->boolOpenWheelConfig != 0)
	{
		MainFreeze_ConfigSetupEntry();
		return;
	}

	// the options menu has gamepad-related settings
	// specificially for DualShock controllers
	// as well as what CTR refers to as "analog controllers", which are jogcons and negcons
	// this struct will be filled out in IDENTIFYGAMEPADS
	GAMEPAD_MainFreeze_MenuPtrOptions gamepad =
	{
		.numGamepads = 0,
		.numAnalogs = 0,
		.gamepadId = {-1, -1, -1, -1},
		.analogId = {-1, -1, -1, -1},
		.isGamepadAnalog = {false, false, false, false},
		.menuRowsToRemove = 0,
	};

	IDENTIFYGAMEPADS_MainFreeze_MenuPtrOptions(menu, &gamepad);
	PROCESSINPUTS_MainFreeze_MenuPtrOptions(menu, &gamepad);
	DISPLAYRECTMENU_MainFreeze_MenuPtrOptions(menu, &gamepad);
}