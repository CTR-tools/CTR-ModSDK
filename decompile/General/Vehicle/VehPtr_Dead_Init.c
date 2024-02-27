#include <common.h>

void DECOMP_VehPtr_Dead_Init(struct Thread *t, struct Driver *d)
{
    VehPtr_EatenByPlant_Init(t, d);
    d->invisibleTimer = 0;
    d->funcPtrs[1] = NULL;
    d->funcPtrs[11] = NULL;
}