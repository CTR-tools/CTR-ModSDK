#include <common.h>

// only Animate is needed, see StopSpin_Init for details

void DECOMP_VehPhysProc_SpinStop_Animate(struct Thread* t, struct Driver* d)
{
	int numFrames;
	struct Instance* inst;
	inst = t->inst;
	
	#if 0
	numFrames = VehFrameInst_GetNumAnimFrames(inst, inst->animIndex);
	#else
	numFrames = FPS_DOUBLE(20)+1;
	#endif
	
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
		
	// desired halfway into steer animation
	numFrames = FPS_DOUBLE(10);
	#if 0 // 10 =
		VehFrameInst_GetStartFrame(
			
			0, // midpoint
			
			VehFrameInst_GetNumAnimFrames(
				inst, // driver instance
				0	  // anim #0, steer
			)
		);
	#endif

	// increment by two frames until reaching midpoint
	inst->animFrame = 
		DECOMP_VehCalc_InterpBySpeed(inst->animFrame, 2, numFrames);
	
	// quit function until midpoint is reached
	if(inst->animFrame != numFrames)
		return;
	
	
	// if you are facing forward
	d->funcPtrs[0] = DECOMP_VehPhysProc_Driving_Init;
}