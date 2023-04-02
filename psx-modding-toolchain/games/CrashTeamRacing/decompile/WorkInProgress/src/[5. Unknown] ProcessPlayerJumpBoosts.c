#include <common.h>

void Turbo_Increment(int param_1, int param_2, u_int param_3, int param_4);
void Voiceline_RequestPlay(u_int param_1, u_int param_2, u_int param_3);

void DECOMP_UI_JumpMeter_Update(struct Driver* driver)
{
	short jumpMeter;
	int jumpMeterMinus32ms;

	//if player is not in the air
	if ((driver->actionsFlagSet & 0x80000) == 0)
	{
		//if, in previous frame? player was not in the air either
		if ((driver->actionsFlagSetPrevFrame & 0x80000) == 0)
		{
			//if Jump meter Timer is done
			if (driver->jumpMeterTimer == 0)
			{
				//reset Jump meter
				driver->jumpMeter = 0;
			}
			
			//if Jump meter Timer is not done
			else
			{
				jumpMeterMinus32ms = (u_int)driver->jumpMeterTimer - (u_int)*(u_short *)sdata->gGT->elapsedTimeMS;
				
				//reduce Jump meter Timer by ~32ms
				driver->jumpMeterTimer = (short)jumpMeterMinus32ms;
				
				//if Jump meter Timer goes negative
				if (jumpMeterMinus32ms * 0x10000 < 0)
				{
					//prevent Jump meter Timer from going negative
					driver->jumpMeterTimer = 0;
				}
			}
		}
		
		//if, in previous frame? player was in the air
		else
		{
			//jumpMeterMinus32ms = Jump meter
			jumpMeterMinus32ms = (int)driver->jumpMeter;

			// if jump is high enough to be significant
			if (jumpMeterMinus32ms > 336)
			{
				// keep track of all jumps
				driver->timeSpentJumping += jumpMeterMinus32ms;
		
				jumpMeterMinus32ms = (int)driver->jumpMeter;
			}

			// if highest jump is less than current jump
			if (*(short *)driver->highestJump < jumpMeterMinus32ms) 
			{
				// save highest jump
				*(u_short *)driver->highestJump = driver->jumpMeter;
			}

			jumpMeter = driver->jumpMeter;

			if (jumpMeter < 1440)
			{
				if (jumpMeter < 960)
				{
					//if Jump meter > 639
					if (jumpMeter > 639)
					{
						// add one second reserves
						Turbo_Increment(driver, 960, 2, 0);
					}
				}

				//if Jump meter >= 960
				else
				{
					// Turbo_Increment
					// add one second reserves, plus speed
					Turbo_Increment(driver, 960, 2, 0x80);
				}
			}

			//if Jump meter >= 1440
			else
			{
				// add one second reserves, plus speed
				Turbo_Increment(driver, 960, 2, 0x100);
			}
		}
	}

	//if player is in the air
	else
	{
		if ((driver->jump_LandingBoost > 1152) && (driver->jumpMeter < 1153))
		{
			//Jump meter related operation

			// Make driver talk
			Voiceline_RequestPlay(7, (int)data.characterIDs[driver->driverID], 0x10);
		}

		driver->jumpMeter = driver->jump_LandingBoost;

		//if Jump meter > 2400
		if (driver->jump_LandingBoost > 2400)
		{
			//prevent Jump meter from going over 2400
			driver->jumpMeter = 2400;
		}

		//keep Jump meter Timer at 1440.
		driver->jumpMeterTimer = 1440;
	}
	return;
}