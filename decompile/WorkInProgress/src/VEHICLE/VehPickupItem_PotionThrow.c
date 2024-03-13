#include <common.h>

u_int VehPickupItem_PotionThrow(struct MineWeapon *potion, struct Instance *inst, u_int flags)
{
    int rng;
    short velX, velZ, rotZ;

    // For TNTs param3 != 0 shoots tnt up into air,
    // direction does not change (komodo joe)

    // For Potions
    // param3 & 1 shoots back a short distance
    // param3 & 2 shoots back a long distance
    // param3 & 4 shoots forward (hold up on d-pad)

    potion->velocity[1] = 0x30;
    potion->crateInst = NULL;
    potion->extraFlags |= 2; // potion is thrown
    
    rotZ = inst->matrix.m[2][2];

    // if you dont want to throw forward
    if ((flags & 4) == 0)
    {
        // if you dont want to throw back long
        if ((flags & 2) == 0)
        {
            // if you dont want to throw back short
            if ((flags & 1) == 0)
            {
                // just quit and drop weapon as-is
                return false;
            }

            // if you want to throw back short
            rng = (RngDeadCoed(&sdata->const_0x30215400) & 0x1f) - 0x10;
            velX = (short)(inst->matrix.m[0][2] * rng >> 12);
            velZ = (short)(rotZ * rng >> 12);
        }

        // if you want to throw back long
        else
        {
            velX = (short)(inst->matrix.m[0][2] * -0x78 >> 12);
            velZ = (short)(rotZ * -120 >> 12);
        }
    }

    // if you want to throw forward
    else
    {
        velX = (short)(inst->matrix.m[0][2] * 0xf >> 9);
        velZ = (short)(rotZ * 15 >> 9);
    }

    potion->velocity[0] = velX;
    potion->velocity[2] = velZ;
    return true;
}
