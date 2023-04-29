#include <common.h>

int DECOMP_DecalFont_GetLineWidthStrlen(char* str, short len, short fontType)
{
	char* character;
	int pixLength = 0;
	u_char shortenedText = 0;
	character = str;

	while((*character != 0) && (len != 0))
	{
		if(shortenedText && fontType == 1) fontType = 3;

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
			case '~':
				character += 2;
				len += 2;
				break;
			case '(':
			case ')':
			case '#':
				break;
			case '':
				shortenedText = true;
				break;
			default:
				// if normal character
				if(*character > 6)
				{
					// normal character spacing
					if(shortenedText && fontType == 2)
						pixLength += data.font_charPixWidth[fontType] - 2;
					else
						pixLength += data.font_charPixWidth[fontType];
				}
		}

		character++;
		len--;
	}

	return pixLength;
}