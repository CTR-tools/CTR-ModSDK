#include <common.h>

int DECOMP_RaceFlag_IsFullyOnScreen(void)
{
    // return true if flag is fully on screen
    // return false if flag is not fully on screen
    return (sdata->RaceFlag_Position == 0);
}