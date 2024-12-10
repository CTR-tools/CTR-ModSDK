#include <common.h>

int DECOMP_DecalFont_DrawMultiLineStrlen(char *str, short len, short posX, short posY, short maxPixLen, short fontType, short flags)
{
	char strCharacter;
	short lineLen;
	char *currPointer;
	short lettersRemaining;
	char *strPointer;
	int totalPassageHeight;

	totalPassageHeight = 0;

	do
	{
		// pointer to string
		strPointer = str;

		// rather than using \n for new lines, CTR uses \r, which is similar if you try it with printf

		// while you've not reached the end of the line
		if (*str != '\r')
		{
			// get the first character
			strCharacter = *str;

			while( 1 )
			{
				// pointer to current letter
				currPointer = strPointer;

				// number of letters remaining
				lettersRemaining = len;

				// if you reached a space, and you're
				// not out of letters yet
				if ((strCharacter == ' ') && (len != 0))
				{
					// increment pointer to next letter
					currPointer = strPointer + 1;

					// one letter less
					lettersRemaining = len - 1;
				}

				// get next character
				strCharacter = *currPointer;

				// if nullptr, or out of letters, quit the loop
				if ((strCharacter == '\0') || (lettersRemaining == 0)) break;

				// if this is a letter, number, or symbol
				if ((strCharacter != ' ') && (strCharacter != '\r'))
				{

					// get the length of the next word
					while (lettersRemaining != 0)
					{
						// increment pointer to next letter
						currPointer = currPointer + 1;

						// get value of next character
						strCharacter = *currPointer;

						// reduce number of remaining characters
						lettersRemaining = lettersRemaining + -1;

						// stop counting at a nullptr,
						// or a space (end of word),
						// or the end of the line '\r'
						if (((strCharacter == '\0') || (strCharacter == ' ')) || (strCharacter == '\r')) break;
					}
				}

				lineLen = DECOMP_DecalFont_GetLineWidthStrlen(str, (u_int)currPointer - (u_int)str, (int)fontType);

				if
				(
					// if parameter line length is longer than string line length
					(maxPixLen <= lineLen) ||
					(
						// get character
						strCharacter = *currPointer,

						// update pointer
						strPointer = currPointer,

						// update number of remaining characters
						len = lettersRemaining,

						// check if this is new line
						strCharacter == '\r'
					)
				) break;
			}
		}

		#if BUILD > UsaRetail
		if (!(flags & 0x800))
		#endif
		DECOMP_DecalFont_DrawLineStrlen(str, (u_int)strPointer - (u_int)str, (int)posX, posY + totalPassageHeight, (int)fontType, (int)flags);

		#if BUILD > SepReview

		totalPassageHeight += data.font_charPixHeight[fontType];

		#else

		// did font_charPixHeight not exist in 903?

		lettersRemaining = (short)totalPassageHeight;
		totalPassageHeight = (int)lettersRemaining + 8;
		if ((int)fontType == 1)
		{
			totalPassageHeight = (int)lettersRemaining + 0x11;
		}
		strCharacter = *strPointer;
		str = strPointer;
		if (strCharacter == '\r')
		{
			if (len != 0)
			{
				strPointer++;
				len--;
			}
			strCharacter = *strPointer;
			str = strPointer;
		}

		#endif

		if (*strPointer == '\0')
		{
			EndFunction:
			return totalPassageHeight;
		}

		if (len != 0)
		{
			strPointer = strPointer + 1;
			len = len + -1;
		}
		if ((*strPointer == '\0') || (str = strPointer, len == 0)) goto EndFunction;
	} while( 1 );
}