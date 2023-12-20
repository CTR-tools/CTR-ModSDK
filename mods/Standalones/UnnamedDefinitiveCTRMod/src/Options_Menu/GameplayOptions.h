////////////////// Options MenuBox //////////////////

#define UDCTRM_OM_GameplayMenuBoxBG_w 350
#define UDCTRM_OM_GameplayMenuBoxBG_x SCREEN_WIDTH/2 - 350/2
#define UDCTRM_OM_GameplayMenuBoxBG_y SCREEN_HEIGHT/2 - 74/2

RECT UDCTRM_OM_GameplaymenuBoxBG =
{
    .x = UDCTRM_OM_GameplayMenuBoxBG_x,
    .y = UDCTRM_OM_GameplayMenuBoxBG_y,
    .w = UDCTRM_OM_GameplayMenuBoxBG_w,
    .h = 70 + 4, 
};

RECT UDCTRM_OM_GameplaytitleSeparatorLine =
{
    .x = UDCTRM_OM_GameplayMenuBoxBG_x,
    .y = UDCTRM_OM_GameplayMenuBoxBG_y + 23,
    .w = UDCTRM_OM_GameplayMenuBoxBG_w,
    .h = 2,
};

RECT UDCTRM_OM_Gameplayglowingcursor =
{
    .x = UDCTRM_OM_GameplayMenuBoxBG_x + 3,
    .y = 0,
    .w = UDCTRM_OM_GameplayMenuBoxBG_w - 6,
    .h = 9,
};