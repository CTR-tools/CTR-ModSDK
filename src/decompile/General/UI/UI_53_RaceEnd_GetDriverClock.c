#include <common.h>

void DECOMP_UI_RaceEnd_GetDriverClock(struct Driver* driver)

{
  char missileLaunched;
  int avgSpd;
  int timeElapsed;
  int numTimesAttacked;

  #if 0
  // "trap" calls removed
  // assume no division by zero
  #endif

  // If race timer is not supposed to stop for this racer
  if ((driver->actionsFlagSet & 0x40000) == 0)
  {
	// time elapsed in race
    timeElapsed = driver->timeElapsedInRace;

    // Stop time for this racer
    driver->actionsFlagSet |= 0x40000;

	if (timeElapsed != 0) 
	{
	  // get average speed over time
      avgSpd = driver->distanceDriven * 100;
	  driver->distanceDriven = avgSpd / timeElapsed;
    }
	
	// if missiles launched is less than 4
    if (driver->numTimesMissileLaunched < 4) 
	{
      driver->NumMissilesComparedToNumAttacks = 0xffffffff;
    }
    
	// if missiles launched is more than 4
	else 
	{
      // number of missiles launched
	  missileLaunched = driver->numTimesMissileLaunched;
      
	  // compare number of missiles to number of attacks
      driver->NumMissilesComparedToNumAttacks = (int)((driver->numTimesAttacking << 0xc) / missileLaunched);
    }
    
    numTimesAttacked = 0;

	// count number of times you were attacked in race
    for (int i = 0; i < 8; i++)
    {
        numTimesAttacked += driver->numTimesAttackedByPlayer[i];
    }

	driver->numTimesAttacked = numTimesAttacked;
    
	// if driver is in first place
	if (driver->driverRank == 0) {
    
	  // duplicate amount of time spent in last place
      driver->TimeWinningDriverSpentLastPlace = driver->timeSpentInLastPlace;
    }
  }
  return;
}