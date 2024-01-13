#include <common.h>

extern void *PlayerEngineRevFuncTable[13];

void DECOMP_VehPtr_EngineRevving_Init(struct Thread *t, struct Driver *d)
{
    // spawn function that waits for traffic lights

    // kart state to rev
    d->kartState = KS_ENGINE_REVVING;
    d->engineRevState = 0;

    // assume reason for revving is: start of race
    d->KartStates.EngineRevving.boolEngineRevMaskGrab = false;
    d->KartStates.EngineRevving.maskObj = NULL;
    d->KartStates.EngineRevving.engineRevFire = 0;

    // if this is a mask grab
    if (d->quadBlockHeight + 0x1000 < d->posCurr[1])
    {
        // assume reason for revving is: mask grab
        d->KartStates.EngineRevving.boolEngineRevMaskGrab = true;
        d->KartStates.EngineRevving.maskObj = Weapon_Mask_UseWeapon(d, 0);

        // Driver flag
        d->actionsFlagSet &= ~(1);

        // CameraDC flag
        sdata->gGT->cameraDC[d->driverID].flags |= 8;
    }

    for (char i = 0; i < 13; i++)
    {
        d->funcPtrs[i] = PlayerEngineRevFuncTable[i];
    }

    d->boolFirstFrameSinceEngineRevving = true;

    d->KartStates.EngineRevving.engineRevMS = 0;
    d->KartStates.EngineRevving.unk58e = 0;
    d->KartStates.EngineRevving.unk590 = 0;
    d->KartStates.EngineRevving.unk[0] = 0;
    d->KartStates.EngineRevving.unk[1] = 0;

    d->KartStates.EngineRevving.engineRevBoostMeter = 
		d->const_SpeedometerScale_ClassStat + d->const_SpeedometerScale_ClassStat / 3;
}

void DECOMP_VehPtr_EngineRevving_Update();
void DECOMP_VehPtr_EngineRevving_PhysLinear();
void DECOMP_VehPtr_EngineRevving_Animate();

void *PlayerEngineRevFuncTable[13] =
{
	NULL,
	DECOMP_VehPtr_EngineRevving_Update,
	DECOMP_VehPtr_EngineRevving_PhysLinear,
	VehPtr_Driving_Audio,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	OnRender,
	DECOMP_VehPtr_EngineRevving_Animate,
	VehParticle_DriverMain,
};