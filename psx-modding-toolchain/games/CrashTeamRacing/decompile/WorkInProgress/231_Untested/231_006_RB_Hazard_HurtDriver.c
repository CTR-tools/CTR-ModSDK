#include <common.h>

void RB_Hazard_HurtDriver(struct Driver* d, int newState)
{
	// if not an AI
	if ((driver->actionsFlagSet & 0x100000) == 0)
	{
		Player_ChangeState(d, newState);
		return;
	}
	
	// if not an AI...
	
	// original code
	#if 1
	
	// if boss mode
	if ((sdata->gGT->gameMode1 & ADVENTURE_BOSS) != 0)
	{
		// if oxide station
		if(sdata->gGT->levelID == 0xd)
		{
			// override to spin out
			newState = 1;
		}
	}
	
	// optimized code
	#else
	
	// if bossID is oxide's challenge (4), 
	// or oxide's final challenge (5)
	if ((sdata->gGT->bossID & 4) != 0)
	{
		// override to spin out
		newState = 1;
	}
	
	#endif
	
	BOTS_ChangeState(d, newState);
}