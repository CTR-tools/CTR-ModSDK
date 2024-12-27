#include <common.h>

extern void *PlayerFreezeFuncTable[13];

void DECOMP_VehPhysProc_FreezeEndEvent_Init(struct Thread *t, struct Driver *d)
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
    DECOMP_VehPhysProc_FreezeEndEvent_PhysLinear,
    DECOMP_VehPhysProc_Driving_Audio,
    DECOMP_VehPhysGeneral_PhysAngular,
    DECOMP_VehPhysForce_OnApplyForces,
	
	#ifndef REBUILD_PS1
    COLL_StartSearch_NearPlayer,
    VehPhysForce_CollideDrivers,
    COLL_StartSearch_Player,
    VehPhysGeneral_JumpAndFriction,
    VehPhysForce_TranslateMatrix,
    VehFrameProc_Driving,
    VehEmitter_DriverMain
	#endif
};