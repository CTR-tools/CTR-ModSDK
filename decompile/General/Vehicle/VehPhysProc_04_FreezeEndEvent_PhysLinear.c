#include <common.h>

void DECOMP_VehPhysProc_FreezeEndEvent_PhysLinear(struct Thread *t, struct Driver *d)
{
    DECOMP_VehPhysProc_Driving_PhysLinear(t, d);

    d->simpTurnState = 0;
    d->wheelRotation = 0;
    d->ampTurnState = 0;

    // reset two speed variables
    d->baseSpeed = 0;
    d->fireSpeed = 0;

    // edit flags
    d->actionsFlagSet |= 8;
    d->actionsFlagSet &= ~(4);

    if (d->jump_TenBuffer > 0)
        d->jump_TenBuffer = 0;
}
