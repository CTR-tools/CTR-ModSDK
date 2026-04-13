#include <common.h>

void DECOMP_VehPhysProc_Driving_Update(struct Thread *t, struct Driver *d)
{
    // if racer touched the ground in this frame
    if ((d->actionsFlagSet & 2) != 0)
    {
        int simpTurnState = d->simpTurnState;

        // set Simplified Turning state to its own absolute value
        if (simpTurnState < 0)
        {
            simpTurnState = -simpTurnState;
        }

        // if steering hard enough to start a drift
        if (
			(
				((d->const_TurnRate + ((d->turnConst << 1) / 5) >> 1) < simpTurnState) &&
				
				// player has jump buttons held
				((sdata->gGamepads->gamepad[d->driverID].buttonsHeldCurrFrame) &
				d->buttonUsedToStartDrift) != 0
			) &&

            // player is not in accel prevention or braking and
            ((d->actionsFlagSet & 8) == 0) &&
            (d->const_Speed_ClassStat >> 1 <= d->speedApprox)
		  )
        {
            DECOMP_VehPhysProc_PowerSlide_Init(t,d);

            // exit the function
            return;
        }
    }

    // at this point, assume driver is not touching ground
    // if driver has been "Player_Driving" more than 0.1 seconds?
    if ((d->StartDriving_0x60 == 0) &&

        // if V_Shift happened too many times,
        // meaning you jitter between two quadblocks
        // in a "V" shape
        (4 < d->unknownTraction))
    {

        // Stop driving, until you press X, prevents jitters
        DECOMP_VehPhysProc_FreezeVShift_Init(t,d);
    }

    else
    {
        // if driver has been "rolling backwards" more than 0.64 seconds
        if (d->StartRollback_0x280 == 0)
        {
            // wipe
            d->unknownTraction = 0;
        }
    }
}
