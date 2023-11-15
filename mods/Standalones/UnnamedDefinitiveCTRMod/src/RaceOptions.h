#define NUM_ROWS 4
#define UDCTRM_RO_MenuBoxBG_w 350
#define UDCTRM_RO_MenuBoxBG_x SCREEN_WIDTH/2 - 350/2
#define UDCTRM_RO_MenuBoxBG_y SCREEN_HEIGHT/2 - 74/2

RECT UDCTRM_RO_menuBoxBG =
{
	.x = UDCTRM_RO_MenuBoxBG_x,
	.y = UDCTRM_RO_MenuBoxBG_y,
	.w = UDCTRM_RO_MenuBoxBG_w,
	.h = 70 + 4, 
};

RECT UDCTRM_RO_titleSeparatorLine =
{
	.x = UDCTRM_RO_MenuBoxBG_x,
	.y = UDCTRM_RO_MenuBoxBG_y + 23,
	.w = UDCTRM_RO_MenuBoxBG_w,
	.h = 2,
};

RECT UDCTRM_RO_glowingcursor =
{
	.x = UDCTRM_RO_MenuBoxBG_x + 3,
	.y = 0,
	.w = UDCTRM_RO_MenuBoxBG_w - 6,
	.h = 9,
};