#include <common.h>

int DECOMP_DecalFont_GetLineWidthStrlen(char* str, short len, short fontType)
{
	char* character;
	int pixLength = 0;
	character = str;

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
				pixLength += data.font_charPixWidth[fontType] + data.font_buttonPixWidth[fontType];
				break;
			// colon or periodt
			case ':':
			case '.':
				// punctuation spacing
				pixLength += data.font_puncPixWidth[fontType];
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
					pixLength += data.font_charPixWidth[fontType];
				}
		}

		character++;
		len--;
	}

	return pixLength;
}