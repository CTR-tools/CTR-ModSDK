#include <common.h>

void DECOMP_VehPhysProc_SpinFirst_PhysAngular(struct Thread* t, struct Driver* d)
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

	d->angle += (short)((d->rotationSpinRate * elapsedTimeMS) >> 0xd);
	d->angle &= 0xfff;

	d->rotCurr.y = d->unk3D4[0] + d->angle + d->turnAngleCurr;

	d->rotCurr.w =
		DECOMP_VehCalc_InterpBySpeed
		(
			d->rotCurr.w,
			(elapsedTimeMS << 5) >> 5,
			0
		);

	#ifndef REBUILD_PS1
	VehPhysForce_RotAxisAngle(&d->matrixMovingDir, &d->AxisAngle1_normalVec.x, d->angle);
	#endif
}