#include <common.h>

short DECOMP_TitleOSK_DrawMenu(u_short string)
{
	short currNameLength;
	u_short uVar3;
	int currNameWidth;
	int cursorPositionLBitshift16;
	u_int uVar2;
	u_int cursorCharacter;
	int cursorPosition;
	u_int keyboardCharacter;
	char* currNameEntered;
	int currNameLengthCopy;
	u_int cursorCharacterLBitshift16;
	u_short strColorBlink;
	u_short strColorBlink2;
	int j;
	int cursorPosition2;
	int i;
	short cursorPositionShort;
	u_int soundID;
	short currNameLengthIncrement;
	char keyboardString [3];
	RECT r;
	u_short stringCopy;
	short nameLength;
	short local_38;
	int local_30;
	int strlenCurrNameEnteredInt;
	u_int keyboardCharacterTopByte;
	u_char character;
	
	soundID = 0;
	local_38 = 0;
	nameLength = 0;
	stringCopy = string;
	strlenCurrNameEnteredInt = strlen(sdata->gGT->currNameEntered);
	currNameLength = strlenCurrNameEnteredInt;
	currNameEntered = sdata->gGT->currNameEntered;
	if (sdata->gGT->currNameEntered[0])
	{
		for(character = *currNameEntered; character; currNameEntered++)
		{
			if (character > 2)
			{
				nameLength++;
			}
			character = *currNameEntered;
		}
	}
	cursorPosition = sdata->gGT->TitleOSK_CursorPosition;
	if ((cursorPosition > 38) && (cursorPosition < 1000))
	{
		cursorPosition = 38;
	}
	cursorPositionShort = cursorPosition;
	sdata->titleoskunknown++;
	local_30 = 1;
	for(i = 0; i < 3; i++)
	{
		if (local_30)
		{
			for(j = 0; j < 13; j++)
			{
				strColorBlink = ORANGE;
				if (cursorPositionShort == j + i*13)
				{
					strColorBlink = (sdata->titleoskunknown & 1) << 2;
				}
				keyboardCharacter = data.unicodeAscii[i*13 + j];
				keyboardCharacterTopByte = keyboardCharacter & 0xff00;
				if ((keyboardCharacter & 0xff00) == 0x1000)
				{
					keyboardCharacter = keyboardCharacter & 0xff;
					keyboardCharacterTopByte = 0;
				}
				if (keyboardCharacterTopByte == 0)
				{
					keyboardString[1] = 0;
					keyboardString[0] = keyboardCharacter;
				}
				else
				{
					keyboardString[2] = 0;
					keyboardString[0] = (keyboardCharacter << 16) >> 24;
					keyboardString[1] = keyboardCharacter;
				}
				DecalFont_DrawLine(keyboardString, j*22 + 116, i*18 + 88, FONT_BIG, strColorBlink);
			}
		}
	}
	DecalFont_DrawLine(sdata->lngStrings[318], 256, 44, FONT_BIG, (CENTER_TEXT | ORANGE));
	DecalFont_DrawLine(sdata->gGT->currNameEntered, 192, 68, FONT_BIG, WHITE);
	if ((sdata->titleoskunknown & 2) && (currNameLength < 16))
	{
		currNameWidth = DecalFont_GetLineWidth(sdata->gGT->currNameEntered, FONT_BIG);
		DecalFont_DrawLine(sdata->str_underscore, currNameWidth + 192, 68, FONT_BIG, ORANGE);
	}
	cursorPosition2 = cursorPositionShort;
	strColorBlink2 = 0;
	if (cursorPosition2 == 1001)
	{
		strColorBlink2 = (sdata->titleoskunknown & 1) << 2;
	}
	DecalFont_DrawLine(sdata->lngStrings[stringCopy], 472, 150, FONT_BIG, (END_AT_X | strColorBlink2));
	strColorBlink = 0;
	if (cursorPosition2 == 1000)
	{
		strColorBlink = (sdata->titleoskunknown & 1) << 2;
	}
	DecalFont_DrawLine(sdata->lngStrings[321], 40, 150, 1, strColorBlink);
	r.x = 32;
	r.w = 448;
	r.y = 62;
	r.h = 2;
	MENUBOX_DrawOuterRect_Edge(&r, (u_int)&sdata->battleSetup_Color_UI_1, 0x20, (u_long*)(sdata->gGT->backBuffer->otMem).startPlusFour);
	r.y = 39;
	r.h = 130;
	MENUBOX_DrawInnerRect(&r, 0, (u_long*)(sdata->gGT->backBuffer->otMem).startPlusFour);
	if ((sdata->buttonTapPerPlayer[0] & (BTN_UP | BTN_DOWN | BTN_LEFT | BTN_RIGHT)) == 0)
	{
		if ((sdata->buttonTapPerPlayer[0] & BTN_START) == 0)
		{
			if ((sdata->buttonTapPerPlayer[0] & (BTN_TRIANGLE | BTN_SQUARE_one)) == 0)
			{
				if (sdata->buttonTapPerPlayer[0] & (BTN_CIRCLE | BTN_CROSS_one))
				{
					if (cursorPosition2 == 38)
					{
						soundID = 2;
						if (currNameLength == 0)
						{
							soundID = 2;
						}
						else
						{
							sdata->gGT->prevNameEntered[currNameLength + 0x10] = 0;
						}
					}
					else if (cursorPosition2 < 38)
					{
						cursorCharacter = data.unicodeAscii[cursorPosition2];
						if ((data.unicodeAscii[cursorPosition2] & 0xff00) == 0x1000)
						{
							cursorCharacter &= 0xff;
						}
						if (nameLength < 8)
						{
							cursorCharacterLBitshift16 = cursorCharacter << 16;
							currNameLengthIncrement = currNameLength;
							if (cursorCharacter & 0xff00)
							{
								currNameLengthIncrement = currNameLength + 1;
								cursorCharacter &= 0xff;
								sdata->gGT->currNameEntered[currNameLength] = cursorCharacterLBitshift16 >> 24;
							}
							soundID = 1;
							sdata->gGT->currNameEntered[currNameLengthIncrement] = cursorCharacter;
						}
						else
						{
							soundID = 5;
						}
					}
					else
					{
						if (cursorPosition2 == 1001)
						{
							soundID = 2;
							local_38 = 1;
							memmove((u_char*)sdata->gGT->prevNameEntered, (u_char*)sdata->gGT->currNameEntered, 0x11);
						}
						else
						{
							soundID = 0;
							if (cursorPosition2 != 1000) goto LAB_8004b0dc;
							soundID = 3;
							local_38 = -1;
						}
						MENUBOX_ClearInput();
					}
				}
			}
			else
			{
				currNameLengthCopy = currNameLength;
				soundID = 0;
				if (currNameLengthCopy)
				{
					sdata->gGT->prevNameEntered[currNameLengthCopy + 0x10] = 0;
					soundID = 4;
					if (sdata->gGT->prevNameEntered[currNameLengthCopy + 0xf] < 3)
					{
						sdata->gGT->prevNameEntered[currNameLengthCopy + 0xf] = 0;
					}
				}
			}
		}
		else
		{
			soundID = 3;
			if (cursorPosition2 == 1000)
			{
				local_38 = -1;
			}
			else
			{
				cursorPositionShort = 1000;
				soundID = 1;
			}
		}
	}
	else
	{
		if (sdata->buttonTapPerPlayer[0] & BTN_UP)
		{
			cursorPosition -= 13;
		}
		if (sdata->buttonTapPerPlayer[0] & BTN_DOWN)
		{
			cursorPosition += 13;
		}
		if (sdata->buttonTapPerPlayer[0] & BTN_LEFT)
		{
			cursorPosition--;
		}
		cursorPositionLBitshift16 = cursorPosition << 16;
		if (sdata->buttonTapPerPlayer[0] & BTN_RIGHT)
		{
			cursorPosition++;
			cursorPositionLBitshift16 = cursorPosition * 0x10000;
		}
		cursorPositionLBitshift16 = cursorPosition << 16;
		if (cursorPositionLBitshift16 < 0)
		{
			cursorPosition = 0x3e9;
			cursorPositionLBitshift16 = 0x3e90000;
		}
		cursorPositionShort = cursorPosition;
		uVar2 = cursorPosition - 500;
		if ((38 < cursorPositionLBitshift16 >> 16) && (uVar2 = cursorPosition - 500,  cursorPositionLBitshift16 >> 16 < 500))
		{
			cursorPositionShort = 0x3e9;
			uVar2 = 0x1f5;
		}
		if ((uVar2 & 0xffff) < 500)
		{
			cursorPositionShort = 38;
		}
		soundID = 1;
		if (0x3ea < cursorPositionShort)
		{
			cursorPositionShort = 0;
		}
	}
LAB_8004b0dc:
	if (soundID)
	{
		OtherFX_Play(*(u_short *)&data.soundIndexArray[soundID], 1);
	}
	sdata->gGT->TitleOSK_CursorPosition = cursorPositionShort;
	return local_38;
}