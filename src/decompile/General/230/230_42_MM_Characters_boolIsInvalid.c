#include <common.h>

// used for preventing players highlighting the same character
// also for when you go left of komodo joe's icon
u_int DECOMP_MM_Characters_boolIsInvalid(short* globalIconPerPlayer, short characterID, short player)
{
	int i = 0;
	
	// if there are players
	if (sdata->gGT->numPlyrNextGame) 
	{
		// loop through players
		for (i = 0; i < sdata->gGT->numPlyrNextGame; i++)
		{
			// if driver is taken
			if ((i != player) && (characterID == globalIconPerPlayer[i]))
			{
				return 1;
			}
		}
	}
	
	// if driver is not taken
	return 0;
}