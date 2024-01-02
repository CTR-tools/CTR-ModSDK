#include <common.h>

// Budget: 52 / 84 bytes

// seems to handle end of blasted effect
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
    }
    else
    {
        // continue driving
        VehPtr_Driving_Init(t, d);
    }
}