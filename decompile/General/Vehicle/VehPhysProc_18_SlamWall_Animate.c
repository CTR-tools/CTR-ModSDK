#include <common.h>

void DECOMP_VehPhysProc_SlamWall_Animate(struct Thread* t, struct Driver* d)
{
	struct Instance* inst;
	inst = t->inst;

	inst->animFrame++;

	#ifdef USE_60FPS
	if(sdata->gGT->timer & 1)
	#endif
	d->matrixIndex++;

	// If crashing animation is not finished, quit function
	if(
		// oxide has no animation
		(data.characterIDs[d->driverID] != 0xF) &&

		// animation is not over
		((inst->animFrame+1) < 15)

		#if 0
		// except for Oxide, who has zero frames
		15 == VehFrameInst_GetNumAnimFrames(inst, inst->animIndex)
		#endif
	  )
	{
		return;
	}

	// == Initialize Driving ==

	d->matrixArray = 0;
	d->matrixIndex = 0;
	inst->animIndex = 0;

	// start halfway into steer animation
	inst->animFrame = FPS_DOUBLE(10);
	#if 0 // 10 =
		VehFrameInst_GetStartFrame(

			0, // midpoint

			VehFrameInst_GetNumAnimFrames(
				inst, // driver instance
				0	  // anim #0, steer
			)
		);
	#endif

	d->funcPtrs[0] = DECOMP_VehPhysProc_Driving_Init;
}