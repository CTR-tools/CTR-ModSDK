#include <common.h>

int DECOMP_GAMEPAD_GetNumConnected(struct GamepadSystem* gGamepads)
{
	int bitwiseConnected;
	int numConnected;
	
	int numSlots;
	int numPortsPerSlot;
	
	int padIndex;
	struct MultitapPacket* ptrControllerPacket;
	struct GamepadBuffer* padCurr;
	
	// 2 players, no multitap
	numSlots = 2;
	numPortsPerSlot = 1;
	
	if(
		// multitap detected
		(gGamepads->slotBuffer[0].isControllerConnected == 0) &&
		(gGamepads->slotBuffer[0].controllerData == (PAD_ID_MULTITAP << 4))
	)
	{
		// 4 players, with multitap
		numSlots = 1;
		numPortsPerSlot = 4;
	}
	
#ifdef REBUILD_PC
	numSlots = 1;
	numPortsPerSlot = 4;
#endif

#ifdef USE_ONLINE
	numSlots = 1;
	numPortsPerSlot = 1;
#endif
	
	padIndex = 0;
	numConnected = 0;
	bitwiseConnected = 0;
	padCurr = &gGamepads->gamepad[0];
	
	for(int Slot = 0; Slot < numSlots; Slot++)
	{
		for(int Port = 0; Port < numPortsPerSlot; Port++)
		{
			ptrControllerPacket = &gGamepads->slotBuffer[Slot];
			if(ptrControllerPacket->isControllerConnected == 0)
			{
				// if multitap plugged in
				if(ptrControllerPacket->controllerData == (PAD_ID_MULTITAP << 4))
				{
					ptrControllerPacket = &ptrControllerPacket->controllers[Port];
				}
				
				if(ptrControllerPacket->isControllerConnected == 0)
				{
					bitwiseConnected |= 1 << (Slot*4 + Port);
					
					
					padCurr->ptrControllerPacket = ptrControllerPacket;
					padCurr->gamepadID = Slot*0x10 + Port;
				}
			}
			
			numConnected++;
			padIndex++;
			padCurr++;
		}
	}
	
	gGamepads->numGamepadsConnected = numConnected;
					
	while(padCurr < &gGamepads->gamepad[8])
	{
		// pad is now unplugged
		padCurr->ptrControllerPacket = 0;
		padCurr++;
	}
	
	// this name is way too long
	int* ptrToSet = &gGamepads->gamepadsConnectedByFlag;
	int oldVal = *ptrToSet;
	*ptrToSet = bitwiseConnected;
	
	if(oldVal == -1) return 0;
	if(oldVal == bitwiseConnected) return 0;
	
	// return change
	return (u_int)((bitwiseConnected ^ oldVal) & oldVal) != 0;
}