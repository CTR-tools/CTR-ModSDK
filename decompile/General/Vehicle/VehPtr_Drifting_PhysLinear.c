#include <common.h>

void DECOMP_VehPtr_Drifting_PhysLinear(struct Thread *thread, struct Driver *driver)
{
	struct GameTracker* gGT;
	
	VehPtr_Driving_PhysLinear(thread, driver);
	gGT = sdata->gGT;
	driver->actionsFlagSet |= 0x1800;
	driver->timeSpentDrifting += gGT->elapsedTimeMS;
	return;
}