#include "..\..\..\include\helper_menu_box.h"


#define ROW_EASY 0
#define ROW_MEDIUM 1
#define ROW_HARD 2
#define ROW_SUPER_HARD 3
#define ROW_ULTRA_HARD 4
#define EXD_VALID_ROWS 5

struct MenuRow UDCTRM_ED_MenuRows[] =
{
    MENU_ROW(ROW_EASY, 346, ROW_EASY, ROW_MEDIUM, ROW_EASY, ROW_EASY),
    MENU_ROW(ROW_MEDIUM, 347, ROW_EASY, ROW_HARD, ROW_MEDIUM, ROW_MEDIUM),
    MENU_ROW(ROW_HARD, 348, ROW_MEDIUM, ROW_SUPER_HARD, ROW_HARD, ROW_HARD),
    MENU_ROW(ROW_SUPER_HARD, 605, ROW_HARD, ROW_ULTRA_HARD, ROW_SUPER_HARD, ROW_SUPER_HARD),
    MENU_ROW(ROW_ULTRA_HARD, 606, ROW_SUPER_HARD, ROW_ULTRA_HARD, ROW_ULTRA_HARD, ROW_ULTRA_HARD),
    FINALIZER_ROW
};

void UDCTRM_ED_FuncPtr(struct RectMenu* menu);

struct RectMenu UDCTRM_ED_MenuProc =
{
    .stringIndexTitle = 345,
    .posX_curr = 0,
    .posY_curr = 0,
    .unk1 = 0,
    .state = CENTER_ON_X | USE_SMALL_FONT | BIG_TEXT_IN_TITLE,
    .rows = UDCTRM_ED_MenuRows,
    .funcPtr = UDCTRM_ED_FuncPtr,
    .width = 171,
    .height = 86
};
