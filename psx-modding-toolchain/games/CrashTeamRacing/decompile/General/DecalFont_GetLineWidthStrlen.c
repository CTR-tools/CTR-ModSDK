#include <common.h>

int DECOMP_DecalFont_GetLineWidthStrlen(char* character, int len, int fontType)
{
	short font_charPixWidth;
	short font_buttonPixWidth;
	short font_puncPixWidth;
	int pixLength;
	char c;
	
	font_charPixWidth = data.font_charPixWidth[fontType];
	font_buttonPixWidth = data.font_buttonPixWidth[fontType];
	font_puncPixWidth = data.font_puncPixWidth[fontType];
	pixLength = 0;

	while((*character != 0) && (len != 0))
	{
		c = *character;
		
		// do not use "switch" or "else if" that increases 
		// number of bytes, and makes the function too large
		
		// if the character is one of the PSX buttons
		// @ is circle, [ is square, ^ is triangle, * is cross
		if(
			(c == '@') ||
			(c == '[') ||
			(c == '^') ||
			(c == '*')
		)
		{
			// character width, plus extra spacing for button
			pixLength += font_charPixWidth + font_buttonPixWidth;
		}
		
		// colon or period
		if(
			(c == ':') ||
			(c == '.')
		)
		{
			// punctuation spacing
			pixLength += font_puncPixWidth;
		}
		
		#if BUILD > UsaRetail
		if(c == '~')
		{
			character += 2;
			len += 2;
		}
		#endif

		// if normal character
		#if BUILD != EurRetail
		if(c > 2)
		#else
		if(c > 3)
		#endif
		{
			// normal character spacing
			pixLength += font_charPixWidth;
		}

		character++;
		len--;
	}

	return pixLength;
}