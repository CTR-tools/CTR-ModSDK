#include <common.h>

// budget = 0x1CC (460)

void DECOMP_VehPtr_Spinning_Update(struct Thread* t, struct Driver* d)
{
	int speedApprox;
	
	// cooldown after the spinning started
	if(d->NoInputTimer != 0)
	{
		// absolute value
		speedApprox = d->speedApprox;
		if(speedApprox < 0) speedApprox = -speedApprox;
		
		// quit if moving quickly
		if(speedApprox > 0x2ff) return;
	}
	
	// if speed has slown to near-halt,
	// or if NoInputTimer ran out
	DECOMP_VehPtr_LastSpin_Init(t,d);
}

void DECOMP_VehPtr_Spinning_PhysLinear(struct Thread* t, struct Driver* d)
{
	int elapsedTimeMS = sdata->gGT->elapsedTimeMS;
	
	d->NoInputTimer -= elapsedTimeMS;
	if(d->NoInputTimer < 0) d->NoInputTimer = 0;
	
	VehPtr_Driving_PhysLinear(t,d);
	
	// baseSpeed and fireSpeed
	// set both "shorts" in one "int"
	*(int*)&d->baseSpeed = 0;
	
	d->actionsFlagSet |= 0x5808;
	
	d->timeSpentSpinningOut += elapsedTimeMS;
}

void DECOMP_VehPtr_Spinning_PhysAngular(struct Thread* t, struct Driver* d)
{
	int elapsedTimeMS = sdata->gGT->elapsedTimeMS;
	
	d->numFramesSpentSteering = 10000;
	
	#ifdef USE_60FPS
	if(sdata->gGT->timer & 1)
	{
	#endif
	
		d->rotationSpinRate -= d->rotationSpinRate >> 3;
		d->unk3D4[0] -= d->unk3D4[0] >> 3;
	
	#ifdef USE_60FPS
	}
	#endif
	
	d->turnAngleCurr += d->KartStates.Spinning.driftSpinRate;
	d->turnAngleCurr += 0x800U;
	d->turnAngleCurr &= 0xfff;
	d->turnAngleCurr -= 0x800;
		
	d->ampTurnState = d->rotationSpinRate;
	
	d->angle = 
	(
		d->angle + 
		(d->rotationSpinRate * elapsedTimeMS >> 0xd)
	) & 0xfff;
	
	d->rotCurr.y = d->unk3D4[0] + d->angle + d->turnAngleCurr;
	
	d->rotCurr.w = 
		InterpBySpeed
		(
			d->rotCurr.w,
			(elapsedTimeMS << 5) >> 5,
			0
		);
		
	Rot_AxisAngle(&d->matrix310, &d->AxisAngle1_normalVec[0], d->angle);
}