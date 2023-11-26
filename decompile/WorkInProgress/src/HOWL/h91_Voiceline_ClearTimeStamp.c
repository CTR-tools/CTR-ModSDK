#include <common.h>

void Voiceline_ClearTimeStamp(void)
{
    for (char i = 0; i < 16; i++)
    {
        // Clear audio timestamps arrays
        ((u_int *)0x80096244)[i] = 0;
        ((u_int *)0x80096284)[i] = 0;
    }
}