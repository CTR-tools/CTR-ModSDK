#include <common.h>

int DECOMP_MainFrame_HaveAllPads(short numPlyrNextGame)
{
	short isGamepadsConnected = 1;

	// if game is not loading
	if (sdata->Loading.stage == -1)
	{
		// if there are no players (cutscene)
		if (numPlyrNextGame == 0)
		{
			// return 0 means gamepad is missing
			isGamepadsConnected = 0;
		}

		// if number of players is not zero
		else
		{
			u_int uVar4 = 1;
			for (int i = 0; i < numPlyrNextGame; i++)
			{
				bool bVar1 = uVar4 != 0;
				uVar4 = 0;
				if (
					// if there are no other gamepads unplugged (so far)
					(bVar1) &&

					// if this gamepad is plugged in
					(sdata->gGamepads->gamepad[i].ptrControllerPacket != NULL)
					)
				{
					// Check if gamepad is compatible with game (not a gun or mouse)
					uVar4 = (u_int)(sdata->gGamepads->gamepad[i].ptrControllerPacket->isControllerConnected == 0);
				}

				// save the result
				isGamepadsConnected = (short)uVar4;
			}
		}

		// return 0 only if a gamepad is missing
		// that is currently needed in the game
		return isGamepadsConnected;
	}
	return 1;
}