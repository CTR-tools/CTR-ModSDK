#include <common.h>

extern void *PlayerDrivingFuncTable[13];

void DECOMP_VehPtr_Driving_Init(struct Thread *t, struct Driver *d)
{
    struct GameTracker *gGT = sdata->gGT;

    if (
			(gGT->levelID < GEM_STONE_VALLEY)
			
			// can I use gGT->podiumID==0 instead?
			// (levelID >= GEMSTONE && gGT->podium!=0) guarantees fail?
			#ifndef REBUILD_PS1
			// AdvHub + 232, so 233 podium wont work
			|| LOAD_IsOpen_AdvHub()
			#endif
		)
    {
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
		
		// must put this HERE, so that 
		// the above IF-statement works
        d->kartState = KS_NORMAL;
    }
}

void *PlayerDrivingFuncTable[13] =
{
    NULL,
    DECOMP_VehPtr_Driving_Update,
    DECOMP_VehPtr_Driving_PhysLinear,
    DECOMP_VehPtr_Driving_Audio,
    DECOMP_VehPtr_Driving_PhysAngular,
	
	#ifndef REBUILD_PS1
    OnApplyForces,
    COLL_StartSearch_NearPlayer,
    OnCollide_Drivers,
    COLL_StartSearch_Player,
    Player_JumpAndFriction,
    OnRender,
    OnAnimate_Driving,
    VehParticle_DriverMain
	#endif
};