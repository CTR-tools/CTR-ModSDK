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
	struct Driver* worstRobotDriver = NULL, *bestHumanDriver = NULL;

	for (int i = MAX_KARTS - 1; i >= 0; i--)
	{
		struct Driver* d = sdata->gGT->driversInRaceOrder[i];
		struct Driver* bestHuman = sdata->bestHumanRank;
		if (d != NULL)
		{
			bestHuman = d; //assume human for now
			if ((d->actionsFlagSet & 0x100000) != 0)
			{
				bestHuman = sdata->bestHumanRank; //is bot, nevermind
				sdata->bestRobotRank = d; //since it's a bot, it is also the *best* bot so far
				if (worstRobotDriver == NULL)
				{
					worstRobotDriver = d; //if not yet assigned, assign worst bot.
				}
			}
		}

		sdata->bestHumanRank = bestHuman;
	}

	if (sdata->bestHumanRank == NULL)
	{
		sdata->bestHumanRank = worstRobotDriver;
	}

	sdata->unk_counter_upTo450++;
}