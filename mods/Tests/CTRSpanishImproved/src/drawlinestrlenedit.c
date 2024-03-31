#include <common.h>

void DecalHUD_DrawPolyGT4_Expanded(struct Icon* icon, u_int posX, int posY, struct PrimMem* primMem, u_long* ot, u_int topLeftColor, u_int topRightColor, u_int bottomLeftColor, u_int bottomRightColor, short scale, u_char scaleY);
void DecalHUD_Arrow2D(struct Icon* icon, u_int posX, int posY, struct PrimMem* primMem, u_long *otMemPtr, u_int color1, u_int color2, u_int color3, u_int color4, u_char semitransparencyEnabled, short scale, u_short rot);

short font_EurDiacriticalTilde[0xC] = {0, 0, 0, 2, -11, 0xc00, 2, -5, 0xc00, 2, -11, 0xc00};
short font_EurQuotationMarkWidth[4] = {0, -3, -2, -3};
short font_EurInvertedExclamationMarkData[8] = {0, 0, 8, 7, 5, 3, 8, 7};
short font_EurInvertedQuestionMarkData[8] = {0, 0, 8, 7, 5, 3, 8, 7};
short font_EurOrdinalIndicatorData[8] = {0, 0, -2, -8, -2, -3, 0, -8};
short font_EurPixWidthExtra[4] = {0, 6, 4, 5};
short AcuteAccent[0xC] = {0, 0, 0, 4, -11, 0xc00, 2, -5, 0xc00, 4, -11, 0xc00};

void DECOMP_DecalFont_DrawLineStrlen(u_char *str, short len, int posX, short posY, short fontType, int flags)
{
	u_char* character;
	int alterX;
	int iconGroupID;
	int japaneseIconGroupID;
	short pixWidthExtra;
	short pixHeightExtra;
	u_short iconID;
	int* ptrColor;
	short iconScale;
	int charLength;

	u_char* nextCharacter;
	u_char* nextNextCharacter;
	struct Icon* iconStruct;

	u_char rotateCharacter;
	u_short* fontDataPointer;
	int iVar13;

	#if BUILD == JpnTrial || BUILD == JpnRetail
	u_short iconIDBackup;
	u_short finalIconID;
	char cVar5;
	u_char unknownY;
	#endif

	int ptrColorBackup[4];
	u_char colorDiacritical = 0;
	int hackyOffset = 0;
	u_char scaleOffsetY = 0;
	u_char diacriticScaleY = 0;
	u_char letterScaleY = 0;

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
					if (*character == '')
					{
						// The tilde as a diacritical mark
						// It's implemented in CTR using the underscore character, shrunk down and placed above the character that follows
						// Seen in the Spanish language for the Ñ, although because of the above mentioned you can use it on anything

						switch(fontType)
						{
							case 1: hackyOffset = 0; break;
							case 2: hackyOffset = 1; break;
							case 3: hackyOffset = 0; break;
						}

						iconID = 0x2f;
						#if BUILD == EurRetail
						pixWidthExtra = data.font_EurDiacriticalTilde[fontType * 3] - hackyOffset;
						pixHeightExtra = data.font_EurDiacriticalTilde[(fontType * 3) + 1];
						iconScale = data.font_EurDiacriticalTilde[(fontType * 3) + 2];
						#else
						pixWidthExtra = font_EurDiacriticalTilde[fontType * 3] - hackyOffset;
						pixHeightExtra = font_EurDiacriticalTilde[(fontType * 3) + 1];
						iconScale = font_EurDiacriticalTilde[(fontType * 3) + 2];
						#endif
						if(fontType == 2) pixHeightExtra += 2;
						charLength = 0;
						colorDiacritical = 1;
						diacriticScaleY = 0;
						letterScaleY = 2;
					}
					else if (*character == '(')
					{
						iconID = 0x27;
						pixWidthExtra = AcuteAccent[fontType * 3];
						pixHeightExtra = AcuteAccent[(fontType * 3) + 1];
						iconScale = AcuteAccent[(fontType * 3) + 2];
						if(fontType == 2) iconScale = 0x1000;
						charLength = 0;
						colorDiacritical = 1;
						diacriticScaleY = 2;
						letterScaleY = 2;
					}
					else
					{
						if (*character != '"')
						{
							if (*character == '#')
							{
								// Inverted exclamation mark, used in the Spanish language
								rotateCharacter = true;
								iconID = 0x25;
								#if BUILD == EurRetail
								fontDataPointer = &data.font_EurInvertedExclamationMarkData[0];
								#else
								fontDataPointer = &font_EurInvertedExclamationMarkData[0];
								#endif
							}
							else
							{
								// Inverted question mark, used in the Spanish language
								if (*character == '$')
								{
									rotateCharacter = true;
									iconID = 0x2e;
									#if BUILD == EurRetail
									fontDataPointer = &data.font_EurInvertedQuestionMarkData[0];
									#else
									fontDataPointer = &font_EurInvertedQuestionMarkData[0];
									#endif
								}
								else
								{
									if (*character != '&')
									{
										// europe only has 0x60 characters
										#if BUILD == EurRetail
										if (((u_int)*character - 0x21) < 0x5f)
										#else
										if (((u_int)*character - 0x21) < 0xdf)
										#endif
										{
											iconID = data.font_characterIconID[*character - 0x21];
										}
										goto DrawIcon;
									}
									// Upwards period
									// Supposed to be the ordinal indicator character in Spanish and French
									iconID = 0x2c;
									#if BUILD == EurRetail
									fontDataPointer = &data.font_EurOrdinalIndicatorData[0];
									#else
									fontDataPointer = &font_EurOrdinalIndicatorData[0];
									#endif
								}
							}
							goto LoadExtraCharacterOffsets;
						}
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
					}
				}
			
				// if iconID is valid
				if (iconID != 0xff)
				{
					#if BUILD == JpnTrial || BUILD == JpnRetail

					iconIDBackup = iconID;

					// if icon ID goes over 0x7f, then this is a japanese font character
					if (iconID > 0x7f)
					{
						// japanese character icons start at 0
						iconIDBackup = iconID - 0x80;

						// the "big" and "small" font icon groups for the japanese characters are 0xE and 0xF respectively
						japaneseIconGroupID = 0xf;
						// if icon group is non-japanese big font, set to japanese
						if (iconGroupID == 4)
						{
							japaneseIconGroupID = 0xe;
						}
						iconGroupID = japaneseIconGroupID;
						
						// icon struct, see common.h
						iconStruct = &sdata->font_icon;
						finalIconID = iconIDBackup & 0xffff;

						if (japaneseIconGroupID == 0xe)
						{
							// yeah this is pretty scuffed
							// naughty dog gets the paletteXY from an array of ints containing 4 bytes of the icon struct data of the first icons in the japanese font icon groups, and the 0x18th in the small group as well, starting at the X data of the first three vertices in the icon
							// which is why I need to do pointer arithmetic here because they didn't just copy the paletteXY instead
							sdata->font_icon.paletteXY = *(short*)((int)&sdata->font_jfontBigIconData[0] + 2);

							if (iconIDBackup & 1)
							{
								sdata->font_icon.paletteXY = *(short*)((int)&sdata->font_jfontBigIconData[0] + 2) + 0x40;
							}

							sdata->font_icon.X1 = (u_char)iconIDBackup * '\b' & 0xf0;
							sdata->font_icon.X2 = sdata->font_icon.X1 + 0xf;

							unknownY = (u_char)(iconIDBackup >> 1) & 0x10;

							sdata->font_icon.Y1 = unknownY + 8;
							sdata->font_icon.Y3 = unknownY + 0x17;

							sdata->font_icon.pageXY = *(short*)((int)&sdata->font_jfontBigIconData[1] + 2) + ((u_short)((iconIDBackup & 0xffff) < 0x40) ^ 1);

							sdata->font_icon.Y2 = sdata->font_icon.Y1;
							sdata->font_icon.X3 = sdata->font_icon.X1;
							sdata->font_icon.X4 = sdata->font_icon.X2;
							sdata->font_icon.Y4 = sdata->font_icon.Y3;
						}
						else
						{
							if (finalIconID < 0x18)
							{
								sdata->font_icon.paletteXY = *(short*)((int)&sdata->font_jfontSmallIconData[0] + 2);

								if (iconIDBackup & 1)
								{
									sdata->font_icon.paletteXY = *(short*)((int)&sdata->font_jfontSmallIconData[0] + 2) + 0x40;
								}

								sdata->font_icon.pageXY = *(short*)((int)&sdata->font_jfontSmallIconData[1] + 2);

								cVar5 = (((u_char)iconIDBackup & 0xfe) + (char)(finalIconID >> 1)) * '\x04';

								if (finalIconID < 0xc)
								{
									sdata->font_icon.X1 = cVar5 + 0xb0;
								}
								else
								{
									sdata->font_icon.X1 = cVar5 + 0x68;
								}

								sdata->font_icon.X2 = sdata->font_icon.X1 + 0xb;

								if ((iconIDBackup & 0xffff) < 0xc)
								{
									sdata->font_icon.Y1 = '\x18';
								}
								else
								{
									sdata->font_icon.Y1 = ' ';
								}

								sdata->font_icon.Y3 = sdata->font_icon.Y1 + '\a';
								sdata->font_icon.Y2 = sdata->font_icon.Y1;
								sdata->font_icon.X3 = sdata->font_icon.X1;
								sdata->font_icon.X4 = sdata->font_icon.X2;
								sdata->font_icon.Y4 = sdata->font_icon.Y3;
							}
							else
							{
								iconIDBackup = iconID - 0x98;
								sdata->font_icon.paletteXY = *(short*)((int)&sdata->font_jfontSmall0x18IconData[0] + 2);

								if ((iconIDBackup & 1) != 0)
								{
									sdata->font_icon.paletteXY = *(short*)((int)&sdata->font_jfontSmall0x18IconData[0] + 2) + 0x40;
								}

								sdata->font_icon.pageXY = *(short*)((int)&sdata->font_jfontSmall0x18IconData[1] + 2);

								sdata->font_icon.X1 = ((u_char)data.font_X1Y1data[((iconIDBackup & 0xffff) * 2) + 1] >> 1) * '\f';
								sdata->font_icon.X2 = sdata->font_icon.X1 + 0xb;

								sdata->font_icon.Y1 = data.font_X1Y1data[(iconIDBackup & 0xffff) * 2] * '\b' + '\b';
								sdata->font_icon.Y3 = data.font_X1Y1data[(iconIDBackup & 0xffff) * 2] * '\b' + '\x0f';

								sdata->font_icon.Y2 = sdata->font_icon.Y1;
								sdata->font_icon.X3 = sdata->font_icon.X1;
								sdata->font_icon.X4 = sdata->font_icon.X2;
								sdata->font_icon.Y4 = sdata->font_icon.Y3;
							}
						}
					}

					#endif

					DrawIcon:
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
										ptrColor[0] = ptrColorBackup[2];
										ptrColor[1] = ptrColorBackup[0];
										ptrColor[2] = ptrColorBackup[0];
										ptrColor[3] = ptrColorBackup[0];
										break;
								}
								colorDiacritical = 0;
							}

							if (diacriticScaleY && !charLength) scaleOffsetY = diacriticScaleY;
							if (letterScaleY && charLength) scaleOffsetY = letterScaleY;
							if (iconGroupID != 5) scaleOffsetY = 0;

							if (rotateCharacter)
							{
								DecalHUD_Arrow2D
								(
									iconStruct,
									
									posX + pixWidthExtra,
									posY + pixHeightExtra,

									&sdata->gGT->backBuffer->primMem,
									sdata->gGT->pushBuffer_UI.ptrOT,

									ptrColor[2],
									ptrColor[3],
									ptrColor[0],
									ptrColor[1],

									0, iconScale, 0x800
								);
							}
							else
							{
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

									iconScale, scaleOffsetY
								);
							}
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
							if(charLength && scaleOffsetY)
							{
								scaleOffsetY = 0;
								diacriticScaleY = 0;
								letterScaleY = 0;
							}
						} while (0 < iVar13 * 0x10000);
					}
				}
				posX += charLength;

			}

			str++;
			len--;
		} while (*str != 0);
	}
	return;
}