#include <common.h>

int s_numString = 0;

void AA_EndEvent_DrawMenu()
{
	struct GameTracker* gGT;
	struct Driver* driver;
	struct UiElement2D* hudArray;
	struct AdvProgress* adv;
	int bitIndex;
	short posXY[2];
	
	short lerpStartX;
	short lerpStartY;
	short lerpEndX;
	short lerpEndY;
	short lerpFrames;
	short currFrame;
	
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
			if(CHECK_ADV_BIT(adv->rewards, bitIndex) != 0)
			{
				// first 10 seconds, lerp closer to center of screen
				if(sdata->framesSinceRaceEnded < 301)
				{
					lerpStartX = data.hud_1P_P1[0x24].x;
					lerpStartY = data.hud_1P_P1[0x24].y;
					lerpEndX = data.hud_1P_P1[0x24].x + 0x10;
					lerpEndY = data.hud_1P_P1[0x24].y + 0x10;
					lerpFrames = 8;
					currFrame = sdata->framesSinceRaceEnded;
				}
				
				// past 10 seconds, lerp off screen
				else
				{
					lerpStartX = data.hud_1P_P1[0x24].x + 0x10;
					lerpStartY = data.hud_1P_P1[0x24].y + 0x10;
					lerpEndX = -400;
					lerpEndY = lerpStartY;
					lerpFrames = 10;
					currFrame = sdata->framesSinceRaceEnded - 300;
				}
				
				UI_Lerp2D_Linear(
					&posXY[0], lerpStartX, lerpStartY, 
					lerpEndX, lerpEndY, currFrame, lerpFrames);
					
				sdata->ptrHudC->matrix.t[0] = UI_ConvertX_2(posXY[0], 0x200);
				sdata->ptrHudC->matrix.t[1] = UI_ConvertY_2(posXY[1], 0x200);
				
				sdata->ptrHudT->matrix.t[0] = UI_ConvertX_2(posXY[0]+0x1d, 0x200);
				sdata->ptrHudT->matrix.t[1] = UI_ConvertY_2(posXY[1]-1, 0x200);
				
				sdata->ptrHudR->matrix.t[0] = UI_ConvertX_2(posXY[0]+0x3a, 0x200);
				sdata->ptrHudR->matrix.t[1] = UI_ConvertY_2(posXY[1], 0x200);
			}
			
			// if won for the first time
			else
			{
				// what on earth does it do with this?
				// sdata->ptrHudC->scale[0] - 0x800
				
				// copy UiElement2D X and Y
				*(int*)&posXY[0] = *(int*)&data.hud_1P_P1[0x24];
			}
		}
		
		// if did not win
		else
		{
			
		}
	}
}