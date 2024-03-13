#include <common.h>

void CalculateVolumeFromDistance(u_int *soundCount_ID, u_int soundID, int distance)
{
    u_int volume;
    u_int soundFlag;
    int distort;

    if (distance < 6000)
    {
        if ((*soundCount_ID != 0) && ((*soundCount_ID & 0xffff) != soundID))
        {
            OtherFX_Stop1(*soundCount_ID);
            *soundCount_ID = 0;
        }
        
        if (distance < 301)
        {
            // full volume
            volume = 255;
        }

        else
        {
            // Map distance from [close, far] to [loud, quiet]
            volume = DECOMP_VehCalc_MapToRange(distance, 300, 6000, 0xff, 0);
        }

        if (soundID != -1)
        {
            if (*soundCount_ID == 0)
            {
                soundID = OtherFX_Play_LowLevel(
                    soundID & 0xffff, 0,
                    (volume & 0xff) << 0x10 |
                    // no distortion, balance L/R
                    0x8080);

                *soundCount_ID = soundID;
            }
            else
            {
                if (soundID == 137)
                {
                    distort = (sdata->gGT->frameTimer_VsyncCallback >> 2 & 0x7f) - 0x40;
                    if (distort < 0)
                    {
                        distort = -distort;
                    }
                    soundFlag =

                        // volume
                        (volume & 0xff) << 0x10 |

                        // distortion
                        (distort + 100U & 0xff) << 8 |

                        // balance L/R
                        0x80;
                }
                else
                {
                    soundFlag =

                        // volume
                        (volume & 0xff) << 0x10 |

                        // no distortion, balance L/R
                        0x8080;
                }

                OtherFX_Modify(*soundCount_ID, soundFlag);
            }
        }
    }
    // if distance is farther than 6000
    else
    {
        if (*soundCount_ID != 0)
        {
            OtherFX_Stop1(*soundCount_ID);
            *soundCount_ID = 0;
        }
    }
}
