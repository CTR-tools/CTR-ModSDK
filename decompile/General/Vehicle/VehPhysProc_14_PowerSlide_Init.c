#include <common.h>

// Budget 200 / 272 bytes

extern void *PlayerDriftingFuncTable[13];

// seems to handle start of drifts
void DECOMP_VehPhysProc_PowerSlide_Init(struct Thread *t, struct Driver *d)
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

#ifdef USE_60FPS
void Hook60_DriverMain(struct Thread *t, struct Driver *d)
{
	#ifndef REBUILD_PS1
	if(sdata->gGT->timer&1)
	{
		// next slot (8-frame cycle)
		d->skidmarkFrameIndex = d->skidmarkFrameIndex - 1U & 7;
	}
	
	// block change
	*(short*)0x80059a6c = 0;
	
	VehEmitter_DriverMain(t, d);
	
	// put it back, for non-drift functions
	*(short*)0x80059a6c = -1;
	#endif
}
#endif

void *PlayerDriftingFuncTable[13] =
{
    DECOMP_VehPhysProc_PowerSlide_InitSetUpdate,
    NULL,
    DECOMP_VehPhysProc_PowerSlide_PhysLinear,
    DECOMP_VehPhysProc_Driving_Audio,
    DECOMP_VehPhysProc_PowerSlide_PhysAngular,
    DECOMP_VehPhysForce_OnApplyForces,
	
	#ifndef REBUILD_PS1
    COLL_StartSearch_NearPlayer,
    VehPhysForce_CollideDrivers,
    COLL_StartSearch_Player,
    VehPhysGeneral_JumpAndFriction,
    VehPhysForce_TranslateMatrix,
    VehFrameProc_Driving,
	
		#ifdef USE_60FPS
		Hook60_DriverMain,
		#else
		VehEmitter_DriverMain
		#endif
	
	#endif
};