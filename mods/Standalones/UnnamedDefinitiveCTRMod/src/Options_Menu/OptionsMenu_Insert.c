#include <common.h>

#include "..\..\..\include\helper_menu_box.h"

////////////////// Options Menu //////////////////

void UDCTRM_OM_FuncPtr(struct RectMenu* menu);
void UDCTRM_OM_GameplayFuncPtr(struct RectMenu* menu);
void UDCTRM_OM_ControllerSFXFuncPtr(struct RectMenu* menu);

struct MenuRow UDCTRM_OM_MenuRows[] =
{
    MENU_ROW(0, 610, 0, 1, 0, 0),
    MENU_ROW(1, 609, 0, 1, 1, 1),
    FINALIZER_ROW
};

struct RectMenu UDCTRM_OM_MenuProc =
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

struct RectMenu UDCTRM_OM_GameplayMenu =
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

struct RectMenu UDCTRM_OM_ControllerSFXMenu =
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

