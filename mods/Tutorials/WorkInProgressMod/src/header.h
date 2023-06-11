int isSelectPause = 0;

RECT r =
{
	.x = 32,
	.w = 448,
	.y = 39,
	.h = 130,
};

void heyguys(struct MenuBox* m);

struct MenuRow MyMenuBox2Rows[] =
{
	[0] =
	{
		.stringIndex = 70,

		.rowOnPressUp    = 1,
		.rowOnPressDown  = 0,
		.rowOnPressLeft  = 0,
		.rowOnPressRight = 1,
	},
	[1] =
	{
		.stringIndex = 2,

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

struct MenuBox MyMenuBox2 =
{
	.stringIndexTitle = 0,

	.posX_curr = 0,
	.posY_curr = SCREEN_HEIGHT/4,

	.unk1 = 0,

	.state = (CENTER_ON_COORDS | SHOW_ONLY_HIGHLIT_ROW),

	.rows = MyMenuBox2Rows,

	.funcPtr = 0,

	.drawStyle = 0,

	.posX_prev = 0,
	.posY_prev = 0,

	.rowSelected = 0,

	.unk1a = 0,
	.unk1e = 0,

	.width = 448,
	.height = 130,

	.ptrNextBox_InHierarchy = 0,
	.ptrPrevBox_InHierarchy = 0,
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

	.state = (CENTER_ON_COORDS | EXECUTE_FUNCPTR),

	.rows = MyMenuBoxRows,

	.funcPtr = heyguys,

	.drawStyle = 0,

	.posX_prev = 0,
	.posY_prev = 0,

	.rowSelected = 0,

	.unk1a = 0,
	.unk1e = 0,

	.width = 448,
	.height = 130,

	.ptrNextBox_InHierarchy = &MyMenuBox2,
	.ptrPrevBox_InHierarchy = 0,
};