#include <common.h>

int DECOMP_RB_Hazard_ThCollide_Missile(struct Thread* thread)
{
	struct TrackerWeapon* tw;
	struct Driver* driver;
	struct Instance* inst;
	
	tw = thread->object;
	inst = thread->inst;
	
	// could I also just do thread->modelID?
	if (inst->model->id == 0x29)
	{
		#ifndef REBUILD_PS1
		// play audio of explosion
		PlaySound3D(0x4c, inst);
		#endif
		
		// kill thread
		thread->flags |= 0x800;

		#ifndef REBUILD_PS1
		// stop audio of moving
		OtherFX_RecycleMute(&tw->audioPtr);
		#endif

		// get driver
		driver = tw->driverTarget;
		
		// if driver is valid
		if(driver != 0)
		{
			// remove 2D square-target being drawn on the player's screen 
			driver->actionsFlagSet &= 0xfbffffff;
		}
	}
	
	return 1;
}