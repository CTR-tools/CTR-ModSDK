#include <common.h>

int DecalFont_GetLineWidthStrlen(char* str, short len, short fontType);

int DECOMP_DecalFont_GetLineWidth(char* str, short fontType)
{
	return DecalFont_GetLineWidthStrlen(str, -1, fontType);
}