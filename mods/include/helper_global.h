#include <common.h>

//is in loading screen?
bool global_IsLoading()
{
    return !(sdata->gGT->gameMode1 & LOADING);
}