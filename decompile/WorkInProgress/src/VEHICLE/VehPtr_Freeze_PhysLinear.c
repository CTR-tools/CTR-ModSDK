#include <common.h>

// Budget: 84/92 bytes

void DECOMP_VehPtr_Freeze_PhysLinear(struct Thread *t, struct Driver *d)
{
    VehPtr_Driving_PhysLinear(t, d);

    // reset turn state
    d->simpTurnState = 0;
    
    // reset wheel Y rotation
    d->wheelRotation = 0;

    // reset amplified turn state
    d->ampTurnState = 0;

    // reset two speed variables
    d->baseSpeed = 0;
    d->fireSpeed = 0;

    // edit flags
    d->actionsFlagSet |= 8;
    d->actionsFlagSet &= ~(4);

    if (0 < d->jump_TenBuffer)
    {
        d->jump_TenBuffer = 0;
    }
}
