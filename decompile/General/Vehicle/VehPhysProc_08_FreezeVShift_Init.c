#include <common.h>

extern void *PlayerAntiVShiftFuncTable[13];

void DECOMP_VehPhysProc_FreezeVShift_Init(struct Thread *t, struct Driver *d)
{
    d->kartState = KS_ANTIVSHIFT;

    // Turbo meter = full
    d->turbo_MeterRoomLeft = 0;

    // turn off 29th flag of actions flag set (means players dont collide anymore)
    d->actionsFlagSet &= ~(0x10000000);

    for (int i = 0; i < 13; i++)
    {
        d->funcPtrs[i] = PlayerAntiVShiftFuncTable[i];
    }
}

void DECOMP_VehPhysProc_FreezeVShift_Update();
void DECOMP_VehPhysProc_FreezeVShift_ReverseOneFrame();

void *PlayerAntiVShiftFuncTable[13] =
{
	NULL,
	DECOMP_VehPhysProc_FreezeVShift_Update,
	DECOMP_VehPhysProc_Driving_PhysLinear,
	DECOMP_VehPhysProc_Driving_Audio,
	DECOMP_VehPhysGeneral_PhysAngular,
	DECOMP_VehPhysForce_OnApplyForces,
	
	#ifndef REBUILD_PS1
	COLL_StartSearch_NearPlayer,
	VehPhysForce_CollideDrivers,
	COLL_StartSearch_Player,
	DECOMP_VehPhysProc_FreezeVShift_ReverseOneFrame,
	VehPhysForce_TranslateMatrix,
	VehFrameProc_Driving,
	VehEmitter_DriverMain
	#endif
};