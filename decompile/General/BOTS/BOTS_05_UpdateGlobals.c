#include <common.h>

#define MAX_KARTS 8

void BOTS_UpdateGlobals(void) //UNTESTED
{
	if (sdata->gGT->numBotsNextGame != 0)
	{
		EngineSound_NearestAIs();
	}

	sdata->bestHumanRank = NULL;
	sdata->bestRobotRank = NULL;
	struct Driver* worstRobotDriver = NULL;

	for (int i = MAX_KARTS - 1; i >= 0; i--)
	{
		struct Driver* d = sdata->gGT->driversInRaceOrder[i];
		if (d != NULL)
		{
			if (d->actionsFlagSet & 0x100000 != 0) //is AI
			{
				sdata->bestRobotRank = d;
				if (worstRobotDriver == NULL)
					worstRobotDriver = d;
			}
			else //is human
				sdata->bestHumanRank = d;
		}
	}

	if (sdata->bestHumanRank == NULL)
	{
		sdata->bestHumanRank = worstRobotDriver;
	}

	sdata->unk_counter_upTo450++;
}