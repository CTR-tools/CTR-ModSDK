#include <common.h>
#include "macro.h"

extern struct MenuRow rows_advDifficulty[];

struct MenuRow new_advHub[] =
    {
        MENU_ROW(2, 4, 1, 0, 0),
        MENU_ROW(11, 0, 2, 1, 1),
        MENU_ROW(7, 1, 3, 2, 2),
        MENU_ROW(14, 2, 4, 3, 3),
        MENU_ROW(3, 3, 0, 4, 4),
        FINALIZER_ROW
    };

void MainFreeze_Difficulty(struct MenuBox *mb);

struct MenuBox AdvHubDifficulty = {
    .stringIndexTitle = 345,
    .posX_curr = 256,
    .posY_curr = 108,
    .unk1 = 0,
    .state = CENTER_ON_COORDS | ALL_PLAYERS_USE_MENU | USE_SMALL_FONT | BIG_TEXT_IN_TITLE | EXECUTE_FUNCPTR,
    .rows = rows_advDifficulty,
    .funcPtr = MainFreeze_Difficulty,
    .width = 209,
    .height = 74};