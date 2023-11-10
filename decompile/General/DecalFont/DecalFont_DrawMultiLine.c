#include <common.h>

int DECOMP_DecalFont_DrawMultiLine(char* str, int posX, int posY, int maxPixLen, short fontType, int flags)
{
	return DECOMP_DecalFont_DrawMultiLineStrlen(str, -1, posX, posY, maxPixLen, fontType, flags);
}