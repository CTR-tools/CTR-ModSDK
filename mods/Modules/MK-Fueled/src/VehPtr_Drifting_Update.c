#include <common.h>

void DECOMP_VehPhysProc_PowerSlide_Update(struct Thread *t, struct Driver *d)
{
    char turbo_level;
    int meterLeft;
    struct GamepadBuffer *pad = &sdata->gGamepads->gamepad[d->driverID];

    // This is the distance remaining that can be filled
    meterLeft = d->turbo_MeterRoomLeft;
    u_short empty = (d->const_turboMaxRoom << 5);

    if ((pad->buttonsTapped & (BTN_R1 | BTN_L1)) == 0)
    {
        turbo_level = d->KartStates.Drifting.numBoostsSuccess;

        // if still drifting
        if ((pad->buttonsReleased & d->buttonUsedToStartDrift) == 0)
        {
            // if (turbo_level)
            // {
            //     MATRIX *currMatrix = &d->instSelf->matrix;
            //     gte_SetRotMatrix(currMatrix);
            //     gte_SetTransMatrix(currMatrix);

            //     struct ParticleEmitter *emset = (sdata->gGT->timer & 1) ? SparksR[turbo_level - 1] : SparksL[turbo_level - 1];

            //     // Tire Sparks
            //     VehEmitter_Terrain_Ground(d, emset);
            // }

            if (turbo_level < 3)
            {
                short turn = d->turnAngleCurr;
                turn = (turn < 0) ? -turn : turn;
                meterLeft -= VehCalc_MapToRange(turn, 0, 1080, 0, 48);

                // if the bar is full or beyond
                if (meterLeft <= 0)
                {
                    // Make a sound
                    OtherFX_Play_Echo(0xf, 1, d->actionsFlagSet & 0x10000);
                    // mini-turbo level up
                    turbo_level++;
                    // reset bar to beginning
                    meterLeft = empty;
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
                VehFire_Increment(
                    // driver
                    d,
                    // amount of reserves
                    1440 * turbo_level,
                    // turbo type
                    TURBO_PAD,
                    // fire level
                    167 * turbo_level);
                // reset turbo_level
                turbo_level = 0;
                meterLeft = empty;
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
        VehPhysProc_PowerSlide_Finalize(t, d);
        VehPhysProc_Driving_Init(t, d);
    }
}