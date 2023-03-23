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
			if (jumpMeterMinus32ms > 0x150)
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

			if (jumpMeter < 0x5a0)
			{
				if (jumpMeter < 0x3c0)
				{
					//if Jump meter > 0x27F
					if (0x27f < jumpMeter)
					{
						// add one second reserves
						Turbo_Increment(driver, 0x3c0, 2, 0);
					}
				}

				//if Jump meter >= 0x3C0
				else
				{
					// Turbo_Increment
					// add one second reserves, plus speed
					Turbo_Increment(driver, 0x3c0, 2, 0x80);
				}
			}

			//if Jump meter >= 0x5A0
			else
			{
				// add one second reserves, plus speed
				Turbo_Increment(driver, 0x3c0, 2, 0x100);
			}
		}
	}

	//if player is in the air
	else
	{
		if ((driver->jump_LandingBoost > 0x480) && (driver->jumpMeter < 0x481))
		{
			//Jump meter related operation

			// Make driver talk
			Voiceline_RequestPlay(7, (int)data.characterIDs[driver->driverID], 0x10);
		}

		//Jump meter = 0x3FC
		driver->jumpMeter = driver->jump_LandingBoost;

		//if Jump meter > 0x960
		if (driver->jump_LandingBoost > 0x960)
		{
			//prevent Jump meter from going over 0x960
			driver->jumpMeter = 0x960;
		}

		//keep Jump meter Timer at 0x5A0.
		driver->jumpMeterTimer = 0x5a0;
	}
	return;
}