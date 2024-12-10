#include <common.h>

int DECOMP_BOTS_Adv_NumTimesLostEvent(int numLost)
{	
	// if you lost more than 10 times
	// the difficulty will not get lower.
	if(numLost > 10)
	{
		// the array apparently has 12, not sure why it stopped at 11.
		numLost = 10; 
	}

	return data.advDifficulty[numLost];
}