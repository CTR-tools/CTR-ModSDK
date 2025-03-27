#include <common.h>

int DECOMP_MainFrame_HaveAllPads(short numPlyrNextGame)
{
	
#ifndef USE_4PADTEST
	
	// if game is not loading
	if (sdata->Loading.stage == -1)
	{
		struct GamepadBuffer* gb = 
			&sdata->gGamepads->gamepad[0];
					
		for (int i = 0; i < numPlyrNextGame; i++)
		{
			struct ControllerPacket* packet = 
				gb->ptrControllerPacket;
			
			if (packet == NULL) return 0;
			if (packet->plugged != PLUGGED) return 0;
			
			gb++;
		}
	}
	
#endif
	
	return 1;
}