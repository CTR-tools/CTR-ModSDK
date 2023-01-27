#include <common.h>

// copy/paste from GameProg
#define CHECK_ADV_BIT(rewards, bitIndex) \
	((rewards[bitIndex>>5] >> (bitIndex & 0x1f)) & 1) != 0

int s_numString = 0;

void AA_EndEvent_DrawMenu()
{
	struct GameTracker* gGT;
	struct Driver* driver;
	struct HudElement* hudArray;
	struct AdvProgress* adv;
	int bitIndex;
	
	gGT = sdata->gGT;
	driver = gGT->drivers[0];
	adv = &sdata->advProgress;
	
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
			// if token was already won
			bitIndex = gGT->levelID + 0x4C;
			if(CHECK_ADV_BIT(adv->rewards, bitIndex))
			{
				
			}
			
			// if won for the first time
			else
			{
				
			}
		}
		
		// if did not win
		else
		{
			
		}
	}
}