int isSelectPause = 0;

RECT r =
{
	.x = 32,
	.w = 448,
	.y = 39,
	.h = 130,
};

struct MenuRow MyMenuBoxRows[] =
{
	[0] =
	{
		.stringIndex = 69,

		.rowOnPressUp    = 1,
		.rowOnPressDown  = 0,
		.rowOnPressLeft  = 0,
		.rowOnPressRight = 1,
	},
	[1] =
	{
		.stringIndex = 1,

		.rowOnPressUp    = 0,
		.rowOnPressDown  = 1,
		.rowOnPressLeft  = 1,
		.rowOnPressRight = 0,
	},
	// END OF MENU
	{
		.stringIndex = 0xFFFF,

		.rowOnPressUp = 0,
		.rowOnPressDown = 0,
		.rowOnPressLeft = 0,
		.rowOnPressRight = 0,
	}
};

struct MenuBox MyMenuBox =
{
	.stringIndexTitle = 45,

	.posX_curr = SCREEN_WIDTH/2,
	.posY_curr = SCREEN_HEIGHT/2,

	.unk1 = 0,

	.state = (CENTER_ON_COORDS),

	.rows = MyMenuBoxRows,

	.funcPtr = 0,

	.drawStyle = 0,

	.posX_prev = 0,
	.posY_prev = 0,

	.rowSelected = 0,

	.unk1a = 0,
	.unk1e = 0,

	.width = 448,
	.height = 130,

	.ptrNextBox_InHierarchy = &MyMenuBox,
	.ptrPrevBox_InHierarchy = &MyMenuBox,
};