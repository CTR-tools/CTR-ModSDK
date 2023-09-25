#include <common.h>

int DECOMP_TitleFlag_IsFullyOffScreen(void)
{
    // return false, "not true", if flag is < 5000, partially on-screen
    // return true, "not false", if flag is >= 5000, fully off-screen
    return ((sdata->TitleFlag_Position + 4999U) < 9999) ^ 1;
}