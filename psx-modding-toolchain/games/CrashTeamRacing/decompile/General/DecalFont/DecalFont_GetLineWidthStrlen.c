#include <common.h>

#if BUILD == JpnRetail
	u_int DecalFont_boolRacingWheel();
#endif

int DECOMP_DecalFont_GetLineWidthStrlen(char* character, int len, int fontType)
{
	short font_charPixWidth;
	short font_buttonPixWidth;
	short font_puncPixWidth;
	int pixLength;
	char c;
	#if BUILD == JpnRetail
		u_int isRacingWheel;
	#endif
	
	font_charPixWidth = data.font_charPixWidth[fontType];
	font_buttonPixWidth = data.font_buttonPixWidth[fontType];
	font_puncPixWidth = data.font_puncPixWidth[fontType];
	pixLength = 0;

	while((*character != 0) && (len != 0))
	{
		c = *character;
		
		// do not use "switch" or "else if" that increases the number of bytes, and makes the function too large

		// if the character is one of the PSX buttons
		// @ is circle, [ is square, ^ is triangle, * is cross
		if
		(
			(c == '@') ||
			(c == '[') ||
			(c == '^') ||
			(c == '*')
		)
		{
			#if BUILD == JpnRetail

				isRacingWheel = DecalFont_boolRacingWheel();
								
				if ((isRacingWheel & 0xffff) == 0) pixLength += font_buttonPixWidth;
				else pixLength += font_charPixWidth;

			#else

				// character width, plus extra spacing for button
				pixLength += font_buttonPixWidth; // + font_charPixWidth

			#endif
		}
		
		// colon or period
		if
		(
			(c == ':') ||
			(c == '.')
		)
		{
			// punctuation spacing
			pixLength += font_puncPixWidth - font_charPixWidth; // + font_charPixWidth
		}
		
		#if BUILD > UsaRetail
		if(c == '~')
		{
			character += 2;
			len -= 2;
			
			// dont add charPixWidth
			goto NextIteration;
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
			// this will be added on top of button,
			// and colon, and period, so dont "else if"
			pixLength += font_charPixWidth;
		}

NextIteration:
		character++;
		len--;
	}

	return pixLength;
}