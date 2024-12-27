#include <common.h>

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