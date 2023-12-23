#include <common.h>

void DECOMP_VehPtr_Drifting_Update(struct Thread *t, struct Driver *d)
{
    char cVar1;
    short noInputTime;
    int incrementReserves;
    int meter;
    int highMeter;
    struct GamepadBuffer* pad = &sdata->gGamepads->gamepad[d->driverID];

    // This is the distance remaining that can be filled
    meter = d->turbo_MeterRoomLeft;

    if ((pad->buttonsTapped & (BTN_R1 | BTN_L1)) == 0)
    {
        // If there is no room in the turbo meter left to fill
        if (meter == 0)
        {
            // If you have not attempted to boost 3 times in a row
            if (d->KartStates.Drifting.numBoostsAttempted < 3)
            {
                // set turbo meter to empty
                meter = d->const_turboMaxRoom << 5;
            }
        }

        // If the turbo meter is not full
        else
        {
            // decreaes the amoutn of room remaining, by elapsed milliseconds per frame, ~32
            meter -= sdata->gGT->elapsedTimeMS;

            // if the bar goes beyond full
            if (meter < 0)
            {
                // set bar to full
                meter = 0;
            }

            // If bar is full
            if (meter == 0)
            {
                // Make a sound
                OtherFX_Play_Echo(0xf, 1, ((d->actionsFlagSet & 0x10000) != 0));

                // Add to your number of boost attempts, this makes it
                // so you can't attempt to boost again until you release L1 + R1
                d->KartStates.Drifting.numBoostsAttempted += 3;
            }
        }
    }

    // If you do press L1 or R1
    else
    {
        // Set drift timer to zero, start the drift
        d->KartStates.Drifting.numFramesDrifting = 0;

        // If turbo meter is not empty
        if (meter != 0)
        {
            // const_turboLowRoomWarning
            // get length where turbo turns from green to red
            highMeter = d->const_turboLowRoomWarning << 5;

            // If distance remaining to be filled in turbo bar, is less than,
            // the distance remaining from the red/green "turning point" to the end,

            // If meter is in the red
            if (meter < highMeter)
            {
                // reserves_gain = map from old range to new range,
                // the more room remaining to fill, the less boost you get
                // old minMax: [zero -> const_turboLowRoomWarning]
                // new minMax: [const_turboFullBarReserveGain, -> zero]
                incrementReserves = MapToRange(meter, 0, highMeter, d->const_turboFullBarReserveGain << 5, 0);

                Turbo_Increment(

                    // driver
                    d,

                    // amount of reserves
                    incrementReserves,

                    2,

                    // fire level, bigger boost for attempt number (1,2, or 3)
                    d->KartStates.Drifting.numBoostsSuccess << 6);

                // increase the counter for number of times you've boosted in a row (0-3)
                d->KartStates.Drifting.numBoostsSuccess++;

                // if you've boosted less than 3 times in a row
                if (d->KartStates.Drifting.numBoostsSuccess < 3)
                {
                    // give a chance to boost again
                    d->actionsFlagSet |= 0x80;
                }

                // drift boost meter = constant
                d->KartStates.Drifting.driftBoostTimeMS = d->unk479 << 5;
            }

            // If meter is in the green
            else
            {
                // reset meter to beginning
                d->unk381 = 8;
            }

            meter = 0;

            // increase number of boost attempts (both success and failure)
            d->KartStates.Drifting.numBoostsAttempted++;
        }
    }

    d->turbo_MeterRoomLeft = meter;

    // 1.0 seconds
    noInputTime = 0x3c0;

    // If the "spin-out" constant is less than your drift counter
    if ((d->const_Drifting_FramesTillSpinout < d->KartStates.Drifting.numFramesDrifting) ||

        ((d->speedApprox < 0 &&
          (
              // 2.0 seconds
              noInputTime = 0x780,

              // if you're not on any turbo pad
              (d->stepFlagSet & 3) == 0))))
    {
        // Make the character spin out from too much drifting

        // Set amount of NoInput
        d->NoInputTimer = noInputTime;

        VehPtr_Spinning_Init(t, d);
    }

    // if you aren't spinning out
    else
    {
        // drift counter counts backwards during switchway drift: did switchway too long?
        if ((d->KartStates.Drifting.numFramesDrifting < -d->const_Drifting_FramesTillSpinout) ||

            // speed is less than half the driver's speed classStat
            (((d->speed < d->const_Speed_ClassStat >> 1 ||

               ((d->actionsFlagSet & 0x2028) != 0)) ||

              // If the gamepad input is...
              ((pad->buttonsHeldCurrFrame &

                // does not include the jump button that you used to start drifting
                d->buttonUsedToStartDrift) == 0))))
        {
            // Stop drifting, just drive
            VehPtr_Drifting_Finalize(t, d);
            VehPtr_Driving_Init(t, d);
        }
    }
}
