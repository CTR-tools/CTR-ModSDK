#include <common.h>

void DECOMP_VehStuckProc_Tumble_PhysAngular(struct Thread* thread, struct Driver* driver)
{
	int elapsedTimeMS = sdata->gGT->elapsedTimeMS;

	driver->numFramesSpentSteering = 10000;

#ifdef USE_60FPS
	if (sdata->gGT->timer & 1)
	{
#endif

		driver->unk3D4[0] -= (driver->unk3D4[0] >> 3);
		driver->rotationSpinRate -= (driver->rotationSpinRate >> 3);
		driver->unk_LerpToForwards -= (driver->unk_LerpToForwards >> 3);

#ifdef USE_60FPS
	}
#endif

	driver->ampTurnState = driver->rotationSpinRate;

	driver->turnAngleCurr += driver->unk_LerpToForwards;
	driver->turnAngleCurr += 0x800;
	driver->turnAngleCurr &= 0xfff;
	driver->turnAngleCurr -= 0x800;

	driver->angle += (short)(((int)driver->rotationSpinRate * elapsedTimeMS) >> 0xd);
	driver->angle &= 0xfff;

	(driver->rotCurr).y =
		driver->unk3D4[0] + driver->angle + driver->turnAngleCurr;

	(driver->rotCurr).w =
		DECOMP_VehCalc_InterpBySpeed((int)(driver->rotCurr).w, (elapsedTimeMS << 5) >> 5, 0);

#ifndef REBUILD_PS1
	VehPhysForce_RotAxisAngle(&driver->matrixMovingDir, (short*)&driver->AxisAngle1_normalVec, driver->angle);
#endif

	return;
}