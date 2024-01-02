#include <common.h>

unsigned int original_map[] = {
	RAW_BTN_UP,
	RAW_BTN_DOWN,
	RAW_BTN_LEFT,
	RAW_BTN_RIGHT,
	RAW_BTN_CROSS,
	RAW_BTN_SQUARE,
	RAW_BTN_CIRCLE,
	RAW_BTN_TRIANGLE,
	RAW_BTN_R1,
	RAW_BTN_R2,
	RAW_BTN_L1,
	RAW_BTN_L2,
	RAW_BTN_SELECT,
	RAW_BTN_START
};

// Swap directions
unsigned int new_map[] = {
	RAW_BTN_UP,
	RAW_BTN_DOWN,
	RAW_BTN_RIGHT,
	RAW_BTN_LEFT,
	RAW_BTN_CROSS,
	RAW_BTN_SQUARE,
	RAW_BTN_CIRCLE,
	RAW_BTN_TRIANGLE,
	RAW_BTN_R1,
	RAW_BTN_R2,
	RAW_BTN_L1,
	RAW_BTN_L2,
	RAW_BTN_SELECT,
	RAW_BTN_START
};

void RemapButtons(unsigned short * buttons)
{
	unsigned short curr_buttons = *buttons;
	unsigned short new_buttons = 0xFFFF;
	for (int i = 0; i < RAW_BTN_COUNT; i++)
	{
		if ((curr_buttons & original_map[i]) == 0)
			new_buttons ^= new_map[i];
	}
	*buttons = new_buttons;
}

void Remap_Main()
{
	struct GamepadBuffer* gamepad;
	struct GameTracker * gGT = sdata->gGT;
	
	for(int i = 0; i < gGT->numPlyrCurrGame; i++)
	{
		gamepad = &sdata->gGamepads->gamepad[i];

		if ((gGT->gameMode1 & (PAUSE_1 | END_OF_RACE | MAIN_MENU)) == 0)
		{
			RemapButtons(&gamepad->ptrControllerPacket->controllerInput);
		}
	}
}