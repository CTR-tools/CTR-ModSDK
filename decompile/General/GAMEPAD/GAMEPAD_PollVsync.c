#include <common.h>

void DECOMP_GAMEPAD_PollVsync(struct GamepadSystem *gGamepads)
{
    u_int uVar2;
    u_int uVar4;
    struct GamepadBuffer *pad;
    int numConnected;
    int port;
    int numPorts;
    int maxPadsPerPort;

    numConnected = 0;

    // 2 players, no multitap
    numPorts = 2;
    maxPadsPerPort = 1;

    // If there is a multitap present
    if ((gGamepads->slotBuffer[0].isControllerConnected == 0) && gGamepads->slotBuffer[0].controllerData == (PAD_ID_MULTITAP << 4))
    {
        // 4 players, with multitap
        numPorts = 1;
        maxPadsPerPort = 4;
    }
	
#ifdef USE_ONLINE
	numPorts = 1;
	maxPadsPerPort = 1;
#endif

	pad = &gGamepads->gamepad[0];

    // loop through all gamepad ports
    // that gameplay cares about. Either
    // 1 or 2, main ports on console
    for (port = 0; port < numPorts; port++)
    {
        // loop through all gamepads that can connect
        // to this gamepad port. 1 for no mtap, 4 for mtap
        for (char i = 0; i < maxPadsPerPort; i++)
        {	
            // if this is not a multitap,
            // skip next block, and just start
            // if-body with ptrPadBuff
            if
            (
				(
					// multitap here, and controller connected
					(gGamepads->slotBuffer[port].controllerData == (PAD_ID_MULTITAP << 4)) &&
					(gGamepads->slotBuffer[port].controllers[i].isControllerConnected != 0)
				) ||
				
				// controller connected
				(gGamepads->slotBuffer[port].isControllerConnected != 0)
            )
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

                DECOMP_GAMEPAD_ProcessState(pad, uVar2, uVar4);
			}

            // increment gamepad counter
            numConnected++;
			pad++;
        }
    }

    // if there are less than 8 gamepads connected,
    // write to buffers of all Unplugged gamepads
    while (pad < &gGamepads->gamepad[8])
    {
        pad->gamepadType = 0;
		pad++;
    }
}