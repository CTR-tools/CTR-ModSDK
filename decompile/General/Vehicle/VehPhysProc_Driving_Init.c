#include <common.h>

extern void *PlayerDrivingFuncTable[13];

void DECOMP_VehPhysProc_Driving_Init(struct Thread *t, struct Driver *d)
{
    struct GameTracker *gGT = sdata->gGT;

    if (
			(gGT->levelID < GEM_STONE_VALLEY)

			
			// can I use gGT->podiumID==0 instead?
			// (levelID >= GEMSTONE && gGT->podium!=0) guarantees fail?


			// AdvHub + 232, so 233 podium wont work
			|| DECOMP_LOAD_IsOpen_AdvHub()
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

#ifdef USE_60FPS
void Hook60_DriverMain(struct Thread *t, struct Driver *d);
#endif

void *PlayerDrivingFuncTable[13] =
{
    NULL,
    DECOMP_VehPhysProc_Driving_Update,
    DECOMP_VehPhysProc_Driving_PhysLinear,
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

		#ifdef USE_60FPS
		Hook60_DriverMain,
		#else
		VehEmitter_DriverMain
		#endif

	#endif
};