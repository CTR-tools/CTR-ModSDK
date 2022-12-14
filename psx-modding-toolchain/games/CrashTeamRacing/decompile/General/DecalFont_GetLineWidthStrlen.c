#include <common.h>

int DECOMP_DecalFont_GetLineWidthStrlen(char* character, int len, int fontType)
{
	short font_charPixWidth;
	short font_buttonPixWidth;
	short font_puncPixWidth;
	int pixLength;
	
	font_charPixWidth = data.font_charPixWidth[fontType];
	font_buttonPixWidth = data.font_buttonPixWidth[fontType];
	font_puncPixWidth = data.font_puncPixWidth[fontType];
	pixLength = 0;

	while((*character != 0) && (len != 0))
	{
		switch(*character)
		{
			// if the character is one of the PSX buttons
			// @ is circle, [ is square, ^ is triangle, * is cross
			case '@':
			case '[':
			case '^':
			case '*':
				// character width, plus extra spacing for button
				pixLength += font_charPixWidth + font_buttonPixWidth;
				break;
				
			// colon or period
			case ':':
			case '.':
				// punctuation spacing
				pixLength += font_puncPixWidth;
				break;

			#if BUILD > UsaRetail
			case '~':
				character += 2;
				len += 2;
				break;
			#endif

			default:
				// if normal character
				#if BUILD != EurRetail
				if(*character > 2)
				#else
				if(*character > 3)
				#endif
				{
					// normal character spacing
					pixLength += font_charPixWidth;
				}
				break;
		}

		character++;
		len--;
	}

	return pixLength;
}