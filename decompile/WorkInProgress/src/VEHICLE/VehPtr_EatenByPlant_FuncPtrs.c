#include <common.h>

void DECOMP_VehPtr_EatenByPlant_Update(struct Thread *t, struct Driver *d)
{
    short noInput;
    struct Instance *inst = t->inst;

    // NoInput timer = NoInput timer - elapsed milliseconds per frame, ~32
    noInput = d->NoInputTimer - sdata->gGT->elapsedTimeMS;

    // if negative
    if (noInput < 0)
    {
        // set to zero
        d->NoInputTimer = 0;
    }

    d->NoInputTimer = noInput;

    if (noInput != 0) return;

    // if input is now allowed

    // enable collision for driver
    t->flags &= ~(0x1000);

    // make driver visible
    inst->flags &= HIDE_MODEL;

    // respawn driver at last valid quadblock
    VehPtr_MaskGrab_FindDestPos(d, d->lastValid);
    VehInit_TeleportSelf(d, 0, 0x80);

    // this lets you rev engine while falling
    VehPtr_EngineRevving_Init(t, d);
}

void DECOMP_VehPtr_EatenByPlant_PhysLinear(struct Thread *t, struct Driver *d)
{
    VehPtr_Driving_PhysLinear(t, d);

    d->simpTurnState = 0;

    // reset two speed variables
    d->fireSpeed = 0;
    d->baseSpeed = 0;

    // reset jump variable
    d->jump_TenBuffer = 0;

    // acceleration prevention,
    // drop bits for jump button, 0x20?, reversing engine
    d->actionsFlagSet = ((d->actionsFlagSet & ~(0x20000 | 0x20 | 4)) | 8);

    // increment time spent in mask grab
    d->timeSpentMaskGrabbed += sdata->gGT->elapsedTimeMS;
}

void DECOMP_VehPtr_EatenByPlant_Animate(struct Thread *t, struct Driver *d)
{
    short sVar1;
    long dist;
    struct Instance* inst;
    SVECTOR plantVector;
    VECTOR* camX;
    int camZ;
    long alStack32[2];

    struct GameTracker *gGT = sdata->gGT;

    struct Thread* plant = d->plantEatingMe;

    // if any plant is eating me
    if (((plant != NULL) &&

        // if not initialized
        (d->KartStates.EatenByPlant.boolInited == false)) &&

        // if more than 0.5s since player death
        (d->NoInputTimer < 2880))
    {
        // get instance from thread
        inst = plant->inst;

        // initialized, player eaten
        d->KartStates.EatenByPlant.boolInited = true;

        plantVector.vx = (((struct Plant *)plant->object)->LeftOrRight == 0) ? 250 : -250;
        plantVector.vy = 0;
        plantVector.vz = 750;

        SetRotMatrix(&inst->matrix);

        SetTransMatrix(&inst->matrix);

        RotTrans(&plantVector, camX, alStack32);

        struct TileView * view = gGT->tileView[d->driverID];

        view->pos[0] = (short)camX;

        // driverY + 0xc0
        view->pos[1] = inst->matrix.t[1] + 0xc0;

        // tileView->posZ
        view->pos[2] = camZ;

        // cameraX = cameraX - driverX
        camX = camX - inst->matrix.t[0];

        // cameraZ = cameraZ - driverZ
        camZ = camZ - inst->matrix.t[2];

        view->rot[1] = (short)ratan2(camX, camZ);

        // get distance between car and camera
        dist = SquareRoot0(camX * camX + camZ * camZ);

        view->rot[0] = (short) 0x800 - ratan2(view->rot[0] - inst->matrix.t[2], dist);

        view->rot[2] = 0;
    }
}

void *PlayerEatenFuncTable[13] =
{
    NULL,
    VehPtr_EatenByPlant_Update,
    VehPtr_EatenByPlant_PhysLinear,
    VehPtr_Driving_Audio,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    OnRender,
    VehPtr_EatenByPlant_Animate,
    NULL,
};

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
    d->actionsFlagSet &= ~(0x80000 | 0x40);

    // "cloud" is the raincloud after hitting red potion

    // if thread of "cloud" exists
    if (d->thCloud != NULL)
    {
        *(short *)&((struct RainCloud *)d->thCloud->object)->unknown[4] = 0;

        // Set driver->cloudTh->funcThTick to destroy thread
        (struct Thread *)(d->thCloud)->funcThTick = RB_RainCloud_FadeAway;

        // erase pointer to "cloud" thread
        d->thCloud = NULL;
    }

#ifndef REBUILD_PS1
    if (
			(LOAD_IsOpen_RacingOrBattle() != 0) &&
			((sdata->gGT->gameMode1 & ADVENTURE_ARENA) == 0)
		)
    {
        RB_Player_ModifyWumpa(d, -2);
    }
#endif

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

