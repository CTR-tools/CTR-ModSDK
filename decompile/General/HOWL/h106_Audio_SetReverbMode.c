#include <common.h>

void DECOMP_Audio_SetReverbMode(int levelID, u_int isBossRace, int bossID)
{
    u_int reverb;
    // if audio is enabled
    if (sdata->boolAudioEnabled != false)
    {
        // If this is not a boss race
        if (isBossRace == 0)
        {
            // Level ID < 30
            // If Level ID is any level you can drive on,
            // including adventure maps
            if (levelID < INTRO_RACE_TODAY)
            {
                // get reverb based on level ID
                reverb = data.reverbMode[levelID];
            }

            // If this is not a level you can drive on:
            // menu, cutscene, etc
            else
            {
                reverb = 4;
            }
        }

        // If this is a boss race
        else
        {
            // if invalid bossID
            if (5 < bossID)
            {
                // quit
                return;
            }

            // get reverb based on boss
            reverb = sdata->reverbModeBossID[bossID];
        }

        DECOMP_SetReverbMode(reverb);
    }
}
