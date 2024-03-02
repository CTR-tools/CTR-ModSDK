#include <common.h>

void DECOMP_MainFreeze_SafeAdvDestroy(void)
{
    if (
        // If you're in Adventure Arena
        ((sdata->gGT->gameMode1 & ADVENTURE_ARENA) != 0) &&

        // check if Adv Hub is loaded
        (DECOMP_LOAD_IsOpen_AdvHub() != 0))
    {
#ifndef REBUILD_PS1
        AH_Pause_Destroy();
#endif
    }
    return;
}