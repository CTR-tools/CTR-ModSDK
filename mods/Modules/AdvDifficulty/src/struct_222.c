#include <common.h>
#include "macro.h"

void MenuProc_Difficulty(struct RectMenu*);
void UI_RaceEnd_MenuProc(struct RectMenu*);
extern struct MenuRow rows_extraDifficulty[];
extern struct MenuRow rows_advDifficulty[];

struct MenuRow new_retryArcade[] = 
{
    MENU_ROW(4, 4, 1, 0, 0),
    MENU_ROW(6, 0, 2, 1, 1),
    MENU_ROW(5, 1, 3, 2, 2),
    MENU_ROW(7, 2, 4, 3, 3),
    MENU_ROW(3, 3, 0, 4, 4),
    FINALIZER_ROW
};

struct MenuRow new_retryAdv[] =
{
        MENU_ROW(4, 2, 1, 0, 0),
        MENU_ROW(7, 0, 2, 1, 1),
        MENU_ROW(13, 1, 0, 2, 2),
        FINALIZER_ROW
};

struct RectMenu End_AdvRaceDifficulty = {
    #if BUILD == JpnRetail
    .stringIndexTitle = 354,
    #else
    .stringIndexTitle = 345,
    #endif
    .posX_curr = 256,
    .posY_curr = 170,
    .unk1 = 0,
    .state = CENTER_ON_COORDS | USE_SMALL_FONT | EXECUTE_FUNCPTR,
    .rows = rows_advDifficulty,
    .funcPtr = MenuProc_Difficulty,
    .width = 209,
    .height = 74
};

struct RectMenu End_arcadeDifficulty = {
    #if BUILD == JpnRetail
    .stringIndexTitle = 354,
    #else
    .stringIndexTitle = 345,
    #endif
    .posX_curr = 256,
    .posY_curr = 170,
    .unk1 = 0,
    .state = CENTER_ON_COORDS | USE_SMALL_FONT | EXECUTE_FUNCPTR,
    .rows = rows_extraDifficulty,
    .funcPtr = MenuProc_Difficulty,
    .width = 209,
    .height = 74
};

struct RectMenu new_retryExitToMap = {
    .stringIndexTitle = -1,
    .posX_curr = 256,
    .posY_curr = 170,
    .unk1 = 0,
    .state = CENTER_ON_COORDS | USE_SMALL_FONT | EXECUTE_FUNCPTR,
    .rows = new_retryAdv,
    .funcPtr = UI_RaceEnd_MenuProc,
    .drawStyle = 4,
    .posX_prev = 256,
    .posY_prev = 170,
    .width = 209,
    .height = 32
};