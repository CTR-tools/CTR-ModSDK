#include <common.h>

extern void *PlayerFreezeFuncTable[13];

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

void *PlayerFreezeFuncTable[13] =
{
    NULL,
    NULL,
    DECOMP_VehPtr_Freeze_PhysLinear,
    DECOMP_VehPtr_Driving_Audio,
    DECOMP_VehPtr_Driving_PhysAngular,
    DECOMP_OnApplyForces,
	
	#ifndef REBUILD_PS1
    COLL_StartSearch_NearPlayer,
    OnCollide_Drivers,
    COLL_StartSearch_Player,
    Player_JumpAndFriction,
    OnRender,
    OnAnimate_Driving,
    VehParticle_DriverMain
	#endif
};