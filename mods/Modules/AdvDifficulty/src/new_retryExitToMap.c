#include <common.h>

extern struct MenuRow new_retryAdv[];
void UI_RaceEnd_MenuBoxFuncPtr(struct MenuBox*);

struct MenuBox new_retryExitToMap = {
    .stringIndexTitle = -1,
    .posX_curr = 256,
    .posY_curr = 170,
    .unk1 = 0,
    .state = CENTER_ON_COORDS | USE_SMALL_FONT | EXECUTE_FUNCPTR,
    .rows = new_retryAdv,
    .funcPtr = UI_RaceEnd_MenuBoxFuncPtr,
    .drawStyle = 4,
    .posX_prev = 256,
    .posY_prev = 170,
    .width = 209,
    .height = 32
};