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
		.stringIndex = 0,

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
};

struct MenuBox MyMenuBox =
{
	.stringIndexTitle = 0,

	.posX_curr = 10,
	.posY_curr = 10,

	.unk1 = 0,

	.state = (CENTER_X | CENTER_Y),

	.rows = MyMenuBoxRows,

	.funcPtr = 0,

	.drawStyle = 0,

	.posX_prev = 10,
	.posY_prev = 10,

	.rowSelected = 0,

	.unk1a = 0,
	.unk1e = 0,

	.width = 448,
	.height = 130,

	.ptrNextBox_InHierarchy = 0,
	.ptrPrevBox_InHierarchy = 0,
};