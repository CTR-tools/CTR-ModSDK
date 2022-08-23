#include <common.h>

void DecalFont_DrawLineStrlen(char* str, short len, int posX, int posY, short fontType, int flags);

void DECOMP_DecalFont_DrawLine(char* str, int posX, int posY, short fontType, int flags)
{
	DecalFont_DrawLineStrlen(str, -1, posX, posY, fontType, flags);
}