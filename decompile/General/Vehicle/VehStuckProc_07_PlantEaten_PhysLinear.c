#include <common.h>

void DECOMP_VehStuckProc_PlantEaten_PhysLinear(struct Thread* t, struct Driver* d)
{
	VehPhysProc_Driving_PhysLinear(t, d);

	d->simpTurnState = 0;

	// reset two speed variables
	d->fireSpeed = 0;
	d->baseSpeed = 0;

	// reset jump variable
	d->jump_TenBuffer = 0;

	// acceleration prevention,
	// drop bits for jump button, 0x20?, reversing engine
	d->actionsFlagSet &= ~(0x20024);
	d->actionsFlagSet |= 8;

	// increment time spent in mask grab
	d->timeSpentMaskGrabbed += sdata->gGT->elapsedTimeMS;
}