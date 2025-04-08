#include <common.h>

#define MAX_KARTS 8

void BOTS_UpdateGlobals(void) //UNTESTED
{
	struct GameTracker* gGT = sdata->gGT;
	
	if (gGT->numBotsNextGame != 0)
	{
		EngineSound_NearestAIs();
	}

	sdata->bestHumanRank = NULL;
	sdata->bestRobotRank = NULL;

	for (int i = MAX_KARTS - 1; i >= 0; i--)
	{
		struct Driver* d = gGT->driversInRaceOrder[i];
		
		if (d == NULL)
			continue;
		
		if ((d->actionsFlagSet & 0x100000) != 0)
		{
			sdata->bestRobotRank = d;
		}
		else
		{
			sdata->bestHumanRank = d;
		}
	}

	if (sdata->bestHumanRank == NULL)
	{
		sdata->bestHumanRank = worstRobotDriver;
	}

	sdata->unk_counter_upTo450++;
}