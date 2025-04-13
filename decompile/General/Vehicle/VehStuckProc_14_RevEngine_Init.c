#include <common.h>

extern void *PlayerRevEngineFuncTable[13];

void DECOMP_VehStuckProc_RevEngine_Init(struct Thread *t, struct Driver *d)
{
    // spawn function that waits for traffic lights

    // kart state to rev
    d->kartState = KS_ENGINE_REVVING;
    d->revEngineState = 0;

    // assume reason for revving is: start of race
    d->KartStates.RevEngine.boolMaskGrab = false;
    d->KartStates.RevEngine.maskObj = NULL;
    d->KartStates.RevEngine.fireLevel = 0;

#ifndef REBUILD_PS1
    // if this is a mask grab
    if (d->quadBlockHeight + 0x1000 < d->posCurr.y)
    {
        // assume reason for revving is: mask grab
        d->KartStates.RevEngine.boolMaskGrab = true;
        d->KartStates.RevEngine.maskObj = VehPickupItem_MaskUseWeapon(d, 0);

        // Driver flag
        d->actionsFlagSet &= ~(1);

		#ifdef USE_ONLINE
		if(d->driverID == 0)
		#endif

			// CameraDC flag
			sdata->gGT->cameraDC[d->driverID].flags |= 8;
    }
#endif

    for (char i = 0; i < 13; i++)
    {
        d->funcPtrs[i] = PlayerRevEngineFuncTable[i];
    }
	
	// WHY does this break if we dont put it here?
	// What custom level data are we missing?
	// Causes driver to have very-small scale at startline
	#if defined(USE_LEVELDEV) || defined(USE_LEVELDISC)
	d->funcPtrs[8] = COLL_FIXED_PlayerSearch;
	#endif

    d->boolFirstFrameSinceRevEngine = true;

    d->KartStates.RevEngine.timeMS = 0;
    d->KartStates.RevEngine.unk58e = 0;
    d->KartStates.RevEngine.unk590 = 0;
    d->KartStates.RevEngine.unk[0] = 0;
    d->KartStates.RevEngine.unk[1] = 0;

    d->KartStates.RevEngine.boostMeter =
		d->const_AccelSpeed_ClassStat + d->const_AccelSpeed_ClassStat / 3;
}

void *PlayerRevEngineFuncTable[13] =
{
	NULL,
	DECOMP_VehStuckProc_RevEngine_Update,
	DECOMP_VehStuckProc_RevEngine_PhysLinear,
	DECOMP_VehPhysProc_Driving_Audio,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,

	#ifndef REBUILD_PS1
	VehPhysForce_TranslateMatrix,
	DECOMP_VehStuckProc_RevEngine_Animate,
	VehEmitter_DriverMain,
	#else
    0,
    DECOMP_VehStuckProc_RevEngine_Animate,
    0
    #endif
};