#include <common.h>

void Player_Driving_Init(struct Thread* t, struct Driver* d);

void Player_Blasted_Update(struct Thread *thread, struct Driver *driver)
{
	if (driver->NoInputTimer == 0)
	{
		driver->animationIndex = 0;
		driver->animationFrame = 0;
		Player_Driving_Init(thread, driver);
	}
	return;
}
