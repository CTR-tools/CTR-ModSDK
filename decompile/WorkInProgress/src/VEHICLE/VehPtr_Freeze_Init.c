#include <common.h>

// Budget: 116/172 bytes

void *PlayerFreezeFuncTable[13] =
{
    NULL,
    NULL,
    VehPtr_Freeze_PhysLinear,
    VehPtr_Driving_Audio,
    VehPtr_Driving_PhysAngular,
    OnApplyForces,
    COLL_StartSearch_NearPlayer,
    OnCollide_Drivers,
    COLL_StartSearch_Player,
    Player_JumpAndFriction,
    OnRender,
    OnAnimate_Driving,
    VehParticle_DriverMain
};

void DECOMP_VehPtr_Freeze_Init(struct Thread *t, struct Driver *d)
{
    if (d->kartState == KS_FREEZE)
        return;

    d->kartState = KS_FREEZE;
    d->speed = 0;
    d->speedApprox = 0;

    for (int i = 0; i < 13; i++)
    {
        d->funcPtrs[i] = PlayerFreezeFuncTable[i];
    }
}