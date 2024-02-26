#include <common.h>

// Budget 200 / 272 bytes

extern void *PlayerDriftingFuncTable[13];

// seems to handle start of drifts
void DECOMP_VehPtr_Drifting_Init(struct Thread *t, struct Driver *d)
{
    d->kartState = KS_DRIFTING;

    // Character's Drift stat + ((Turning multiplier? << 2) / 5) * 100
    short drift = (d->unk460 + ((d->turnConst << 2) / 5)) * 0x100;

    // if simplified turning state is negative (means you're turning right)
    if (d->simpTurnState < 0)
    {
        // also make Multiplied drift negative
        drift = -drift;
    }

    d->multDrift = drift;

    d->rotationSpinRate = 0;
    d->unk_LerpToForwards = 0;
    d->timeUntilDriftSpinout = 0;

    // Turbo meter space left to fill = Length of Turbo meter << 5
    d->turbo_MeterRoomLeft = d->const_turboMaxRoom << 5;

    // erase union in driver struct
    d->KartStates.Drifting.numFramesDrifting = 0;
    d->KartStates.Drifting.driftBoostTimeMS = 0;
    d->KartStates.Drifting.driftTotalTimeMS = 0;
    d->KartStates.Drifting.numBoostsAttempted = 0;
    d->KartStates.Drifting.numBoostsSuccess = 0;

    for (int i = 0; i < 13; i++)
    {
        d->funcPtrs[i] = PlayerDriftingFuncTable[i];
    }
}

void *PlayerDriftingFuncTable[13] =
{
    DECOMP_VehPtr_Drifting_InitSetUpdate,
    NULL,
    DECOMP_VehPtr_Drifting_PhysLinear,
    DECOMP_VehPtr_Driving_Audio,
    DECOMP_VehPtr_Drifting_PhysAngular,
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