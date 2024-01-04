#include <common.h>

// Budget : 128 / 184 bytes

void *PlayerAntiVShiftFuncTable[13] =
{
	NULL,
	VehPtr_AntiVShift_Update,
	VehPtr_Driving_PhysLinear,
	VehPtr_Driving_Audio,
	VehPtr_Driving_PhysAngular,
	OnApplyForces,
	COLL_StartSearch_NearPlayer,
	OnCollide_Drivers,
	COLL_StartSearch_Player,
	VehPtr_AntiVShift_ReverseOneFrame,
	OnRender,
	OnAnimate_Driving,
	VehParticle_DriverMain
};

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