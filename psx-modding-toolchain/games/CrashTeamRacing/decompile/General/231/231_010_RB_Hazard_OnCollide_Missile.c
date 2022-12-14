#include <common.h>

int RB_Hazard_OnCollide_Missile(struct Thread* thread)
{
	struct TrackerWeapon* tw;
	struct Driver* driver;
	struct Instance* inst;
	
	tw = thread->object;
	inst = thread->inst;
	
	// could I also just do thread->modelID?
	if (inst->model->id == 0x29)
	{
		driver = tw->driverTarget;
		
		if(driver != 0)
		{
			// remove 2D square-target being drawn on the player's screen 
			driver->actionsFlagSet &= 0xfbffffff;
		}
		
		// play audio of explosion
		PlaySound3D(0x4c, inst);
		
		// stop audio of moving
		OtherFX_Stop_Safe(tw->audioPtr);
		
		// kill thread
		thread->flags |= 0x800;
	}
	
	return 1;
}