#include <common.h>

void CalculateVolumeFromDistance(uint *soundCount, uint soundID, int distance)
{
    uint vol;
    int distort;

    if (distance < 6000)
    {
        if ((*soundCount != 0) && ((*soundCount & 0xffff) != soundID))
        {
            OtherFX_Stop1(*soundCount);
            *soundCount = 0;
        }
        
        if (distance < 301)
        {
            // full volume
            vol = 0xff;
        }

        else
        {
            // Map distance from [close, far] to [loud, quiet]
            vol = MapToRange(distance, 300, 6000, 0xff, 0);
        }

        if (soundID != 0xffffffff)
        {
            if (*soundCount == 0)
            {
                vol = OtherFX_Play_LowLevel(
                    soundID & 0xffff, 0,
                    (vol & 0xff) << 0x10 |
                    // no distortion, balance L/R
                    0x8080);

                *soundCount = vol;
            }
            else
            {
                if (soundID == 0x89)
                {
                    distort = (sdata->gGT.frameTimer_VsyncCallback >> 2 & 0x7f) - 0x40;
                    if (distort < 0)
                    {
                        distort = -distort;
                    }
                    vol =

                        // volume
                        (vol & 0xff) << 0x10 |

                        // distortion
                        (distort + 100U & 0xff) << 8 |

                        // balance L/R
                        0x80;
                }
                else
                {
                    vol =

                        // volume
                        (vol & 0xff) << 0x10 |

                        // no distortion, balance L/R
                        0x8080;
                }

                OtherFX_Modify(*soundCount, vol);
            }
        }
    }
    // if distance is farther than 6000
    else
    {
        if (*soundCount != 0)
        {
            OtherFX_Stop1(*soundCount);
            *soundCount = 0;
        }
    }
}

void PlayWarppadSound(u_int distance)
{
    CalculateVolumeFromDistance(&sdata->soundFadeInput[0].soundID_soundCount, 0x98, distance);
}
