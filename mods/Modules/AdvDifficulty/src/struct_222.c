#include <common.h>
#include "macro.h"

void Retry_Difficulty(struct MenuBox*);
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

struct MenuBox End_AdvRaceDifficulty = {
    .stringIndexTitle = 345,
    .posX_curr = 256,
    .posY_curr = 170,
    .unk1 = 0,
    .state = CENTER_ON_COORDS | USE_SMALL_FONT | EXECUTE_FUNCPTR,
    .rows = rows_advDifficulty,
    .funcPtr = Retry_Difficulty,
    .width = 209,
    .height = 74
};

struct MenuBox End_arcadeDifficulty = {
    .stringIndexTitle = 345,
    .posX_curr = 256,
    .posY_curr = 170,
    .unk1 = 0,
    .state = CENTER_ON_COORDS | USE_SMALL_FONT | EXECUTE_FUNCPTR,
    .rows = rows_extraDifficulty,
    .funcPtr = Retry_Difficulty,
    .width = 209,
    .height = 74
};