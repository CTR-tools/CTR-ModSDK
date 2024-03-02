#include <common.h>

void DECOMP_MainFreeze_MenuPtrOptions(struct MenuBox* mb)
{
	short sVar1;
	char bVar2;
	short sVar3;
	short menuRowsNegativePadding_halved_again;
	char cVar5;
	u_short uVar6;
	int iVar7;
	short menuRowsToRemove;
	struct ControllerPacket *psVar9;
	int iVar10;
	char **volumeModeString;
	char **dualshockVibrateString;
	u_short areBothControllerLabelsNecessary;
	int selectedRow;
	int somethingToDoWithVolumeLineWidth;
	int i;
	u_int uVar13;
	int iVar14;

	u_short uVar15;
	u_short analogId [4];
	u_short gamepadId [4];
	u_short isGamepadAnalog [4];

	// used for the volume sliders
	RECT volumeSliderBar;
	RECT volumeSliderBarOutline;
	short volumeSliderTriangle [8];

	// extra menubox details
	RECT glowingcursor;
	RECT titleSeparatorLine;
	RECT menuBoxBG;
	
	short local_70;
	u_short menuRowsNegativePaddingCopy;
	u_short dualShockListVerticalPadding;
	u_short numGamepads;
	u_short numAnalogs;
	u_short isMultitap;
	short whateverThisIsNow;
	int thisOtherThing;
	
	local_70 = 0;
	numGamepads = 0;
	isMultitap = (u_short)(sdata->gGamepads->slotBuffer[0].controllerData == (PAD_ID_MULTITAP << 4)) << 1;
	MainFreeze_SafeAdvDestroy();
	somethingToDoWithVolumeLineWidth = 0;
	numAnalogs = 0;
	if (sdata->boolOpenWheelConfig != 0)
	{
		MainFreeze_ConfigSetupEntry();
		return;
	}
	
	// get number of ordinary gamepads and/or "analog controllers" connected, and which players are using which
	i = 0;
	if (sdata->gGT->numPlyrCurrGame != 0)
	{
		iVar7 = 0;
		do
		{
			psVar9 = sdata->gGamepads->gamepad[iVar7 >> 0x10].ptrControllerPacket;
			if (((psVar9 == (struct ControllerPacket *)0x0) || (psVar9->isControllerConnected != 0)) || ((psVar9->controllerData != ((PAD_ID_JOGCON << 4) | 3) && (psVar9->controllerData != ((PAD_ID_NEGCON << 4) | 3)))))
			{
				uVar13 = (u_int)numGamepads;
				numGamepads = numGamepads + 1;
				gamepadId[uVar13] = (short)i;
				isGamepadAnalog[i] = false;
			}
			else
			{
				uVar13 = (u_int)numAnalogs;
				numAnalogs = numAnalogs + 1;
				analogId[uVar13] = (short)i;
				isGamepadAnalog[iVar7 >> 0x10] = true;
			}
			i = i + 1;
			iVar7 = i * 0x10000;
		} while (i * 0x10000 >> 0x10 < (int)(u_int)sdata->gGT->numPlyrCurrGame);
	}

	// bool
	// 0 for no "analog controllers"
	// 1 for yes "analog controllers"
	areBothControllerLabelsNecessary = 0;
	if (numGamepads != 0)
	{
		areBothControllerLabelsNecessary = (u_short)(numAnalogs != 0);
	}

	// amount of menu rows to hide
	// used for the dualshock and/or "analog" rows which are variable

	// in singleplayer, regardless of gamepad, 2 of these rows are always visible
	// with 4 regular gamepads connected, in multiplayer, there's 5 rows visible
	// maximum amount of rows is 6, which happens if there's 4 controllers and one of them is "analog"
	// in the last scenario, menuRowsToRemove will equal -1
	menuRowsToRemove = (4 - areBothControllerLabelsNecessary) - (u_short)sdata->gGT->numPlyrCurrGame;

	u_short menuRowsNegativePadding = menuRowsToRemove * 10;

	if (numGamepads == 0)
	{
		dualShockListVerticalPadding = 0;
	}
	else
	{
		dualShockListVerticalPadding = (numGamepads + 1) * 10;
	}

	int menuRowsNegativePadding_halved = (int)((u_int)menuRowsNegativePadding << 0x10) >> 0x11;

	// cursor location for exit button, which will change depending on how many dualshock rows there need to be
	data.Options_HighlightBar[8].posY = menuRowsToRemove * -10 + 119;

	// cursor location for dualshock rows
	i = 0;
	if (0 < (short)numGamepads)
	{
		iVar10 = 0;
		do
		{
			data.Options_HighlightBar[(iVar10 >> 0x10) + 4].posY = (short)((u_int)iVar10 >> 0x10) * 10 + 79;
			i = i + 1;
			iVar10 = i * 0x10000;
		} while (i * 0x10000 >> 0x10 < (int)(short)numGamepads);
	}

	// cursor location for "analog" rows...?
	iVar10 = (u_int)numAnalogs << 0x10;
	i = 0;
	if (0 < iVar10)
	{
		do
		{
			uVar6 = 0;
			short analogIdx = (short)i;
			if ((short)numGamepads != 0)
			{
				uVar6 = (u_short)(iVar10 != 0); // bool
			}
			i = i + 1;
			data.Options_HighlightBar[(int)(short)numGamepads + analogIdx + 4].posY = (analogIdx + numGamepads + uVar6) * 10 + 79;
			iVar10 = (u_int)numAnalogs << 0x10;
		} while (i * 0x10000 < iVar10);
	}

	uVar6 = mb->drawStyle & 0xfeff;
	mb->drawStyle = uVar6;
	if (2 < sdata->gGT->numPlyrCurrGame)
	{
		mb->drawStyle = uVar6 | 0x100;
	}

	menuRowsNegativePaddingCopy = menuRowsNegativePadding;

	if ((sdata->AnyPlayerTap & BTN_UP) == 0)
	{
		if ((sdata->AnyPlayerTap & BTN_DOWN) == 0)
		{
			// Do the same for all 3 sliders in Options menu
			// 0: FX slider
			// 1: Music slider
			// 2: Voice slider
			switch(mb->rowSelected)
			{
			case 0:
			case 1:
			case 2:
				selectedRow = (int)mb->rowSelected;
				OptionsMenu_TestSound(selectedRow, 1);
				if ((sdata->AnyPlayerHold & BTN_LEFT) == 0)
				{
					if ((sdata->AnyPlayerHold & BTN_RIGHT) != 0)
					{
						// get value of volume slider
						uVar6 = howl_VolumeGet(selectedRow);
						// add to the slider
						uVar6 = (uVar6 & 0xff) + 4;
						// set slider maximum value to 0xFF
						if (0xff < uVar6)
						{
							uVar6 = 0xff;
						}
						howl_VolumeSet(selectedRow, (char)uVar6);
					}
				}
				else
				{
					uVar6 = howl_VolumeGet(selectedRow);
					i = (uVar6 & 0xff) - 4;
					if (i < 0)
					{
						i = 0;
					}
					howl_VolumeSet(selectedRow, i);
				}
				break;
			case 3:
				OptionsMenu_TestSound(0, 0);
				if (sdata->AnyPlayerTap & (BTN_CIRCLE | BTN_CROSS_one))
				{
					OtherFX_Play(1, 1);
					cVar5 = howl_ModeGet();
					howl_ModeSet(cVar5 == 0);
				}
				break;
			case 4:
			case 5:
			case 6:
			case 7:
				OptionsMenu_TestSound(0, 0);
				if (sdata->AnyPlayerTap & (BTN_CIRCLE | BTN_CROSS_one))
				{
					uVar6 = mb->rowSelected;
					OtherFX_Play(1, 1);
					i = (int)((uVar6 - 4) * 0x10000) >> 0x10;
					// if the row you selected is for configuring a racing wheel gamepad
					if (i < (short)numGamepads)
					{
						sdata->gGT->gameMode1 = sdata->gGT->gameMode1 ^ data.gGT_gameMode1_Vibration_PerPlayer[(short)gamepadId[i]];
					}
					else
					{
						sdata->gamepad_ID_ThatOpenedRaceWheelConfig = analogId[i - (short)numGamepads];
						sdata->boolOpenWheelConfig = 1;
						sdata->raceWheelConfigPageIndex = 0;
					}
				}
				break;
			case 8:
				OptionsMenu_TestSound(0, 0);
				if (sdata->AnyPlayerTap & (BTN_CIRCLE | BTN_CROSS_one))
				{
					OtherFX_Play(1, 1);
					local_70 = 1;
				}
			}
			goto switchD_80038f90_caseD_9;
		}
		OtherFX_Play(0, 1);
		short rowSelectedCopy = mb->rowSelected + 1;
		mb->rowSelected = rowSelectedCopy;
		if (8 < rowSelectedCopy)
		{
			mb->rowSelected = 0;
			goto switchD_80038f90_caseD_9;
		}
		if ((int)rowSelectedCopy < (int)(sdata->gGT->numPlyrCurrGame + 4)) goto switchD_80038f90_caseD_9;
	}
	else
	{
		OtherFX_Play(0, 1);
		short rowSelectedCopy = mb->rowSelected + -1;
		mb->rowSelected = rowSelectedCopy;
		if (-1 < rowSelectedCopy)
		{
			if (rowSelectedCopy == 7)
			{
				mb->rowSelected = sdata->gGT->numPlyrCurrGame + 3;
			}
			goto switchD_80038f90_caseD_9;
		}
	}
	mb->rowSelected = 8;
switchD_80038f90_caseD_9:
	uVar13 = 0;
	i = 0;
	do
	{
		i = DecalFont_GetLineWidth(sdata->lngStrings[*(short *)((int)data.Options_StringIDs_Audio + (i >> 0xf))], 2);
		if (somethingToDoWithVolumeLineWidth << 0x10 < i << 0x10)
		{
			somethingToDoWithVolumeLineWidth = i;
		}
		uVar13 = uVar13 + 1;
		i = uVar13 * 0x10000;
	} while ((uVar13 & 0xffff) < 3);
	iVar10 = 0;
	
	// "OPTIONS"
	DecalFont_DrawLine(sdata->lngStrings[324], 0x100, (short)((u_int)((menuRowsNegativePadding_halved + 0x1a) * 0x10000) >> 0x10), FONT_BIG, (JUSTIFY_CENTER | ORANGE));

	i = 0x17c - (somethingToDoWithVolumeLineWidth + 0x1e);
	whateverThisIsNow = (short)i;
	thisOtherThing = (i * 0x10000 >> 0x10) + -5;
	i = 0;
	do
	{
		i = i >> 0x10;
		uVar6 = howl_VolumeGet(i);
		iVar14 = (uVar6 & 0xff) * thisOtherThing;
		menuRowsNegativePadding_halved_again = (short)menuRowsNegativePadding >> 1;
		short volumeHeightSomething = menuRowsNegativePadding_halved_again + (short)(i * 10);
		if (iVar14 < 0)
		{
			iVar14 = iVar14 + 0xff;
		}
		sVar3 = (short)(somethingToDoWithVolumeLineWidth + 0x1e);
		sVar1 = sVar3 + (short)((u_int)iVar14 >> 8) + 0x38;
		volumeSliderBar.x = sVar1 + 1;
		volumeSliderBar.y = volumeHeightSomething + 0x30;
		volumeSliderBar.w = 3;
		volumeSliderBar.h = 10;
		CTR_Box_DrawSolidBox(&volumeSliderBar, (u_int *)(data.Options_VolumeSlider_Colors + 0xc), (u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour, &sdata->gGT->backBuffer->primMem);
		volumeSliderBarOutline.y = volumeHeightSomething + 0x2f;
		volumeSliderBarOutline.w = 5;
		volumeSliderBarOutline.h = 0xc;
		volumeSliderBarOutline.x = sVar1;
		CTR_Box_DrawSolidBox(&volumeSliderBarOutline, (u_int *)(data.Options_VolumeSlider_Colors + 0x10), (u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour, &sdata->gGT->backBuffer->primMem);
		volumeSliderTriangle[0] = sVar3 + 0x38;
		volumeSliderTriangle[1] = volumeHeightSomething + 0x3a;
		volumeSliderTriangle[2] = sVar3 + whateverThisIsNow + 0x38;
		volumeSliderTriangle[3] = volumeHeightSomething + 0x30;
		volumeSliderTriangle[4] = volumeSliderTriangle[2];
		volumeSliderTriangle[5] = volumeSliderTriangle[1];
		MENUBOX_DrawRwdTriangle(volumeSliderTriangle, data.Options_VolumeSlider_Colors, (u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour, &sdata->gGT->backBuffer->primMem);
		
		// "FX:" "MUSIC:" "VOICE:"
		DecalFont_DrawLine(sdata->lngStrings[data.Options_StringIDs_Audio[i]], 0x4c, (short)((u_int)((i * 10 + menuRowsNegativePadding_halved + 0x32) * 0x10000) >> 0x10), 2, ORANGE);

		iVar10 = iVar10 + 1;
		i = iVar10 * 0x10000;
	} while (iVar10 * 0x10000 >> 0x10 < 3);

	// "MODE:"
	DecalFont_DrawLine(sdata->lngStrings[332], 0x4c, (short)((u_int)((menuRowsNegativePadding_halved + 0x50) * 0x10000) >> 0x10), FONT_SMALL, ORANGE);

	cVar5 = howl_ModeGet();
	if (cVar5 == '\0')
	{
		// "MONO"
		volumeModeString = &sdata->lngStrings[333];
	}
	else
	{
		// "STEREO"
		volumeModeString = &sdata->lngStrings[334];
	}
	DecalFont_DrawLine(*volumeModeString, 0x1b4, (short)((u_int)((menuRowsNegativePadding_halved + 0x50) * 0x10000) >> 0x10), FONT_SMALL, (JUSTIFY_RIGHT | WHITE));

	u_short numGamepadsCopy = numGamepads;
	if (numGamepads != 0)
	{
		// "DUAL SHOCK:"
		DecalFont_DrawLine(sdata->lngStrings[330], 0x4c, (short)((u_int)((menuRowsNegativePadding_halved + 0x5a) * 0x10000) >> 0x10), FONT_SMALL, ORANGE);

		i = DecalFont_GetLineWidth(sdata->lngStrings[data.Options_StringIDs_Gamepads[2]], 2);
		iVar10 = DecalFont_GetLineWidth(sdata->lngStrings[326], 2);
		somethingToDoWithVolumeLineWidth = DecalFont_GetLineWidth(sdata->lngStrings[325], 2);
		iVar14 = 0;
		if (somethingToDoWithVolumeLineWidth << 0x10 < iVar10 << 0x10)
		{
			somethingToDoWithVolumeLineWidth = iVar10;
		}
		somethingToDoWithVolumeLineWidth = (i + somethingToDoWithVolumeLineWidth + 10) * 0x10000;
		somethingToDoWithVolumeLineWidth = 0x100 - ((somethingToDoWithVolumeLineWidth >> 0x10) - (somethingToDoWithVolumeLineWidth >> 0x1f) >> 1);
		if (0 < (short)numGamepadsCopy)
		{
			iVar10 = 0;
			do
			{
				bVar2 = false;
				areBothControllerLabelsNecessary = *(u_short *)((int)gamepadId + (iVar10 >> 0xf));
				uVar13 = (u_int)areBothControllerLabelsNecessary;
				psVar9 = sdata->gGamepads->gamepad[(short)areBothControllerLabelsNecessary].ptrControllerPacket;
				if ((psVar9 == (struct ControllerPacket *)0x0) || (psVar9->isControllerConnected != 0))
				{
					bVar2 = true;
				}
				if (bVar2)
				{
					uVar15 = GRAY;
				}
				else
				{
					uVar15 = ORANGE;
				}
				// "CONTROLLER 1", "CONTROLLER 2", "CONTROLLER 1A", "CONTROLLER 1B", "CONTROLLER 1C", "CONTROLLER 1D"
				DecalFont_DrawLine
				(
					sdata->lngStrings[*(short *)((int)data.Options_StringIDs_Gamepads + ((int)((uVar13 + isMultitap) * 0x10000) >> 0xf))],
					(short)((u_int)(somethingToDoWithVolumeLineWidth * 0x10000) >> 0x10),
					(short)((u_int)(((short)iVar14 * 10 + menuRowsNegativePadding_halved + 100) * 0x10000) >> 0x10),
					FONT_SMALL, uVar15
				);
				if ((sdata->gGT->gameMode1 & *(u_int *)((int)data.gGT_gameMode1_Vibration_PerPlayer + ((int)(uVar13 << 0x10) >> 0xe))) == 0)
				{
					// "VIBRATE ON"
					dualshockVibrateString = &sdata->lngStrings[325];
				}
				else
				{
					// "VIBRATE OFF"
					dualshockVibrateString = &sdata->lngStrings[326];
				}
				uVar15 = GRAY;
				if ((!bVar2) && (uVar15 = RED, (sdata->gGT->gameMode1 & *(u_int *)((int)data.gGT_gameMode1_Vibration_PerPlayer + ((int)(uVar13 << 0x10) >> 0xe))) == 0))
				{
					uVar15 = WHITE;
				}
				DecalFont_DrawLine
				(
					*dualshockVibrateString,
					(short)((u_int)((somethingToDoWithVolumeLineWidth + i + 10) * 0x10000) >> 0x10),
					(short)((u_int)(((short)iVar14 * 10 + menuRowsNegativePadding_halved + 100) * 0x10000) >> 0x10),
					FONT_SMALL, uVar15
				);
				iVar14 = iVar14 + 1;
				iVar10 = iVar14 * 0x10000;
			} while (iVar14 * 0x10000 < (int)((u_int)numGamepads << 0x10));
		}
	}
	somethingToDoWithVolumeLineWidth = (int)(short)numAnalogs;
	if (somethingToDoWithVolumeLineWidth != 0)
	{
		i = 0;
		DecalFont_DrawLine(sdata->lngStrings[336], 0x4c, (short)(((u_int)dualShockListVerticalPadding + menuRowsNegativePadding_halved + 0x5a) * 0x10000 >> 0x10), FONT_SMALL, ORANGE);
		if (0 < somethingToDoWithVolumeLineWidth)
		{
			do
			{
				DecalFont_DrawLine
				(
					sdata->lngStrings[*(short *)((int)data.Options_StringIDs_Gamepads + ((int)(((u_int)analogId[(short)i] + (u_int)isMultitap) * 0x10000) >> 0xf))],
					0x100,
					(short)((menuRowsNegativePadding_halved + (u_int)dualShockListVerticalPadding + (short)i * 10 + 100) * 0x10000 >> 0x10),
					FONT_SMALL, (JUSTIFY_CENTER | ORANGE)
				);
				i = i + 1;
			} while (i * 0x10000 >> 0x10 < somethingToDoWithVolumeLineWidth);
		}
	}
	// "EXIT"
	DecalFont_DrawLine(sdata->lngStrings[331], 0x4c, (short)(((menuRowsNegativePadding_halved + 0x8c) - (u_int)menuRowsNegativePaddingCopy) * 0x10000 >> 0x10), FONT_SMALL, ORANGE);

	glowingcursor.x = 0x4a;
	glowingcursor.w = 0x16c;
	glowingcursor.y = data.Options_HighlightBar[mb->rowSelected].posY + menuRowsNegativePadding_halved_again + 0x14;
	glowingcursor.h = data.Options_HighlightBar[mb->rowSelected].sizeY;
	CTR_Box_DrawClearBox(&glowingcursor, &sdata->menuRowHighlight_Normal, TRANS_50_DECAL, (u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour, &sdata->gGT->backBuffer->primMem);

	titleSeparatorLine.x = 66;
	titleSeparatorLine.y = menuRowsNegativePadding_halved_again + 43;
	titleSeparatorLine.w = 380;
	titleSeparatorLine.h = 2;
	MENUBOX_DrawOuterRect_Edge(&titleSeparatorLine, (u_int)&sdata->battleSetup_Color_UI_1, 0x20, (u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour);

	menuBoxBG.x = 0x38;
	menuBoxBG.w = 400;
	menuBoxBG.h = 0x87 - menuRowsNegativePaddingCopy;
	menuBoxBG.y = menuRowsNegativePadding_halved_again + 0x14;
	MENUBOX_DrawInnerRect(&menuBoxBG, 4, (u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour);

	if ((local_70 != 0) || ((sdata->AnyPlayerTap & (BTN_TRIANGLE | BTN_START | BTN_SQUARE_one)) != 0))
	{
		OtherFX_Play(1, 1);
		OptionsMenu_TestSound(0, 0);
		MENUBOX_ClearInput();
		sdata->ptrDesiredMenuBox = MainFreeze_GetMenuBox();
	}
	return;
}
