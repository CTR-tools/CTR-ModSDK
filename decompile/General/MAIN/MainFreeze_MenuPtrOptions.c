#include <common.h>

// WARNING: Type propagation algorithm not settling

void DECOMP_MainFreeze_MenuPtrOptions(struct GameTracker* gGT)
{
	short sVar1;
	char bVar2;
	short sVar3;
	short sVar4;
	char cVar5;
	u_short uVar6;
	int iVar7;
	short sVar8;
	short *psVar9;
	int iVar10;
	char **ppcVar11;
	u_short areThereRacingWheels;
	int highlitRow;
	int iVar12;
	int i;
	u_int uVar13;
	int iVar14;
	u_short auStackY131246 [32767];
	u_short auStackY65712 [4];
	u_short auStackY65704 [4];
	u_short auStackY65696 [32756];
	u_short uVar15;
	u_short local_b0 [4];
	u_short local_a8 [4];
	u_short local_a0 [4];
	RECT local_98;
	short local_90 [8];
	RECT local_80;
	struct GameTracker *gametrack;
	short local_70;
	u_short local_68;
	u_short local_60;
	u_short numRacingWheels;
	u_short numAnalogGamepads;
	u_short gamepadSlotBufferMeta1;
	short local_38;
	int local_30;
	struct GameTracker *gametrack2;
	
	local_70 = 0;
	numRacingWheels = 0;
	gamepadSlotBufferMeta1 = (u_short)(sdata->gGamepads->slotBuffer[0].meta[1] == -0x80) << 1;
	gametrack = gGT;
	MainFreeze_SafeAdvDestroy();
	iVar12 = 0;
	numAnalogGamepads = 0;
	if (sdata->boolOpenWheelConfig != 0)
	{
		MainFreeze_ConfigSetupEntry();
		return;
	}
	// For if you are not in racing wheel configuration
	// Since you did not hit "return", you will continue with the rest of the Options menu
	i = 0;
	if (sdata->gGT->numPlyrCurrGame != 0)
	{
		iVar7 = 0;
		do
		{
			psVar9 = sdata->gGamepads->gamepad[iVar7 >> 0x10].ptrRawInput;
			if (((psVar9 == (short *)0x0) || (*(char *)psVar9 != 0)) || ((*(char *)((int)psVar9 + 1) != -0x1d && (*(char *)((int)psVar9 + 1) != '#'))))
			{
				uVar13 = (u_int)numRacingWheels;
				numRacingWheels = numRacingWheels + 1;
				*(short *)((int)local_a8 + ((int)(uVar13 << 0x10) >> 0xf)) = (short)i;
				*(u_short *)((int)local_a0 + ((i << 0x10) >> 0xf)) = 0;
			}
			else
			{
				uVar13 = (u_int)numAnalogGamepads;
				numAnalogGamepads = numAnalogGamepads + 1;
				*(short *)((int)local_b0 + ((int)(uVar13 << 0x10) >> 0xf)) = (short)i;
				local_a0[iVar7 >> 0x10] = 1;
			}
			i = i + 1;
			iVar7 = i * 0x10000;
		} while (i * 0x10000 >> 0x10 < (int)(u_int)sdata->gGT->numPlyrCurrGame);
	}
	// 0 for no racing wheels
	// 1 for racing wheels
	areThereRacingWheels = 0;
	if (numRacingWheels != 0)
	{
		areThereRacingWheels = (u_short)(numAnalogGamepads != 0);
	}
	sVar8 = (4 - areThereRacingWheels) - (u_short)sdata->gGT->numPlyrCurrGame;
	areThereRacingWheels = sVar8 * 10;
	if (numRacingWheels == 0)
	{
		local_60 = 0;
	}
	else
	{
		local_60 = (numRacingWheels + 1) * 10;
	}
	iVar7 = (int)((u_int)areThereRacingWheels << 0x10) >> 0x11;
	data.Options_HighlightBar_PosY[8][0] = sVar8 * -10 + 0x77;
	i = 0;
	if (0 < (short)numRacingWheels)
	{
		iVar10 = 0;
		do
		{
			data.Options_HighlightBar_PosY[(iVar10 >> 0x10) + 4][0] = (short)((u_int)iVar10 >> 0x10) * 10 + 0x4f;
			i = i + 1;
			iVar10 = i * 0x10000;
		} while (i * 0x10000 >> 0x10 < (int)(short)numRacingWheels);
	}
	iVar10 = (u_int)numAnalogGamepads << 0x10;
	i = 0;
	if (0 < iVar10)
	{
		do
		{
			uVar6 = 0;
			sVar8 = (short)i;
			if ((short)numRacingWheels != 0)
			{
				uVar6 = (u_short)(iVar10 != 0);
			}
			i = i + 1;
			data.Options_HighlightBar_PosY[(int)(short)numRacingWheels + sVar8 + 4][0] = (sVar8 + numRacingWheels + uVar6) * 10 + 0x4f;
			iVar10 = (u_int)numAnalogGamepads << 0x10;
		} while (i * 0x10000 < iVar10);
	}
	gametrack2 = sdata->gGT;
	uVar6 = *(u_short *)&gametrack->frontBuffer & 0xfeff;
	*(u_short *)&gametrack->frontBuffer = uVar6;
	if (2 < gametrack2->numPlyrCurrGame)
	{
		*(u_short *)&gametrack->frontBuffer = uVar6 | 0x100;
	}
	local_68 = areThereRacingWheels;
	if ((sdata->AnyPlayerTap & 1) == 0)
	{
		if ((sdata->AnyPlayerTap & 2) == 0)
		{
			// Do the same for all 3 sliders in Options menu
			// 0: FX slider
			// 1: Music slider
			// 2: Voice slider
			switch(gametrack->db[0].drawEnv.clip.y)
			{
			case 0:
			case 1:
			case 2:
				highlitRow = (int)gametrack->db[0].drawEnv.clip.y;
				OptionsMenu_TestSound(highlitRow, 1);
				if ((sdata->AnyPlayerHold & 4) == 0)
				{
					if ((sdata->AnyPlayerHold & 8) != 0)
					{
						// get value of volume slider
						uVar6 = howl_VolumeGet(highlitRow);
						// add to the slider
						uVar6 = (uVar6 & 0xff) + 4;
						// set slider maximum value to 0xFF
						if (0xff < uVar6)
						{
							uVar6 = 0xff;
						}
						howl_VolumeSet(highlitRow, (char)uVar6);
					}
				}
				else
				{
					uVar6 = howl_VolumeGet(highlitRow);
					i = (uVar6 & 0xff) - 4;
					if (i < 0)
					{
						i = 0;
					}
					howl_VolumeSet(highlitRow, (char)i);
				}
				break;
			case 3:
				OptionsMenu_TestSound(0, 0);
				if ((sdata->AnyPlayerTap & 0x50) != 0)
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
				if ((sdata->AnyPlayerTap & 0x50) != 0)
				{
					uVar6 = gametrack->db[0].drawEnv.clip.y;
					OtherFX_Play(1, 1);
					i = (int)((uVar6 - 4) * 0x10000) >> 0x10;
					// if the row you selected is for configuring a racing wheel gamepad
					if (i < (short)numRacingWheels)
					{
						sdata->gGT->gameMode1 = sdata->gGT->gameMode1 ^ data.gGT_gameMode1_Vibration_PerPlayer[(short)local_a8[i]];
					}
					else
					{
						sdata->gamepad_ID_ThatOpenedRaceWheelConfig = local_b0[i - (short)numRacingWheels];
						sdata->boolOpenWheelConfig = 1;
						sdata->raceWheelConfigPageIndex = 0;
					}
				}
				break;
			case 8:
				OptionsMenu_TestSound(0, 0);
				if ((sdata->AnyPlayerTap & 0x50) != 0)
				{
					OtherFX_Play(1, 1);
					local_70 = 1;
				}
			}
			goto switchD_80038f90_caseD_9;
		}
		OtherFX_Play(0, 1);
		sVar8 = gametrack->db[0].drawEnv.clip.y + 1;
		gametrack->db[0].drawEnv.clip.y = sVar8;
		if (8 < sVar8)
		{
			gametrack->db[0].drawEnv.clip.y = 0;
			goto switchD_80038f90_caseD_9;
		}
		if ((int)sVar8 < (int)(sdata->gGT->numPlyrCurrGame + 4)) goto switchD_80038f90_caseD_9;
	}
	else
	{
		OtherFX_Play(0, 1);
		sVar8 = gametrack->db[0].drawEnv.clip.y + -1;
		gametrack->db[0].drawEnv.clip.y = sVar8;
		if (-1 < sVar8)
		{
			if (sVar8 == 7)
			{
				gametrack->db[0].drawEnv.clip.y = sdata->gGT->numPlyrCurrGame + 3;
			}
			goto switchD_80038f90_caseD_9;
		}
	}
	gametrack->db[0].drawEnv.clip.y = 8;
switchD_80038f90_caseD_9:
	uVar13 = 0;
	i = 0;
	do
	{
		i = DecalFont_GetLineWidth(sdata->lngStrings[*(short *)((int)data.Options_StringIDs_Audio + (i >> 0xf))], 2);
		if (iVar12 << 0x10 < i << 0x10)
		{
			iVar12 = i;
		}
		uVar13 = uVar13 + 1;
		i = uVar13 * 0x10000;
	} while ((uVar13 & 0xffff) < 3);
	iVar10 = 0;
	DecalFont_DrawLine(sdata->lngStrings[324], 0x100, (short)((u_int)((iVar7 + 0x1a) * 0x10000) >> 0x10), FONT_BIG, (CENTER_TEXT | ORANGE));
	i = 0x17c - (iVar12 + 0x1e);
	local_38 = (short)i;
	local_30 = (i * 0x10000 >> 0x10) + -5;
	i = 0;
	do
	{
		i = i >> 0x10;
		uVar6 = howl_VolumeGet(i);
		iVar14 = (uVar6 & 0xff) * local_30;
		sVar4 = (short)areThereRacingWheels >> 1;
		sVar8 = sVar4 + (short)(i * 10);
		if (iVar14 < 0)
		{
			iVar14 = iVar14 + 0xff;
		}
		sVar3 = (short)(iVar12 + 0x1e);
		sVar1 = sVar3 + (short)((u_int)iVar14 >> 8) + 0x38;
		local_98.x = sVar1 + 1;
		local_98.y = sVar8 + 0x30;
		local_98.w = 3;
		local_98.h = 10;
		CTR_Box_DrawSolidBox(&local_98, (u_int *)(data.Options_VolumeSlider_Colors + 0xc), (u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour, &sdata->gGT->backBuffer->primMem);
		local_98.y = sVar8 + 0x2f;
		local_98.w = 5;
		local_98.h = 0xc;
		local_98.x = sVar1;
		CTR_Box_DrawSolidBox(&local_98, (u_int *)(data.Options_VolumeSlider_Colors + 0x10), (u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour, &sdata->gGT->backBuffer->primMem);
		local_90[0] = sVar3 + 0x38;
		local_90[1] = sVar8 + 0x3a;
		local_90[2] = sVar3 + local_38 + 0x38;
		local_90[3] = sVar8 + 0x30;
		local_90[4] = local_90[2];
		local_90[5] = local_90[1];
		MENUBOX_DrawRwdTriangle(local_90, data.Options_VolumeSlider_Colors, (u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour, &sdata->gGT->backBuffer->primMem);
		DecalFont_DrawLine(sdata->lngStrings[data.Options_StringIDs_Audio[i]], 0x4c, (short)((u_int)((i * 10 + iVar7 + 0x32) * 0x10000) >> 0x10), 2, ORANGE);
		iVar10 = iVar10 + 1;
		i = iVar10 * 0x10000;
	} while (iVar10 * 0x10000 >> 0x10 < 3);
	DecalFont_DrawLine(sdata->lngStrings[332], 0x4c, (short)((u_int)((iVar7 + 0x50) * 0x10000) >> 0x10), FONT_SMALL, ORANGE);
	cVar5 = howl_ModeGet();
	if (cVar5 == '\0')
	{
		ppcVar11 = &sdata->lngStrings[333];
	}
	else
	{
		ppcVar11 = &sdata->lngStrings[334];
	}
	DecalFont_DrawLine(*ppcVar11, 0x1b4, (short)((u_int)((iVar7 + 0x50) * 0x10000) >> 0x10), FONT_SMALL, (END_AT_X | WHITE));
	areThereRacingWheels = numRacingWheels;
	if (numRacingWheels != 0)
	{
		DecalFont_DrawLine(sdata->lngStrings[330], 0x4c, (short)((u_int)((iVar7 + 0x5a) * 0x10000) >> 0x10), FONT_SMALL, ORANGE);
		i = DecalFont_GetLineWidth(sdata->lngStrings[data.Options_StringIDs_Gamepads[2]], 2);
		iVar10 = DecalFont_GetLineWidth(sdata->lngStrings[326], 2);
		iVar12 = DecalFont_GetLineWidth(sdata->lngStrings[325], 2);
		iVar14 = 0;
		if (iVar12 << 0x10 < iVar10 << 0x10)
		{
			iVar12 = iVar10;
		}
		iVar12 = (i + iVar12 + 10) * 0x10000;
		iVar12 = 0x100 - ((iVar12 >> 0x10) - (iVar12 >> 0x1f) >> 1);
		if (0 < (short)areThereRacingWheels)
		{
			iVar10 = 0;
			do
			{
				bVar2 = false;
				areThereRacingWheels = *(u_short *)((int)local_a8 + (iVar10 >> 0xf));
				uVar13 = (u_int)areThereRacingWheels;
				psVar9 = sdata->gGamepads->gamepad[(short)areThereRacingWheels].ptrRawInput;
				if ((psVar9 == (short *)0x0) || (*(char *)psVar9 != '\0'))
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
				DecalFont_DrawLine(sdata->lngStrings[*(short *)((int)data.Options_StringIDs_Gamepads + ((int)((uVar13 + gamepadSlotBufferMeta1) * 0x10000) >> 0xf))], (short)((u_int)(iVar12 * 0x10000) >> 0x10), (short)((u_int)(((short)iVar14 * 10 + iVar7 + 100) * 0x10000) >> 0x10), FONT_SMALL, uVar15);
				if ((sdata->gGT->gameMode1 & *(u_int *)((int)data.gGT_gameMode1_Vibration_PerPlayer + ((int)(uVar13 << 0x10) >> 0xe))) == 0)
				{
					ppcVar11 = &sdata->lngStrings[325];
				}
				else
				{
					ppcVar11 = &sdata->lngStrings[326];
				}
				uVar15 = GRAY;
				if ((!bVar2) && (uVar15 = RED, (sdata->gGT->gameMode1 & *(u_int *)((int)data.gGT_gameMode1_Vibration_PerPlayer + ((int)(uVar13 << 0x10) >> 0xe))) == 0))
				{
					uVar15 = WHITE;
				}
				DecalFont_DrawLine(*ppcVar11, (short)((u_int)((iVar12 + i + 10) * 0x10000) >> 0x10), (short)((u_int)(((short)iVar14 * 10 + iVar7 + 100) * 0x10000) >> 0x10), FONT_SMALL, uVar15);
				iVar14 = iVar14 + 1;
				iVar10 = iVar14 * 0x10000;
			} while (iVar14 * 0x10000 < (int)((u_int)numRacingWheels << 0x10));
		}
	}
	iVar12 = (int)(short)numAnalogGamepads;
	if (iVar12 != 0)
	{
		i = 0;
		DecalFont_DrawLine(sdata->lngStrings[336], 0x4c, (short)(((u_int)local_60 + iVar7 + 0x5a) * 0x10000 >> 0x10), FONT_SMALL, ORANGE);
		if (0 < iVar12)
		{
			do
			{
				DecalFont_DrawLine(sdata->lngStrings[*(short *)((int)data.Options_StringIDs_Gamepads + ((int)(((u_int)local_b0[(short)i] + (u_int)gamepadSlotBufferMeta1) * 0x10000) >> 0xf))], 0x100, (short)((iVar7 + (u_int)local_60 + (short)i * 10 + 100) * 0x10000 >> 0x10), FONT_SMALL, (CENTER_TEXT | ORANGE));
				i = i + 1;
			} while (i * 0x10000 >> 0x10 < iVar12);
		}
	}
	DecalFont_DrawLine(sdata->lngStrings[331], 0x4c, (short)(((iVar7 + 0x8c) - (u_int)local_68) * 0x10000 >> 0x10), FONT_SMALL, ORANGE);
	local_80.x = 0x4a;
	local_80.w = 0x16c;
	local_80.y = data.Options_HighlightBar_PosY[gametrack->db[0].drawEnv.clip.y][0] + sVar4 + 0x14;
	local_80.h = data.Options_HighlightBar_PosY[gametrack->db[0].drawEnv.clip.y][1];
	CTR_Box_DrawClearBox(&local_80, &sdata->menuRowHighlight_Normal, 1, (u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour, &sdata->gGT->backBuffer->primMem);
	local_80.x = 0x42;
	local_80.y = sVar4 + 0x2b;
	local_80.w = 0x17c;
	local_80.h = 2;
	MENUBOX_DrawOuterRect_Edge(&local_80, (u_int)&sdata->battleSetup_Color_UI_1, 0x20, (u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour);
	local_80.x = 0x38;
	local_80.w = 400;
	local_80.h = 0x87 - local_68;
	local_80.y = sVar4 + 0x14;
	MENUBOX_DrawInnerRect(&local_80, 4, (u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour);
	if ((local_70 != 0) || ((sdata->AnyPlayerTap & 0x41020) != 0))
	{
		OtherFX_Play(1, 1);
		OptionsMenu_TestSound(0, 0);
		MENUBOX_ClearInput();
		sdata->ptrDesiredMenuBox = MainFreeze_GetMenuBox();
	}
	// WARNING: Read-only address (ram, 0x8008d950) is written
	// WARNING: Read-only address (ram, 0x8008d974) is written
	// WARNING: Read-only address (ram, 0x8009d2ac) is written
	// WARNING: Read-only address (ram, 0x8009d2b0) is written
	// WARNING: Read-only address (ram, 0x8009d878) is written
	return;
}