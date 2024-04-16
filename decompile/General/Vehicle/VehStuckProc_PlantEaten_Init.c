#include <common.h>

extern void *PlayerEatenFuncTable[13];

// when eaten by plant on papu pyramid
void DECOMP_VehStuckProc_PlantEaten_Init(struct Thread *t, struct Driver *d)
{
    // when this function executes, you are lifted
    // above the track by the mask, where you respawn

    char i;
    struct Instance *inst = t->inst;

    // set state to mask grab, so nobody hits you with weapon
    d->kartState = KS_MASK_GRABBED;

    d->KartStates.EatenByPlant.boolInited = false;

    d->turbo_MeterRoomLeft = 0;
    d->turbo_outsideTimer = 0;
    d->reserves = 0;

    // drop bits for airborne (and another?)
    d->actionsFlagSet &= ~(0x80000); 
	d->actionsFlagSet |= 0x40;

    // "cloud" is the raincloud after hitting red potion

    // if thread of "cloud" exists
    if (d->thCloud != NULL)
    {
        ((struct RainCloud *)d->thCloud->object)->timeMS = 0;

        d->thCloud->funcThTick = RB_RainCloud_FadeAway;
		d->thCloud = NULL;
    }

    if (
			(DECOMP_LOAD_IsOpen_RacingOrBattle() != 0) &&
			((sdata->gGT->gameMode1 & ADVENTURE_ARENA) == 0)
		)
    {
        DECOMP_RB_Player_ModifyWumpa(d, -2);
    }

    // allow this thread to ignore all collisions
    t->flags |= 0x1000;

    // make invisible
    inst->flags |= HIDE_MODEL;

    for (i = 0; i < 3; i++)
    {
        OtherFX_Stop1(d->driverAudioPtrs[i]);
        d->driverAudioPtrs[i] = NULL;
    }

    for (i = 0; i < 13; i++)
        d->funcPtrs[i] = PlayerEatenFuncTable[i];
}

void DECOMP_VehStuckProc_PlantEaten_Update(struct Thread *t, struct Driver *d);
void DECOMP_VehStuckProc_PlantEaten_PhysLinear(struct Thread *t, struct Driver *d);
void DECOMP_VehStuckProc_PlantEaten_Animate(struct Thread *t, struct Driver *d);

void *PlayerEatenFuncTable[13] =
{
    NULL,
    DECOMP_VehStuckProc_PlantEaten_Update,
    DECOMP_VehStuckProc_PlantEaten_PhysLinear,
    DECOMP_VehPhysProc_Driving_Audio,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    VehPhysForce_TranslateMatrix,
    DECOMP_VehStuckProc_PlantEaten_Animate,
    NULL,
};