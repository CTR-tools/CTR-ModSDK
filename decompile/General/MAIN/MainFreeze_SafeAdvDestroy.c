#include <common.h>

void DECOMP_MainFreeze_SafeAdvDestroy(void)
{
    if (
        // If you're in Adventure Arena
        ((sdata->gGT->gameMode1 & ADVENTURE_ARENA) != 0) &&

        // check if Adv Hub is loaded
        (LOAD_IsOpen_AdvHub() != 0))
    {
        AH_Pause_Destroy();
    }
    return;
}