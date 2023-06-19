#include <common.h>

//is in loading screen?
force_inline bool global_IsLoading()
{
    return !(sdata->gGT->gameMode1 & LOADING);
}