#include <common.h>

void DECOMP_MainFreeze_ConfigSetupEntry(void)
{
	short sVar1;
	short sVar2;
	int iVar3;
	short *psVar4;
	u_int uVar5;
	int iVar6;
	u_int uVar7;
	RECT *r;
	u_char red;
	u_short y0;
	int iVar8;
	int iVar9;
	int iVar10;
	void *ot;
	u_short uVar11;
	int iVar12;
	short local_48 [8];
	RECT local_38;
	RECT local_30;
	
	if ((sdata->AnyPlayerTap & 0x40020) != 0)
	{
		sdata->boolOpenWheelConfig = 0;
		return;
	}

	iVar9 = (int)sdata->gamepad_ID_ThatOpenedRaceWheelConfig;
	psVar4 = sdata->gGamepads->gamepad[iVar9].ptrRawInput;

	if (psVar4 == 0)
	{
		sdata->boolOpenWheelConfig = 0;
		return;
	}

	if (*(char *)psVar4 != 0)
	{
		sdata->boolOpenWheelConfig = 0;
		return;
	}

	uVar7 = (u_int)(*(char *)((int)psVar4 + 1) == -0x1d);
	if (sdata->raceWheelConfigPageIndex == 1)
	{
		uVar5 = sdata->buttonTapPerPlayer[iVar9];
		if ((uVar5 & 5) == 0)
		{
			if ((uVar5 & 10) == 0)
			{
				if ((uVar5 & 0x50) != 0)
				{
					sdata->raceWheelConfigPageIndex = 2;
					data.rwd[iVar9].deadZone = *(short *)(&data.raceConfig_unknown_deadzone_array + (short)sdata->WheelConfigOption * 6);
				}
			}
			else
			{
				sdata->WheelConfigOption = sdata->WheelConfigOption + 1;
				if (3 < (short)sdata->WheelConfigOption)
				{
					sdata->WheelConfigOption = 0;
				}
			}
		}
		else
		{
			sdata->WheelConfigOption = sdata->WheelConfigOption - 1;
			if ((int)((u_int)sdata->WheelConfigOption << 0x10) < 0)
			{
				sdata->WheelConfigOption = 3;
			}
		}
		DecalFont_DrawMultiLine(sdata->lngStrings[0x223], 0x100, (int)sdata->posY_MultiLine[uVar7 * 2], 0x1cc, 1, -0x8000);
		DecalFont_DrawLine(sdata->lngStrings[data.raceConfig_unk80084258[(short)sdata->WheelConfigOption * 3]], 0x100, sdata->posY_Arrows[uVar7 * 2], 1, 0x8000);
		MainFreeze_ConfigDrawArrows(0x100, sdata->posY_Arrows[uVar7 * 2], sdata->lngStrings[data.raceConfig_unk80084258[(short)sdata->WheelConfigOption * 3]]);
		sdata->unk_RaceWheelConfig[0] = (int)data.raceConfig_unk80084258[(short)sdata->WheelConfigOption * 3 + 1];
	}
	else if (sdata->raceWheelConfigPageIndex < 2)
	{
		if (sdata->raceWheelConfigPageIndex == 0)
		{
			DecalFont_DrawMultiLine(sdata->lngStrings[0x222], 0x100, (int)sdata->posY_MultiLine[uVar7 * 2], 0x1cc, 1, -0x8000);
			iVar9 = (int)sdata->gamepad_ID_ThatOpenedRaceWheelConfig;
			if ((sdata->buttonTapPerPlayer[iVar9] & 0x50) != 0)
			{
				sdata->raceWheelConfigPageIndex = sdata->raceWheelConfigPageIndex + 1;
				if (uVar7 == 0)
				{
					data.rwd[iVar9].gamepadCenter = (u_short)*(u_char *)(sdata->gGamepads->gamepad[iVar9].ptrRawInput + 2);
				}
				else
				{
					sdata->gGamepads->gamepad[iVar9].unk_44_countdown = '\x04';
					data.rwd[sdata->gamepad_ID_ThatOpenedRaceWheelConfig].gamepadCenter = 0x80;
				}
				MENUBOX_ClearInput();
			}
			sdata->unk_RaceWheelConfig[0] = 0;
		}
	}
	else if (sdata->raceWheelConfigPageIndex == 2)
	{
		uVar5 = sdata->buttonTapPerPlayer[iVar9];
		if ((uVar5 & 5) == 0)
		{
			if ((uVar5 & 10) == 0)
			{
				if ((uVar5 & 0x50) != 0)
				{
					sdata->boolOpenWheelConfig = 0;
					data.rwd[iVar9].range = data.raceConfig_unknown_rwd_range[(short)sdata->raceWheelConfigOptionIndex * 3];
					MENUBOX_ClearInput();
				}
			}
			else
			{
				sdata->raceWheelConfigOptionIndex = sdata->raceWheelConfigOptionIndex + 1;
				if (data.raceConfig_unk80084290[uVar7] < (short)sdata->raceWheelConfigOptionIndex)
				{
					sdata->raceWheelConfigOptionIndex = 0;
				}
			}
		}
		else
		{
			sdata->raceWheelConfigOptionIndex = sdata->raceWheelConfigOptionIndex - 1;
			if ((int)((u_int)sdata->raceWheelConfigOptionIndex << 0x10) < 0)
			{
				sdata->raceWheelConfigOptionIndex = data.raceConfig_unk80084290[uVar7];
			}
		}
		sdata->unk_RaceWheelConfig[0] = (int)data.raceConfig_unk80084270[(short)sdata->raceWheelConfigOptionIndex * 3 + 1];
		DecalFont_DrawMultiLine(sdata->lngStrings[0x228], 0x100, (int)sdata->posY_MultiLine[uVar7 * 2], 0x1cc, 1, -0x8000);
		DecalFont_DrawLine(sdata->lngStrings[data.raceConfig_unk80084270[(short)sdata->raceWheelConfigOptionIndex * 3]], 0x100, sdata->posY_Arrows[uVar7 * 2], 1, 0x8000);
		MainFreeze_ConfigDrawArrows(0x100, sdata->posY_Arrows[uVar7 * 2], sdata->lngStrings[data.raceConfig_unk80084270[(short)sdata->raceWheelConfigOptionIndex * 3]]);
	}
	iVar9 = sdata->unk_RaceWheelConfig[0];
	iVar12 = 0;
	if (uVar7 == 0)
	{
		iVar12 = 0;
		uVar7 = sdata->unk_RaceWheelConfig[0] & 0x3ff;
		do
		{
			uVar5 = *(u_int*)&data.trigApprox[uVar7].sin;
			if ((iVar9 & 0x400U) == 0)
			{
				uVar5 = uVar5 << 0x10;
			}
			iVar6 = (int)uVar5 >> 0x10;
			if ((iVar9 & 0x800U) != 0)
			{
				iVar6 = -iVar6;
			}
			ot = (sdata->gGT->tileView_UI).ptrOT;
			if (((short)iVar12 != 1) && (iVar9 == 0x600))
			{
				ot = (void *)((int)ot + 0xc);
			}
			y0 = (u_short)((u_int)((sdata->unk_drawingRaceWheelRects[0] + (iVar6 * ((short)iVar12 + -1) * 0x20 >> 0xc) + 0x20) * 0x10000) >> 0x10);
			CTR_Box_DrawWirePrims(0xe2, y0, 0x11e, y0, 0, 0xff, 0, ot, &sdata->gGT->backBuffer->primMem);
			iVar12 = iVar12 + 1;
		} while (iVar12 * 0x10000 >> 0x10 < 3);
		iVar6 = 0;
		iVar12 = 0;
		do
		{
			uVar7 = sdata->frameCounter * 0x40 + (iVar12 >> 5);
			uVar5 = *(u_int*)&data.trigApprox[uVar7 & 0x3c0].sin;
			if ((uVar7 & 0x400) == 0)
			{
				uVar5 = uVar5 << 0x10;
			}
			iVar12 = (int)uVar5 >> 0x10;
			if ((uVar7 & 0x800) != 0)
			{
				iVar12 = -iVar12;
			}
			uVar7 = iVar9 * iVar12 >> 0xc;
			uVar5 = *(u_int*)&data.trigApprox[uVar7 & 0x3ff].sin;
			if ((uVar7 & 0x400) == 0)
			{
				uVar5 = uVar5 << 0x10;
			}
			iVar12 = (int)uVar5 >> 0x10;
			if ((uVar7 & 0x800) != 0)
			{
				iVar12 = -iVar12;
			}
			iVar8 = 0;
			iVar10 = (short)iVar6 * 0xc;
			do
			{
				iVar3 = (iVar8 << 0x10) >> 0xe;
				if ((short)iVar6 == 0)
				{
					sVar1 = 0x114;
				}
				else
				{
					sVar1 = 0xec;
				}
				*(short *)((int)local_48 + iVar3) = *(short *)((int)data.raceConfig_unk80084294 + iVar3 + iVar10) + sVar1;
				iVar3 = iVar8 << 0x10;
				iVar8 = iVar8 + 1;
				iVar3 = iVar3 >> 0xe;
				*(short *)((int)local_48 + iVar3 + 2) = (short)sdata->unk_drawingRaceWheelRects[0] + (short)((iVar12 << 5) >> 0xc) + 0x20 + *(short *)((int)data.raceConfig_unk80084294 + iVar3 + iVar10 + 2);
			} while (iVar8 * 0x10000 >> 0x10 < 3);
			MENUBOX_DrawRwdTriangle(local_48, (char *)data.raceConfig_colors_arrows, (u_long *)(sdata->gGT->tileView_UI).ptrOT, &sdata->gGT->backBuffer->primMem);
			iVar6 = iVar6 + 1;
			iVar12 = iVar6 * 0x10000;
		} while (iVar6 * 0x10000 >> 0x10 < 2);
		local_38.x = 0xec;
		local_38.w = 0x28;
		local_38.h = 0x41;
		local_38.y = (short)sdata->unk_drawingRaceWheelRects[0];
		MENUBOX_DrawRwdBlueRect(&local_38, (char *)data.raceConfig_colors_blueRect, (u_long *)(sdata->gGT->tileView_UI).ptrOT, &sdata->gGT->backBuffer->primMem);
		r = &local_30;
		local_30.x = -0x14;
		local_30.w = 0x228;
		local_30.h = 0x91;
		local_30.y = (short)sdata->unk_drawingRaceWheelRects[0] + -0x14;
		goto LAB_80038b24;
	}
	iVar6 = -sdata->unk_RaceWheelConfig[0];
	iVar8 = 0;
	do
	{
		iVar10 = iVar9;
		if (iVar8 == 0)
		{
			iVar10 = iVar6;
		}
		uVar7 = iVar10 - 0x400;
		sVar1 = (short)(*(u_int*)&data.trigApprox[uVar7 & 0x3ff].sin);
		iVar8 = (int)(*(u_int*)&data.trigApprox[uVar7 & 0x3ff].sin) >> 0x10;
		if ((uVar7 & 0x400) == 0)
		{
			iVar10 = (int)sVar1;
			if ((uVar7 & 0x800) != 0)
			{
				iVar3 = -iVar8;
				goto LAB_80038620;
			}
		}
		else
		{
			iVar3 = (int)sVar1;
			iVar10 = iVar8;
			if ((uVar7 & 0x800) == 0)
			{
				iVar8 = -iVar3;
			}
			else
			{
LAB_80038620:
				iVar10 = -iVar10;
				iVar8 = iVar3;
			}
		}
		CTR_Box_DrawWirePrims((u_short)((u_int)(((iVar8 * 400) / 0x5000 + 0x100) * 0x10000) >> 0x10), (u_short)(((u_int)(u_short)sdata->unk_drawingRaceWheelRects[1] + (iVar10 * 0x32 >> 0xc)) * 0x10000 >> 0x10), (u_short)((u_int)(((iVar8 * 0x118) / 0x5000 + 0x100) * 0x10000) >> 0x10), (u_short)(((u_int)(u_short)sdata->unk_drawingRaceWheelRects[1] + (iVar10 * 0x23 >> 0xc)) * 0x10000 >> 0x10), '\0', 0xff, '\0', (sdata->gGT->tileView_UI).ptrOT, &sdata->gGT->backBuffer->primMem);
		iVar12 = iVar12 + 1;
		iVar8 = iVar12 * 0x10000;
	} while (iVar12 * 0x10000 >> 0x10 < 2);
	uVar7 = (int)sdata->frameCounter << 6;
	uVar5 = *(u_int*)&data.trigApprox[uVar7 & 0x3c0].sin;
	if ((uVar7 & 0x400) == 0)
	{
		uVar5 = uVar5 << 0x10;
	}
	iVar12 = (int)uVar5 >> 0x10;
	if ((uVar7 & 0x800) != 0)
	{
		iVar12 = -iVar12;
	}
	uVar7 = (iVar12 * iVar9 >> 0xc) - 0x400;
	iVar9 = (int)(*(u_int*)&data.trigApprox[uVar7 & 0x3ff].sin) >> 0x10;
	sVar1 = (short)(*(u_int*)&data.trigApprox[uVar7 & 0x3ff].sin);
	if ((uVar7 & 0x400) == 0)
	{
		iVar6 = (int)sVar1;
		iVar12 = iVar9;
		if ((uVar7 & 0x800) != 0)
		{
			iVar12 = -iVar9;
			goto LAB_800387c4;
		}
	}
	else
	{
		iVar12 = (int)sVar1;
		iVar6 = iVar9;
		if ((uVar7 & 0x800) == 0)
		{
			iVar12 = -iVar12;
		}
		else
		{
LAB_800387c4:
			iVar6 = -iVar6;
		}
	}
	do
	{
		iVar9 = 0;
		do
		{
			iVar8 = iVar9;
			iVar9 = (iVar8 << 0x10) >> 0xe;
			sVar1 = (short)(uVar7 & 0xfff);
			MainFreeze_ConfigDrawNPC105((short)(((u_int)*(u_short *)((int)data.unkNamcoGamepad_800842DC + iVar9) + (iVar12 * 200) / 0x5000 + 0x100) * 0x10000 >> 0x10), (short)(((u_int)*(u_short *)((int)data.unkNamcoGamepad_800842DC + iVar9 + 2) + (u_int)(u_short)sdata->unk_drawingRaceWheelRects[1] + (iVar6 * 0x19 >> 0xc)) * 0x10000 >> 0x10), 10, 0x80, sVar1, (char *)(data.unkNamcoGamepadRwdTriangleColors + iVar9), (u_long *)(sdata->gGT->tileView_UI).ptrOT, &sdata->gGT->backBuffer->primMem);
			iVar9 = iVar8 + 1;
		} while ((iVar8 + 1) * 0x10000 >> 0x10 < 3);
		iVar9 = 0;
	} while ((iVar8 + 2) * 0x10000 >> 0x10 < 3);
	do
	{
		iVar12 = 0;
		do
		{
			red = '2';
			if ((short)iVar9 != 0)
			{
				red = 'P';
			}
			uVar5 = (uVar7 & 0xfff) + iVar12 + iVar9;
			sVar2 = (short)(*(u_int*)&data.trigApprox[uVar5 & 0x3ff].sin);
			iVar6 = (int)(*(u_int*)&data.trigApprox[uVar5 & 0x3ff].sin) >> 0x10;
			if ((uVar5 & 0x400) == 0)
			{
				iVar8 = (int)sVar2;
				if ((uVar5 & 0x800) != 0)
				{
					iVar10 = -iVar6;
					goto LAB_8003892c;
				}
			}
			else
			{
				iVar10 = (int)sVar2;
				iVar8 = iVar6;
				if ((uVar5 & 0x800) == 0)
				{
					iVar6 = -iVar10;
				}
				else
				{
LAB_8003892c:
					iVar8 = -iVar8;
					iVar6 = iVar10;
				}
			}
			iVar10 = iVar6;
			if (iVar6 < 0)
			{
				iVar10 = iVar6 + 0x3f;
			}
			CTR_Box_DrawWirePrims((u_short)((u_int)(((iVar10 >> 6) + 0x100) * 0x10000) >> 0x10), (u_short)(((u_int)(u_short)sdata->unk_drawingRaceWheelRects[1] + (iVar8 * 0x28 >> 0xc)) * 0x10000 >> 0x10), (u_short)((u_int)(((iVar6 * 0x120) / 0x5000 + 0x100) * 0x10000) >> 0x10), (u_short)(((u_int)(u_short)sdata->unk_drawingRaceWheelRects[1] + (iVar8 * 0x24 >> 0xc)) * 0x10000 >> 0x10), red, red, red, (sdata->gGT->tileView_UI).ptrOT, &sdata->gGT->backBuffer->primMem);
			iVar12 = iVar12 + 0x400;
			iVar6 = iVar9 + 0xaa;
		} while (iVar12 * 0x10000 >> 0x10 < 0x1000);
		iVar9 = iVar6;
	} while (iVar6 * 0x10000 >> 0x10 < 0x400);
	uVar11 = 0;
	do
	{
		iVar12 = 0;
		iVar9 = (int)((u_int)uVar11 << 0x10) >> 0xe;
		iVar6 = 0;
		do
		{
			iVar6 = iVar6 >> 0xe;
			sVar2 = *(short *)((int)data.unkNamcoGamepad_800842DC + iVar9 + 0xe);
			MainFreeze_ConfigDrawNPC105(*(short *)((int)data.unkNamcoGamepad_800842DC + iVar6 + 0x24) * sVar2 + 0x100, (u_short)sdata->unk_drawingRaceWheelRects[1] + *(short *)((int)data.unkNamcoGamepad_800842DC + iVar6 + 0x26) * sVar2, *(short *)((int)data.unkNamcoGamepad_800842DC + iVar9 + 0xc), 0x80, sVar1, (char *)((int)data.unkNamcoGamepad_800842DC + iVar6 + 0x18), (u_long *)(sdata->gGT->tileView_UI).ptrOT, &sdata->gGT->backBuffer->primMem);
			iVar12 = iVar12 + 1;
			iVar6 = iVar12 * 0x10000;
		} while (iVar12 * 0x10000 >> 0x10 < 3);
		uVar11 = uVar11 + 1;
	} while (uVar11 < 3);
	r = &local_38;
	local_38.x = -0x14;
	local_38.w = 0x228;
	local_38.h = 0xa0;
	local_38.y = (u_short)sdata->unk_drawingRaceWheelRects[1] - 0x3c;
LAB_80038b24:
	MENUBOX_DrawInnerRect(r, 4, (u_long *)(sdata->gGT->tileView_UI).ptrOT);
	return;
}