#include <common.h>

struct MenuRow rowsWithSave[4] =
{
	// Retry
	{
		.stringIndex = 4,
		.rowOnPressUp = 0,
		.rowOnPressDown = 1,
		.rowOnPressLeft = 0,
		.rowOnPressRight = 0,
	},

	// Save Ghost
	{
		.stringIndex = 9,
		.rowOnPressUp = 0,
		.rowOnPressDown = 2,
		.rowOnPressLeft = 1,
		.rowOnPressRight = 1,
	},

	// Quit
	{
		.stringIndex = 3,
		.rowOnPressUp = 1,
		.rowOnPressDown = 2,
		.rowOnPressLeft = 2,
		.rowOnPressRight = 2,
	},

	// NULL, end of menu
	{
		.stringIndex = 0xFFFF,
		.rowOnPressUp = 0,
		.rowOnPressDown = 0,
		.rowOnPressLeft = 0,
		.rowOnPressRight = 0,
	}
};