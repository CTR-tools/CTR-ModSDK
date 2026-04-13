#include <common.h>

// Electric particles spin in circle under driver
void DECOMP_VehStuckProc_Warp_AddDustPuff1(struct ScratchpadStruct *sps)
{
    struct GameTracker *gGT = sdata->gGT;

    // if even frame don't spawn
    if (gGT->timer & 1) return;

    struct Particle *p = Particle_Init(0, gGT->iconGroup[1], &data.emSet_Warppad[0]);

    if (p == NULL) return;

    // position variables
    for (char i = 0; i < 3; i++)
        p->axis[i].startVal += sps->Input1.pos[i];
}
