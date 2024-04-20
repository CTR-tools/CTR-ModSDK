#include <common.h>

void DECOMP_MainFreeze_ConfigSetupEntry()
{
	short sVar1;
	short sVar2;
	int iVar3;
	struct ControllerPacket *psVar4;
	uint uVar5;
	int iVar6;
	uint uVar7;
	RECT *r;
	u_char red;
	u_short y0;
	int iVar8;
	int iVar9;
	int iVar10;
	void *ot;
	ushort uVar11;
	int iVar12;
	short local_48 [8];
	RECT local_38;
	RECT local_30;
	
	if ((sdata_AnyPlayerTap & 0x40020) != 0)
	{
		sdata_boolOpenWheelConfig = 0;
		return;
	}
	iVar9 = (int)sdata_gamepadID_OwnerRaceWheelConfig;
	psVar4 = sdata_gGamepads->gamepad[iVar9].ptrControllerPacket;
	if (psVar4 == (struct ControllerPacket *)0x0)
	{
		sdata_boolOpenWheelConfig = 0;
		return;
	}
	if (psVar4->isControllerConnected != '\0')
	{
		sdata_boolOpenWheelConfig = 0;
		return;
	}
	uVar7 = (uint)(psVar4->controllerData == 0xe3);
	if (sdata_raceWheelConfigPageIndex == 1)
	{
		uVar5 = sdata_buttonTapPerPlayer[iVar9];
		if ((uVar5 & 5) == 0)
	{
			if ((uVar5 & 10) == 0)
	{
				if ((uVar5 & 0x50) != 0)
	{
					sdata_raceWheelConfigPageIndex = 2;
					data_rwd[iVar9].deadZone = data_raceConfig_unk80084258[(short)sdata_WheelConfigOption].hi1;
				}
			}
			else
	{
				sdata_WheelConfigOption = sdata_WheelConfigOption + 1;
				if (3 < (short)sdata_WheelConfigOption)
	{
					sdata_WheelConfigOption = 0;
				}
			}
		}
		else
	{
			sdata_WheelConfigOption = sdata_WheelConfigOption - 1;
			if ((int)((uint)sdata_WheelConfigOption << 0x10) < 0)
	{
				sdata_WheelConfigOption = 3;
			}
		}
		DecalFont_DrawMultiLine(sdata_lngStrings[0x223],0x100,(int)sdata_posY_MultiLine[uVar7 * 2],0x1cc,1,-0x8000);
		DecalFont_DrawLine(sdata_lngStrings[data_raceConfig_unk80084258[(short)sdata_WheelConfigOption].lngIndex],0x100,sdata_posY_Arrows[uVar7 * 2],1,0x8000);
		MainFreeze_ConfigDrawArrows(0x100,sdata_posY_Arrows[uVar7 * 2],sdata_lngStrings[data_raceConfig_unk80084258[(short)sdata_WheelConfigOption].lngIndex]);
		sdata_unk_RaceWheelConfig[0] = (int)data_raceConfig_unk80084258[(short)sdata_WheelConfigOption].lo16;
	}
	else if (sdata_raceWheelConfigPageIndex < 2)
	{
		if (sdata_raceWheelConfigPageIndex == 0)
	{
			DecalFont_DrawMultiLine(sdata_lngStrings[0x222],0x100,(int)sdata_posY_MultiLine[uVar7 * 2],0x1cc,1,-0x8000);
			iVar9 = (int)sdata_gamepadID_OwnerRaceWheelConfig;
			if ((sdata_buttonTapPerPlayer[iVar9] & 0x50) != 0)
	{
				sdata_raceWheelConfigPageIndex = sdata_raceWheelConfigPageIndex + 1;
				if (uVar7 == 0)
	{
					data_rwd[iVar9].gamepadCenter = (ushort)((sdata_gGamepads->gamepad[iVar9].ptrControllerPacket)->field3_0x4).analog.rightX;
				}
				else
	{
					sdata_gGamepads->gamepad[iVar9].unk44 = '\x04';
					data_rwd[sdata_gamepadID_OwnerRaceWheelConfig].gamepadCenter = 0x80;
				}
				RECTMENU_ClearInput();
			}
			sdata_unk_RaceWheelConfig[0] = 0;
		}
	}
	else if (sdata_raceWheelConfigPageIndex == 2)
	{
		uVar5 = sdata_buttonTapPerPlayer[iVar9];
		if ((uVar5 & 5) == 0)
	{
			if ((uVar5 & 10) == 0)
	{
				if ((uVar5 & 0x50) != 0)
	{
					sdata_boolOpenWheelConfig = 0;
					data_rwd[iVar9].range = data_raceConfig_unk80084270[(short)sdata_raceWheelConfigOptionIndex].hi1;
					RECTMENU_ClearInput();
				}
			}
			else
	{
				sdata_raceWheelConfigOptionIndex = sdata_raceWheelConfigOptionIndex + 1;
				if ((short)data_raceConfig_unk80084290[uVar7] < (short)sdata_raceWheelConfigOptionIndex)
	{
					sdata_raceWheelConfigOptionIndex = 0;
				}
			}
		}
		else
	{
			sdata_raceWheelConfigOptionIndex = sdata_raceWheelConfigOptionIndex - 1;
			if ((int)((uint)sdata_raceWheelConfigOptionIndex << 0x10) < 0)
	{
				sdata_raceWheelConfigOptionIndex = data_raceConfig_unk80084290[uVar7];
			}
		}
		sdata_unk_RaceWheelConfig[0] = (int)data_raceConfig_unk80084270[(short)sdata_raceWheelConfigOptionIndex].lo16;
		DecalFont_DrawMultiLine(sdata_lngStrings[0x228],0x100,(int)sdata_posY_MultiLine[uVar7 * 2],0x1cc,1,-0x8000);
		DecalFont_DrawLine(sdata_lngStrings[data_raceConfig_unk80084270[(short)sdata_raceWheelConfigOptionIndex].lngIndex],0x100,sdata_posY_Arrows[uVar7 * 2],1,0x8000);
		MainFreeze_ConfigDrawArrows(0x100,sdata_posY_Arrows[uVar7 * 2],sdata_lngStrings[data_raceConfig_unk80084270[(short)sdata_raceWheelConfigOptionIndex].lngIndex]);
	}
	iVar9 = sdata_unk_RaceWheelConfig[0];
	iVar12 = 0;
	if (uVar7 == 0)
	{
		iVar12 = 0;
		uVar7 = sdata_unk_RaceWheelConfig[0] & 0x3ff;
		do
	{
			uVar5 = data_trigApprox[uVar7];
			if ((iVar9 & 0x400U) == 0)
	{
				uVar5 = uVar5 << 0x10;
			}
			iVar6 = (int)uVar5 >> 0x10;
			if ((iVar9 & 0x800U) != 0)
	{
				iVar6 = -iVar6;
			}
			ot = (sdata_gGT->pushBuffer_UI).ptrOT;
			if (((short)iVar12 != 1) && (iVar9 == 0x600))
	{
				ot = (void *)((int)ot + 0xc);
			}
			y0 = (u_short)((uint)((sdata_unk_drawingRaceWheelRects[0] + (iVar6 * ((short)iVar12 + -1) * 0x20 >> 0xc) + 0x20) * 0x10000) >> 0x10);
			CTR_Box_DrawWirePrims(0xe2,y0,0x11e,y0,0,0xff,0,ot,&sdata_gGT->backBuffer->primMem);
			iVar12 = iVar12 + 1;
		} while (iVar12 * 0x10000 >> 0x10 < 3);
		iVar6 = 0;
		iVar12 = 0;
		do
	{
			uVar7 = sdata_frameCounter * 0x40 + (iVar12 >> 5);
			uVar5 = data_trigApprox[uVar7 & 0x3c0];
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
			uVar5 = data_trigApprox[uVar7 & 0x3ff];
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
				*(short *)((int)local_48 + iVar3) = *(short *)((int)data_raceConfig_unk80084290 + iVar3 + iVar10 + 4) + sVar1;
				iVar3 = iVar8 << 0x10;
				iVar8 = iVar8 + 1;
				iVar3 = iVar3 >> 0xe;
				*(short *)((int)local_48 + iVar3 + 2) = (short)sdata_unk_drawingRaceWheelRects[0] + (short)((iVar12 << 5) >> 0xc) + 0x20 + *(short *)((int)data_raceConfig_unk80084290 + iVar3 + iVar10 + 6);
			} while (iVar8 * 0x10000 >> 0x10 < 3);
			RECTMENU_DrawRwdTriangle(local_48,(char *)data_raceConfig_colors_arrows,(u_long *)(sdata_gGT->pushBuffer_UI).ptrOT,&sdata_gGT->backBuffer->primMem);
			iVar6 = iVar6 + 1;
			iVar12 = iVar6 * 0x10000;
		} while (iVar6 * 0x10000 >> 0x10 < 2);
		local_38.x = 0xec;
		local_38.w = 0x28;
		local_38.h = 0x41;
		local_38.y = (short)sdata_unk_drawingRaceWheelRects[0];
		RECTMENU_DrawRwdBlueRect(&local_38,(char *)data_raceConfig_colors_blueRect,(u_long *)(sdata_gGT->pushBuffer_UI).ptrOT,&sdata_gGT->backBuffer->primMem);
		r = &local_30;
		local_30.x = -0x14;
		local_30.w = 0x228;
		local_30.h = 0x91;
		local_30.y = (short)sdata_unk_drawingRaceWheelRects[0] + -0x14;
		goto LAB_80038b24;
	}
	iVar6 = -sdata_unk_RaceWheelConfig[0];
	iVar8 = 0;
	do
	{
		iVar10 = iVar9;
		if (iVar8 == 0)
	{
			iVar10 = iVar6;
		}
		uVar7 = iVar10 - 0x400;
		sVar1 = (short)data_trigApprox[uVar7 & 0x3ff];
		iVar8 = (int)data_trigApprox[uVar7 & 0x3ff] >> 0x10;
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
		CTR_Box_DrawWirePrims((u_short)((uint)(((iVar8 * 400) / 0x5000 + 0x100) * 0x10000) >> 0x10),(u_short)(((uint)(ushort)sdata_unk_drawingRaceWheelRects[1] + (iVar10 * 0x32 >> 0xc)) * 0x10000 >> 0x10),(u_short)((uint)(((iVar8 * 0x118) / 0x5000 + 0x100) * 0x10000) >> 0x10),(u_short)(((uint)(ushort)sdata_unk_drawingRaceWheelRects[1] + (iVar10 * 0x23 >> 0xc)) * 0x10000 >> 0x10),'\0',0xff,'\0',(sdata_gGT->pushBuffer_UI).ptrOT,&sdata_gGT->backBuffer->primMem);
		iVar12 = iVar12 + 1;
		iVar8 = iVar12 * 0x10000;
	} while (iVar12 * 0x10000 >> 0x10 < 2);
	uVar7 = (int)sdata_frameCounter << 6;
	uVar5 = data_trigApprox[uVar7 & 0x3c0];
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
	iVar9 = (int)data_trigApprox[uVar7 & 0x3ff] >> 0x10;
	sVar1 = (short)data_trigApprox[uVar7 & 0x3ff];
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
			MainFreeze_ConfigDrawNPC105((short)(((uint)*(ushort *)((int)data_unkNamcoGamepad_800842DC + iVar9) + (iVar12 * 200) / 0x5000 + 0x100) * 0x10000 >> 0x10),(short)(((uint)*(ushort *)((int)data_unkNamcoGamepad_800842DC + iVar9 + 2) + (uint)(ushort)sdata_unk_drawingRaceWheelRects[1] + (iVar6 * 0x19 >> 0xc)) * 0x10000 >> 0x10),10,0x80,sVar1,(char *)(data_unkNamcoGamepadRwdTriangleColors + iVar9),(u_long *)(sdata_gGT->pushBuffer_UI).ptrOT,&sdata_gGT->backBuffer->primMem);
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
			sVar2 = (short)data_trigApprox[uVar5 & 0x3ff];
			iVar6 = (int)data_trigApprox[uVar5 & 0x3ff] >> 0x10;
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
			CTR_Box_DrawWirePrims((u_short)((uint)(((iVar10 >> 6) + 0x100) * 0x10000) >> 0x10),(u_short)(((uint)(ushort)sdata_unk_drawingRaceWheelRects[1] + (iVar8 * 0x28 >> 0xc)) * 0x10000 >> 0x10),(u_short)((uint)(((iVar6 * 0x120) / 0x5000 + 0x100) * 0x10000) >> 0x10),(u_short)(((uint)(ushort)sdata_unk_drawingRaceWheelRects[1] + (iVar8 * 0x24 >> 0xc)) * 0x10000 >> 0x10),red,red,red,(sdata_gGT->pushBuffer_UI).ptrOT,&sdata_gGT->backBuffer->primMem);
			iVar12 = iVar12 + 0x400;
			iVar6 = iVar9 + 0xaa;
		} while (iVar12 * 0x10000 >> 0x10 < 0x1000);
		iVar9 = iVar6;
	} while (iVar6 * 0x10000 >> 0x10 < 0x400);
	uVar11 = 0;
	do
	{
		iVar12 = 0;
		iVar9 = (int)((uint)uVar11 << 0x10) >> 0xe;
		iVar6 = 0;
		do
	{
			iVar6 = iVar6 >> 0xe;
			sVar2 = *(short *)((int)data_unkNamcoGamepad_800842DC + iVar9 + 0xe);
			MainFreeze_ConfigDrawNPC105(*(short *)((int)data_unkNamcoGamepad_800842DC + iVar6 + 0x24) * sVar2 + 0x100,(ushort)sdata_unk_drawingRaceWheelRects[1] + *(short *)((int)data_unkNamcoGamepad_800842DC + iVar6 + 0x26) * sVar2,*(short *)((int)data_unkNamcoGamepad_800842DC + iVar9 + 0xc),0x80,sVar1,(char *)((int)data_unkNamcoGamepad_800842DC + iVar6 + 0x18),(u_long *)(sdata_gGT->pushBuffer_UI).ptrOT,&sdata_gGT->backBuffer->primMem);
			iVar12 = iVar12 + 1;
			iVar6 = iVar12 * 0x10000;
		} while (iVar12 * 0x10000 >> 0x10 < 3);
		uVar11 = uVar11 + 1;
	} while (uVar11 < 3);
	r = &local_38;
	local_38.x = -0x14;
	local_38.w = 0x228;
	local_38.h = 0xa0;
	local_38.y = (ushort)sdata_unk_drawingRaceWheelRects[1] - 0x3c;
LAB_80038b24:
	RECTMENU_DrawInnerRect(r,4,(u_long *)(sdata_gGT->pushBuffer_UI).ptrOT);
	return;
}