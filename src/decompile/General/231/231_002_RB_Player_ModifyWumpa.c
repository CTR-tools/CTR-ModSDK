#include <common.h>

void DECOMP_RB_Player_ModifyWumpa(struct Driver* driver, int wumpaDelta)
{
	char numWumpaOriginal = driver->numWumpas;
	
	// if using unlimited wumpa, quit
	if((sdata->gGT->gameMode2 & CHEAT_WUMPA) != 0) return;

	if (
			// if wumpa is being subtracted
			(wumpaDelta < 0) &&
			
			// using mask weapon
			((driver->actionsFlagSet & 0x800000) != 0)
		)
	{
		// quit, dont lose wumpa
		return;
	}
	
	if (
			// wumpa increasing
			(wumpaDelta > 0) &&
			
			// driver is not an AI
			((driver->actionsFlagSet & 0x100000) == 0)
		)
	{
		// for end-of-race comments
		driver->numTimesWumpa += wumpaDelta;
	}
	
	// works for positive and negative delta
	driver->numWumpas += wumpaDelta;
	
	// dont allow negatives
	if (driver->numWumpas < 0)
	{
		driver->numWumpas = 0;
	}
	
	// cap at 10
	if (driver->numWumpas > 10)
	{
		driver->numWumpas = 10;
	}
	
	#ifdef USE_ONLINE
	if(driver->driverID != 0)
		return;
	#endif
	
	if (
			// if did not have 10 before
			(numWumpaOriginal < 10) &&
			
			// if have 10 now
			(driver->numWumpas == 10)
		)
	{
		// Play "juiced up" sound
		DECOMP_OtherFX_Play(0x41, 1);
		
		driver->BattleHUD.juicedUpCooldown = 10;
	}
}