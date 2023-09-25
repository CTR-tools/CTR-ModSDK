#include <common.h>

void DECOMP_TitleFlag_SetFullyOnScreen()
{
    sdata->TitleFlag_AnimationType = 0;
    sdata->TitleFlag_LoadingTextAnimFrame = -1;
	
    // flag is now fully on-screen
    sdata->TitleFlag_Position = 0;

    // enable loading screen's checkered flag
    sdata->gGT->renderFlags |= 0x1000;
}