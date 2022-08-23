#include <common.h>

int DECOMP_BOTS_Adv_NumTimesLostEvent(int index)
{
	if(index > 10)
	{
		index = 10;
	}

	return data.advDifficulty[index];
}