#include <common.h>

void DECOMP_VehPtr_Drifting_Update(struct Thread *t, struct Driver *d)
{
    short reserves[3] = {1100, 2250, 3300};
    short fireLevel[3] = {384, 509, 634};
    char turbo_level;
    int incrementReserves;
    int meterLeft;
    int highMeter;
    struct GamepadBuffer *pad = &sdata->gGamepads->gamepad[d->driverID];

    // This is the distance remaining that can be filled
    meterLeft = d->turbo_MeterRoomLeft;
#define EMPTY_METER (d->const_turboMaxRoom << 5)

    if ((pad->buttonsTapped & (BTN_R1 | BTN_L1)) == 0)
    {
        turbo_level = d->KartStates.Drifting.numBoostsSuccess;
        // if still drifting
        if ((pad->buttonsReleased & (BTN_R1 | BTN_L1)) == 0)
        {
            if (turbo_level < 3)
            {
                meterLeft -= sdata->gGT->elapsedTimeMS;

                // if the bar is full or beyond
                if (meterLeft <= 0)
                {
                    // Make a sound
                    OtherFX_Play_Echo(0xf, 1, ((d->actionsFlagSet & 0x10000) != 0));
                    // mini-turbo level up
                    turbo_level++;
                    // reset bar to beginning
                    meterLeft = EMPTY_METER;
                }
            }
            else
            {
                // stay at full bar
                meterLeft = 1;
            }
        }
        // you released L1 / R1 after drifting.
        else
        {
            // if you haven't filled the turbo at least 1x
            if ((turbo_level == 0) && (meterLeft > 0))
            {
                // reset meter to beginning
                d->unk381 = 8;
            }
            else
            {
                // Mini-Turbo
                Turbo_Increment(
                    // driver
                    d,
                    // amount of reserves
                    reserves[turbo_level - 1],
                    // turbo type
                    POWER_SLIDE_HANG_TIME,
                    // fire level
                    fireLevel[turbo_level - 1]);
                // reset turbo_level
                turbo_level = 0;
                meterLeft = EMPTY_METER;
            }
        }
        d->KartStates.Drifting.numBoostsSuccess = turbo_level;
    }

    // If you do press L1 or R1
    else
    {
        // Set drift timer to zero, start the drift
        d->KartStates.Drifting.numFramesDrifting = 0;
    }

    d->turbo_MeterRoomLeft = meterLeft;

    if ( // speed is less than half the driver's speed classStat
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