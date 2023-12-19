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

force_inline void IDENTIFYGAMEPADS_MainFreeze_MenuPtrOptions(struct MenuBox* mb, GAMEPAD_MainFreeze_MenuPtrOptions* gamepad)
{
	// get number of ordinary gamepads and/or "analog controllers" connected, and which players are using which
	if (sdata->gGT->numPlyrCurrGame != 0)
	{
		for(int i = 0; i < sdata->gGT->numPlyrCurrGame; i++)
		{
			struct ControllerPacket* ptrControllerPacket = sdata->gGamepads->gamepad[i].ptrControllerPacket;

			// if gamepad is not an "analog controller", as CTR uses to refer to jogcons and negcons
			if
			(
				((ptrControllerPacket == 0) || (ptrControllerPacket->isControllerConnected != 0)) ||
				((ptrControllerPacket->controllerData != ((PAD_ID_JOGCON << 4) | 3) && (ptrControllerPacket->controllerData != ((PAD_ID_NEGCON << 4) | 3))))
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
	}

	int areBothControllerLabelsNecessary = false;
	if (gamepad->numGamepads != 0) areBothControllerLabelsNecessary = (gamepad->numAnalogs != 0);

	gamepad->menuRowsToRemove = (4 - areBothControllerLabelsNecessary) - sdata->gGT->numPlyrCurrGame;
}

force_inline void PROCESSINPUTS_MainFreeze_MenuPtrOptions(struct MenuBox* mb, GAMEPAD_MainFreeze_MenuPtrOptions* gamepad)
{
	int exitMenu = false;

	if (sdata->AnyPlayerTap & (BTN_UP | BTN_DOWN))
	{
		// play sound for when you're moving around in the menu
		OtherFX_Play(0, 1);

		// there are only 9 rows total
		if (sdata->AnyPlayerTap & BTN_UP)
		{
			mb->rowSelected = (mb->rowSelected + (9 - 1)) % 9;
			if (mb->rowSelected == 7) mb->rowSelected = sdata->gGT->numPlyrCurrGame + 3;
		}
		if (sdata->AnyPlayerTap & BTN_DOWN)
		{
			mb->rowSelected = (mb->rowSelected + 1) % 9;
			if (mb->rowSelected > (sdata->gGT->numPlyrCurrGame + 3)) mb->rowSelected = 8;
		}
	}

	switch (mb->rowSelected)
	{
		// 0: FX slider
		// 1: Music slider
		// 2: Voice slider
		case 0:
		case 1:
		case 2:
			OptionsMenu_TestSound(mb->rowSelected, 1);
			if (sdata->AnyPlayerHold & (BTN_LEFT | BTN_RIGHT))
			{
				int volume = howl_VolumeGet(mb->rowSelected) & 0xff;

				if (sdata->AnyPlayerHold & BTN_LEFT)  volume = (volume + (0xff - 4)) % 0xff;
				if (sdata->AnyPlayerHold & BTN_RIGHT) volume = (volume + 4) % 0xff;

				howl_VolumeSet(mb->rowSelected, volume);
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

				int gamepadRow = mb->rowSelected - 4;

				if (gamepadRow < gamepad->numGamepads)
				{
					// selecting dualshock row
					// toggle gamepad vibration
					sdata->gGT->gameMode1 ^= data.gGT_gameMode1_Vibration_PerPlayer[gamepad->gamepadId[gamepadRow]];
				}
				else
				{
					// selecting "analog controller" row
					// this will open the analog controller config menu
					sdata->gamepad_ID_ThatOpenedRaceWheelConfig = gamepad->analogId[gamepadRow - gamepad->numGamepads];
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
		MENUBOX_ClearInput();
		sdata->ptrDesiredMenuBox = MainFreeze_GetMenuBox();
	}
}

// stuff is drawn last to first
force_inline void DISPLAYMENUBOX_MainFreeze_MenuPtrOptions(struct MenuBox* mb, GAMEPAD_MainFreeze_MenuPtrOptions* gamepad)
{
	// note: multitap only works if it's connected to the P1 slot
	int isMultitap = (sdata->gGamepads->slotBuffer[0].controllerData == (PAD_ID_MULTITAP << 4));

	int somethingToDoWithVolumeLineWidth = 0;

	// a menubox row is 10 pixels
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
	mb->drawStyle &= 0xfeff;
	if (sdata->gGT->numPlyrCurrGame > 2) mb->drawStyle |= 0x100;

	for(int i = 0; i < 3; i++)
	{
		int lineWidth = DecalFont_GetLineWidth(sdata->lngStrings[data.Options_StringIDs_Audio[i]], FONT_SMALL);
		if (somethingToDoWithVolumeLineWidth < lineWidth) somethingToDoWithVolumeLineWidth = lineWidth;
	}

	// "OPTIONS"
	DecalFont_DrawLine(sdata->lngStrings[324], 256, (menuRowsNegativePadding / 2) + 26, FONT_BIG, (JUSTIFY_CENTER | ORANGE));

	int whateverThisIsNow = 380 - (somethingToDoWithVolumeLineWidth + 30);
	int thisOtherThing = whateverThisIsNow - 5;

	// draw volume sliders
	for(int i = 0; i <3; i++)
	{
		int volume = howl_VolumeGet(i) & 0xff;
		int iDontKnow = volume * thisOtherThing;

		short volumeHeightSomething = (menuRowsNegativePadding / 2) + (i * 10);

		if (iDontKnow < 0) iDontKnow += 0xff;

		int beatsMe = somethingToDoWithVolumeLineWidth + 30;
		int knowAsMuchAsIDo = beatsMe + (short)((u_int)iDontKnow >> 8) + 0x38; // yeah, I really don't know

		RECT volumeSliderBar =
		{
			.x = knowAsMuchAsIDo + 1,
			.y = volumeHeightSomething + 48,
			.w = 3,
			.h = 10
		};
		CTR_Box_DrawSolidBox(&volumeSliderBar, (u_int *)(data.Options_VolumeSlider_Colors + 0xc), (u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour, &sdata->gGT->backBuffer->primMem);
		RECT volumeSliderBarOutline =
		{
			.x = knowAsMuchAsIDo,
			.y = volumeHeightSomething + 47,
			.w = 5,
			.h = 12
		};
		CTR_Box_DrawSolidBox(&volumeSliderBarOutline, (u_int *)(data.Options_VolumeSlider_Colors + 0x10), (u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour, &sdata->gGT->backBuffer->primMem);
		short volumeSliderTriangle[8] =
		{
			beatsMe + 56,
			volumeHeightSomething + 58,
			beatsMe + whateverThisIsNow + 56,
			volumeHeightSomething + 48,
			volumeSliderTriangle[2],
			volumeSliderTriangle[1]
		};
		MENUBOX_DrawRwdTriangle(volumeSliderTriangle, data.Options_VolumeSlider_Colors, (u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour, &sdata->gGT->backBuffer->primMem);
		
		// "FX:" "MUSIC:" "VOICE:"
		DecalFont_DrawLine(sdata->lngStrings[data.Options_StringIDs_Audio[i]], 76, (i * 10) + (menuRowsNegativePadding / 2) + 50, FONT_SMALL, ORANGE);
	}

	// "MODE:"
	DecalFont_DrawLine(sdata->lngStrings[332], 76, (menuRowsNegativePadding / 2) + 80, FONT_SMALL, ORANGE);

	int mode = howl_ModeGet();
	char* volumeModeString = (mode == 0 ? sdata->lngStrings[333] : sdata->lngStrings[334]);

	DecalFont_DrawLine(volumeModeString, 436, (menuRowsNegativePadding / 2) + 80, FONT_SMALL, (JUSTIFY_RIGHT | WHITE));

	if (gamepad->numGamepads != 0)
	{
		// "DUAL SHOCK:"
		DecalFont_DrawLine(sdata->lngStrings[330], 76, (menuRowsNegativePadding / 2) + 90, FONT_SMALL, ORANGE);

		int lineWidth_idk = DecalFont_GetLineWidth(sdata->lngStrings[data.Options_StringIDs_Gamepads[2]], FONT_SMALL);
		int lineWidth_vibrateOff = DecalFont_GetLineWidth(sdata->lngStrings[326], FONT_SMALL);
		int lineWidth_vibrateOn = DecalFont_GetLineWidth(sdata->lngStrings[325], FONT_SMALL);

		if (lineWidth_vibrateOn < lineWidth_vibrateOff) lineWidth_vibrateOn = lineWidth_vibrateOff;

		lineWidth_vibrateOn = (lineWidth_idk + lineWidth_vibrateOn + 10);
		lineWidth_vibrateOn = 256 - (lineWidth_vibrateOn - (lineWidth_vibrateOn >> 0xf) >> 1);

		if (gamepad->numGamepads > 0)
		{
			for(int i = 0; i < gamepad->numGamepads; i++)
			{
				int gamepadConnected = false;
				int dualShockRowColor = ORANGE;
				int currPad = gamepad->gamepadId[i];
				struct ControllerPacket* ptrControllerPacket = sdata->gGamepads->gamepad[currPad].ptrControllerPacket;

				if (ptrControllerPacket == 0 || ptrControllerPacket->isControllerConnected != 0)
				{
					gamepadConnected = true;
					dualShockRowColor = GRAY;
				}

				// "CONTROLLER 1", "CONTROLLER 2", "CONTROLLER 1A", "CONTROLLER 1B", "CONTROLLER 1C", "CONTROLLER 1D"
				DecalFont_DrawLine
				(
					sdata->lngStrings[data.Options_StringIDs_Gamepads[currPad + isMultitap]], //perhaps isMultitap * 2?
					lineWidth_vibrateOn,
					(i * 10) + (menuRowsNegativePadding / 2) + 100,
					FONT_SMALL, dualShockRowColor
				);

				char* dualshockVibrateString = 0;

				if ((sdata->gGT->gameMode1 & data.gGT_gameMode1_Vibration_PerPlayer[currPad]) == 0)
				{
					// "VIBRATE ON"
					dualshockVibrateString = sdata->lngStrings[325];
				}
				else
				{
					// "VIBRATE OFF"
					dualshockVibrateString = sdata->lngStrings[326];
				}

				dualShockRowColor = GRAY;
				if ((!gamepadConnected) && (dualShockRowColor = RED, (sdata->gGT->gameMode1 & data.gGT_gameMode1_Vibration_PerPlayer[currPad]) == 0))
				{
					dualShockRowColor = WHITE;
				}

				DecalFont_DrawLine
				(
					dualshockVibrateString,
					lineWidth_vibrateOn + lineWidth_idk + 10,
					(i * 10) + (menuRowsNegativePadding / 2) + 100,
					FONT_SMALL, dualShockRowColor
				);
			}
		}
	}

	if (gamepad->numAnalogs != 0)
	{
		// "CONFIGURE ANALOG:"
		DecalFont_DrawLine(sdata->lngStrings[336], 76, analogRowPosY + (menuRowsNegativePadding / 2) + 90, FONT_SMALL, ORANGE);

		if (gamepad->numAnalogs > 0)
		{
			for(int i = 0; i < gamepad->numAnalogs; i++)
			{
				DecalFont_DrawLine
				(
					sdata->lngStrings[data.Options_StringIDs_Gamepads[gamepad->analogId[i] + isMultitap]],
					256,
					(menuRowsNegativePadding / 2) + analogRowPosY + (i * 10) + 100,
					FONT_SMALL, (JUSTIFY_CENTER | ORANGE)
				);
			}
		}
	}

	// "EXIT"
	DecalFont_DrawLine(sdata->lngStrings[331], 76, (menuRowsNegativePadding / 2) + 140 - menuRowsNegativePadding, FONT_SMALL, ORANGE);

	RECT cursor =
	{
		.x = 74,
		.y = data.Options_HighlightBar[mb->rowSelected].posY + (menuRowsNegativePadding / 2) + 20,
		.w = 364,
		.h = data.Options_HighlightBar[mb->rowSelected].sizeY
	};
	CTR_Box_DrawClearBox(&cursor, &sdata->menuRowHighlight_Normal, TRANS_50_DECAL, (u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour, &sdata->gGT->backBuffer->primMem);

	RECT titleSeparatorLine =
	{
		.x = 66,
		.y = (menuRowsNegativePadding / 2) + 43,
		.w = 380,
		.h = 2
	};
	MENUBOX_DrawOuterRect_Edge(&titleSeparatorLine, (u_int)&sdata->battleSetup_Color_UI_1, 0x20, (u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour);

	RECT menuBoxBG =
	{
		.x = 56,
		.y = (menuRowsNegativePadding / 2) + 20,
		.w = 400,
		.h = 135 - menuRowsNegativePadding
	};
	MENUBOX_DrawInnerRect(&menuBoxBG, 4, (u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour);
}

void DECOMP_MainFreeze_MenuPtrOptions(struct MenuBox* mb)
{
	MainFreeze_SafeAdvDestroy();

	// open racing wheel config menu instead
	if (sdata->boolOpenWheelConfig != 0)
	{
		MainFreeze_ConfigSetupEntry();
		return;
	}

	GAMEPAD_MainFreeze_MenuPtrOptions gamepad =
	{
		.numGamepads = 0,
		.numAnalogs = 0,
		.gamepadId = {-1, -1, -1, -1},
		.analogId = {-1, -1, -1, -1},
		.isGamepadAnalog = {false, false, false, false},
		.menuRowsToRemove = 0,
	};

	IDENTIFYGAMEPADS_MainFreeze_MenuPtrOptions(mb, &gamepad);
	PROCESSINPUTS_MainFreeze_MenuPtrOptions(mb, &gamepad);
	DISPLAYMENUBOX_MainFreeze_MenuPtrOptions(mb, &gamepad);

	printf("%d\n", mb->rowSelected);
}