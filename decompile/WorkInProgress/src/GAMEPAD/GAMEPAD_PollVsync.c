#include <common.h>

void GAMEPAD_PollVsync(struct GamepadSystem *gGamepads)
{
    u_int uVar2;
    u_int uVar4;
    struct GamepadBuffer *pad;
    int numConnected;
    int port;
    int numPorts;
    int maxPadsPerPort;

    numConnected = 0;

    // number of ports that gameplay cares about,
    // 2 by default, no multitaps, 2 gamepads
    numPorts = 2;

    // number of gamepads per gamepad port,
    // set to 1 if there is no multitap (default)
    maxPadsPerPort = 1;

    // If there is a multitap present
    if ((gGamepads->slotBuffer->meta[0] == 0) && gGamepads->slotBuffer->meta[1] == -0x80)
    {
        // Gameplay now only cares about one gamepad port,
        // Port 1, which has the multitap. However, the gamepad
        // system still processes input for port 2, Gameshark can
        // be programmed with button input from all 8 gamepads
        numPorts = 1;

        // There can now be 4 gamepads in one port
        maxPadsPerPort = 4;
    }

    // If there are gamepad ports that
    // gameplay cares about (always > 0)
    if (numPorts > 0)
    {
        // loop through all gamepad ports
        // that gameplay cares about. Either
        // 1 or 2, main ports on console
        for (port = 0; port < numPorts; port++)
        {
            // if max number of gamepad ports is not zero,
            // which will always be true no matter what
            if (maxPadsPerPort != 0)
            {

                // loop through all gamepads that can connect
                // to this gamepad port. 1 for no mtap, 4 for mtap
                for (char i = 0; i < maxPadsPerPort; i++)
                {
                    pad = gGamepads->gamepad[i];
                    // if this is not a multitap,
                    // skip next block, and just start
                    // if-body with ptrPadBuff
                    if ((gGamepads->slotBuffer[port].meta[1] == -0x80) &&

                        // assuming this is a multitap
                        (gGamepads->slotBuffer[port].meta[0] != 0) ||

                        (gGamepads->slotBuffer[port].padBuffer[0].data[0] != 0))
                    {
                        // no analog sticks found
                        pad->gamepadType = 0;
                    }
                    else
                    {
                        uVar4 = (port << 4) | i;

                        // according to libref
                        // 0 - PadStateDisCon
                        // 1 - PadStateFindPad
                        // and many more...
                        uVar2 = PadGetState(uVar4);

                        GAMEPAD_ProcessState(pad, uVar2, uVar4);
                    }
                    // increment gamepad counter
                    numConnected++;
                }
            }
        }
    }

    // if there are less than 8 gamepads connected,
    // write to buffers of all Unplugged gamepads
    if (numConnected < 8)
    {
        for (;
             numConnected < 8;
             numConnected++;)
        {
            pad = gGamepads->gamepad[numConnected];
            // no analog sticks found
            pad->gamepadType = 0;
        }
    }
}