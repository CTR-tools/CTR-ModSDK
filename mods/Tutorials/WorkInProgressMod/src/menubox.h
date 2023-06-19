RECT r =
{
	.x = 32,
	.w = 448,
	.y = 39,
	.h = 130,
};

RECT glowingcursor =
{
	.x = 40,
	.w = 40,
	.y = 128,
	.h = 50,
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