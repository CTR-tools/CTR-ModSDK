RECT r =
{
	.x = 32,
	.y = 39,
	.w = 448,
	.h = 130,
};

RECT ones =
{
	.x = SCREEN_WIDTH/2 + SCREEN_WIDTH/8,
	.y = SCREEN_HEIGHT/2,
	.w = 15+10,
	.h = 15+10
};

RECT glowingcursor =
{
	.x = 0,
	.y = 0,
	.w = 19,
	.h = 21,
};

void heyguys(struct MenuBox*);

struct MenuBox MyMenuBox =
{
	.stringIndexTitle = 45,

	.posX_curr = SCREEN_WIDTH/2,
	.posY_curr = SCREEN_HEIGHT/2,

	.unk1 = 0,

	.state = (DISABLE_INPUT_ALLOW_FUNCPTRS | 0x800 | USE_SMALL_FONT | CENTER_ON_COORDS),

	.rows = 0,

	.funcPtr = heyguys,

	.drawStyle = 0,

	.posX_prev = 0,
	.posY_prev = 0,

	.rowSelected = 0,

	.unk1a = 0,
	.unk1e = 1,

	.width = 448,
	.height = 130,

	.ptrNextBox_InHierarchy = 0,
	.ptrPrevBox_InHierarchy = 0,
};