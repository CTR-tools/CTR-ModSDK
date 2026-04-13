#include <common.h>

void Level_SoundLoopSet(int *soundCount_ID, u_int soundID, u_int currVolume)
{
    int soundID;

    if (currVolume == 0)
    {
        if (*soundCount_ID != 0)
        {
            OtherFX_Stop1(*soundCount_ID);
            *soundCount_ID = 0;
        }
    }
    else
    {
        if (*soundCount_ID == 0)
        {
            soundID = OtherFX_Play_LowLevel(

                // sound ID
                soundID & 0xffff, 0,

                // volume
                (currVolume & 0xff) << 0x10 |

                // no distort, balance LR
                0x8080);

            // save soundID with soundCount
            *soundCount_ID = soundID;
        }
        // if already playing
        else
        {
            OtherFX_Modify(*soundCount_ID, (currVolume & 0xff) << 0x10 | 0x8080);
        }
    }
}