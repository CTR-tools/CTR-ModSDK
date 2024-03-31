#include <common.h>

void DecalHUD_DrawPolyGT4_Expanded(struct Icon* icon, u_int posX, int posY, struct PrimMem* primMem, u_long* ot, u_int topLeftColor, u_int topRightColor, u_int bottomLeftColor, u_int bottomRightColor, short scale, u_char scaleX, u_char scaleY, u_short rot, u_char mirrorX);

short font_EurDiacriticalTilde[0xC] = {0, 0, 0, 2, -11, 0xc00, 2, -5, 0xc00, 2, -11, 0xc00};
//short font_EurQuotationMarkWidth[4] = {0, -3, -2, -3};
short font_EurOrdinalIndicatorData[8] = {0, 0, -2, -8, -2, -3, 0, -8};
short font_EurPixWidthExtra[4] = {0, 6, 4, 5};
short AcuteAccent[0xC] = {0, 0, 0, 4, -11, 0xc00, 2, -5, 0xc00, 4, -11, 0xc00};
short Cedilla[0xC] = {0, 0, 0, 4, 8, 0xc00, 2, 1, 0xc00, 4, 8, 0xc00};
short Circumflex[0xC] = {0, 0, 0, 7, -1, 0x1000, 5, 2, 0xc00, 7, -1, 0x1000};

void DECOMP_DecalFont_DrawLineStrlen(u_char *str, short len, int posX, short posY, short fontType, int flags)
{
	u_char* character;
	int alterX;
	int iconGroupID;
	short pixWidthExtra;
	short pixHeightExtra;
	u_short iconID;
	int* ptrColor;
	short iconScale;
	int charLength;

	u_char* nextCharacter;
	u_char* nextNextCharacter;
	struct Icon* iconStruct;

	char rotateCharacter;
	u_short* fontDataPointer;
	int iVar13;

	int ptrColorBackup[4];
	int colorDiacritical = 0;
	int scaleOffsetX = 0;
	char scaleOffsetY = 0;
	char isCedilla = 0;
	char diacriticScaleY = 0;
	char letterScaleY = 0;
	u_short rot = 0;
	char mirrorX;
	char shortenedText = 0;

	// If you do not want text centered
	if ((flags & 0x8000) == 0)
	{
		// If you dont want text to "end" at the given X position
		if ((flags & 0x4000) == 0)
		{
			// make the text "start" at the given X position
			goto LAB_80022598;
		}

		// If you want text to "end" here

		// subtract X position by result
		alterX = DecalFont_GetLineWidthStrlen(str, len, fontType);
	}

	// If you do want text centered
	else
	{
		alterX = DecalFont_GetLineWidthStrlen(str, len, fontType);

		// Subtract X position by half of length
		alterX = (alterX << 0x10) >> 0x11;
	}

	// subtract posX for alignment
	posX = posX - alterX;

LAB_80022598:

	flags &= 0x7ff;

	// At this point, posX may or may not have
	// been modified, depending on preference

	// Draw string, starting at posX = posX

	if (*str != 0)
	{
		do
		{
			pixWidthExtra = 0;
			if (len == 0)
			{
				return;
			}
			iconID = 0xff;
			pixHeightExtra = 0;

			// get vertex color for character
			ptrColor = data.ptrColor[flags];

			charLength = data.font_charPixWidth[fontType];

			// current character
			character = str;
		
			iconScale = 0x1000;

			iVar13 = 1;
			rotateCharacter = 0;
			iconGroupID = 0;
			iconStruct = 0;
			mirrorX = 0;

			if (*character == '~')
			{
				// if the current character in the string is a tilde, delete the next two characters and color the rest of the word depending on the characters being deleted
				// used with numbers according to the color ID, e.g. ~01 gives the blue-ish gray color seen in the race lap count
				// a hacky implementation of in-line coloring but a cool one nonetheless

				nextCharacter = str + 1;
				nextNextCharacter = str + 2;
				str += 2;
				len -= 2;
				flags = (*nextNextCharacter + (*nextCharacter - 0x30) * 10) - 0x30;
				charLength = 0;
			}

			else
			{

				if ((*character == ':') || (*character == '.')) 
				{
					charLength = data.font_puncPixWidth[fontType];
				}

				else
				{
					if ((((*character == '@') || (*character == '[')) || (*character == '^')) || (*character == '*')) 
					{
						iconScale = data.font_buttonScale[fontType];
						pixHeightExtra = data.font_buttonPixHeight[fontType];
						charLength = data.font_charPixWidth[fontType] + data.font_buttonPixWidth[fontType];

						// use neutral vertex color for button characters
						ptrColor = data.ptrColor[GRAY];
					}
				}
			
				// used for Europe-only characters
				if (*character < 3) 
				{
					charLength = 0;
					iconID = data.font_indentIconID[fontType * 2 + *character - 1];
					
					fontDataPointer = &data.font_indentPixDimensions[0];

					LoadExtraCharacterOffsets:
					pixWidthExtra = fontDataPointer[fontType * 2];
					pixHeightExtra = fontDataPointer[(fontType * 2) + 1];
				}
				else
				{
					switch (*character)
					{
						case '':
							// The tilde as a diacritical mark
							// It's implemented in CTR using the underscore character, shrunk down and placed above the character that follows
							// Seen in the Spanish language for the Ñ, although because of the above mentioned you can use it on anything

							iconID = 0x2f;
							#if BUILD == EurRetail
							pixWidthExtra = data.font_EurDiacriticalTilde[fontType * 3];
							if(fontType == 2) pixWidthExtra = data.font_EurDiacriticalTilde[fontType * 3] - 1;
							pixHeightExtra = data.font_EurDiacriticalTilde[(fontType * 3) + 1];
							iconScale = data.font_EurDiacriticalTilde[(fontType * 3) + 2];
							#else
							pixWidthExtra = font_EurDiacriticalTilde[fontType * 3];
							if(fontType == 2) pixWidthExtra = font_EurDiacriticalTilde[fontType * 3] - 1;
							pixHeightExtra = font_EurDiacriticalTilde[(fontType * 3) + 1];
							iconScale = font_EurDiacriticalTilde[(fontType * 3) + 2];
							#endif
							if(fontType == 2) pixHeightExtra += 2;
							charLength = 0;
							colorDiacritical = 1;
							diacriticScaleY = 0;
							letterScaleY = 2;
							break;
						case '(':
							iconID = 0x27;
							pixWidthExtra = AcuteAccent[fontType * 3];
							pixHeightExtra = AcuteAccent[(fontType * 3) + 1];
							iconScale = AcuteAccent[(fontType * 3) + 2];
							if(fontType == 2) iconScale = 0x1000;
							charLength = 0;
							colorDiacritical = 1;
							diacriticScaleY = 2;
							letterScaleY = 2;
							break;
						case ')':
							iconID = 0x27;
							pixWidthExtra = Cedilla[fontType * 3];
							pixHeightExtra = Cedilla[(fontType * 3) + 1];
							iconScale = Cedilla[(fontType * 3) + 2];
							if(fontType == 2) iconScale = 0x1000;
							charLength = 0;
							colorDiacritical = 1;
							diacriticScaleY = 2;
							letterScaleY = 1;
							break;
						case '':
							rotateCharacter = true;
							iconID = 0x1f;
							pixWidthExtra = Circumflex[fontType * 3];
							pixHeightExtra = Circumflex[(fontType * 3) + 1];
							iconScale = Circumflex[(fontType * 3) + 2];
							charLength = 0;
							colorDiacritical = 1;
							diacriticScaleY = 2;
							letterScaleY = 2;
							break;
						case '':
							iconID = 0x27;
							pixWidthExtra = AcuteAccent[fontType * 3] - 5;
							pixHeightExtra = AcuteAccent[(fontType * 3) + 1];
							iconScale = AcuteAccent[(fontType * 3) + 2];
							if(fontType == 2) iconScale = 0x1000;
							charLength = 0;
							colorDiacritical = 1;
							diacriticScaleY = 2;
							letterScaleY = 2;
							mirrorX = true;
							break;
						case '':
							if (fontType == 1) fontType = 3;
							charLength = 0;
							iconID = 0xFF;
							shortenedText |= 2;
							break;
						case '#':
							charLength = -4;
							iconID = 0xFF;
							if (fontType == 1 || fontType == 3) scaleOffsetX = 4;
							shortenedText |= 4;
							break;
						/*
						case '"':
							// the current character must be a quotation mark at this point
							// unlike the other characters it is actually used for a quotation mark
							// quotation marks in the european version are two apostrophes joined together
							iVar13 = 2;
							#if BUILD == EurRetail
							pixWidthExtra = data.font_EurQuotationMarkWidth[fontType];
							#else
							pixWidthExtra = font_EurQuotationMarkWidth[fontType];
							#endif
							// set icon ID to apostrophe
							iconID = 0x24;
							break;
						*/
						case '&':
							// Upwards period
							// Supposed to be the ordinal indicator character in Spanish and French
							iconID = 0x2c;
							#if BUILD == EurRetail
							fontDataPointer = &data.font_EurOrdinalIndicatorData[0];
							#else
							fontDataPointer = &font_EurOrdinalIndicatorData[0];
							#endif
							goto LoadExtraCharacterOffsets;
							break;
						default:
							// europe only has 0x60 characters
							#if BUILD == EurRetail
							if (((u_int)*character - 0x21) < 0x5f)
							#else
							if (((u_int)*character - 0x21) < 0xdf)
							#endif
							{
								iconID = data.font_characterIconID[*character - 0x21];
							}
					}
				}
			
				// if iconID is valid
				if (iconID != 0xff)
				{
					iconGroupID = data.font_IconGroupID[fontType];

					ptrColorBackup[0] = ptrColor[0];
					ptrColorBackup[1] = ptrColor[1];
					ptrColorBackup[2] = ptrColor[2];
					ptrColorBackup[3] = ptrColor[3];
					
					// if icon struct somehow doesn't exist then use fallback
					if (!iconStruct)
					{
						if (iconID < sdata->gGT->iconGroup[iconGroupID]->numIcons)
						{							
							struct Icon** iconPtrArray =
								ICONGROUP_GETICONS(sdata->gGT->iconGroup[iconGroupID]);
							
							iconStruct = iconPtrArray[iconID];
						}
					}
					if (iconStruct)
					{
						do
						{
							if(colorDiacritical)
							{
								switch(*character)
								{
									case '':
										ptrColor[0] = ptrColorBackup[2];
										ptrColor[1] = ptrColorBackup[2];
										ptrColor[2] = ptrColorBackup[0];
										ptrColor[3] = ptrColorBackup[0];
										break;
									case '(':
									case '':
										ptrColor[0] = ptrColorBackup[2];
										ptrColor[1] = ptrColorBackup[0];
										ptrColor[2] = ptrColorBackup[0];
										ptrColor[3] = ptrColorBackup[0];
										break;
									case ')':
										ptrColor[0] = ptrColorBackup[3];
										ptrColor[1] = ptrColorBackup[3];
										ptrColor[2] = ptrColorBackup[3];
										ptrColor[3] = ptrColorBackup[3];
										break;
									case '':
										ptrColor[0] = ptrColorBackup[0];
										ptrColor[1] = ptrColorBackup[0];
										ptrColor[2] = ptrColorBackup[0];
										ptrColor[3] = ptrColorBackup[0];
								}
								colorDiacritical = 0;
							}

							if (diacriticScaleY && !charLength) scaleOffsetY = diacriticScaleY;
							if (letterScaleY && charLength) scaleOffsetY = letterScaleY;
							if (iconGroupID != 5)
							{
								scaleOffsetY = 0;
								if (*character == ')') scaleOffsetY = 2;
								if (*character == '')
								{
							
									struct Icon** iconPtrArray =
										ICONGROUP_GETICONS(sdata->gGT->iconGroup[5]);
							
									iconStruct = iconPtrArray[0x1f];
									scaleOffsetY = 2;
								}
							}
							if (isCedilla)
							{
								if (iconGroupID == 5) pixHeightExtra -= 1;
								isCedilla = 0;
							}

							if (rotateCharacter) rot = 0x800;
							if (!rotateCharacter) rot = 0;
							DecalHUD_DrawPolyGT4_Expanded
							(
								iconStruct,
								
								posX + pixWidthExtra,
								posY + pixHeightExtra,

								&sdata->gGT->backBuffer->primMem,
								sdata->gGT->pushBuffer_UI.ptrOT,

								ptrColor[0],
								ptrColor[1],
								ptrColor[2],
								ptrColor[3],

								iconScale, scaleOffsetX, scaleOffsetY, rot, mirrorX
							);
							iVar13--;
							#if BUILD == EurRetail
							pixWidthExtra += data.font_EurPixWidthExtra[fontType];
							#else
							pixWidthExtra += font_EurPixWidthExtra[fontType];
							#endif
							if(!colorDiacritical)
							{
								ptrColor[0] = ptrColorBackup[0];
								ptrColor[1] = ptrColorBackup[1];
								ptrColor[2] = ptrColorBackup[2];
								ptrColor[3] = ptrColorBackup[3];
							}
							if (*character == ')') isCedilla = 1;
							if(charLength && scaleOffsetY)
							{
								scaleOffsetY = 0;
								diacriticScaleY = 0;
								letterScaleY = 0;
							}
						} while (0 < iVar13 * 0x10000);
					}
				}
				if (charLength > 0)
				{
					if (shortenedText & 2)
					{
						if (iconGroupID == 5) charLength -= 2;
						if (fontType == 2 && iconID == 0xff) charLength -= 4;
						if (fontType == 3 && iconID == 0xff) charLength -= 6;
					}
					if (shortenedText & 4) charLength -= 2;
				}
				posX += charLength;

			}

			str++;
			len--;
		} while (*str != 0);
	}
	return;
}