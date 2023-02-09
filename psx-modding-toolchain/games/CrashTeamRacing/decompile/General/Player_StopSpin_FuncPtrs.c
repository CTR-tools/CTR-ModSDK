#include <common.h>

// only Animate is needed, see StopSpin_Init for details

void DECOMP_Player_StopSpin_Animate(struct Thread* t, struct Driver* d)
{
	int numFrames;
	struct Instance* inst;
	inst = t->inst;
	
	numFrames = Instance_GetNumAnimFrames(inst, inst->animIndex);
	
	// if you are spinning right
	if(d->KartStates.Spinning.spinDir == -1)
	{
		// steer from left to right, to exaggerate
		// the force when steering stops abruptly
		inst->animFrame += 5;
		
		// if not finished, quit function
		if(inst->animFrame < numFrames)
			return;
		
		// if finished
		inst->animFrame = numFrames-1;
		d->KartStates.Spinning.spinDir = 0;
		return;
	}
	
	// if you are spinning left
	if(d->KartStates.Spinning.spinDir == 1)
	{
		// steer from right to left, to exaggerate
		// the force when steering stops abruptly
		inst->animFrame -= 5;
		
		// if not finished, quit function
		if(inst->animFrame > 0)
			return;
		
		// if finished
		inst->animFrame = 0;
		d->KartStates.Spinning.spinDir = 0;
		return;
	}
	
	
	// === spinning has stopped ===
	
	// return driver to center steering 
	// animation frame
	
	// desired halfway into steer animation
	numFrames = 
		
		Instance_GetStartFrame(
			
			0, // midpoint
			
			Instance_GetNumAnimFrames(
				inst, // driver instance
				0	  // anim #0, steer
			)
		);
		
	// increment by two frames until reaching midpoint
	inst->animFrame = InterpBySpeed(inst->animFrame, 2, numFrames);
	
	// quit function until midpoint is reached
	if(inst->animFrame != numFrames)
		return;
	
	
	// if you are facing forward
	void Player_Driving_Init(struct Thread* t, struct Driver* d);
	d->funcPtrs[0] = Player_Driving_Init;
}