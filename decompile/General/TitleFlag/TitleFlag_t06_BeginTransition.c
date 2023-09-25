#include <common.h>

void DECOMP_TitleFlag_BeginTransition(int direction)
{
    // Begin Transition on-screen
    if (direction == 1)
    {
        sdata->TitleFlag_LoadingTextAnimFrame = -1;

        sdata->TitleFlag_Position = 5000;

        sdata->TitleFlag_AnimationType = 0;
    }
	
    // Begin Transition off-screen
    else if (direction == 2)
    {
        TitleFlag_SetDrawOrder(0);

        sdata->TitleFlag_Position = 0;

        sdata->TitleFlag_AnimationType = direction;
    }

    // enable loading screen's checkered flag
    sdata->gGT->renderFlags |= 0x1000;
}