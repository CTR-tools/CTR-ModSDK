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

// Mimic Nitro-Fueled Polswid controls!
// Simple remap: L2 -> Down, Down -> Left, Left -> Triangle, Triangle -> L2
// This will also remap the buttons while in the main menu, however
// Try adding your own check for that!
unsigned int new_map[] = {
	RAW_BTN_UP, 		// UP
	RAW_BTN_LEFT,		// DOWN
	RAW_BTN_TRIANGLE,	// LEFT
	RAW_BTN_RIGHT,		// RIGHT
	RAW_BTN_CROSS,		// CROSS
	RAW_BTN_SQUARE,		// SQUARE
	RAW_BTN_CIRCLE,		// CIRCLE
	RAW_BTN_L2,			// TRIANGLE
	RAW_BTN_R1,			// R1
	RAW_BTN_R2,			// R2
	RAW_BTN_L1,			// L1
	RAW_BTN_DOWN,		// L2
	RAW_BTN_SELECT,		// SELECT
	RAW_BTN_START		// START
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
	struct GamepadBuffer * gamepad = &sdata->gGamepads->gamepad[0];
	RemapButtons(&gamepad->ptrControllerPacket->controllerInput);
}