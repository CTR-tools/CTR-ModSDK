#include <common.h>

void DECOMP_RaceFlag_SetFullyOnScreen()
{
    sdata->RaceFlag_AnimationType = 0;
    sdata->RaceFlag_LoadingTextAnimFrame = -1;
	
    // flag is now fully on-screen
    sdata->RaceFlag_Position = 0;

    // enable loading screen's checkered flag
    sdata->gGT->renderFlags |= 0x1000;
}