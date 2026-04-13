#include <common.h>

void DECOMP_VehStuckProc_MaskGrab_Particles(struct Driver *d)
{
    struct Particle *p;

    for (char i = 10; i > 0; i--)
    {
        // Create instance in particle pool
        p = Particle_Init(0, sdata->gGT->iconGroup[0], &data.emSet_Maskgrab[0]);

        if (p == NULL)
            return;

        // position variables
        p->axis[0].startVal += d->posCurr.x;
        p->axis[1].startVal += d->posCurr.y;
        p->axis[2].startVal += d->posCurr.z;
    }
}