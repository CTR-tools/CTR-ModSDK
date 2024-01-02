#include <common.h>

// Budget: 192 / 308 bytes

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

void DECOMP_VehPtr_Driving_Init(struct Thread *t, struct Driver *d)
{
    // spawn function that gives you immediate control,
    // used for adventure spawn, and dropping a mask-grab

    struct GameTracker *gGT = sdata->gGT;

    // This if-statement prevents driving in Main Menu,
    // Cutscenes, Naughty Dog Box Scene, etc

    // if Level ID is not an adv hub
    if ((4 < (gGT->levelID - GEM_STONE_VALLEY)) ||
        // or, this is an adv hub, and 232 is loaded
        (LOAD_IsOpen_AdvHub()))
    {
        d->kartState = NORMAL;

        // Turbo meter = full
        d->turbo_MeterRoomLeft = 0;

        d->StartDriving_0x60 = 0x60;
        d->StartRollback_0x280 = 0x280;

        d->unknownTraction = 0;

        for (int i = 0; i < 13; i++)
        {
            d->funcPtrs[i] = PlayerDrivingFuncTable[i];
        }

        // If you're in Battle Mode and
        if (((gGT->gameMode1 & BATTLE_MODE) != 0) &&

            // player is blasted
            (d->kartState == 6))
        {
            d->invincibleTimer = 0xb40;
        }
    }
}
