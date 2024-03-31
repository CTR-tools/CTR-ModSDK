#include <common.h>

void DECOMP_DecalFont_DrawLineStrlen(u_char* str, short len, int posX, short posY, short fontType, int flags)
{
	struct GameTracker* gGT = sdata->gGT;

	// text is justified left by default
	if (flags & (JUSTIFY_CENTER | JUSTIFY_RIGHT))
	{
		int alignX = DECOMP_DecalFont_GetLineWidthStrlen(str, len, fontType);

		if (flags & JUSTIFY_CENTER) alignX /= 2;

		posX -= alignX;
	}

	// bug fix exclusive to versions after USA Retail
	#if BUILD >= JpnTrial

		flags &= 0x7ff;

	#else

		flags &= 0xfff;

	#endif

	for(*str != 0; *str != 0 && len != 0; str++, len--)
	{
		u_char* strcopy = str;
		u_short iconID = 0xff;
		short charWidth = data.font_charPixWidth[fontType];
		short pixWidthExtra = 0;
		short pixHeightExtra = 0;
		short iconScale = FP(1.0);

		#if BUILD == EurRetail

			int numCharacters = 1;
			int upsideDownCharacter = false;

		#endif

		int* ptrColor = data.ptrColor[flags];

		#if BUILD >= JpnTrial

			if (*strcopy == '~')
			{
				// if the current character in the string is a tilde, delete the next two characters and color the rest of the word depending on the characters being deleted
				// used with numbers according to the color ID, e.g. ~01 gives the blue-ish gray color seen in the race lap count

				u_char* strnext = str + 1;
				u_char* strnextnext = str + 2;
				str += 2;
				len -= 2;
				flags = (*strnextnext + (*strnext - 0x30) * 10) - 0x30;
				charWidth = 0;

				continue;
			}

		#endif

		if (*strcopy == ':' || *strcopy == '.') charWidth = data.font_puncPixWidth[fontType];

		// if the character is one of the PSX buttons
		// @ is circle, [ is square, ^ is triangle, * is X
		if ((((*strcopy == '@') || (*strcopy == '[')) || (*strcopy == '^')) || (*strcopy == '*'))
		{
			#if BUILD != JpnRetail

				iconScale = data.font_buttonScale[fontType];
				pixHeightExtra = data.font_buttonPixHeight[fontType];
				charWidth = data.font_charPixWidth[fontType] + data.font_buttonPixWidth[fontType];

				// use neutral vertex color for button characters
				ptrColor = data.ptrColor[GRAY];

			#else

				// japan retail adds support for the Mad Catz MC2 Racing Wheel (probably the best thing Naughty Dog added to this version to be honest)
				// this replaces the regular face button characters with ones that match the buttons on the steering wheel and recolors them accordingly

				short isRacingWheel = DECOMP_DecalFont_boolRacingWheel();

				if (!(isRacingWheel))
				{
					iconScale = data.font_buttonScale[fontType];
					pixHeightExtra = data.font_buttonPixHeight[fontType];
					charWidth = data.font_charPixWidth[fontType] + data.font_buttonPixWidth[fontType];

					// use neutral vertex color for button characters
					ptrColor = data.ptrColor[GRAY];
				}
				else
				{
					// note: the Mad Catz MC2 Racing Wheel does not use the traditional PSX buttons
					// it uses A, B, 1, and 2 instead
					int racingWheelButtonColor = PERIWINKLE;

					if (*strcopy == '@') *strcopy = 'A';
					if (*strcopy == '^') *strcopy = 'B';

					if (*strcopy == '*' || *strcopy == '[')
					{
						if (*strcopy == '*') *strcopy = '1';
						if (*strcopy == '[') *strcopy = '2';

						racingWheelButtonColor = RED;
					}

					ptrColor = data.ptrColor[racingWheelButtonColor];
				}

			#endif
		}

		// Set character sprite (icon) IDs
		// The first 0x21 (counting 0) ASCII characters don't have icon IDs assigned to them
		// Europe has additional characters composed of existing characters rearranged to resemble new ones
		// USA Retail and prototypes have placeholder data for additional characters found in the Japanese versions

		#if BUILD != EurRetail

			// ascii characters + japanese characters
			// 0xE0 characters from 0x20 to 0x100
			// TO DO: figure out why the cast to u_int is necessary --Super
			if (((u_int)*strcopy - 0x21) < 0xdf)
			{
				// get iconID based on ascii character
				iconID = data.font_characterIconID[*strcopy - 0x21];
			}

			// Japanese dakuten and handakuten
			// unused in NTSC-U and PAL
			if (*strcopy < 3)
			{
				charWidth = 0;
				iconID = data.font_indentIconID[fontType * 2 + *strcopy - 1];
				pixWidthExtra = data.font_indentPixDimensions[fontType * 2];
				pixHeightExtra = data.font_indentPixDimensions[(fontType * 2) + 1];
			}

		#else

			// europe only has 0x60 characters
			if (((u_int)*strcopy - 0x21) < 0x5f)
			{
				// get iconID based on ascii character
				iconID = data.font_characterIconID[*strcopy - 0x21];
			}

			if (*strcopy == '')
			{
				// The tilde as a diacritical mark
				// It's implemented in CTR using the underscore character, shrunk down and placed above the character that follows
				// Seen in the Spanish language for the Ñ, although because of the above mentioned you can use it on anything
				
				iconID = 0x2f;
				pixWidthExtra = data.font_EurDiacriticalTilde[fontType * 3];
				pixHeightExtra = data.font_EurDiacriticalTilde[(fontType * 3) + 1];
				iconScale = data.font_EurDiacriticalTilde[(fontType * 3) + 2];
				charWidth = 0;
			}
			if (*strcopy == '"')
			{
				// Quotation mark
				// Unlike the other new characters its representing character is actually used for a quotation mark
				// Quotation marks in the PAL version are two apostrophes joined together
				iconID = 0x24;
				numCharacters = 2;
				pixWidthExtra = data.font_EurQuotationMarkWidth[fontType];
			}

			// the following characters make use of additional width and height padding
			if (*strcopy < 3 || *strcopy == '#' || *strcopy == '$' || *strcopy == '&')
			{
				short* characterExtraDimensionsArray = 0;

				if (*strcopy < 3)
				{
					// Japanese dakuten and handakuten
					// unused in NTSC-U and PAL
					charWidth = 0;
					iconID = data.font_indentIconID[fontType * 2 + *strcopy - 1];
					characterExtraDimensionsArray = data.font_indentPixDimensions;
				}
				if (*strcopy == '#')
				{
					// Inverted exclamation mark, used in the Spanish language
					upsideDownCharacter = true;
					iconID = 0x25;
					characterExtraDimensionsArray = data.font_EurInvertedExclamationMarkData;
				}
				if (*strcopy == '$')
				{
					// Inverted question mark, used in the Spanish language
					upsideDownCharacter = true;
					iconID = 0x2e;
					characterExtraDimensionsArray = data.font_EurInvertedExclamationMarkData;
				}
				if (*strcopy == '&')
				{
					// Upwards period
					// Supposed to be the ordinal indicator character in Spanish and French
					iconID = 0x2c;
					characterExtraDimensionsArray = data.font_EurOrdinalIndicatorData;
				}

				pixWidthExtra = characterExtraDimensionsArray[fontType * 2];
				pixHeightExtra = characterExtraDimensionsArray[(fontType * 2) + 1];
			}

		#endif

		// if iconID is valid
		if (iconID != 0xff)
		{
			short iconGroupID = data.font_IconGroupID[fontType];

			#if BUILD <= UsaRetail

				// incomplete implementation of japanese font, unused
				// see below for more details
				if (iconID > 0x7f)
				{
					iconID -= 0x80;
					short kanaIconGroupID = 15;
					if (iconGroupID == 4) kanaIconGroupID = 14;
					iconGroupID = kanaIconGroupID;
				}

			#elif BUILD == JpnTrial || BUILD == JpnRetail

				// defined here as a fallback for if the character in question isn't kana
				u_short kanaID = iconID;

				struct Icon* iconStruct = 0;

				// if icon ID goes over 0x7f, then this is a japanese character (i.e. kana)
				if (iconID > 0x7f)
				{
					// kana icon IDs are in a separate icon group from other font characters
					u_short kanaID = iconID - 0x80;

					// the "big" and "small" font icon groups for kana are 14 and 15 respectively
					short kanaIconGroupID = 15;

					// if icon group is non-japanese big font, set to japanese
					if (iconGroupID == 4) kanaIconGroupID = 14;

					iconGroupID = kanaIconGroupID;

					iconStruct = &sdata->font_icon;

					if (kanaIconGroupID == 14)
					{
						sdata->font_icon.texLayout.clut = sdata->font_jfontBigIconData.clut;

						if (kanaID & 1) sdata->font_icon.texLayout.clut += 0x40;

						sdata->font_icon.texLayout.u0 = kanaID * 8 & 0xf0;
						sdata->font_icon.texLayout.u1 = sdata->font_icon.texLayout.u0 + 15;

						short whateverThisIs_big = kanaID / 2 & 0x10;

						sdata->font_icon.texLayout.v0 = whateverThisIs_big + 8;
						sdata->font_icon.texLayout.v2 = whateverThisIs_big + 23;

						sdata->font_icon.texLayout.tpage = sdata->font_jfontBigIconData.tpage + ((kanaID < 0x40) ^ 1);

						sdata->font_icon.texLayout.v1 = sdata->font_icon.texLayout.v0;
						sdata->font_icon.texLayout.u2 = sdata->font_icon.texLayout.u0;
						sdata->font_icon.texLayout.u3 = sdata->font_icon.texLayout.u1;
						sdata->font_icon.texLayout.v3 = sdata->font_icon.texLayout.v2;
					}
					else // i.e. small font
					{
						if (kanaID < 24)
						{
							sdata->font_icon.texLayout.clut = sdata->font_jfontSmallIconData.clut;

							if (kanaID & 1) sdata->font_icon.texLayout.clut += 0x40;

							sdata->font_icon.texLayout.tpage = sdata->font_jfontSmallIconData.tpage;

							short whateverThisIs_small = ((kanaID & 0xfe) + kanaID / 2) * 4; // this is the one

							if (kanaID < 12) sdata->font_icon.texLayout.u0 = whateverThisIs_small + 176;
							else             sdata->font_icon.texLayout.u0 = whateverThisIs_small + 104;

							sdata->font_icon.texLayout.u1 = sdata->font_icon.texLayout.u0 + 11;

							if (kanaID < 12) sdata->font_icon.texLayout.v0 = 24;
							else             sdata->font_icon.texLayout.v0 = 32;

							sdata->font_icon.texLayout.v2 = sdata->font_icon.texLayout.v0 + 7;

							sdata->font_icon.texLayout.v1 = sdata->font_icon.texLayout.v0;
							sdata->font_icon.texLayout.u2 = sdata->font_icon.texLayout.u0;
							sdata->font_icon.texLayout.u3 = sdata->font_icon.texLayout.u1;
							sdata->font_icon.texLayout.v3 = sdata->font_icon.texLayout.v2;
						}
						else
						{
							kanaID = (u_char)iconID - 0x98; // if you remove the u_char cast the dakuten and handakuten diacritics break. why??? --Super
							sdata->font_icon.texLayout.clut = sdata->font_jfontSmall0x18IconData.clut;

							if (kanaID & 1) sdata->font_icon.texLayout.clut += 0x40;

							sdata->font_icon.texLayout.tpage = sdata->font_jfontSmall0x18IconData.tpage;

							sdata->font_icon.texLayout.u0 = data.font_X1Y1data[kanaID * 2 + 1] / 2 * 12;
							sdata->font_icon.texLayout.u1 = sdata->font_icon.texLayout.u0 + 11;

							sdata->font_icon.texLayout.v0 = data.font_X1Y1data[kanaID * 2] * 8 + 8;
							sdata->font_icon.texLayout.v2 = data.font_X1Y1data[kanaID * 2] * 8 + 15;

							sdata->font_icon.texLayout.v1 = sdata->font_icon.texLayout.v0;
							sdata->font_icon.texLayout.u2 = sdata->font_icon.texLayout.u0;
							sdata->font_icon.texLayout.u3 = sdata->font_icon.texLayout.u1;
							sdata->font_icon.texLayout.v3 = sdata->font_icon.texLayout.v2;
						}
					}
				}

			#endif

			#if BUILD <= UsaRetail

				if (iconID < gGT->iconGroup[iconGroupID]->numIcons)
				{
					struct Icon** iconPtrArray = ICONGROUP_GETICONS(gGT->iconGroup[iconGroupID]);

					DECOMP_DecalHUD_DrawPolyGT4
					(						
						iconPtrArray[iconID],

						posX + pixWidthExtra,
						posY + pixHeightExtra,

						&gGT->backBuffer->primMem,
						gGT->pushBuffer_UI.ptrOT,

						ptrColor[0],
						ptrColor[1],
						ptrColor[2],
						ptrColor[3],

						0, iconScale
					);
				}

			#elif BUILD == JpnTrial || BUILD == JpnRetail

				if (iconStruct == 0)
				{
					struct Icon** iconPtrArray = ICONGROUP_GETICONS(gGT->iconGroup[iconGroupID]);
					if (kanaID < gGT->iconGroup[iconGroupID]->numIcons) iconStruct = iconPtrArray[kanaID];
				}
				if (iconStruct != 0)
				{
					DECOMP_DecalHUD_DrawPolyGT4
					(						
						iconStruct,

						posX + pixWidthExtra,
						posY + pixHeightExtra,

						&gGT->backBuffer->primMem,
						gGT->pushBuffer_UI.ptrOT,

						ptrColor[0],
						ptrColor[1],
						ptrColor[2],
						ptrColor[3],

						0, iconScale
					);
				}

			#else // i.e. european build

				struct Icon** iconPtrArray = ICONGROUP_GETICONS(gGT->iconGroup[iconGroupID]);

				for(; numCharacters > 0; numCharacters--, pixWidthExtra += data.font_EurPixWidthExtra[fontType])
				{
					if (upsideDownCharacter)
					{
						DECOMP_DecalHUD_Arrow2D
						(
							iconPtrArray[iconID],
							
							posX + pixWidthExtra,
							posY + pixHeightExtra,

							&gGT->backBuffer->primMem,
							gGT->pushBuffer_UI.ptrOT,

							ptrColor[2],
							ptrColor[3],
							ptrColor[0],
							ptrColor[1],

							0, iconScale, 0x800
						);
					}
					else
					{
						DECOMP_DecalHUD_DrawPolyGT4
						(
							iconPtrArray[iconID],
							
							posX + pixWidthExtra,
							posY + pixHeightExtra,

							&gGT->backBuffer->primMem,
							gGT->pushBuffer_UI.ptrOT,

							ptrColor[0],
							ptrColor[1],
							ptrColor[2],
							ptrColor[3],

							0, iconScale
						);
					}
				}

			#endif
		}
		posX += charWidth;
	}
}