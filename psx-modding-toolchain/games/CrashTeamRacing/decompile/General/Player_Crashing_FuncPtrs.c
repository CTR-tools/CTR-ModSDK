#include <common.h>

// budget = 0x190 (400)

void DECOMP_Player_Crashing_PhysLinear(struct Thread* t, struct Driver* d)
{	
	Player_Driving_PhysLinear(t,d);
	
	// baseSpeed and fireSpeed
	// set both "shorts" in one "int"
	*(int*)&d->baseSpeed = 0;
}

void DECOMP_Player_Crashing_PhysAngular(struct Thread* t, struct Driver* d)
{
	int elapsedTimeMS = sdata->gGT->elapsedTimeMS;
	
	d->angle = 
	(
		d->angle + 
		(d->ampTurnState * elapsedTimeMS >> 0xd)
	) & 0xfff;
	
	d->rotCurr.y = d->unk3D4[0] + d->angle + d->unknownDimension2Curr;
	
	d->rotCurr.w = 
		InterpBySpeed
		(
			d->rotCurr.w,
			(elapsedTimeMS << 5) >> 5,
			0
		);
		
	Rot_AxisAngle(&d->matrix310, &d->AxisAngle1_normalVec[0], d->angle);
}

void DECOMP_Player_Crashing_Animate(struct Thread* t, struct Driver* d)
{
	struct Instance* inst;
	inst = t->inst;
	
	inst->animFrame++;
	d->animationFrame++;
	
	// If crashing animation is not finished, quit function
	if(
		(inst->animFrame+1) <
		Instance_GetNumAnimFrames(inst, inst->animIndex)
	  )
	{
		return;
	}
	
	// == Initialize Driving ==
	
	d->animationIndex = 0;
	d->animationFrame = 0;
	inst->animIndex = 0;
	
	// start halfway into steer animation
	inst->animFrame = 
		
		Instance_GetStartFrame(
			
			0, // midpoint
			
			Instance_GetNumAnimFrames(
				inst, // driver instance
				0	  // anim #0, steer
			)
		);
		
	void Player_Driving_Init(struct Thread* t, struct Driver* d);
	d->funcPtrs[0] = Player_Driving_Init;
}