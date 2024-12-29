#include <common.h>

void DECOMP_VehPhysProc_SlamWall_PhysAngular(struct Thread* t, struct Driver* d);

void DECOMP_VehPhysProc_SpinLast_PhysAngular(struct Thread* t, struct Driver* d)
{
	int driftAngleCurr;
	driftAngleCurr = d->turnAngleCurr;
	
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
	
	d->ampTurnState = d->rotationSpinRate;
	
	if(driftAngleCurr < 0)
	{
		if(
			(d->KartStates.Spinning.driftSpinRate > 0) &&
			(driftAngleCurr > -400)
		  )
		{
			d->KartStates.Spinning.driftSpinRate = 
				(driftAngleCurr * -4) >> 3;
			
			if(d->KartStates.Spinning.driftSpinRate < FPS_HALF(0x20))
				d->KartStates.Spinning.driftSpinRate = FPS_HALF(0x20);
		}
	
		d->turnAngleCurr += d->KartStates.Spinning.driftSpinRate;
		d->turnAngleCurr += 0x800U;
		d->turnAngleCurr &= 0xfff;
		d->turnAngleCurr -= 0x800;
	
		if(
			(d->KartStates.Spinning.driftSpinRate > 0) &&
			(d->turnAngleCurr > 0)
		)
		{
			d->turnAngleCurr = 0;
		}
	}
	
	if(driftAngleCurr > 0)
	{
		if(
			(d->KartStates.Spinning.driftSpinRate < 0) &&
			(driftAngleCurr < 400)
		  )
		{
			d->KartStates.Spinning.driftSpinRate = 
				(driftAngleCurr * -4) >> 3;
			
			if(d->KartStates.Spinning.driftSpinRate > FPS_HALF(-0x20))
				d->KartStates.Spinning.driftSpinRate = FPS_HALF(-0x20);
		}
	
		d->turnAngleCurr += d->KartStates.Spinning.driftSpinRate;
		d->turnAngleCurr += 0x800U;
		d->turnAngleCurr &= 0xfff;
		d->turnAngleCurr -= 0x800;
		
		if(
			(d->KartStates.Spinning.driftSpinRate < 0) &&
			(d->turnAngleCurr < 0)
		)
		{
			d->turnAngleCurr = 0;
		}
	}
	
	DECOMP_VehPhysProc_SlamWall_PhysAngular(t, d);
}