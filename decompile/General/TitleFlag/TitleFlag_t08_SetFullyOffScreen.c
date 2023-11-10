#include <common.h>

void DECOMP_TitleFlag_SetFullyOffScreen()
{
    sdata->TitleFlag_AnimationType = 0;
    sdata->TitleFlag_LoadingTextAnimFrame = -1;

    // flag is now fully off-screen
    sdata->TitleFlag_Position = 5000;

    // disable loading screen's checkered flag
    sdata->gGT->renderFlags &= ~(0x1000);
}