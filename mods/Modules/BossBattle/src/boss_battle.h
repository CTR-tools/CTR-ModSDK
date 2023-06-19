#include "..\..\mods\include\helper_menu_box.h"

#define ROW_SINGLE 0
#define ROW_CUP 1
#define ROW_BOSS_BATTLE 2

struct MenuRow rows_boss[] =
{
    MENU_ROW(ROW_SINGLE, 351, ROW_BOSS_BATTLE,ROW_CUP,ROW_SINGLE,ROW_SINGLE),
    MENU_ROW_VERTICAL(ROW_CUP, 352, ROW_SINGLE, ROW_BOSS_BATTLE),
    MENU_ROW_VERTICAL(ROW_BOSS_BATTLE, 591, ROW_CUP, ROW_SINGLE),
    FINALIZER_ROW
};

struct MenuBox boss_battle_menu =
{
    .stringIndexTitle = 345,
    .posX_curr = 0,
    .posY_curr = 0,
    .unk1 = 0,
    .state = CENTER_ON_X | USE_SMALL_FONT | BIG_TEXT_IN_TITLE,
    .rows = rows_boss,
    .funcPtr = MM_MenuBox_BossBattle,
    .width = 171,
    .height = 86
};