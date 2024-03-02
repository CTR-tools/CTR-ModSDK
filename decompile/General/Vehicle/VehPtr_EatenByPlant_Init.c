#include <common.h>

extern void *PlayerEatenFuncTable[13];

void RB_RainCloud_FadeAway(struct Thread *t);

// when eaten by plant on papu pyramid
void DECOMP_VehPtr_EatenByPlant_Init(struct Thread *t, struct Driver *d)
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
        *(short *)&((struct RainCloud *)d->thCloud->object)->unknown[4] = 0;

        d->thCloud->funcThTick = RB_RainCloud_FadeAway;
		d->thCloud = NULL;
    }

    if (
			(DECOMP_LOAD_IsOpen_RacingOrBattle() != 0) &&
			((sdata->gGT->gameMode1 & ADVENTURE_ARENA) == 0)
		)
    {
#ifndef REBUILD_PS1
        RB_Player_ModifyWumpa(d, -2);
#endif
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

void DECOMP_VehPtr_EatenByPlant_Update(struct Thread *t, struct Driver *d);
void DECOMP_VehPtr_EatenByPlant_PhysLinear(struct Thread *t, struct Driver *d);
void DECOMP_VehPtr_EatenByPlant_Animate(struct Thread *t, struct Driver *d);

void *PlayerEatenFuncTable[13] =
{
    NULL,
    DECOMP_VehPtr_EatenByPlant_Update,
    DECOMP_VehPtr_EatenByPlant_PhysLinear,
    DECOMP_VehPtr_Driving_Audio,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    OnRender,
    DECOMP_VehPtr_EatenByPlant_Animate,
    NULL,
};