#include <common.h>

extern void *PlayerDrivingFuncTable[13];

void DECOMP_VehPtr_Driving_Init(struct Thread *t, struct Driver *d)
{
    struct GameTracker *gGT = sdata->gGT;

    if (
			(gGT->levelID < GEM_STONE_VALLEY) ||
			
			// AdvHub + 232, so 233 podium wont work
			LOAD_IsOpen_AdvHub()
		)
    {
        d->kartState = KS_NORMAL;

        // Turbo meter = full
        d->turbo_MeterRoomLeft = 0;

        d->StartDriving_0x60 = 0x60;
        d->StartRollback_0x280 = 0x280;

        d->unknownTraction = 0;

        for (int i = 0; i < 13; i++)
        {
            d->funcPtrs[i] = PlayerDrivingFuncTable[i];
        }

        if (
				((gGT->gameMode1 & BATTLE_MODE) != 0) &&
				(d->kartState == KS_BLASTED)
			)
        {
            d->invincibleTimer = 0xb40;
        }
    }
}

void *PlayerDrivingFuncTable[13] =
{
    NULL,
    VehPtr_Driving_Update,
    VehPtr_Driving_PhysLinear,
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