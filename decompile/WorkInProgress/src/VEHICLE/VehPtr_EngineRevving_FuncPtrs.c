#include <common.h>

void DECOMP_VehPtr_EngineRevving_Update(struct Thread *t, struct Driver *d)
{
    int revFireLevel;

    // If race has not started
    if (d->KartStates.boolEngineRevMaskGrab == false)
    {
        // If Traffic Lights are not done counting down
        if (0 < sdata->gGT->trafficLightsTimer)
        {
            // Dont continue with the function,
            // let your kart stay in a revving state
            return;
        }
    }

    // If race has started
    else
    {

        // If mask grab has not lowered you close
        // enough to the track to let you go
        if (d->quadBlockHeight + 0x4000 <= d->posCurr[1])
        {
            // Dont continue with the function,
            // let your kart stay in a revving state
            return;
        }
    }

    // Assume it's time to transition out of being
    // frozen, and into driving, last iteration of
    // this function

    // if reason for revving is mask grab
    if ((d->KartStates.boolEngineRevMaskGrab == true) &&

        // if maskObj exists
        (d->maskObj != NULL))
    {
        // end duration
        (struct MaskHeadWeapon *)(d->maskObj)->duration = 0;
    }

    if ((d->const_SpeedometerScale_ClassStat < d->KartStates.EngineRevving.engineRevFire) &&
        (d->KartStates.EngineRevving.unk[1] & 3) == 0)
    {
        // While not moving, if you rev'd your engine less than...
        if (d->KartStates.EngineRevving.engineRevBoostMeter < (d->const_SpeedometerScale_ClassStat + d->const_SacredFireSpeed))
        {
            // You get a small boost
            revFireLevel = 0x20;
        }

        // if you rev'd your engine high
        else
        {
            // you get a big boost
            revFireLevel = 0x80;
        }

        // one full second of reserves
        Turbo_Increment(d, 960, 0, revFireLevel);
    }

    // full meter
    d->turbo_MeterRoomLeft = 0;
    d->engineRevState = 0;

    VehPtr_Driving_Init(t, d);
}

void DECOMP_VehPtr_EngineRevving_PhysLinear(struct Thread *t, struct Driver *d)
{
    struct GameTracker *gGT = sdata->gGT;
    int unkTimer = d->KartStates.EngineRevving.unk58e;
    // elapsed milliseconds per frame, ~32
    unkTimer -= gGT->elapsedTimeMS;
    if (unkTimer * 0x10000 < 0)
    {
        unkTimer = 0;
    }
    d->KartStates.EngineRevving.unk58e = unkTimer;

    unkTimer = d->KartStates.EngineRevving.unk590;

    // elapsed milliseconds per frame, ~32
    unkTimer -= gGT->elapsedTimeMS;
    if (unkTimer * 0x10000 < 0)
    {
        unkTimer = 0;
    }
    d->KartStates.EngineRevving.unk590 = unkTimer;

    VehPtr_Driving_PhysLinear(t, d);

    // if race already started
    if (d->KartStates.boolEngineRevMaskGrab != 0)
    {
        struct CameraDC *cDC = &gGT.cameraDC[d->driverID];

        cDC->flags |= 0x10;
        cDC->unk98 = 0x40;

        // Y pos -= 0x200
        d->posCurr[1] -= 0x200;

        // if maskObj exists
        if (d->maskObj != 0)
        {
            // set mask duration to 8 secs
            (struct MaskHeadWeapon *)(d->maskObj)->duration = 7680;
        }
    }
}

void DECOMP_VehPtr_EngineRevving_Animate(struct Thread *t, struct Driver *d)
{
    char bVar1;
    u_char bVar2;
    short uVar3;
    int iVar4;
    int local_18;
    short sVar5;
    int uVar6;
    int iVar7;
    uint uVar8;
    int iVar9;
    
    struct Instance *inst = t->inst;

    if (((0 < d->fireSpeed) && (d->KartStates.EngineRevving.unk58e == 0)) &&
        (d->KartStates.EngineRevving.unk[1] & 3) == 0)
    {
        // Curr revving meter   -   Max revving meter
        iVar4 = d->KartStates.EngineRevving.engineRevFire - d->KartStates.EngineRevving.engineRevBoostMeter;

        // absolute value
        if (iVar4 < 0)
        {
            iVar4 = -iVar4;
        }

        // NOPing will fill meter in
        // slow motion, showing how it works
        iVar4 = iVar4 >> 1;

        iVar7 = iVar4;

        // Speed of filling the meter changes
        // depending on how full the meter is,
        // there are two speeds

        if (5000 < iVar4)
        {
            iVar7 = 5000;
        }

        if (iVar4 < 0x100)
        {
            iVar7 = 0x100;
        }

        // Interpolate turboMeter by speed
        // parameters: curr revving meter and meter filling speed
        iVar4 = InterpBySpeed(d->KartStates.EngineRevving.engineRevFire, iVar7);

        // Set new curr rev
        d->KartStates.EngineRevving.engineRevFire = iVar4;
        d->KartStates.EngineRevving.unk[0] = 2;

        // if max revv > filling speed
        if (iVar4 < d->KartStates.EngineRevving.engineRevBoostMeter)
        {
            d->KartStates.EngineRevving.engineRevMS = 0;
        }

        else
        {
            // elapsed milliseconds per frame, ~32
            sVar5 = d->KartStates.EngineRevving.engineRevMS + sdata->gGT->elapsedTimeMS;
            d->KartStates.EngineRevving.engineRevMS = sVar5;

            // if more than 0.192s
            if (192 < sVar5)
            {
                d->KartStates.EngineRevving.unk[0] = 0;
                d->KartStates.EngineRevving.unk[1] |= 3;

                OtherFX_Play_Echo(0xf, 1, (d->actionsFlagSet & 1));
            }
        }
        goto LAB_80067dec;
    }
    d->KartStates.EngineRevving.engineRevMS = 0;
    if (d->KartStates.EngineRevving.unk[0] == 2)
    {
        d->KartStates.EngineRevving.unk58e = 0x100;
        d->KartStates.EngineRevving.unk[0] = 0;

        // if curr rev > ???
        if (d->const_SpeedometerScale_ClassStat < d->KartStates.EngineRevving.engineRevFire)
        {
            d->KartStates.EngineRevving.unk[0] = 1;
        }
    }
    if ((d->KartStates.EngineRevving.unk[0] != 0) &&

        // curr rev < ???
        (d->KartStates.EngineRevving.engineRevFire < d->const_SpeedometerScale_ClassStat))
    {
        d->KartStates.EngineRevving.unk[0] = 0;

        // Interpolate rotation by speed
        // params: max revv, ???
        uVar6 = InterpBySpeed(d->KartStates.EngineRevving.engineRevBoostMeter, d->const_SacredFireSpeed / 3 + 3);

        // max rev = ???
        d->KartStates.EngineRevving.engineRevBoostMeter = uVar6;
    }

    // if curr rev < 1
    if (d->KartStates.EngineRevving.engineRevFire < 1)
    {
        d->KartStates.EngineRevving.unk[1] &= ~(2);

        // max rev = ???
        d->KartStates.EngineRevving.engineRevBoostMeter =
            d->const_SpeedometerScale_ClassStat + d->const_SacredFireSpeed / 3;
    }

    // if curr rev >= 1
    else
    {

        // rev deacceleration rate = curr rev / 2
        uVar8 = d->KartStates.EngineRevving.engineRevFire >> 1;

        if ((d->KartStates.EngineRevving.unk[1] & 2) == 0)
        {
            bVar2 = (int)uVar8 < 0x100;

            // if rev deacceleration rate > 1000
            if (1000 < (int)uVar8)
            {

                // rev deacceleration rate = 1000
                uVar8 = 1000;
                goto LAB_80067d64;
            }
        }

        else
        {
            bVar2 = (int)uVar8 < 0x100;

            // if rev deacceleration rate > 3000
            if (3000 < (int)uVar8)
            {

                // rev deacceleration rate = 3000
                uVar8 = 3000;
            LAB_80067d64:
                bVar2 = uVar8 < 0x100;
            }
        }
        if (bVar2)
        {

            // rev deacceleration rate = 0x100
            uVar8 = 0x100;
        }

        // new rev = curr rev - rev deacceleration rate
        iVar4 = d->KartStates.EngineRevving.engineRevFire - uVar8;

        // curr rev = new rev
        d->KartStates.EngineRevving.engineRevFire = iVar4;

        // if new rev < 1
        if (iVar4 < 1)
        {

            d->KartStates.EngineRevving.unk590 = 0xc0;

            // curr rev = 0
            d->KartStates.EngineRevving.engineRevFire = 0;
        }
    }
    if (d->fireSpeed < 1)
    {
        d->KartStates.EngineRevving.unk[1] &= ~(1);
    }

LAB_80067dec:

    if ((*(u_int *)&d->KartStates.EngineRevving.unk590 & 0x200ffff) == 0)
    {

        // if curr rev < ???
        if (d->KartStates.EngineRevving.engineRevFire < d->const_SpeedometerScale_ClassStat)
        {
            d->engineRevState = 0;
        }
        else
        {
            d->engineRevState = 1;
        }
    }
    else
    {
        d->engineRevState = 2;
    }

    iVar4 = d->const_SpeedometerScale_ClassStat;

    // ??? = curr rev
    d->unk36E = d->KartStates.EngineRevving.engineRevFire;

    // if curr rev < ???
    if (d->KartStates.EngineRevving.engineRevFire < iVar4)
    {

        // 476 and 447 can be absolutely any value,
        // by default they are 15 and 30, but as long as
        // they are proportional (1 and 2, 4 and 8), they
        // behave the same as 15 and 30

        bVar1 = d->const_turboMaxRoom;

        // 477 changes when meter turns red
        local_18 = d->const_turboLowRoomWarning * 0x20 + 1;

        // curr rev
        uVar6 = d->KartStates.EngineRevving.engineRevFire;
        iVar7 = 0;
        iVar9 = iVar4;
    }
    else
    {
        // 477 changes when meter turns red
        bVar1 = d->const_turboLowRoomWarning;

        local_18 = 1;

        // curr rev
        uVar6 = d->KartStates.EngineRevving.engineRevFire;
        iVar9 = iVar4 + d->const_SacredFireSpeed;
        iVar7 = iVar4;
    }

    // Get percentage of uVar6 between iVar7 and iVar9,
    // then return that same percentage between bVar1<<5 and local18
    // Map value from [oldMin, oldMax] to [newMin, newMax]
    // inverting newMin and newMax will give an inverse range mapping
    uVar3 = MapToRange(uVar6, iVar7, iVar9, (uint)bVar1 << 5, local_18);

    d->turbo_MeterRoomLeft = uVar3;
    d->distanceDrivenBackwards = 0;
    iVar4 = d->unk36E >> 6;

    if (iVar4 < 0x401)
    {
        if (iVar4 < 0)
        {
            iVar4 = 0;
        }
    }
    else
    {
        iVar4 = 0x400;
    }

    // Set the scale of the car while revving the engine,
    // this is a basic "squash and stretch" concept of animation, before motion

    // Reduce height a little
    inst->scale[1] = 3276 - iVar4;
    inst->scale[0] = (short)((iVar4 * 6) / 10) + 3276;
    inst->scale[2] = (short)((iVar4 * 6) / 10) + 3276;

    d->jumpSquishStretch = iVar4;
}

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

void DECOMP_VehPtr_EngineRevving_Init(struct Thread *t, struct Driver *d)
{
    // spawn function that waits for traffic lights

    // kart state to rev
    d->kartState = KS_ENGINE_REVVING;
    d->engineRevState = 0; // no rev
    d->KartStates.EngineRevving.engineRevFire = 0;

    // assume reason for revving is: start of race
    d->KartStates.EngineRevving.boolEngineRevMaskGrab = false;

    // clear maskObj
    d->maskObj = NULL;

    // if this is a mask grab
    if (d->quadBlockHeight + 0x1000 < d->posCurr[1])
    {
        // assume reason for revving is: mask grab
        d->KartStates.EngineRevving.boolEngineRevMaskGrab = true;

        // Mask Object
        d->maskObj = Weapon_Mask_UseWeapon(d, 0);

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

    d->KartStates.EngineRevving.engineRevBoostMeter = d->const_SpeedometerScale_ClassStat + d->const_SpeedometerScale_ClassStat / 3;
}