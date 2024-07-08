#include <common.h>

void DECOMP_VehPhysProc_FreezeVShift_Update(struct Thread *t, struct Driver *d)
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

void DECOMP_VehPhysProc_FreezeVShift_ReverseOneFrame(struct Thread *t, struct Driver *d)
{
	#ifndef REBUILD_PS1
    VehPhysGeneral_JumpAndFriction();
	#endif

	int actionFlagSet = d->actionsFlagSet;

    // if player did not start jumping this frame
    if ((actionFlagSet & 0x400) == 0)
    {
        // if there are not two humans colliding
        if ((actionFlagSet & 0x10000000) == 0)
        {
			d->xSpeed = 0;
			d->ySpeed = 0;
			d->zSpeed = 0;

			// d->speed and d->speedApprox
			*(int*)&d->speed = 0;

			// set position to previous position
			d->posCurr.x = d->posPrev.x;
			d->posCurr.y = d->posPrev.y;
			d->posCurr.z = d->posPrev.z;
        }

		return;
    }

	DECOMP_VehPhysProc_Driving_Init(t, d);
}