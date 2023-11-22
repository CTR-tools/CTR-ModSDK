#include <common.h>
// determine which buttons are held this frame,
// store a backup of "currFrame" into "lastFrame"
// param1 is pointer to gamepadSystem

void DECOMP_GAMEPAD_ProcessHold(struct GamepadSystem *gGamepads)
{
    char j;
    char* btnMapPtr;
    u_int *puVar2;
    unsigned char *rawInputBytes;
    unsigned short uVar4;
    u_int uVar5;

    struct GamepadBuffer *pad;

    // loop through all 8 gamepadBuffers
    for (
			pad = &gGamepads->gamepad[0];
			pad < &gGamepads->gamepad[8];
			pad++
		)
    {
        rawInputBytes = pad->ptrRawInput;

        pad->buttonsHeldPrevFrame = pad->buttonsHeldCurrFrame;

        // if pointer is invalid
        if (rawInputBytes == NULL)
        {
            // erase buttons held this frame and prev
            pad->buttonsHeldPrevFrame = 0;
            pad->buttonsHeldCurrFrame = 0;
        }

        // must be zero to confirm connection
        else if (rawInputBytes[0] == NULL)
		{
			uVar4 = (rawInputBytes[2] << 8) | rawInputBytes[3];
			uVar4 = uVar4 ^ 0xffff;
			uVar5 = 0;
			
			// If this is madcatz racing wheel
			if (rawInputBytes[1] == 35)
			{
				if (0x40 < rawInputBytes[5])
				{
					uVar4 |= 0x40;
				}
				if (0x40 < rawInputBytes[6])
				{
					uVar4 |= 0x80;
				}
				if (0x40 < rawInputBytes[7])
				{
					uVar4 |= 4;
				}
			}
	
			// If this is not madcatz racing wheel
			else
			{
				// If this is ANAJ
				// could be different from NPC-105
				if (rawInputBytes[1] == 83)
				{
					uVar4 = uVar4 << 0x10;
				}
			}
			
#ifndef REBUILD_PC

			// gamepadMapBtn to map RawInput enum
			// to Buttons enum, to support different
			// types of controllers
			for (
					btnMapPtr = &data.gamepadMapBtn[0].input; 
					*(int*)&btnMapPtr[0] != 0;
					btnMapPtr += 8
				)
			{
				if ((uVar4 & *(int*)&btnMapPtr[0]) != 0)
				{
					uVar5 |= *(int*)&btnMapPtr[4];
				}
			}
			
#else

			// apply to all
			if (WIN_GetPressCross())
				uVar5 |= BTN_CROSS;

			if(pad == &gGamepads->gamepad[0])
			{
				if (WIN_GetPressUp())
					uVar5 |= BTN_UP;
			
				if (WIN_GetPressDown())
					uVar5 |= BTN_DOWN;
			
				if (WIN_GetPressLeft())
					uVar5 |= BTN_LEFT;
			
				if (WIN_GetPressRight())
					uVar5 |= BTN_RIGHT;
			
				if (WIN_GetPressTriangle())
					uVar5 |= BTN_TRIANGLE;
			}
#endif
	
			// record buttons held this frame
			pad->buttonsHeldCurrFrame = uVar5;
	
			// if nothing was held
			if (uVar5 == 0)
			{
				if (pad->framesSinceLastInput < 65000)
					pad->framesSinceLastInput++;
			} 
			
			// if buttons were pressed
			else
			{
				// reset number of frames since last input
				pad->framesSinceLastInput = 0;
			}
		}
	}
}
