#include <common.h>

void Player_Driving_PhysLinear(struct Thread* thread, struct Driver* driver);

void Player_Drifting_PhysLinear(struct Thread *thread, struct Driver *driver)
{
	struct GameTracker* gGT;
	
	Player_Driving_PhysLinear(thread, driver);
	gGT = sdata->gGT;
	driver->actionsFlagSet |= 0x1800;
	driver->timeSpentDrifting += gGT->elapsedTimeMS;
	return;
}