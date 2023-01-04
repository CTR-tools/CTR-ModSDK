#include <common.h>

void DECOMP_MENUBOX_GetHeight(struct MenuBox* m, short* height, int boolCheckSubmenu)
{
	int lineHeight;
	
	// heighth of small line
	lineHeight = data.font_charPixHeight[FONT_SMALL];
	
	// if small text disabled
	if((m->state & 0x80) == 0)
	{
		// height of big line
		lineHeight = data.font_charPixHeight[FONT_BIG] + 3;
	}
}