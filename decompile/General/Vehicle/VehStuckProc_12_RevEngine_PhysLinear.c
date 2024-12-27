#include <common.h>

void DECOMP_VehStuckProc_RevEngine_PhysLinear(struct Thread* t, struct Driver* d)
{
	int unkTimer;

	struct GameTracker* gGT = sdata->gGT;

	unkTimer = d->KartStates.RevEngine.unk58e;
	unkTimer -= gGT->elapsedTimeMS;
	if (unkTimer * 0x10000 < 0) unkTimer = 0;
	d->KartStates.RevEngine.unk58e = unkTimer;

	unkTimer = d->KartStates.RevEngine.unk590;
	unkTimer -= gGT->elapsedTimeMS;
	if (unkTimer * 0x10000 < 0) unkTimer = 0;
	d->KartStates.RevEngine.unk590 = unkTimer;

	DECOMP_VehPhysProc_Driving_PhysLinear(t, d);

	if (d->KartStates.RevEngine.boolMaskGrab == 0)
		return;

	d->posCurr.y -= FPS_HALF(0x200);

	// if maskObj exists
	if (d->KartStates.RevEngine.maskObj != 0)
		d->KartStates.RevEngine.maskObj->duration = 7680;

#ifdef USE_ONLINE
	if (d->driverID != 0)
		return;
#endif

	struct CameraDC* cDC = &gGT->cameraDC[d->driverID];
	cDC->flags |= 0x10;
	cDC->unk98 = 0x40;
}