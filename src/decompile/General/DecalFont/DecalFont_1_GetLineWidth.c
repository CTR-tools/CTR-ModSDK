#include <common.h>

int DECOMP_DecalFont_GetLineWidth(char* str, short fontType)
{
	return DECOMP_DecalFont_GetLineWidthStrlen(str, -1, fontType);
}