#include <common.h>

void Player_Driving_PhysLinear(struct Thread* thread, struct Driver* driver);

void Player_Blasted_PhysLinear(struct Thread *thread, struct Driver *driver)
{
	int NoInputTimer;
	
	NoInputTimer = (u_int)(u_short)driver->NoInputTimer - (u_int)*(u_short*)&sdata->gGT->elapsedTimeMS;
	driver->NoInputTimer = (short)NoInputTimer;
	if (NoInputTimer * 0x10000 < 0)
	{
		driver->NoInputTimer = 0;
	}
	Player_Driving_PhysLinear(thread, driver);
	driver->jump_ForcedMS = 0x60;
	driver->baseSpeed = 0;
	driver->fireSpeed = 0;
	driver->actionsFlagSet |= 0x5808;
	driver->jump_InitialVelY = driver->NoInputTimer * 2 + 6000;
	return;
}