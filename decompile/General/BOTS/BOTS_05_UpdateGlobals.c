#include <common.h>

void BOTS_UpdateGlobals(void) //UNTESTED
{
	if (sdata->gGT->numBotsNextGame > 0)
	{
		EngineSound_NearestAIs();
	}
	sdata->bestHumanRank = NULL;
	sdata->bestRobotRank = NULL;
	struct Driver* worstAI = NULL;
	for (int i = 7; i >= 0; i--) //loop through all driver rank low to high (7 to 0)
	{
		struct Driver* d = sdata->gGT->driversInRaceOrder[7];
		struct Driver* bestHuman = sdata->bestHumanRank;
		if (
	           (
				   (d != NULL) && //is valid (for races w/ less than 8 drivers?)
				   (bestHuman = d, d->actionsFlagSet & 0x100000 != 0) //if this is an AI
			   ) &&
			   (
				   bestHuman = sdata->bestHumanRank, //get best human from backup
				   sdata->bestRobotRank = d, //set best AI driver
				   worstAI == NULL //if worst AI is not found
			   )
		   )
		{
			worstAI = d;
		}
		sdata->bestHumanRank = bestHuman;
	}
	if (sdata->bestHumanRank == NULL)
	{
		sdata->bestHumanRank = worstAI;
	}
	sdata->unk_counter_upTo450++;
	//I finished doing this decomp, and before testing I realized there's also an entry
	//in /WIP for this function. Whoops.
}