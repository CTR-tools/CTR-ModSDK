#include "global.h"

// replace GameInit_Drivers
void SpawnDrivers(struct GameTracker* gGT)
{	
	int i;
	int bitFlag;
	struct Driver* dr;

	#if USE_K1 == 0
	struct OnlineCTR* octr = (struct OnlineCTR*)0x8000C000;
	#endif

	for(i = 0; i < 8; i++)
	{
		gGT->drivers[i] = 0;
	}
	
	// if first boot
	if(gGT->levelID == 0x32)
	{
		gGT->drivers[0] = Init_Player(0);
		return;
	}
	
	gGT->numBotsNextGame = 0;
	
	// must be called before spawning AIs,
	// therefore, must not be Adv specific
	BOTS_Adv_AdjustDifficulty();
	
	if(LOAD_IsOpen_RacingOrBattle())
		RB_MinePool_Init();
	
	// 8 spawn positions
	bitFlag = 7;
	
	// override for battle maps
	if(
		(gGT->levelID > 0x11) &&
		(gGT->levelID < 0x19)
	  )
	{
		// 4 spawn positions
		bitFlag = 3;
	}
	
	// All clients must spawn drivers in the same order,
	// so that pointers can be sent over network
	
	for(i = 0; i < octr->DriverID; i++)
	{
		// init, save, fakeID, teleport, realID
		dr = BOTS_Driver_Init(i+1);
		gGT->drivers[i+1] = dr;
		dr->driverID = i&bitFlag;
		Driver_TeleportSelf(dr,3,0);
		dr->driverID = i+1;
	}
	
	// init, save, fakeID, teleport, realID
	dr = Init_Player(0);
	gGT->drivers[0] = dr;
	dr->driverID = i&bitFlag;
	Driver_TeleportSelf(dr,3,0);
	dr->driverID = 0;
	
	for(i = i+1; i < octr->NumDrivers; i++)
	{
		// init, save, fakeID, teleport, realID
		dr = BOTS_Driver_Init(i);
		gGT->drivers[i] = dr;
		dr->driverID = i&bitFlag;
		Driver_TeleportSelf(dr,3,0);
		dr->driverID = i;
	}
}