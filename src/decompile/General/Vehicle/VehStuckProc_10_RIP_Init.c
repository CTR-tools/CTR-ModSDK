#include <common.h>

void DECOMP_VehStuckProc_RIP_Init(struct Thread *t, struct Driver *d)
{
    VehStuckProc_PlantEaten_Init(t, d);
    d->invisibleTimer = 0;
    d->funcPtrs[1] = NULL;
    d->funcPtrs[11] = NULL;
}