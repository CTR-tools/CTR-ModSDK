#include "utils.h"

#include <common.h>

void MM_TrackSelect_MenuProc(struct RectMenu* menu)
{
    sdata->gameTracker.currLEV = CUSTOM_LEVEL_ID;
    D230.trackSel_transitionState = EXITING_MENU;
    sdata->ptrGhostTapePlaying = MEMPACK_AllocHighMem(0x3e00);
    memset(sdata->ptrGhostTapePlaying, 0, 0x28);
    sdata->boolReplayHumanGhost = 0;
    sdata->ptrDesiredMenu = &data.menuQueueLoadTrack;
    sdata->errorMessagePosIndex = 0;
}