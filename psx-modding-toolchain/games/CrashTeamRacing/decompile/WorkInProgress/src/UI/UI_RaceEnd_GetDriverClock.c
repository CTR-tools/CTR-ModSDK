#include <common.h>

void DECOMP_UI_RaceEnd_GetDriverClock(struct Driver* driver)

{
  char missileLaunched;
  int avgSpd;
  int timeElapsed;
  int numTimesAttacked;

  // If race timer is not supposed to stop for this racer
  if ((driver->actionsFlagSet & 0x40000) == 0)
  {
	// time elapsed in race
    timeElapsed = driver->timeElapsedInRace;

    // Stop time for this racer
    driver->actionsFlagSet |= 0x40000;

	if (timeElapsed != 0) 
	{
	  // get average speed over time (assumed)
	  
      avgSpd = driver->distanceDriven * 100;
	  
      if (timeElapsed == 0) { trap(0x1c00); }
      if ((timeElapsed == -1) && (avgSpd == -0x80000000)) { trap(0x1800); }
      
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
      
	  if (missileLaunched == 0) { trap(0x1c00); }
      if ((missileLaunched == 0xffffffff) && (driver->numTimesAttacking == 0x80000)) { trap(0x1800); }
	  
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