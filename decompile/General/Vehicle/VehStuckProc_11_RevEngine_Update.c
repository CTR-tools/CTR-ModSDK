#include <common.h>

void DECOMP_VehStuckProc_RevEngine_Update(struct Thread *t, struct Driver *d)
{
    int revFireLevel;

    // If race has not started
    if (d->KartStates.RevEngine.boolMaskGrab == false)
    {
        // If Traffic Lights are not done counting down
        if (sdata->gGT->trafficLightsTimer > SECONDS(0))
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