#include <common.h>

int DECOMP_TitleFlag_IsFullyOnScreen(void)
{
    // return true if flag is fully on screen
    // return false if flag is not fully on screen
    return (sdata->TitleFlag_Position == 0);
}