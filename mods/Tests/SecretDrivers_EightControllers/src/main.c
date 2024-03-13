#include <common.h>

#define NUM_PLAYERS 8

void RunInitHook()
{
	int i;

	struct Driver** drivers;
	drivers = sdata->gGT->drivers;

	// move drivers that are not P1
	for(i = 1; i < NUM_PLAYERS; i++)
	{
		// player[0] already exists
		drivers[i] = VehBirth_Player(i);
	}

	// In EurRetail and JpnRetail, Parking Lot has
	// four spawn positions, not eight, let's trick the spawner
	drivers[4]->driverID = 0;
	drivers[5]->driverID = 1;
	drivers[6]->driverID = 2;
	drivers[7]->driverID = 3;

	// send to start line (corrects driver animations)
	VehBirth_TeleportAll(sdata->gGT, 2);

	// and change it back
	drivers[4]->driverID = 4;
	drivers[5]->driverID = 5;
	drivers[6]->driverID = 6;
	drivers[7]->driverID = 7;

	// move drivers that are not P1
	for(i = 1; i < NUM_PLAYERS; i++)
	{
		drivers[i]->posCurr[0] = 0x8000 * i;
		drivers[i]->posCurr[1] = 0;
		drivers[i]->posCurr[2] = 0;
	}
}

