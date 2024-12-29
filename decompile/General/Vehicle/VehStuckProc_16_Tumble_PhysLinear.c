#include <common.h>

void DECOMP_VehStuckProc_Tumble_PhysLinear(struct Thread* thread, struct Driver* driver)
{
	driver->NoInputTimer -= sdata->gGT->elapsedTimeMS;

	if (driver->NoInputTimer < 0)
	    driver->NoInputTimer = 0;

	DECOMP_VehPhysProc_Driving_PhysLinear(thread, driver);

	driver->jump_ForcedMS = 0x60;
	driver->baseSpeed = 0;
	driver->fireSpeed = 0;
	driver->actionsFlagSet |= 0x5808;
	driver->jump_InitialVelY = driver->NoInputTimer * 2 + 6000;

	return;
}