#include <common.h>

void RB_Hazard_HurtDriver(
	struct Driver* driverVictim, 
	int damageType,
	struct Driver* driverAttacker,
	int reason)
{
	struct GameTracker* gGT = sdata->gGT;
	
	// if not an AI
	if ((driverVictim->actionsFlagSet & 0x100000) == 0)
	{
		#ifndef REBUILD_PS1
		VehPickState_NewState(driverVictim, damageType, driverAttacker, reason);
		#endif
		
		return;
	}
	
	// if boss mode
	if ((gGT->gameMode1 & ADVENTURE_BOSS) != 0)
	{
		// if oxide station
		if(gGT->levelID == OXIDE_STATION)
		{
			// override to spin out
			damageType = 1;
		}
	}
	
	#ifndef REBUILD_PS1
	BOTS_ChangeState(driverVictim, damageType, driverAttacker, reason);
	#endif
}