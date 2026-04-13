#include <common.h>

int VehPhysCrash_Attack(struct Driver *driver1, struct Driver *driver2, int param_3, int param_4)
{
    // if driver (1) is not using mask weapon
    if ((driver1->actionsFlagSet & 0x800000) == 0)
    {
        // if driver (2) is using mask weapon
        if ((driver2->actionsFlagSet & 0x800000) != 0)
        {
            // param_1 was hit with a mask weapon
            driver1->ChangeState_param2 = 2;
            driver1->ChangeState_param4 = 6;
            driver1->ChangeState_param3 = driver2;

            if (((param_3 != 0) && (driver1->kartState != KS_BLASTED)) &&
                (driver1->invincibleTimer == 0))
            {
                OtherFX_DriverCrashing(

                    // if driver is supposed to echo
                    *(u_short *)((int)driver1 + 0x2ca) & 1,

                    0xff);

                // Make driver talk
                Voiceline_RequestPlay(1, data.characterIDs[driver1->driverID], 0x10);
            }
        }

        // if one driver has a bubble, and the other does not
        if ((driver2->instBubbleHold != 0) && (driver1->instBubbleHold == 0))
        {
            // driver -> bubbleInst -> thread -> object
            struct Shield *bubble = driver2->instBubbleHold->thread->object;

            bubble->flags |= 8;

            // clear bubbleInst pointer
            driver2->instBubbleHold = 0;

            driver1->ChangeState_param2 = 2;
            driver1->ChangeState_param4 = 0;
            driver1->ChangeState_param3 = driver2;

            if ((param_3 != 0) &&

                ((
                    // if driver is not blasted
                    driver1->kartState != KS_BLASTED &&

                    // if driver is not invincible
                    (driver1->invincibleTimer == 0))))
            {
                OtherFX_DriverCrashing(

                    // if driver is supposed to echo
                    (uint) * (u_short *)((int)driver1 + 0x2ca) & 1,

                    0xff);

                if (param_4 != 0)
                {
                    OtherFX_Play(0x4f, 1);
                }

                // Make driver talk
                Voiceline_RequestPlay(1, data.characterIDs[driver1->driverID], 0x10);
            }
        }

        // if one driver squished the other with turbo
        if (
            (
                (
                    // force that the drivers collided is high
                    (0xa00 < sdata->unk_8008d9f4[0]) &&

                    // attacking driver has reserves
                    (driver2->reserves != 0)) &&

                // attacking driver is using turbo weapon
                ((driver2->actionsFlagSet & 0x200) != 0)) &&

            // attacked driver has no reserves
            (driver1->reserves == 0))
        {
            // set forcedJump_trampoline on attacking driver
            driver2->forcedJump_trampoline = 2;

            // attacked driver has been squished by attacking driver,
            // this happens when one driver uses turbo weapon on another
            driver1->ChangeState_param2 = 3;
            driver1->ChangeState_param4 = 5;
            driver1->ChangeState_param3 = driver2;
        }
    }
    return param_3;
}