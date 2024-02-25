#include <common.h>

extern void *PlayerAntiVShiftFuncTable[13];

void DECOMP_VehPtr_AntiVShift_Init(struct Thread *t, struct Driver *d)
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

void DECOMP_VehPtr_AntiVShift_Update();
void DECOMP_VehPtr_AntiVShift_ReverseOneFrame();

void *PlayerAntiVShiftFuncTable[13] =
{
	NULL,
	DECOMP_VehPtr_AntiVShift_Update,
	DECOMP_VehPtr_Driving_PhysLinear,
	DECOMP_VehPtr_Driving_Audio,
	DECOMP_VehPtr_Driving_PhysAngular,
	
	#ifndef REBUILD_PS1
	OnApplyForces,
	COLL_StartSearch_NearPlayer,
	OnCollide_Drivers,
	COLL_StartSearch_Player,
	DECOMP_VehPtr_AntiVShift_ReverseOneFrame,
	OnRender,
	OnAnimate_Driving,
	VehParticle_DriverMain
	#endif
};