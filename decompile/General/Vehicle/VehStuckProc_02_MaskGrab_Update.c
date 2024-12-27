#include <common.h>

void DECOMP_VehStuckProc_MaskGrab_Update(struct Thread* t, struct Driver* d)
{
	struct GameTracker* gGT = sdata->gGT;

	d->NoInputTimer -= gGT->elapsedTimeMS;

	if (d->NoInputTimer < 0)
		d->NoInputTimer = 0;

	if (d->NoInputTimer != 0)
		return;

	// when input is allowed,
	// which is when driver is spawned back over track

	struct MaskHeadWeapon* mask = d->KartStates.MaskGrab.maskObj;

	if (mask != NULL)
	{
		// mask rotZ
		mask->rot[2] &= ~(1);

		// scale = 100%
		mask->scale = 0x1000;
	}


#ifdef USE_ONLINE
	if (d->driverID == 0)
#endif

		// CameraDC flag
		gGT->cameraDC[d->driverID].flags |= 8;


	VehStuckProc_MaskGrab_FindDestPos((struct Thread*)d, (struct Driver*)d->lastValid);

	VehBirth_TeleportSelf(d, 0, 0x80);

	VehStuckProc_RevEngine_Init(t, d);
}