#include "global.h"

// replace AllocAllDrivers
void SpawnDrivers(struct GameTracker* gGT)
{	
	int i;
	int flag;

	#if USE_K1 == 0
	struct OnlineCTR* octr = 0x8000C000;
	#endif

	for(i = 0; i < 8; i++)
	{
		gGT->drivers[i] = 0;
	}
	
	gGT->numRobotcars = 0;
	
	// must be called before spawning AIs,
	// therefore, must not be Adv specific
	BOTS_Adv_AdjustDifficulty();
	
	if(LOAD_IsOpen_RacingOrBattle())
		RB_MinePool_Init();
	
	// spawn positions
	flag = 7;
	
	// override for battle maps
	if(
		(gGT->levelID > 0x11) &&
		(gGT->levelID < 0x19)
	  )
	{
		flag = 3;
	}
	
	// All clients must spawn drivers in the same order,
	// so that pointers can be sent over network
	
	// To do: Set DriverID to 0-3, then TeleportAll, then 
	// reset ID to 0-7, like SecretDrivers_EightControllers
	
	for(i = 0; i < octr->DriverID; i++)
	{
		sdata.gGT->drivers[i+1] = BOTS_Driver_Init(i+1);
	}
	
	sdata.gGT->drivers[0] = Init_Player(0);
	sdata.gGT->drivers[0]->driverID = 0;
	sdata.kartSpawnOrderArray[0] = i;
	
	for(i = i+1; i < octr->NumDrivers; i++)
	{
		sdata.gGT->drivers[i] = BOTS_Driver_Init(i);
	}
}