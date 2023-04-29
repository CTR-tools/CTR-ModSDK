#include <common.h>

int DecalFont_DrawMultiLineStrlen(char *str, short len, short posX, short posY, short maxPixLen, short fontType, short flags);

int DECOMP_DecalFont_DrawMultiLine(char* str, int posX, int posY, int maxPixLen, short fontType, int flags)
{
	return DecalFont_DrawMultiLineStrlen(str, -1, posX, posY, maxPixLen, fontType, flags);
}