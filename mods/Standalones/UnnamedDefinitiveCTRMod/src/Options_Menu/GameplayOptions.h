////////////////// Options Menu //////////////////

#define UDCTRM_OM_GameplayMenuBG_w 400
#define UDCTRM_OM_GameplayMenuBG_x SCREEN_WIDTH/2 - 400/2
#define UDCTRM_OM_GameplayMenuBG_y SCREEN_HEIGHT/2 - 84/2 // add 10 to 84/2 every time you want to add a new row
#define UDCTRM_OM_GameplayNumRows 5

RECT UDCTRM_OM_GameplaymenuBG =
{
    .x = UDCTRM_OM_GameplayMenuBG_x,
    .y = UDCTRM_OM_GameplayMenuBG_y,
    .w = UDCTRM_OM_GameplayMenuBG_w,
    .h = 80 + 4, // ditto
};

RECT UDCTRM_OM_GameplaytitleSeparatorLine =
{
    .x = UDCTRM_OM_GameplayMenuBG_x,
    .y = UDCTRM_OM_GameplayMenuBG_y + 23,
    .w = UDCTRM_OM_GameplayMenuBG_w,
    .h = 2,
};

RECT UDCTRM_OM_Gameplayglowingcursor =
{
    .x = UDCTRM_OM_GameplayMenuBG_x + 3,
    .y = 0,
    .w = UDCTRM_OM_GameplayMenuBG_w - 6,
    .h = 9,
};