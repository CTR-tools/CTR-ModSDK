#include <common.h>

void RB_Hazard_HurtDriver(
	struct Driver* driverVictim, 
	int damageType,
	struct Driver* driverAttacker,
	int reason)
{
	// if not an AI
	if ((driverVictim->actionsFlagSet & 0x100000) == 0)
	{
		Player_ChangeState(driverVictim, damageType, driverAttacker, reason);
		return;
	}
	
	// if not an AI...
	
	// original code
	#if 0
	
	// if boss mode
	if ((sdata->gGT->gameMode1 & ADVENTURE_BOSS) != 0)
	{
		// if oxide station
		if(sdata->gGT->levelID == 0xd)
		{
			// override to spin out
			damageType = 1;
		}
	}
	
	// optimized code
	#else
	
	// if bossID is oxide's challenge (4), 
	// or oxide's final challenge (5)
	if ((sdata->gGT->bossID & 4) != 0)
	{
		// override to spin out
		damageType = 1;
	}
	
	#endif
	
	BOTS_ChangeState(driverVictim, damageType, driverAttacker, reason);
}