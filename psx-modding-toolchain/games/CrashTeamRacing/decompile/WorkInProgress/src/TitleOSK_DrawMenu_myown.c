#include <common.h>

short DECOMP_TitleOSK_DrawMenu(u_short string)
{
	short strlenCurrNameEntered;
	u_int strColorBlink2;
	int TitleOSK_CursorPosition;
	u_int uVar2;
	char *currNameEntered;
	int iVar3;
	int iVar4;
	short TitleOSK_CursorPositionShort;
	int iVar5;
	short strColorBlink;
	char local_58;
	char local_57;
	u_char local_56;
	RECT local_50;
	u_short local_48;
	short nameSize;
	short local_38;
	int local_30;
	int strlenCurrNameEnteredInt;
	u_char character;
	
	iVar5 = 0;
	local_38 = 0;
	nameSize = 0;
	local_48 = string;
	strlenCurrNameEnteredInt = strlen(sdata->gGT->currNameEntered);
	strlenCurrNameEntered = (short)strlenCurrNameEnteredInt;
	currNameEntered = sdata->gGT->currNameEntered;
	if (sdata->gGT->currNameEntered[0] != 0)
	{
		character = *currNameEntered;
		do
		{
			if (character > 2)
			{
				nameSize++;
			}
			currNameEntered++;
			character = *currNameEntered;
		} while (character != 0);
	}
	TitleOSK_CursorPosition = (int)sdata->gGT->TitleOSK_CursorPosition;
	if ((0x26 < TitleOSK_CursorPosition) && (TitleOSK_CursorPosition < 1000))
	{
		TitleOSK_CursorPosition = 0x26;
	}
	TitleOSK_CursorPositionShort = (short)TitleOSK_CursorPosition;
	sdata->titleoskunknown++;
	iVar4 = 0;
	local_30 = 1;
	do
	{
		iVar3 = 0;
		if (local_30 != 0)
		{
			do
			{
				strColorBlink = ORANGE;
				if ((int)TitleOSK_CursorPositionShort == (iVar3 + iVar4 * 0xd) * 0x10000 >> 0x10)
				{
					strColorBlink = (short)((sdata->titleoskunknown & 1) << 2);
				}
				uVar2 = (u_int)data.unicodeAscii[(short)iVar4 * 0xd + (int)(short)iVar3];
				strColorBlink2 = uVar2 & 0xff00;
				if ((uVar2 & 0xff00) == 0x1000)
				{
					uVar2 = uVar2 & 0xff;
					strColorBlink2 = 0;
				}
				if (strColorBlink2 == 0)
				{
					local_57 = '\0';
					local_58 = (char)uVar2;
				}
				else
				{
					local_56 = 0;
					local_58 = (char)((uVar2 << 0x10) >> 0x18);
					local_57 = (char)uVar2;
				}
				DecalFont_DrawLine(&local_58, ((short)iVar3 * 0x16 + 0x74) * 0x10000 >> 0x10, ((short)iVar4 * 0x12 + 0x58) * 0x10000 >> 0x10, FONT_BIG, (int)strColorBlink);
				iVar3++;
			} while (iVar3 * 0x10000 >> 0x10 < 0xd);
		}
		iVar4++;
	} while (iVar4 * 0x10000 >> 0x10 < 3);
	DecalFont_DrawLine(sdata->lngStrings[318], 0x100, 0x2c, FONT_BIG, (CENTER_TEXT | ORANGE));
	DecalFont_DrawLine(sdata->gGT->currNameEntered, 0xc0, 0x44, FONT_BIG, TINY_GREEN);
	if (((sdata->titleoskunknown & 2) != 0) && (strlenCurrNameEntered < 0x10))
	{
		iVar4 = DecalFont_GetLineWidth(sdata->gGT->currNameEntered, FONT_BIG);
		DecalFont_DrawLine(sdata->str_underscore, (iVar4 + 0xc0) * 0x10000 >> 0x10, 0x44, FONT_BIG, ORANGE);
	}
	iVar4 = (int)TitleOSK_CursorPositionShort;
	strColorBlink2 = 0;
	if (iVar4 == 0x3e9)
	{
		strColorBlink2 = (sdata->titleoskunknown & 1) << 2;
	}
	DecalFont_DrawLine(sdata->lngStrings[local_48], 0x1d8, 0x96, FONT_BIG, strColorBlink2 | END_AT_X);
	strColorBlink = 0;
	if (iVar4 == 1000)
	{
		strColorBlink = (short)((sdata->titleoskunknown & 1) << 2);
	}
	DecalFont_DrawLine(sdata->lngStrings[321], 0x28, 0x96, FONT_BIG, (int)strColorBlink);
	local_50.x = 0x20;
	local_50.w = 0x1c0;
	local_50.y = 0x3e;
	local_50.h = 2;
	MenuBox_DrawOuterRect_Edge(&local_50, (u_int)sdata->battleSetup_Color_UI_1, 0x20, (u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour);
	local_50.y = 0x27;
	local_50.h = 0x82;
	MenuBox_DrawInnerRect(&local_50, 0, (u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour);
	if ((sdata->buttonTapPerPlayer[0] & (BTN_UP | BTN_DOWN | BTN_LEFT | BTN_RIGHT)) == 0)
	{
		if ((sdata->buttonTapPerPlayer[0] & BTN_START) == 0)
		{
			if ((sdata->buttonTapPerPlayer[0] & (BTN_TRIANGLE | BTN_SQUARE_one)) == 0)
			{
				if ((sdata->buttonTapPerPlayer[0] & (BTN_CIRCLE | BTN_CROSS_one)) != 0)
				{
					if (iVar4 == 0x26)
					{
						iVar5 = 2;
						if (strlenCurrNameEntered == 0)
						{
							iVar5 = 2;
						}
						else
						{
							sdata->gGT->prevNameEntered[strlenCurrNameEntered + 0x10] = '\0';
						}
					}
					else if (iVar4 < 0x26)
					{
						strColorBlink2 = (u_int)(u_short)data.unicodeAscii[iVar4];
						if (((int)data.unicodeAscii[iVar4] & 0xff00U) == 0x1000)
						{
							strColorBlink2 = strColorBlink2 & 0xff;
						}
						if (nameSize < 8)
						{
							iVar5 = strColorBlink2 << 0x10;
							strColorBlink = strlenCurrNameEntered;
							if ((strColorBlink2 & 0xff00) != 0)
							{
								strColorBlink = strlenCurrNameEntered + 1;
								strColorBlink2 = strColorBlink2 & 0xff;
								sdata->gGT->currNameEntered[strlenCurrNameEntered] = (char)((u_int)iVar5 >> 0x18);
							}
							iVar5 = 1;
							sdata->gGT->currNameEntered[strColorBlink] = (char)strColorBlink2;
						}
						else
						{
							iVar5 = 5;
						}
					}
					else
					{
						if (iVar4 == 0x3e9)
						{
							iVar5 = 2;
							local_38 = 1;
							memmove((u_char *)sdata->gGT->prevNameEntered, (u_char *)sdata->gGT->currNameEntered, 0x11);
						}
						else
						{
							iVar5 = 0;
							if (iVar4 != 1000) goto LAB_8004b0dc;
							iVar5 = 3;
							local_38 = -1;
						}
						MenuBox_ClearInput();
					}
				}
			}
			else
			{
				TitleOSK_CursorPosition = (int)strlenCurrNameEntered;
				iVar5 = 0;
				if (TitleOSK_CursorPosition != 0)
				{
					sdata->gGT->prevNameEntered[TitleOSK_CursorPosition + 0x10] = 0;
					iVar5 = 4;
					if ((u_char)sdata->gGT->prevNameEntered[TitleOSK_CursorPosition + 0xf] < 3)
					{
						sdata->gGT->prevNameEntered[TitleOSK_CursorPosition + 0xf] = '\0';
					}
				}
			}
		}
		else
		{
			iVar5 = 3;
			if (iVar4 == 1000)
			{
				local_38 = -1;
			}
			else
			{
				TitleOSK_CursorPositionShort = 1000;
				iVar5 = 1;
			}
		}
	}
	else
	{
		if ((sdata->buttonTapPerPlayer[0] & 1) != 0)
		{
			TitleOSK_CursorPosition = TitleOSK_CursorPosition - 0xd;
		}
		if ((sdata->buttonTapPerPlayer[0] & 2) != 0)
		{
			TitleOSK_CursorPosition = TitleOSK_CursorPosition + 0xd;
		}
		if ((sdata->buttonTapPerPlayer[0] & 4) != 0)
		{
			TitleOSK_CursorPosition = TitleOSK_CursorPosition - 1;
		}
		iVar5 = TitleOSK_CursorPosition << 0x10;
		if ((sdata->buttonTapPerPlayer[0] & 8) != 0)
		{
			TitleOSK_CursorPosition = TitleOSK_CursorPosition + 1;
			iVar5 = TitleOSK_CursorPosition * 0x10000;
		}
		iVar4 = TitleOSK_CursorPosition << 0x10;
		if (iVar5 < 0)
		{
			TitleOSK_CursorPosition = 0x3e9;
			iVar4 = 0x3e90000;
		}
		TitleOSK_CursorPositionShort = (short)TitleOSK_CursorPosition;
		strColorBlink2 = TitleOSK_CursorPosition - 500;
		if ((0x26 < iVar4 >> 0x10) && (strColorBlink2 = TitleOSK_CursorPosition - 500,  iVar4 >> 0x10 < 500))
		{
			TitleOSK_CursorPositionShort = 0x3e9;
			strColorBlink2 = 0x1f5;
		}
		if ((strColorBlink2 & 0xffff) < 500)
		{
			TitleOSK_CursorPositionShort = 0x26;
		}
		iVar5 = 1;
		if (0x3ea < TitleOSK_CursorPositionShort)
		{
			TitleOSK_CursorPositionShort = 0;
		}
	}
LAB_8004b0dc:
	if (iVar5 != 0)
	{
		DECOMP_OtherFX_Play(*(u_short *)&data.soundIndexArray[iVar5], 1);
	}
	sdata->gGT->TitleOSK_CursorPosition = TitleOSK_CursorPositionShort;
	return local_38;
}