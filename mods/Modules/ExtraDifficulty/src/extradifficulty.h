#define ROW_EASY       0
#define ROW_MEDIUM     1
#define ROW_HARD       2
#define ROW_SUPER_HARD 3
#define ROW_ULTRA_HARD 4
#define EXD_VALID_ROWS 5

void MM_ExtraDifficulty(struct MenuBox*);

struct MenuRow rows_extraDifficulty[] =
{
	[ROW_EASY] =
	{
		.stringIndex = 346,
		.rowOnPressUp = ROW_EASY,
		.rowOnPressDown = ROW_MEDIUM,
		.rowOnPressLeft = ROW_EASY,
		.rowOnPressRight = ROW_EASY
	},
	[ROW_MEDIUM] =
	{
		.stringIndex = 347,
		.rowOnPressUp = ROW_EASY,
		.rowOnPressDown = ROW_HARD,
		.rowOnPressLeft = ROW_MEDIUM,
		.rowOnPressRight = ROW_MEDIUM
	},
	[ROW_HARD] =
	{
		.stringIndex = 348,
		.rowOnPressUp = ROW_MEDIUM,
		.rowOnPressDown = ROW_SUPER_HARD,
		.rowOnPressLeft = ROW_HARD,
		.rowOnPressRight = ROW_HARD
	},
	[ROW_SUPER_HARD] =
	{
		.stringIndex = 588,
		.rowOnPressUp = ROW_HARD,
		.rowOnPressDown = ROW_ULTRA_HARD,
		.rowOnPressLeft = ROW_SUPER_HARD,
		.rowOnPressRight = ROW_SUPER_HARD
	},
	[ROW_ULTRA_HARD] =
	{
		.stringIndex = 589,
		.rowOnPressUp = ROW_SUPER_HARD,
		.rowOnPressDown = ROW_ULTRA_HARD,
		.rowOnPressLeft = ROW_ULTRA_HARD,
		.rowOnPressRight = ROW_ULTRA_HARD
	},
	// finalizer
	{
		.stringIndex = -1,
		.rowOnPressUp = 0,
		.rowOnPressDown = 0,
		.rowOnPressLeft = 0,
		.rowOnPressRight = 0
	}
};

struct MenuBox extra_difficulty =
{
	.stringIndexTitle = 345,
	.posX_curr = 0,
	.posY_curr = 0,
	.unk1 = 0,
	.state = CENTER_ON_X | USE_SMALL_FONT | BIG_TEXT_IN_TITLE,
	.rows = rows_extraDifficulty,
	.funcPtr = MM_ExtraDifficulty,
	.width = 171,
	.height = 86
};