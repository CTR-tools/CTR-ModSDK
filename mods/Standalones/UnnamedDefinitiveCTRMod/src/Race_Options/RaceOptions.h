#define UDCTRM_RO_NUM_ROWS 4
#define UDCTRM_RO_MenuProcBG_w 350
#define UDCTRM_RO_MenuProcBG_x SCREEN_WIDTH/2 - 350/2
#define UDCTRM_RO_MenuProcBG_y SCREEN_HEIGHT/2 - 74/2

RECT UDCTRM_RO_menuBG =
{
	.x = UDCTRM_RO_MenuProcBG_x,
	.y = UDCTRM_RO_MenuProcBG_y,
	.w = UDCTRM_RO_MenuProcBG_w,
	.h = 70 + 4, 
};

RECT UDCTRM_RO_titleSeparatorLine =
{
	.x = UDCTRM_RO_MenuProcBG_x,
	.y = UDCTRM_RO_MenuProcBG_y + 23,
	.w = UDCTRM_RO_MenuProcBG_w,
	.h = 2,
};

RECT UDCTRM_RO_glowingcursor =
{
	.x = UDCTRM_RO_MenuProcBG_x + 3,
	.y = 0,
	.w = UDCTRM_RO_MenuProcBG_w - 6,
	.h = 9,
};