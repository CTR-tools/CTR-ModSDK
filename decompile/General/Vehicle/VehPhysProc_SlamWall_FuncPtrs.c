#include <common.h>

// budget = 0x190 (400)

void DECOMP_VehPhysProc_SlamWall_PhysLinear(struct Thread* t, struct Driver* d)
{
	DECOMP_VehPhysProc_Driving_PhysLinear(t,d);

	// baseSpeed and fireSpeed
	// set both "shorts" in one "int"
	*(int*)&d->baseSpeed = 0;
}

void DECOMP_VehPhysProc_SlamWall_PhysAngular(struct Thread* t, struct Driver* d)
{
	int elapsedTimeMS = sdata->gGT->elapsedTimeMS;

	d->angle += (short)((d->ampTurnState * elapsedTimeMS) >> 0xd);
	d->angle &= 0xfff;

	d->rotCurr.y = d->unk3D4[0] + d->angle + d->turnAngleCurr;

	d->rotCurr.w =
		DECOMP_VehCalc_InterpBySpeed
		(
			d->rotCurr.w,
			(elapsedTimeMS << 5) >> 5,
			0
		);

	d->turnAngleCurr =
		DECOMP_VehCalc_InterpBySpeed
		(
			d->turnAngleCurr,
			(elapsedTimeMS << 7) >> 5,
			0
		);

	#ifndef REBUILD_PS1
	VehPhysForce_RotAxisAngle(&d->matrixMovingDir, &d->AxisAngle1_normalVec.x, d->angle);
	#endif
}

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