#include <common.h>

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