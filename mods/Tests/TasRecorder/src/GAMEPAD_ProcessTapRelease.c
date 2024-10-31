#include <common.h>

// Byte Budget: 1472 (TapRelease + Motors)
void DECOMP_GAMEPAD_ProcessTapRelease(struct GamepadSystem *gGamepads)
{
    char cVar1;
    struct GamepadBuffer *pad;

    char numConnected = gGamepads->numGamepadsConnected;

    if (!numConnected)
        return;

	// TAS Recorder
	if((sdata->gGT->gameMode1 & LOADING) == 0)
	{
		// Player 1
		pad = &gGamepads->gamepad[0];
		
		// frame counter
		int currIndex = *(int*)0x8000fff0;
		
		// requires 8mb RAM
		int* buttonArr = 0x80200000;
		
		int hold;
		
		// RECORD mode
		if(*(int*)0x8000fff4 == 0)
		{
			// value pressed
			hold = pad->buttonsHeldCurrFrame;
		
			// record
			buttonArr[currIndex] = pad->buttonsHeldCurrFrame;
		}
		
		// REPLAY mode
		else
		{
			// value pressed
			hold = buttonArr[currIndex];
		
			// replay
			pad->buttonsHeldCurrFrame = hold;
			
			// In this order: Up, Down, Left, Right
			if ((hold & 1) != 0) pad->stickLY = 0;
			if ((hold & 2) != 0) pad->stickLY = 0xFF;
			if ((hold & 4) != 0) pad->stickLX = 0;
			if ((hold & 8) != 0) pad->stickLX = 0xFF;

		}
		
		// draw
		sprintf(0x8000f000, "FRAME: %08X %08X", currIndex, hold);
		DecalFont_DrawLine(0x8000f000, 5, 206, FONT_SMALL, ORANGE);
						
		// increment
		*(int*)0x8000fff0 = *(int*)0x8000fff0 + 1;
	}

    for (char i = 0; i < numConnected; i++)
    {
        pad = &gGamepads->gamepad[i];
        if (pad->ptrControllerPacket == NULL)
        {
            // erase tap and release
            pad->buttonsTapped = 0;
            pad->buttonsReleased = 0;
        }
        else
        {
            // tapped
            pad->buttonsTapped = ~pad->buttonsHeldPrevFrame & pad->buttonsHeldCurrFrame;

            // released
            pad->buttonsReleased = pad->buttonsHeldPrevFrame & ~pad->buttonsHeldCurrFrame;
        }
    }
}