#include <common.h>

void DECOMP_VehPhysProc_FreezeVShift_Update(struct Thread* t, struct Driver* d)
{
	// if firespeed = 0 and
	// player is not in accel prevention (4),
	// not pressing Square (4, 6),
	if ((d->fireSpeed == 0) &&
		// not in player-on-player collision
		((d->actionsFlagSet & 0x10000028) == 0))
	{
		// stop kart
		d->speed = 0;
		d->speedApprox = 0;

		return;
	}

	DECOMP_VehPhysProc_Driving_Init(t, d);
}