#include <common.h>

// For some reason, the game uses empty
// Menu structs to change funcPtr, rather
// than threads

// Judging by Aug 5, using Menu
// for Adv Character Select, there was probably
// a time when every state of main menu was a
// traditional-looking Menu, so it was just
// kept that way

void MM_CupSelect_Init();
void MM_TrackSelect_Init();

void MyMenuProc(struct RectMenu* m);

struct RectMenu myBox =
{
	.stringIndexTitle = -1,
	.state = 0x28,
	.funcPtr = (void*)MyMenuProc,
	.unk6 = 1,
};

void MyMenuProc(struct RectMenu* m)
{
	struct GamepadBuffer* gb;

	DecalFont_DrawLine("Press X", 100, 100, FONT_BIG, ORANGE);

	gb = &sdata->gGamepads->gamepad[0];

	if ((gb->buttonsTapped & BTN_CROSS) == 0) return;

	// if you are in a cup
	if ((sdata->gGT->gameMode2 & CUP_ANY_KIND) != 0)
	{
		// change desiredMenu to Cup race selection
		sdata->ptrDesiredMenu = (struct RectMenu*)0x800b472c;

		MM_CupSelect_Init();

		return;
	}

	// if going to track selection

	// change desiredMenu to Single race selection
	sdata->ptrDesiredMenu = (struct RectMenu*)0x800b46e0;

	MM_TrackSelect_Init();

	return;
}

// runs on the JR RA of MM_Characters_HideDrivers
void GoToNewState()
{
	// set our new main menu state
	sdata->ptrDesiredMenu = &myBox;

	// quit the function
	return;
}