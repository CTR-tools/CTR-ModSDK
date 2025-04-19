#include <common.h>

extern struct MenuRow rowsWithSave[];

struct RectMenu menu224 =
{
	.stringIndexTitle = 0xFFFF,
	.posX_curr = 0x100,
	.posY_curr = 0xA0,

	.unk1 = 0,

	.state = 0xC83,
	.rows = rowsWithSave,
	.funcPtr = UI_RaceEnd_MenuProc,
	.drawStyle = 4,
};