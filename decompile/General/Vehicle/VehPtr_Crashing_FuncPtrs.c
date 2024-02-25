#include <common.h>

// budget = 0x190 (400)

void DECOMP_VehPtr_Crashing_PhysLinear(struct Thread* t, struct Driver* d)
{	
	DECOMP_VehPtr_Driving_PhysLinear(t,d);
	
	// baseSpeed and fireSpeed
	// set both "shorts" in one "int"
	*(int*)&d->baseSpeed = 0;
}

void DECOMP_VehPtr_Crashing_PhysAngular(struct Thread* t, struct Driver* d)
{
	int elapsedTimeMS = sdata->gGT->elapsedTimeMS;
	
	d->angle = 
	(
		d->angle + 
		(d->ampTurnState * elapsedTimeMS >> 0xd)
	) & 0xfff;
	
	d->rotCurr.y = d->unk3D4[0] + d->angle + d->turnAngleCurr;
	
	d->rotCurr.w = 
		InterpBySpeed
		(
			d->rotCurr.w,
			(elapsedTimeMS << 5) >> 5,
			0
		);
		
	#ifndef REBUILD_PS1
	Rot_AxisAngle(&d->matrix310, &d->AxisAngle1_normalVec[0], d->angle);
	#endif
}

void DECOMP_VehPtr_Crashing_Animate(struct Thread* t, struct Driver* d)
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
		(inst->animFrame+1) <
		VehAnim_Instance_GetNumAnimFrames(inst, inst->animIndex)
	  )
	{
		return;
	}
	
	// == Initialize Driving ==
	
	d->matrixArray = 0;
	d->matrixIndex = 0;
	inst->animIndex = 0;
	
	// start halfway into steer animation
	inst->animFrame = 
		
		VehAnim_Instance_GetStartFrame(
			
			0, // midpoint
			
			VehAnim_Instance_GetNumAnimFrames(
				inst, // driver instance
				0	  // anim #0, steer
			)
		);
		
	d->funcPtrs[0] = DECOMP_VehPtr_Driving_Init;
}