#include <common.h>

int s_numString;

void AA_EndEvent_DrawMenu()
{
	struct GameTracker* gGT;
	struct Driver* driver;
	struct HudElement* hudArray;
	
	gGT = sdata->gGT;
	driver = gGT->drivers[0];
	
	hudArray = data.hudStructPtr[gGT->numPlyrCurrGame-1];
	
	// count frames
	if(sdata->framesSinceRaceEnded < 900)
		sdata->framesSinceRaceEnded++;
	
	if(driver->BigNumber[0]->scale[0] != 0x1e00)
	{
		driver->BigNumber[0]->scale[0] = 0;
		driver->BigNumber[0]->scale[1] = 0;
		driver->BigNumber[0]->scale[2] = 0;
	}
	
	// sdata->ptrHudC
	
	// if adventure mode
	if((gGT->gameMode & ADVENTURE_MODE) != 0)
	{
		// won C-T-R challenge,
		// placed 1st and got all letters
		if(
			(driver->driverRank == 0) &&
			(driver->PickupLetterHUD.numCollected == 3)
		)
		{
			
		}
		
		// if did not win
		else
		{
			
		}
	}
}