#include <common.h>

#ifdef REBUILD_PC
int kbCurr = 0;
int kbPrev = 0;
void SubmitName_UseKeyboard(int key)
{
	kbCurr = key;
}
#endif

short DECOMP_SubmitName_DrawMenu(u_short string)
{
	short currNameLength;
	u_short uVar3;
	int currNameWidth;
	u_int uVar2;
	u_int cursorCharacter;
	int cursorPosition;
	u_int keyboardCharacter;
	char* currNameEntered;
	u_short strColorBlink;
	u_short blinkWhite;
	int j;
	int i;
	u_int soundID;
	short currNameLengthIncrement;
	RECT r;
	u_short stringCopy;
	short nameLength;
	short local_38;
	int letterID;
	int strlenCurrNameEnteredInt;
	u_int keyboardCharacterTopByte;
	u_char character;

	struct GameTracker* gGT = sdata->gGT;

	soundID = 0;
	local_38 = 0;
	nameLength = 0;
	stringCopy = string;
	strlenCurrNameEnteredInt = strlen(gGT->currNameEntered);
	currNameLength = strlenCurrNameEnteredInt;
	currNameEntered = gGT->currNameEntered;
	blinkWhite = ((sdata->typeTimer >> FPS_RIGHTSHIFT(0)) & 1) << 2;

	while(currNameEntered[0] != 0)
	{
		if (currNameEntered[0] > 2)
		{
			nameLength++;
		}

		currNameEntered++;
	}

	cursorPosition = gGT->typeCursorPosition;
	if ((cursorPosition > 38) && (cursorPosition < 1000))
	{
		cursorPosition = 38;
	}

	sdata->typeTimer++;
	letterID = 0;

	// grid of letters, 13x3
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 13; j++)
		{
			// Not certain if this is "needed" by the Japan version,
			// or if this was a mistake, by using "int" and pointer to int, that
			// makes a 4-byte string that works fine, have not tested japan yet

#if 0

	// char[4] keyboardString instead of int
			keyboardCharacter = data.unicodeAscii[letterID];
			keyboardCharacterTopByte = keyboardCharacter & 0xff00;
			if ((keyboardCharacter & 0xff00) == 0x1000)
			{
				keyboardCharacter = keyboardCharacter & 0xff;
				keyboardCharacterTopByte = 0;
			}

			// if American letters (char in array of short)
			if (keyboardCharacterTopByte == 0)
			{
				keyboardString[1] = 0;
				keyboardString[0] = keyboardCharacter;
			}

			// if Japan letters (short in array of short)
			else
			{
				keyboardString[2] = 0;
				keyboardString[0] = (keyboardCharacter << 16) >> 24;
				keyboardString[1] = keyboardCharacter;
			}

#endif

			// this works fine?
#if 1
// Turn two-byte value into four-byte string (int)
			int keyboardString = data.unicodeAscii[letterID];
#endif

			// LETTER button blink
			strColorBlink = 0;
			if (cursorPosition == letterID)
				strColorBlink = blinkWhite;

			// LETTER button draw
			DECOMP_DecalFont_DrawLine(
				&keyboardString,

				//j*22 + 116,
				j * WIDE_PICK(22, 17) + WIDE_PICK(116, 148),

				i * 18 + 88,
				FONT_BIG, strColorBlink);

			letterID++;
		}
	}

	// PLEASE ENTER YOUR NAME
	DECOMP_DecalFont_DrawLine(sdata->lngStrings[318], 256, 44, FONT_BIG, (JUSTIFY_CENTER | ORANGE));

	// player name
	DECOMP_DecalFont_DrawLine(
		gGT->currNameEntered,

		// original name max len = 8,
		// 192 = 256 - iconW(16) * halfMaxLen(4)
		WIDE_PICK(192,  208),

		68,
		FONT_BIG, WHITE);

	if (((sdata->typeTimer & FPS_DOUBLE(2)) != 0) && (currNameLength < 16))
	{
		currNameWidth = DECOMP_DecalFont_GetLineWidth(gGT->currNameEntered, FONT_BIG);

		DECOMP_DecalFont_DrawLine(
			sdata->str_underscore,
			currNameWidth + WIDE_PICK(192,  208),

			68,
			FONT_BIG, ORANGE);
	}

	// SAVE button blink
	strColorBlink = 0;
	if (cursorPosition == 1001)
		strColorBlink = blinkWhite;

	// SAVE button draw
	DECOMP_DecalFont_DrawLine(
		sdata->lngStrings[stringCopy],

		// 472 is (r.x + r.w - 8)
		WIDE_PICK(472, 416),

		150,
		FONT_BIG, (JUSTIFY_RIGHT | strColorBlink));

	// CANCEL button blink
	strColorBlink = 0;
	if (cursorPosition == 1000)
		strColorBlink = blinkWhite;

	DECOMP_DecalFont_DrawLine(
		sdata->lngStrings[321],

		// 40 is (r.x + 8)
		WIDE_PICK(40, 96),

		150,
		1, strColorBlink);

	// leftX = 32 (256-224)
	// rightX = 480 (256+224)
	// r.w = 32
	// r.w = 448

	// in 16x9,
	// subtract 1/8 from r.x
	// subtract 1/4 from r.w
	r.x = WIDE_PICK(32, 88);
	r.w = WIDE_34(448);

	r.y = 62;
	r.h = 2;
	Color color;
	color.self = sdata->battleSetup_Color_UI_1;
	DECOMP_RECTMENU_DrawOuterRect_Edge(&r, color, 0x20, gGT->backBuffer->otMem.startPlusFour);

	r.y = 39;
	r.h = 130;
	DECOMP_RECTMENU_DrawInnerRect(
		&r, 0,
		gGT->backBuffer->otMem.startPlusFour);

	int tap = sdata->buttonTapPerPlayer[0];

#ifdef REBUILD_PC

	if (kbCurr != kbPrev)
	{
		// Between A and Z
		if (
				(kbCurr >= 4) &&
				(kbCurr <= 29)
			)
		{
			// SDL_KEY_A = 4
			kbCurr -= 4;

			// cursor position of 'A'
			kbCurr += 0;

			cursorPosition = kbCurr;
			soundID = 1;
			tap = BTN_CIRCLE;
		}

		// '0' key
		if (kbCurr == 39)
		{
			cursorPosition = 2*13;
			tap = BTN_CIRCLE;
		}

		// Between 1 and 9
		if (
			(kbCurr >= 30) &&
			(kbCurr <= 38)
			)
		{
			// SDL_SCANCODE_1 = 30
			kbCurr -= 30;

			// cursor position of '1'
			kbCurr += 2*13 + 1;

			cursorPosition = kbCurr;
			tap = BTN_CIRCLE;
		}

		// Escape
		if (kbCurr == 41)
		{
			cursorPosition = 1000;
			tap = BTN_CIRCLE;
		}

		// Backspace
		if (kbCurr == 42)
		{
			cursorPosition = kbCurr-4;
			tap = BTN_CIRCLE;
		}

		// Space
		if (kbCurr == 44)
		{
			cursorPosition = 37;
			tap = BTN_CIRCLE;
		}
	}

	kbPrev = kbCurr;

	// Press Enter
	int NikoGetEnterKey();
	if (NikoGetEnterKey())
	{
		cursorPosition = 1001;
		tap = BTN_CIRCLE;
	}

#endif

	if ((tap & (BTN_UP | BTN_DOWN | BTN_LEFT | BTN_RIGHT)) == 0)
	{
		if ((tap & BTN_START) == 0)
		{
			if ((tap & (BTN_TRIANGLE | BTN_SQUARE_one)) == 0)
			{
				if (tap & (BTN_CIRCLE | BTN_CROSS_one))
				{
					// Go Back button
					if (cursorPosition == 38)
					{
						soundID = 2;
						gGT->currNameEntered[currNameLength - 1] = 0;
					}

					// not Go Back button
					else if (cursorPosition < 38)
					{
						// Save or Cancel
						cursorCharacter = data.unicodeAscii[cursorPosition];
						if ((data.unicodeAscii[cursorPosition] & 0xff00) == 0x1000)
						{
							cursorCharacter &= 0xff;
						}

						// too many letters
						soundID = 5;

						if (nameLength < 8)
						{
							soundID = 1;

							// Same issue as before, might be needed in japan,
							// might not be needed at all, needs testing
#if 0
							cursorCharacterLBitshift16 = cursorCharacter << 16;
							currNameLengthIncrement = currNameLength;
							if (cursorCharacter & 0xff00)
							{
								currNameLengthIncrement = currNameLength + 1;
								cursorCharacter &= 0xff;
								gGT->currNameEntered[currNameLength] = cursorCharacterLBitshift16 >> 24;
							}
#endif

							gGT->currNameEntered[currNameLength] = cursorCharacter;
						}
					}

					else
					{
						// SAVE button
						if (cursorPosition == 1001)
						{
							soundID = 2;
							local_38 = 1;
							memmove(gGT->prevNameEntered, gGT->currNameEntered, 0x11);
						}

						// CANCEL button
						else
						{
							soundID = 0;
							if (cursorPosition != 1000) goto LAB_8004b0dc;
							soundID = 3;
							local_38 = -1;
						}

						DECOMP_RECTMENU_ClearInput();
					}
				}
			}

			// Backspace
			else
			{
				// no sound
				soundID = 0;
				if (currNameLength != 0)
				{
					// go back one character
					soundID = 4;
					gGT->currNameEntered[currNameLength - 1] = 0;

					if (gGT->currNameEntered[currNameLength - 2] < 3)
						gGT->currNameEntered[currNameLength - 2] = 0;
				}
			}
		}
		else
		{
			soundID = 3;
			if (cursorPosition == 1000)
			{
				local_38 = -1;
			}
			else
			{
				cursorPosition = 1000;
				soundID = 1;
			}
		}
	}
	else
	{
		int tap = sdata->buttonTapPerPlayer[0];

		if (tap & BTN_UP)
		{
			cursorPosition -= 13;
		}
		if (tap & BTN_DOWN)
		{
			cursorPosition += 13;
		}
		if (tap & BTN_LEFT)
		{
			cursorPosition--;
		}
		if (tap & BTN_RIGHT)
		{
			cursorPosition++;
		}

		if (cursorPosition < 0)
		{
			cursorPosition = 1001;
		}

		uVar2 = cursorPosition - 500;
		if ((38 < cursorPosition) && (cursorPosition < 500))
		{
			cursorPosition = 1001;
			uVar2 = 501;
		}
		if ((uVar2 & 0xffff) < 500)
		{
			cursorPosition = 38;
		}
		soundID = 1;

		// == Naughty Dog Bug ==
		// This used to be 1002, which would allow you to
		// press Right on SAVE, and cursor would go off-screen
		if (cursorPosition > 1001)
		{
			cursorPosition = 0;
		}
	}

LAB_8004b0dc:

if (soundID != 0)
	{
		DECOMP_OtherFX_Play(data.soundIndexArray[soundID], 1);
	}
	gGT->typeCursorPosition = cursorPosition;
	return local_38;
}