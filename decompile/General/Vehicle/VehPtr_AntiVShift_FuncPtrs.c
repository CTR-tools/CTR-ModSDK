#include <common.h>

void DECOMP_VehPtr_AntiVShift_Update(struct Thread *t, struct Driver *d)
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

	VehPtr_Driving_Init(t, d);
}

void DECOMP_VehPtr_AntiVShift_ReverseOneFrame(struct Thread *t, struct Driver *d)
{
    Player_JumpAndFriction();

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
			d->posCurr[0] = d->posPrev[0];
			d->posCurr[1] = d->posPrev[1];
			d->posCurr[2] = d->posPrev[2];
        }
		
		return;
    }

	VehPtr_Driving_Init(t, d);
}