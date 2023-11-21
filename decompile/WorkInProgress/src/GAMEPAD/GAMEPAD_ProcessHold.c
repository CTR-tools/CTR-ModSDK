#include <common.h>
// determine which buttons are held this frame,
// store a backup of "currFrame" into "lastFrame"
// param1 is pointer to gamepadSystem

void GAMEPAD_ProcessHold(struct GamepadSystem *gGamepads)
{
    char i, j;
    u_int btnMap;
    u_int *puVar2;
    char *rawInputBytes;
    u_int uVar4;
    u_int uVar5;
    u_int temp;

    struct GamepadBuffer *pad;

    temp = 0;

    // loop through all 8 gamepadBuffers
    for (i = 0; i < 8; i++)
    {
        pad = &gGamepads->gamepad[i];

        rawInputBytes = pad->ptrRawInput;

        pad->buttonsHeldPrevFrame = pad->buttonsHeldCurrFrame;

        // if pointer is invalid
        if (rawInputBytes == NULL)
        {
            // erase buttons held this frame and prev
            pad->buttonsHeldPrevFrame = 0;
            pad->buttonsHeldCurrFrame = 0;
        }

        // if pointer is valid
        else
        {
            if (rawInputBytes[0] == NULL)
            {
                uVar4 = (u_int) CONCAT11(rawInputBytes[2], rawInputBytes[3]) ^ 0xffff;
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
                    // could just be different sensitivity, or gamepad signal
                    if (rawInputBytes[1] == 83)
                    {
                        uVar4 = uVar4 << 0x10;
                    }
                }

                // gamepadMapBtn to map RawInput enum
                // to Buttons enum, to support different
                // types of controllers
                for (j = 0; btnMap = *(u_int *)&data.gamepadMapBtn[i].input, btnMap != 0; j++)
                {
                    if ((uVar4 & btnMap) != 0)
                    {
                        uVar5 |= data.gamepadMapBtn->output;
                    }
                }

                // record buttons held this frame
                pad->buttonsHeldCurrFrame = uVar5;

                // if nothing was held
                if (uVar5 == 0)
                {
                    if (pad->framesSinceLastInput < 65000)
                        pad->framesSinceLastInput++;
                } // if buttons were pressed
                else
                {
                    // reset number of frames since last input
                    pad->framesSinceLastInput = 0;
                }

                temp |= uVar5;
            }
        }
    }
}
