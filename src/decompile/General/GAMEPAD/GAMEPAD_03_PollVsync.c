#include <common.h>

void DECOMP_GAMEPAD_PollVsync(struct GamepadSystem *gGamepads)
{
    u_int uVar2;
    u_int uVar4;
    struct GamepadBuffer *pad;
    int port;
    int numPorts;
    int maxPadsPerPort;

    // 2 players, no multitap
    numPorts = 2;
    maxPadsPerPort = 1;

    // If there is a multitap present
    if (
			(gGamepads->slotBuffer[0].plugged == PLUGGED) && 
			(gGamepads->slotBuffer[0].controllerData == (PAD_ID_MULTITAP << 4))
		)
    {
        // 4 players, with multitap
        numPorts = 1;
        maxPadsPerPort = 4;
    }
	
#ifdef USE_ONLINE
	numPorts = 1;
	maxPadsPerPort = 1;
#endif

#ifdef USE_REAL60PS1
	numPorts = 1;
	maxPadsPerPort = 1;
#endif

#ifdef USE_4PADTEST
	// use 1 controller for all 4
    numPorts = 1;
    maxPadsPerPort = 4;
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
			bool unpluggedPort =
			(
				(
					// multitap here, and unplugged
					(gGamepads->slotBuffer[port].controllerData == (PAD_ID_MULTITAP << 4)) &&
					(gGamepads->slotBuffer[port].controllers[i].plugged != PLUGGED)
				) ||
				
				// controller unplugged
				(gGamepads->slotBuffer[port].plugged != PLUGGED)
			);
			
			#ifdef USE_4PADTEST
			unpluggedPort = 0;
			#endif
			
            if (unpluggedPort)
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
				
				// use 1 controller for all 4
				#ifdef USE_4PADTEST
				uVar2 = PadGetState(0);
				#endif

                DECOMP_GAMEPAD_ProcessState(pad, uVar2, uVar4);
			}

            // increment gamepad counter
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