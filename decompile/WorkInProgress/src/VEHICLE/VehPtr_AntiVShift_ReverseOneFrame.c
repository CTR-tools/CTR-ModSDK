#include <common.h>

// Budget: 136 / 144 by

// reverse one frame of position
void DECOMP_VehPtr_AntiVShift_ReverseOneFrame(struct Thread *t, struct Driver *d)
{
    Player_JumpAndFriction();

    // if player did not start jumping this frame
    if ((d->actionsFlagSet & 0x10000400) == 0)
    {
        // // if there are not two humans colliding
        // if ((d->actionsFlagSet & 0x10000000) == 0)
        // {
        d->xSpeed = 0;
        d->ySpeed = 0;
        d->zSpeed = 0;

        d->speed = 0;
        d->speedApprox = 0;

        // set position to previous position
        for (int i = 0; i < 3; i++)
            d->posCurr[i] = d->posPrev[i];
        // }
    }
    // if player did start jumping this frame
    else
    {
        VehPtr_Driving_Init(t, d);
    }
}