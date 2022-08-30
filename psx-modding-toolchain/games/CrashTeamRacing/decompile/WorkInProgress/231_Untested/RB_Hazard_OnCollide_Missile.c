#include <common.h>

int RB_Hazard_OnCollide_Missile(struct Thread* thread)
{
	struct TrackerWeapon* tw;
	struct Driver* driver;
	
	tw = thread->object;
	
	// could I also just do thread->modelID?
	if (thread->inst->model->modelID == 0x29)
	{
		driver = tw->driverChasing;
		
		if(driver != 0)
		{
			// remove 2D square-target being drawn on the player's screen 
			driver->actionsFlagSet &= 0xfbffffff;
		}
		
		// play audio of explosion
		PlaySound3D(0x4c);
		
		// stop audio of moving
		OtherFX_Stop_Safe(tw->audioPtr);
		
		// kill thread
		thread->flags |= 0x800;
	}
	
	return 1;
}