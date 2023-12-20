#include <common.h>

#include "..\..\..\include\helper_menu_box.h"

////////////////// Options MenuBox //////////////////

void UDCTRM_OM_FuncPtr(struct MenuBox* mb);
void UDCTRM_OM_GameplayFuncPtr(struct MenuBox* mb);
void UDCTRM_OM_ControllerSFXFuncPtr(struct MenuBox* mb);

struct MenuRow UDCTRM_OM_MenuRows[] =
{
    MENU_ROW(0, 610, 0, 1, 0, 0),
    MENU_ROW(1, 606, 0, 1, 1, 1),
    FINALIZER_ROW
};

struct MenuBox UDCTRM_OM_MenuBox =
{
    .stringIndexTitle = -1,

    .posX_curr = 0,
    .posY_curr = 0,

    .unk1 = 0,

    .state = CENTER_ON_X | USE_SMALL_FONT | BIG_TEXT_IN_TITLE,

    .rows = UDCTRM_OM_MenuRows,

    .funcPtr = UDCTRM_OM_FuncPtr,

    .drawStyle = 0,

    .posX_prev = 0,
    .posY_prev = 0,

    .rowSelected = 0,

    .unk1c = 0,
    .unk1e = 0,

    .width = 171,
    .height = 86,

    .ptrNextBox_InHierarchy = 0,
    .ptrPrevBox_InHierarchy = 0,
};

struct MenuBox UDCTRM_OM_GameplayMenuBox =
{
    .stringIndexTitle = -1,

    .posX_curr = 0,
    .posY_curr = 0,

    .unk1 = 0,

    .state = DISABLE_INPUT_ALLOW_FUNCPTRS,

    .rows = 0,

    .funcPtr = UDCTRM_OM_GameplayFuncPtr,

    .drawStyle = 0,

    .posX_prev = 0,
    .posY_prev = 0,

    .rowSelected = 0,

    .unk1c = 0,
    .unk1e = 0,

    .width = 0,
    .height = 0,

    .ptrNextBox_InHierarchy = 0,
    .ptrPrevBox_InHierarchy = 0,
};

struct MenuBox UDCTRM_OM_ControllerSFXMenuBox =
{
    .stringIndexTitle = -1,

    .posX_curr = 0,
    .posY_curr = 0,

    .unk1 = 0,

    .state = DISABLE_INPUT_ALLOW_FUNCPTRS,

    .rows = 0,

    .funcPtr = UDCTRM_OM_ControllerSFXFuncPtr,

    .drawStyle = 0,

    .posX_prev = 0,
    .posY_prev = 0,

    .rowSelected = 0,

    .unk1c = 0,
    .unk1e = 0,

    .width = 0,
    .height = 0,

    .ptrNextBox_InHierarchy = 0,
    .ptrPrevBox_InHierarchy = 0,
};

////////////////// Main Menu Rows //////////////////

#define UDCTRM_MM_ROW_ADVENTURE 0
#define UDCTRM_MM_ROW_TIME_TRIAL 1
#define UDCTRM_MM_ROW_ARCADE 2
#define UDCTRM_MM_ROW_VERSUS 3
#define UDCTRM_MM_ROW_BATTLE 4
#define UDCTRM_MM_ROW_HIGH_SCORE 5
#define UDCTRM_MM_ROW_SCRAPBOOK 6
#define UDCTRM_MM_ROW_OPTIONS 7
#define UDCTRM_MM_NUM_ROWS 8

struct MenuRow UDCTRM_MM_MenuRows[] =
{
    MENU_ROW(UDCTRM_MM_ROW_ADVENTURE, 76, UDCTRM_MM_ROW_ADVENTURE, UDCTRM_MM_ROW_TIME_TRIAL, UDCTRM_MM_ROW_ADVENTURE, UDCTRM_MM_ROW_ADVENTURE),
    MENU_ROW(UDCTRM_MM_ROW_TIME_TRIAL, 77, UDCTRM_MM_ROW_ADVENTURE, UDCTRM_MM_ROW_ARCADE, UDCTRM_MM_ROW_TIME_TRIAL, UDCTRM_MM_ROW_TIME_TRIAL),
    MENU_ROW(UDCTRM_MM_ROW_ARCADE, 78, UDCTRM_MM_ROW_TIME_TRIAL, UDCTRM_MM_ROW_VERSUS, UDCTRM_MM_ROW_ARCADE, UDCTRM_MM_ROW_ARCADE),
    MENU_ROW(UDCTRM_MM_ROW_VERSUS, 79, UDCTRM_MM_ROW_ARCADE, UDCTRM_MM_ROW_BATTLE, UDCTRM_MM_ROW_VERSUS, UDCTRM_MM_ROW_VERSUS),
    MENU_ROW(UDCTRM_MM_ROW_BATTLE, 80, UDCTRM_MM_ROW_VERSUS, UDCTRM_MM_ROW_HIGH_SCORE, UDCTRM_MM_ROW_BATTLE, UDCTRM_MM_ROW_BATTLE),
    MENU_ROW(UDCTRM_MM_ROW_HIGH_SCORE, 81, UDCTRM_MM_ROW_BATTLE, 6, UDCTRM_MM_ROW_HIGH_SCORE, UDCTRM_MM_ROW_HIGH_SCORE),
    MENU_ROW(6, 14, UDCTRM_MM_ROW_HIGH_SCORE, 6, 6, 6),
    FINALIZER_ROW
};

struct MenuRow UDCTRM_MM_MenuRows_ScrapbookUnlocked[] =
{
    MENU_ROW(UDCTRM_MM_ROW_ADVENTURE, 76, UDCTRM_MM_ROW_ADVENTURE, UDCTRM_MM_ROW_TIME_TRIAL, UDCTRM_MM_ROW_ADVENTURE, UDCTRM_MM_ROW_ADVENTURE),
    MENU_ROW(UDCTRM_MM_ROW_TIME_TRIAL, 77, UDCTRM_MM_ROW_ADVENTURE, UDCTRM_MM_ROW_ARCADE, UDCTRM_MM_ROW_TIME_TRIAL, UDCTRM_MM_ROW_TIME_TRIAL),
    MENU_ROW(UDCTRM_MM_ROW_ARCADE, 78, UDCTRM_MM_ROW_TIME_TRIAL, UDCTRM_MM_ROW_VERSUS, UDCTRM_MM_ROW_ARCADE, UDCTRM_MM_ROW_ARCADE),
    MENU_ROW(UDCTRM_MM_ROW_VERSUS, 79, UDCTRM_MM_ROW_ARCADE, UDCTRM_MM_ROW_BATTLE, UDCTRM_MM_ROW_VERSUS, UDCTRM_MM_ROW_VERSUS),
    MENU_ROW(UDCTRM_MM_ROW_BATTLE, 80, UDCTRM_MM_ROW_VERSUS, UDCTRM_MM_ROW_HIGH_SCORE, UDCTRM_MM_ROW_BATTLE, UDCTRM_MM_ROW_BATTLE),
    MENU_ROW(UDCTRM_MM_ROW_HIGH_SCORE, 81, UDCTRM_MM_ROW_BATTLE, UDCTRM_MM_ROW_SCRAPBOOK, UDCTRM_MM_ROW_HIGH_SCORE, UDCTRM_MM_ROW_HIGH_SCORE),
    MENU_ROW(UDCTRM_MM_ROW_SCRAPBOOK, 564, UDCTRM_MM_ROW_HIGH_SCORE, UDCTRM_MM_ROW_OPTIONS, UDCTRM_MM_ROW_SCRAPBOOK, UDCTRM_MM_ROW_SCRAPBOOK),
    MENU_ROW(UDCTRM_MM_ROW_OPTIONS, 14, UDCTRM_MM_ROW_SCRAPBOOK, UDCTRM_MM_ROW_OPTIONS, UDCTRM_MM_ROW_OPTIONS, UDCTRM_MM_ROW_OPTIONS),
    FINALIZER_ROW
};