#include <common.h>

// budget 0x228 (552 bytes)

void DECOMP_VehPtr_Crashing_PhysAngular(struct Thread* t, struct Driver* d);
void VehPtr_StopSpin_Init(struct Thread* t, struct Driver* d);
void VehPtr_Driving_PhysLinear(struct Thread* t, struct Driver* d);

void DECOMP_VehPtr_LastSpin_Update(struct Thread* t, struct Driver* d)
{
	int driftAngle = d->unknownDimension2Curr;
	
	// if almost facing forward
	if(
		(driftAngle < 0x10) &&
		(driftAngle > -0x10)
		)
	{
		// stop spin
		VehPtr_StopSpin_Init(t, d);
	}
}

void DECOMP_VehPtr_LastSpin_PhysLinear(struct Thread* t, struct Driver* d)
{
	VehPtr_Driving_PhysLinear(t,d);
	
	// baseSpeed and fireSpeed
	// set both "shorts" in one "int"
	*(int*)&d->baseSpeed = 0;
	
	d->actionsFlagSet |= 0x4008;
}

void DECOMP_VehPtr_LastSpin_PhysAngular(struct Thread* t, struct Driver* d)
{
	int unknownDimension2Curr;
	unknownDimension2Curr = d->unknownDimension2Curr;
	
	d->numFramesSpentSteering = 10000;
	
	d->rotationSpinRate -= d->rotationSpinRate >> 3;
	d->unk3D4[0] -= d->unk3D4[0] >> 3;
	d->ampTurnState = d->rotationSpinRate;
	
	if(unknownDimension2Curr < 0)
	{
		if(
			(d->KartStates.Spinning.driftSpinRate > 0) &&
			(unknownDimension2Curr > -400)
		  )
		{
			d->KartStates.Spinning.driftSpinRate = 
				(unknownDimension2Curr * -4) >> 3;
			
			if(d->KartStates.Spinning.driftSpinRate < 0x20)
				d->KartStates.Spinning.driftSpinRate = 0x20;
		}
	
		d->unknownDimension2Curr += d->KartStates.Spinning.driftSpinRate;
		d->unknownDimension2Curr += 0x800U;
		d->unknownDimension2Curr &= 0xfff;
		d->unknownDimension2Curr -= 0x800;
	
		if(
			(d->KartStates.Spinning.driftSpinRate > 0) &&
			(d->unknownDimension2Curr > 0)
		)
		{
			d->unknownDimension2Curr = 0;
		}
	}
	
	if(unknownDimension2Curr > 0)
	{
		if(
			(d->KartStates.Spinning.driftSpinRate < 0) &&
			(unknownDimension2Curr < 400)
		  )
		{
			d->KartStates.Spinning.driftSpinRate = 
				(unknownDimension2Curr * -4) >> 3;
			
			if(d->KartStates.Spinning.driftSpinRate > -0x20)
				d->KartStates.Spinning.driftSpinRate = -0x20;
		}
	
		d->unknownDimension2Curr += d->KartStates.Spinning.driftSpinRate;
		d->unknownDimension2Curr += 0x800U;
		d->unknownDimension2Curr &= 0xfff;
		d->unknownDimension2Curr -= 0x800;
		
		if(
			(d->KartStates.Spinning.driftSpinRate < 0) &&
			(d->unknownDimension2Curr < 0)
		)
		{
			d->unknownDimension2Curr = 0;
		}
	}
	
	DECOMP_VehPtr_Crashing_PhysAngular(t, d);
}