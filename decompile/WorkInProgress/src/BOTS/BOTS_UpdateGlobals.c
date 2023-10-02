#include <common.h>

#define MAX_KARTS 8

void BOTS_UpdateGlobals()
{
  struct GameTracker *gGT = sdata->gGT;
  struct Driver *pDriver = gGT->driversInRaceOrder[MAX_KARTS-1];
  struct Driver *bestDriver = NULL;
  struct Driver *worstDriver = NULL;

  if (gGT->numBotsNextGame > 0) EngineSound_NearestAIs();

  sdata->bestHumanRank = NULL;
  sdata->bestRobotRank = NULL;

  for (int i = 0; i < MAX_KARTS; i++)
  {
    bestDriver = sdata->bestHumanRank;

    if (pDriver != NULL)
    {
      bestDriver = pDriver;

      if ((bestDriver->actionsFlagSet & 0x100000) != 0)
      {
        bestDriver = sdata->bestHumanRank;
        sdata->bestRobotRank = pDriver;

        if (worstDriver == NULL) worstDriver = pDriver;
      }
    }

    sdata->bestHumanRank = bestDriver;

    pDriver--;
  }

  if (sdata->bestHumanRank == NULL) sdata->bestHumanRank = worstDriver;

  sdata->unk_counter_upTo450++;
}