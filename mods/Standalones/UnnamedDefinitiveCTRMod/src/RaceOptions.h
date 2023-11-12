#define NUM_ROWS 4
#define MenuBoxBG_w 350
#define MenuBoxBG_x SCREEN_WIDTH/2 - 350/2
#define MenuBoxBG_y SCREEN_HEIGHT/2 - 74/2

RECT menuBoxBG =
{
	.x = MenuBoxBG_x,
	.y = MenuBoxBG_y,
	.w = MenuBoxBG_w,
	.h = 70 + 4, 
};

RECT titleSeparatorLine =
{
	.x = MenuBoxBG_x,
	.y = MenuBoxBG_y + 23,
	.w = MenuBoxBG_w,
	.h = 2,
};

RECT glowingcursor =
{
	.x = MenuBoxBG_x + 3,
	.y = 0,
	.w = MenuBoxBG_w - 6,
	.h = 9,
};

void RaceOptions_FuncPtr(struct MenuBox*);

struct MenuBox RaceOptions =
{
	.stringIndexTitle = 45,

	.posX_curr = SCREEN_WIDTH/2,
	.posY_curr = SCREEN_HEIGHT/2,

	.unk1 = 0,

	.state = (DISABLE_INPUT_ALLOW_FUNCPTRS | 0x800 | USE_SMALL_FONT | CENTER_ON_COORDS),

	.rows = 0,

	.funcPtr = RaceOptions_FuncPtr,

	.drawStyle = 0,

	.posX_prev = 0,
	.posY_prev = 0,

	.rowSelected = 0,

	.unk1c = 0,
	.unk1e = 0,

	.width = 448,
	.height = 130,

	.ptrNextBox_InHierarchy = 0,
	.ptrPrevBox_InHierarchy = 0,
};