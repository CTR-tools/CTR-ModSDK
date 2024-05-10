#include <common.h>
// determine which buttons are held this frame,
// store a backup of "currFrame" into "lastFrame"
// param1 is pointer to gamepadSystem

void DECOMP_GAMEPAD_ProcessHold(struct GamepadSystem *gGamepads)
{
    char j;
    char* btnMapPtr;
    u_int *puVar2;
    struct ControllerPacket *ptrControllerPacket;
    unsigned short uVar4;
    u_int uVar5;

    struct GamepadBuffer *pad;

    // loop through all 8 gamepadBuffers
    for(pad = &gGamepads->gamepad[0]; pad < &gGamepads->gamepad[8]; pad++)
    {
        ptrControllerPacket = pad->ptrControllerPacket;

        pad->buttonsHeldPrevFrame = pad->buttonsHeldCurrFrame;

        // if pointer is invalid
        if (ptrControllerPacket == NULL)
        {
            // erase buttons held this frame and prev
            pad->buttonsHeldPrevFrame = 0;
            pad->buttonsHeldCurrFrame = 0;
        }

        // must be zero to confirm connection
        else if (ptrControllerPacket->isControllerConnected == 0)
		{
			// endian flip
			uVar4 = (ptrControllerPacket->controllerInput1 << 8) | ptrControllerPacket->controllerInput2;
			
			uVar4 = uVar4 ^ 0xffff;
			uVar5 = 0;
			
			// If this is madcatz racing wheel
			if (ptrControllerPacket->controllerData == ((PAD_ID_NEGCON << 4) | 3))
			{
				if (0x40 < ptrControllerPacket->neGcon.btn_1)
				{
					uVar4 |= 0x40;
				}
				if (0x40 < ptrControllerPacket->neGcon.btn_2)
				{
					uVar4 |= 0x80;
				}
				if (0x40 < ptrControllerPacket->neGcon.trg_l)
				{
					uVar4 |= 4;
				}
			}
	
			// If this is not madcatz racing wheel
			else
			{
				// If this is ANAJ
				// could be different from NPC-105
				if (ptrControllerPacket->controllerData == ((PAD_ID_ANALOG_STICK << 4) | 3))
				{
					uVar4 = uVar4 << 0x10;
				}
			}

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
	
		#ifdef USE_ONLINE
		break;
		#endif
	}
}
