#include <common.h>

void DECOMP_RaceFlag_BeginTransition(int direction)
{
    // Begin Transition on-screen
    if (direction == 1)
    {
        sdata->RaceFlag_LoadingTextAnimFrame = -1;

        sdata->RaceFlag_Position = 5000;

        sdata->RaceFlag_AnimationType = 0;
    }
	
    // Begin Transition off-screen
    else if (direction == 2)
    {
        DECOMP_RaceFlag_SetDrawOrder(0);

        sdata->RaceFlag_Position = 0;

        sdata->RaceFlag_AnimationType = direction;
    }

    // enable loading screen's checkered flag
    sdata->gGT->renderFlags |= 0x1000;
}