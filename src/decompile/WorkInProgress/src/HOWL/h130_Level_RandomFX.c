#include <common.h>

// water droplets in Roo's Tubes
void Level_RandomFX(int *param_1, u_int soundID, int param_3, uint param_4, int param_5)
{
    // deref
    int cooldown = *param_1;

    // if cooldown remains
    if (0 < cooldown)
    {
        // reduce cooldown
        *param_1 = cooldown - 1;
        cooldown = *param_1;
    }

    // if no cooldown
    if (cooldown == 0)
    {
        // inline audioRNG scramble
        sdata->audioRNG = ((sdata->audioRNG >> 3) + sdata->audioRNG * 0x20000000) * 5 + 1;

        //
        // 1000000 = echo
        // 0008080 = no distortion, and balance L/R
        OtherFX_Play_LowLevel(

            soundID & 0xffff, 0,

            // random volume
            ((sdata->audioRNG % 100 + 100) * param_5 >> 8 & 0xff) << 0x10 |

            // echo, no distort, balance LR
            0x1008080);

        // inline audioRNG scramble
        sdata->audioRNG = ((sdata->audioRNG >> 3) + sdata->audioRNG * 0x20000000) * 5 + 1;

        // if (param_4 == 0)
        // {
        //     trap(0x1c00);
        // }

        // set random cooldown to next sfx
        *param_1 = sdata->audioRNG % param_4 + param_3;
    }
}