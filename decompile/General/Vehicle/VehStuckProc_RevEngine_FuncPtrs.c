#include <common.h>

void DECOMP_VehStuckProc_RevEngine_Update(struct Thread *t, struct Driver *d)
{
    int revFireLevel;

    // If race has not started
    if (d->KartStates.RevEngine.boolMaskGrab == false)
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
        if (d->quadBlockHeight + 0x4000 <= d->posCurr.y)
        {
            // Dont continue with the function,
            // let your kart stay in a revving state
            return;
        }
    }

    // Assume it's time to transition out of being
    // frozen, and into driving, last iteration of
    // this function

    if ((d->KartStates.RevEngine.boolMaskGrab == true) &&
		(d->KartStates.RevEngine.maskObj != NULL))
		 d->KartStates.RevEngine.maskObj->duration = 0;

    if ((d->const_AccelSpeed_ClassStat < d->KartStates.RevEngine.fireLevel) &&
        (d->KartStates.RevEngine.unk[1] & 3) == 0)
    {
        // While not moving, if you rev'd your engine less than...
        if (d->KartStates.RevEngine.boostMeter < (d->const_AccelSpeed_ClassStat + d->const_SacredFireSpeed))
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
        DECOMP_VehFire_Increment(d, 960, 0, revFireLevel);
    }

    // full meter
    d->turbo_MeterRoomLeft = 0;
    d->revEngineState = 0;

    DECOMP_VehPhysProc_Driving_Init(t, d);
}

void DECOMP_VehStuckProc_RevEngine_PhysLinear(struct Thread *t, struct Driver *d)
{
	int unkTimer;

    struct GameTracker *gGT = sdata->gGT;

	unkTimer = d->KartStates.RevEngine.unk58e;
    unkTimer -= gGT->elapsedTimeMS;
    if (unkTimer * 0x10000 < 0) unkTimer = 0;
    d->KartStates.RevEngine.unk58e = unkTimer;

    unkTimer = d->KartStates.RevEngine.unk590;
    unkTimer -= gGT->elapsedTimeMS;
    if (unkTimer * 0x10000 < 0) unkTimer = 0;
    d->KartStates.RevEngine.unk590 = unkTimer;

    DECOMP_VehPhysProc_Driving_PhysLinear(t, d);

    if (d->KartStates.RevEngine.boolMaskGrab == 0)
		return;

    d->posCurr.y -= FPS_HALF(0x200);

    // if maskObj exists
    if (d->KartStates.RevEngine.maskObj != 0)
        d->KartStates.RevEngine.maskObj->duration = 7680;

	#ifdef USE_ONLINE
	if(d->driverID != 0)
		return;
	#endif

	struct CameraDC *cDC = &gGT->cameraDC[d->driverID];
    cDC->flags |= 0x10;
    cDC->unk98 = 0x40;
}

void DECOMP_VehStuckProc_RevEngine_Animate(struct Thread *t, struct Driver *d)
{
    char bVar1;
    u_char bVar2;
    short uVar3;
    int iVar4;
    int local_18;
    short sVar5;
    int uVar6;
    int iVar7;
    u_int uVar8;
    int iVar9;

    struct Instance *inst = t->inst;

    if (
			(d->fireSpeed > 0) &&
			(d->KartStates.RevEngine.unk58e == 0) &&
			((d->KartStates.RevEngine.unk[1] & 3) == 0)
		)
    {
        // Curr revving meter - Max revving meter
        iVar4 =
			d->KartStates.RevEngine.fireLevel -
			d->KartStates.RevEngine.boostMeter;

        // absolute value
        if (iVar4 < 0)
        {
            iVar4 = -iVar4;
        }

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

        iVar4 = DECOMP_VehCalc_InterpBySpeed(
				d->KartStates.RevEngine.fireLevel,
				FPS_HALF(iVar7),
				d->KartStates.RevEngine.boostMeter);

        // Set new curr rev
        d->KartStates.RevEngine.fireLevel = iVar4;
        d->KartStates.RevEngine.unk[0] = 2;

        // if max revv > filling speed
        if (iVar4 < d->KartStates.RevEngine.boostMeter)
        {
            d->KartStates.RevEngine.timeMS = 0;
        }

        else
        {
            // elapsed milliseconds per frame, ~32
            sVar5 = d->KartStates.RevEngine.timeMS + sdata->gGT->elapsedTimeMS;
            d->KartStates.RevEngine.timeMS = sVar5;

            // if more than 0.192s
            if (192 < sVar5)
            {
                d->KartStates.RevEngine.unk[0] = 0;
                d->KartStates.RevEngine.unk[1] |= 3;

				#ifdef USE_ONLINE
				if(d->driverID == 0)
				#endif

					DECOMP_OtherFX_Play_Echo(0xf, 1, d->actionsFlagSet & 0x10000);
            }
        }
        goto LAB_80067dec;
    }
    d->KartStates.RevEngine.timeMS = 0;
    if (d->KartStates.RevEngine.unk[0] == 2)
    {
        d->KartStates.RevEngine.unk58e = 0x100;
        d->KartStates.RevEngine.unk[0] = 0;

        // if curr rev > ???
        if (d->const_AccelSpeed_ClassStat < d->KartStates.RevEngine.fireLevel)
        {
            d->KartStates.RevEngine.unk[0] = 1;
        }
    }
    if ((d->KartStates.RevEngine.unk[0] != 0) &&

        // curr rev < ???
        (d->KartStates.RevEngine.fireLevel < d->const_AccelSpeed_ClassStat))
    {
        d->KartStates.RevEngine.unk[0] = 0;

        uVar6 = DECOMP_VehCalc_InterpBySpeed(
				d->KartStates.RevEngine.boostMeter,
				FPS_HALF(d->const_SacredFireSpeed / 3 + 3),
				d->const_SacredFireSpeed + d->const_AccelSpeed_ClassStat);

        d->KartStates.RevEngine.boostMeter = uVar6;
    }

    // if curr rev < 1
    if (d->KartStates.RevEngine.fireLevel < 1)
    {
        d->KartStates.RevEngine.unk[1] &= ~(2);

        // max rev = ???
        d->KartStates.RevEngine.boostMeter =
            d->const_AccelSpeed_ClassStat + d->const_SacredFireSpeed / 3;
    }

    // if curr rev >= 1
    else
    {

        // rev deacceleration rate = curr rev / 2
        uVar8 = d->KartStates.RevEngine.fireLevel >> 1;

        if ((d->KartStates.RevEngine.unk[1] & 2) == 0)
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
        iVar4 = d->KartStates.RevEngine.fireLevel - FPS_HALF(uVar8);

        // curr rev = new rev
        d->KartStates.RevEngine.fireLevel = iVar4;

        // if new rev < 1
        if (iVar4 < 1)
        {

            d->KartStates.RevEngine.unk590 = 0xc0;

            // curr rev = 0
            d->KartStates.RevEngine.fireLevel = 0;
        }
    }
    if (d->fireSpeed < 1)
    {
        d->KartStates.RevEngine.unk[1] &= ~(1);
    }

LAB_80067dec:

    if ((*(u_int *)&d->KartStates.RevEngine.unk590 & 0x200ffff) == 0)
    {

        // if curr rev < ???
        if (d->KartStates.RevEngine.fireLevel < d->const_AccelSpeed_ClassStat)
        {
            d->revEngineState = 0;
        }
        else
        {
            d->revEngineState = 1;
        }
    }
    else
    {
        d->revEngineState = 2;
    }

    iVar4 = d->const_AccelSpeed_ClassStat;

    // ??? = curr rev
    d->unk36E = d->KartStates.RevEngine.fireLevel;

    // if curr rev < ???
    if (d->KartStates.RevEngine.fireLevel < iVar4)
    {

        // 476 and 447 can be absolutely any value,
        // by default they are 15 and 30, but as long as
        // they are proportional (1 and 2, 4 and 8), they
        // behave the same as 15 and 30

        bVar1 = d->const_turboMaxRoom;

        // 477 changes when meter turns red
        local_18 = d->const_turboLowRoomWarning * 0x20 + 1;

        // min, max
        iVar7 = 0;
        iVar9 = iVar4;
    }
    else
    {
        // 477 changes when meter turns red
        bVar1 = d->const_turboLowRoomWarning;

        local_18 = 1;

        // min, max
        iVar7 = iVar4;
        iVar9 = iVar4 + d->const_SacredFireSpeed;
    }

    uVar3 = DECOMP_VehCalc_MapToRange
	(
		d->KartStates.RevEngine.fireLevel,
		iVar7, iVar9,
		(u_int)bVar1 << 5, local_18
	);

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