#include <common.h>

// For some reason, the game uses empty
// MenuBox structs to change funcPtr, rather
// than threads

// Judging by Aug 5, using MenuBox
// for Adv Character Select, there was probably
// a time when every state of main menu was a
// traditional-looking MenuBox, so it was just
// kept that way

void MM_CupSelect_Init();
void MM_TrackSelect_Init();

void MyMenuBoxFuncPtr(struct MenuBox* m);

struct MenuBox myBox =
{
	.stringIndexTitle = -1,
	.state = MAIN_MENU_CHARACTER_SELECT,
	.funcPtr = (void*)MyMenuBoxFuncPtr,
	.unk6 = 1,
};

void MyMenuBoxFuncPtr(struct MenuBox* m)
{
	struct GamepadBuffer* gb;

	DecalFont_DrawLine("Press X", 100, 100, FONT_BIG, ORANGE);

	gb = &sdata->gGamepads->gamepad[0];

	if ((gb->buttonsTapped & BTN_CROSS) == 0) return;

	// if you are in a cup
	if ((sdata->gGT->gameMode2 & CUP_ANY_KIND) != 0)
	{
		// change desiredMenuBox to Cup race selection
		sdata->ptrDesiredMenuBox = (struct MenuBox*)0x800b472c;

		MM_CupSelect_Init();

		return;
	}

	// if going to track selection

	// change desiredMenuBox to Single race selection
	sdata->ptrDesiredMenuBox = (struct MenuBox*)0x800b46e0;

	MM_TrackSelect_Init();

	return;
}

// runs on the JR RA of MM_Characters_HideDrivers
void GoToNewState()
{
	// set our new main menu state
	sdata->ptrDesiredMenuBox = &myBox;

	// quit the function
	return;
}