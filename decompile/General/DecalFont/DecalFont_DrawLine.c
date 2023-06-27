#include <common.h>

void DECOMP_DecalFont_DrawLine(char* str, int posX, int posY, short fontType, int flags)
{
	DecalFont_DrawLineStrlen(str, -1, posX, posY, fontType, flags);
}