#include <common.h>

void DECOMP_Voiceline_ClearTimeStamp(void)
{
    for (char i = 0; i < 16; i++)
    {
        // Clear audio timestamps arrays
        sdata->timeSet1[i] = 0;
        sdata->timeSet2[i] = 0;
    }
}