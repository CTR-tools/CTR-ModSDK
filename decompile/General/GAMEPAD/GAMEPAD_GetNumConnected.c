#include <common.h>

int DECOMP_GAMEPAD_GetNumConnected(struct GamepadSystem* gGamepads)
{
	int bitwiseConnected;
	int numConnected;
	
	int numSlots;
	int numPortsPerSlot;
	
	int padIndex;
	char* ptrRawInput;
	struct GamepadBuffer* padCurr;
	
	// 2 players, no multitap
	numSlots = 2;
	numPortsPerSlot = 1;
	
	if(
		// multitap detected
		(gGamepads->slotBuffer[0].meta[0] == 0) &&
		(gGamepads->slotBuffer[0].meta[1] == -0x80)
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
	
	padIndex = 0;
	numConnected = 0;
	bitwiseConnected = 0;
	padCurr = &gGamepads->gamepad[0];
	
	for(int Slot = 0; Slot < numSlots; Slot++)
	{
		for(int Port = 0; Port < numPortsPerSlot; Port++)
		{
			ptrRawInput = &gGamepads->slotBuffer[Slot].meta[0];
			if(ptrRawInput[0] == 0)
			{
				// if multitap plugged in
				if(ptrRawInput[1] == -0x80)
				{
					ptrRawInput = &gGamepads->slotBuffer[Slot].padBuffer[Port];
				}
				
				if(ptrRawInput[0] == 0)
				{
					bitwiseConnected |= (Slot*4 + Port);
					
					gGamepads->numGamepadsConnected = numConnected + 1;
					
					padCurr->ptrRawInput = ptrRawInput;
					padCurr->gamepadID = Port + Slot*0x10;
				}
			}
			
			numConnected++; // what?
			padIndex++;
			padCurr++;
		}
	}
	
	if(padIndex < 8)
	{
		// pad is now unplugged
		padCurr->ptrRawInput = 0;
		padCurr++;
	}
}