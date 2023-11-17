#include <common.h>

void DECOMP_MM_MENUBOX_Main();
void DECOMP_MM_MENUBOX_1p2p();
void DECOMP_MM_MENUBOX_2p3p4p();
void DECOMP_MM_MENUBOX_Difficulty();
void DECOMP_MM_MENUBOX_SingleCup();
void DECOMP_MM_MENUBOX_NewLoad();
void DECOMP_MM_Characters_MenuBox();
void DECOMP_MM_TrackSelect_MenuBox();
void DECOMP_MM_CupSelect_MenuBox();
void DECOMP_MM_Battle_MenuBox();
void DECOMP_MM_HighScore_MenuBox();
void DECOMP_MM_Scrapbook_PlayMovie();
void DECOMP_MM_Battle_CloseSubMenu();

struct OverlayDATA_230 D230 =
{
	// MAIN MENU CONSTS
	
	.rows_mainMenu_Basic =
	{
		{0x4C, 0,1,0,0},
		{0x4D, 0,2,1,1},
		{0x4E, 1,3,2,2},
		{0x4F, 2,4,3,3},
		{0x50, 3,5,4,4},
		{0x51, 4,5,5,5},
		{-1},
	},
	
	.rows_mainMenu_WithScrapbook =
	{
		{0x4C, 0,1,0,0},
		{0x4D, 0,2,1,1},
		{0x4E, 1,3,2,2},
		{0x4F, 2,4,3,3},
		{0x50, 3,5,4,4},
		{0x51, 4,6,5,5},
		{0x234,5,6,6,6},
		{-1},
	},
	
	.menubox_mainMenu =
	{
		.stringIndexTitle = -1,
		
		.posX_curr = 0x180,
		.posY_curr = 0x6c,
		
		.state = 0x2b,
		.rows = &D230.rows_mainMenu_Basic,
		.funcPtr = DECOMP_MM_MENUBOX_Main,
		
		.unk1e = 1,
	},
	
	.rows_players1P2P =
	{
		{0x54,   0,1,0,0},
		{0x8055, 0,1,1,1},
		{-1},
	},
	
	.menubox_players1P2P =
	{
		.stringIndexTitle = 0x53,
		
		.state = 9,
		.rows = &D230.rows_players1P2P,
		.funcPtr = DECOMP_MM_MENUBOX_1p2p,	
	},
	
	.rows_players2P3P4P =
	{
		{0x8055, 0,1,0,0},
		{0x8056, 0,2,1,1},
		{0x8057, 1,2,2,2},
		{-1},
	},
	
	.menubox_players2P3P4P =
	{
		.stringIndexTitle = 0x53,
		
		.state = 9,
		.rows = &D230.rows_players2P3P4P,
		.funcPtr = DECOMP_MM_MENUBOX_2p3p4p,	
	},
	
	.rows_difficulty =
	{
		{0x15A, 0,1,0,0},
		{0x15B, 0,2,1,1},
		{0x15C, 1,2,2,2},
		{-1},
	},
	
	.menubox_difficulty =
	{
		.stringIndexTitle = 0x159,
		
		.state = 1,
		.rows = &D230.rows_difficulty,
		.funcPtr = DECOMP_MM_MENUBOX_Difficulty,	
	},
	
	.rows_raceType =
	{
		{0x15E, 0,1,0,0},
		{0x15F, 0,1,1,1},
		{-1},
	},
	
	.menubox_raceType =
	{
		.stringIndexTitle = 0x15D,
		
		.state = 1,
		.rows = &D230.rows_raceType,
		.funcPtr = DECOMP_MM_MENUBOX_SingleCup,	
	},
	
	.rows_adventure =
	{
		{0x8d, 0,1,0,0},
		{0x8e, 0,1,1,1},
		{-1},
	},
	
	.menubox_adventure =
	{
		.stringIndexTitle = -1,
		
		.state = 9,
		.rows = &D230.rows_adventure,
		.funcPtr = DECOMP_MM_MENUBOX_NewLoad,	
	},

#if 0
	.langIndex = {2,3,4,5,6,7},

	.rows_language = 
	{
		{0x85, 0,1,0,0},
		{0x86, 0,2,1,1},
		{0x87, 1,3,2,2},
		{0x88, 2,4,3,3},
		{0x89, 3,5,4,4},
		{0x8a, 4,5,5,5},
		{-1}
	},

	.menubox_language = 
	{
		.stringIndexTitle = -1,
		
		.state = 0x400001,
		.rows = &D230.rows_lngBoot,
		.funcPtr = DECOMP_MM_MENUBOX_Language
	},

#endif
	
	.menubox_characterSelect =
	{
		.stringIndexTitle = -1,
		
		.state = 0x28,
		.funcPtr = DECOMP_MM_Characters_MenuBox,
	},
	
	.menubox_trackSelect =
	{
		.stringIndexTitle = -1,
		
		.state = 0x28,
		.funcPtr = DECOMP_MM_TrackSelect_MenuBox,
	},
	
	.rows_cupSelect =
	{
		{0, 0,2,0,1},
		{0, 1,3,0,1},
		{0, 0,2,2,3},
		{0, 1,3,2,3},
		{-1}
	},
	
	.menubox_cupSelect =
	{
		.stringIndexTitle = -1,
		
		.state = 0x2408,
		.rows = &D230.rows_cupSelect,
		.funcPtr = DECOMP_MM_CupSelect_MenuBox,	
	},
	
	.menubox_battleWeapons =
	{
		.stringIndexTitle = -1,
		
		.state = 0x28,
		.funcPtr = DECOMP_MM_Battle_MenuBox,
	},
	
	.menubox_highScores =
	{
		.stringIndexTitle = -1,
		
		.state = 0x28,
		.funcPtr = DECOMP_MM_HighScore_MenuBox,
	},
	
	.menubox_scrapbook =
	{
		.stringIndexTitle = -1,
		
		.state = 0x20,
		.funcPtr = DECOMP_MM_Scrapbook_PlayMovie,
	},
	
	.ptrMenuBoxes =
	{
		&D230.menubox_mainMenu,
		&D230.menubox_players1P2P,
		&D230.menubox_players2P3P4P,
		&D230.menubox_adventure,
		&D230.menubox_characterSelect,
		&D230.menubox_trackSelect,
		&D230.menubox_cupSelect,
		&D230.menubox_battleWeapons,
		&D230.menubox_highScores
	},
	
	.titleInstances =
	{
		{0x68, 0x4e, 0xe6, 0},
		{0x66, 0, 0xe6, 1},
		{0x67, 0x14, 0xe6, 0},
		{0x69, 0x4e, 0xe6, 0},
		{0x6a, 0x8c, 0xe6, 0},
		{0x6b, 0xd7, 0xe6, 0}
	},
	
	.titleCameraPos = {0x32, 0xFFE2, 0x64, 0},
	.titleCameraRot = {0, 0xFF9C, 0, 0},
	
	.title_numFrameTotal = 0xC,
	.title_numTransition = 8,
	
	.title_mainPosX = 0x180,
	.title_mainPosY = 0x6c,
	
	.title_advPosX = 0,
	.title_advPosY = 0,
	.title_racePosX = 0,
	.title_racePosY = 0,
	.title_plyrPosX = 0,
	.title_plyrPosY = 0,
	.title_diffPosX = 0,
	.title_diffPosY = 0,
	
	.title_camPos = {0x32, 0xFFE2, 0x64, 0},
	
	.transitionMeta_Menu =
	{
		{512, 0, 0, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 2, 0, 0},
		{0, 0, 3, 0, 0},
		{0x4B0, 0xFFE2, 0, 0, 0},
		{0x64, 0xC8, 0, 0, 0},
		{0, 0, -1, 0, 0},
	},
	
	.titleSounds =
	{
		{0x94, 0x9B},
		{0x9E, 0x9C},
		{0xAA, 0x9D},
		{0xB4, 0x9E},
		{0x6C, 0x9F},
		{0x49, 0xA0},
		{0x84, 0xA1},
		{0xC8, 0xA2},
	},
	
	// these are rewritten in MM_CheatCodes
	.cheatButtonEntry = {0},
	
	.cupDifficultyUnlockFlags = {-1, 0xC, 0x10, 0},
	.cupDifficultyLngIndex = {0x15A, 0x15B, 0x15C, 0},
	.cupDifficultySpeed = {0x50, 0xA0, 0xF0},
	
	// CHARACTER SELECT CONSTS
	
	.characterSelectWindowPos =
	{
		// 1P full menu
		{0x7F, 0xA},
		
		// 1P small menu
		{0x4D, 0x1E}, 
		
		// 2P full menu
		{0xA, 0xA},
		{0x101, 0xA},
		
		// 2P small menu
		{0x1E, 0x1E},
		{0x100, 0x1E},
		
		// 3P menu
		{0x136, 0x4},
		{0x136, 0x4A},
		{0x136, 0x90},
		
		// 4P menu
		{0x15, 0x1},
		{0x13F, 0x1},
		{0x15, 0x95},
		{0x13F, 0x95},
	},
	
	.ptrSelectWindowPos =
	{
		// full menus, 1p2p3p4p
		&D230.characterSelectWindowPos[0],
		&D230.characterSelectWindowPos[2],
		&D230.characterSelectWindowPos[6],
		&D230.characterSelectWindowPos[9],
		
		// small menus, 1p2p
		&D230.characterSelectWindowPos[1],
		&D230.characterSelectWindowPos[4],
	},
	
	.windowW =
	{
		0xF6, 0xD6, 0xA0, 0xA0, 0x15A, 0xD6
	},
	
	.windowH =
	{
		0x50, 0x50, 0x40, 0x40, 0x5C, 0x5C
	},
	
	.driverPosZ =
	{
		0xC8, 0xC8, 0xFa, 0xFa, 0xAA, 0xAA
	},
	
	.driverPosY =
	{
		0x28, 0x28, 0x28, 0x28, 0x28, 0x28
	},
	
	.textPosArr =
	{
		0x46, 0x46, 0x36, 0x36, 0x52, 0x52
	},

	.csm_1P2P_limited = 
	{
		// Crash
		{0x80, 0x80,  {0, 4,8,1}, 0, 0xFFFF},
		// Cortex
		{0xC0, 0x80,  {1, 5,0,2}, 1, 0xFFFF},
		// Tiny
		{0x100, 0x80, {2,6,1,3}, 2, 0xFFFF},
		// Coco
		{0x140, 0x80, {3,7,2,9}, 3, 0xFFFF},
		// N. Gin
		{0x80, 0xA7,  {0,12,10,5}, 4, 0xFFFF},
		// Dingo
		{0xC0, 0xA7,  {1,13,4,6}, 5, 0xFFFF},
		// Polar
		{0x100, 0xA7, {2,14,5,7}, 6, 0xFFFF},
		// Pura
		{0x140, 0xA7, {3,14,6,11}, 7, 0xFFFF},
		// N. Tropy
		{0x40, 0x80,  {8,10,8,0}, 12, 0x5},
		// Pinstripe
		{0x180, 0x80, {9,11,3,9}, 8, 0xA},
		// Roo
		{0x40, 0xA7,  {8,10,10,4}, 10, 0x7},
		// Papu
		{0x180, 0xA7, {9,11,7,11}, 9, 0x8},
		// Komodo Joe
		{0xA0, 0xCE,  {4,12,12,13}, 11, 0x9},
		// Penta
		{0xE0, 0xCE,  {5,13,12,14}, 13, 0x6},
		// Fake Crash
		{0x120, 0xCE, {6,14,13,14}, 14, 0xB}
	},

	.csm_1P2P = 
	{
		// Crash
		{0x80, 0x60,  {0,4,8,1}, 0, 0xFFFF},
		// Cortex
		{0xC0, 0x60,  {1,5,0,2}, 1, 0xFFFF},
		// Tiny
		{0x100, 0x60, {2,6,1,3}, 2, 0xFFFF},
		// Coco
		{0x140, 0x60, {3,7,2,9}, 3, 0xFFFF},
		// N. Gin
		{0x80, 0x87,  {0,12,10,5}, 4, 0xFFFF},
		// Dingo
		{0xC0, 0x87,  {1,13,4,6}, 5, 0xFFFF},
		// Polar
		{0x100, 0x87, {2,14,5,7}, 6, 0xFFFF},
		// Pura
		{0x140, 0x87, {3,14,6,11}, 7, 0xFFFF},
		// N. Tropy
		{0x40, 0x60,  {8,10,8,0}, 12, 0x5},
		// Pinstripe
		{0x180, 0x60, {9,11,3,9}, 8, 0xA},
		// Roo
		{0x40, 0x87,  {8,10,10,4}, 10, 0x7},
		// Papu
		{0x180, 0x87, {9,11,7,11}, 9, 0x8},
		// Komodo Joe
		{0xA0, 0xAE,  {4,12,12,13}, 11, 0x9},
		// Penta
		{0xE0, 0xAE,  {5,13,12,14}, 13, 0x6},
		// Fake Crash
		{0x120, 0xAE, {6,14,13,14}, 14, 0xB}
	},

	.csm_3P = 
	{
		// Crash
		{0x20, 0x47,  {12,4,0,1}, 0, 0xFFFF},
		// Cortex
		{0x60, 0x47,  {13,5,0,2}, 1, 0xFFFF},
		// Tiny
		{0xA0, 0x47,  {14,6,1,3}, 2, 0xFFFF},
		// Coco
		{0xE0, 0x47,  {14,7,2,3}, 3, 0xFFFF},
		// N. Gin
		{0x20, 0x6E,  {0,8,4,5}, 4, 0xFFFF},
		// Dingo
		{0x60, 0x6E,  {1,9,4,6}, 5, 0xFFFF},
		// Polar
		{0xA0, 0x6E,  {2,10,5,7}, 6, 0xFFFF},
		// Pura
		{0xE0, 0x6E,  {3,11,6,7}, 7, 0xFFFF},
		// N. Tropy
		{0x20, 0x95,  {4,8,8,9}, 12, 0x5},
		// Pinstripe
		{0x60, 0x95,  {5,9,8,10}, 8, 0xA},
		// Roo
		{0xA0, 0x95,  {6,10,9,11}, 10, 0x7},
		// Papu
		{0xE0, 0x95,  {7,11,10,11}, 9, 0x8},
		// Komodo Joe
		{0x40, 0x20,  {12,1,12,13}, 11, 0x9},
		// Penta
		{0x80, 0x20,  {13,2,12,14}, 13, 0x6},
		// Fake Crash
		{0xC0, 0x20,  {14,3,13,14}, 14, 0xB}
	},

	.csm_4P = 
	{
		// Crash
		{0x80, 0x47,  {0,4,10,1}, 0, 0xFFFF},
		// Cortex
		{0xC0, 0x47,  {14,5,0,2}, 1, 0xFFFF},
		// Tiny
		{0x100, 0x47,  {14,6,1,3}, 2, 0xFFFF},
		// Coco
		{0x140, 0x47,  {3,7,2,11}, 3, 0xFFFF},
		// N. Gin
		{0x80, 0x6E,  {0,4,12,5}, 4, 0xFFFF},
		// Dingo
		{0xC0, 0x6E,  {1,8,4,6}, 5, 0xFFFF},
		// Polar
		{0x100, 0x6E,  {2,9,5,7}, 6, 0xFFFF},
		// Pura
		{0x140, 0x6E,  {3,7,6,13}, 7, 0xFFFF},
		// N. Tropy
		{0xC0, 0x95,  {5,8,8,9}, 12, 0x5},
		// Fake Crash
		{0x100, 0x95,  {6,9,8,9}, 14, 0xB},
		// Roo
		{0x40, 0x47,  {10,12,10,0}, 10, 0x7},
		// Papu
		{0x180, 0x47,  {11,13,3,11}, 9, 0x8},
		// Komodo Joe
		{0x40, 0x6E,  {10,12,12,4}, 11, 0x9},
		// Pinstripe
		{0x180, 0x6E,  {11,13,7,13}, 8, 0xA},
		// Penta
		{0xE0, 0x20,  {14,1,14,14}, 13, 0x6}
	},
	
	.ptrCsmArr = 
	{
		&D230.csm_1P2P,
		&D230.csm_1P2P,
		&D230.csm_3P,
		&D230.csm_4P,
		&D230.csm_1P2P_limited,
		&D230.csm_1P2P_limited
	},

	.characterIcon = 
	{
		-1, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	},

	.transitionMeta_csm_1P2P = 
	{
		{0, 0xC8, 6, 0, 0},
		{0, 0xC8, 5, 0, 0},
		{0, 0xC8, 4, 0, 0},
		{0, 0xC8, 3, 0, 0},
		{0, 0xC8, 5, 0, 0},
		{0, 0xC8, 4, 0, 0},
		{0, 0xC8, 3, 0, 0},
		{0, 0xC8, 2, 0, 0},
		{0, 0xC8, 7, 0, 0},
		{0, 0xC8, 1, 0, 0},
		{0, 0xC8, 6, 0, 0},
		{0, 0xC8, 0, 0, 0},
		{0, 0xC8, 4, 0, 0},
		{0, 0xC8, 3, 0, 0},
		{0, 0xC8, 2, 0, 0},
		{-512, 0, 2, 0, 0},
		{512, 0, 3, 0, 0},
		{512, 0, 1, 0, 0},
		{512, 0, 7, 0, 0},
		{512, 0, 5, 0, 0},
		{0, 0, -1, 0, 0},
	},

	.transitionMeta_csm_3P = 
	{
		{-512, 0, 2, 0, 0},
		{-512, 0, 3, 0, 0},
		{-512, 0, 4, 0, 0},
		{-512, 0, 5, 0, 0},
		{-512, 0, 1, 0, 0},
		{-512, 0, 2, 0, 0},
		{-512, 0, 3, 0, 0},
		{-512, 0, 4, 0, 0},
		{-512, 0, 0, 0, 0},
		{-512, 0, 1, 0, 0},
		{-512, 0, 2, 0, 0},
		{-512, 0, 3, 0, 0},
		{-512, 0, 2, 0, 0},
		{-512, 0, 3, 0, 0},
		{-512, 0, 4, 0, 0},
		{-512, 0, 0, 0, 0},
		{512, 0, 5, 0, 0},
		{512, 0, 3, 0, 0},
		{512, 0, 1, 0, 0},
		{512, 0, 5, 0, 0},
		{0, 0, -1, 0, 0},
	},

	.transitionMeta_csm_4P = 
	{
		{-512, 0, 1, 0, 0},
		{-512, 0, 2, 0, 0},
		{-512, 0, 3, 0, 0},
		{-512, 0, 4, 0, 0},
		{-512, 0, 2, 0, 0},
		{-512, 0, 3, 0, 0},
		{-512, 0, 4, 0, 0},
		{-512, 0, 5, 0, 0},
		{-512, 0, 3, 0, 0},
		{-512, 0, 4, 0, 0},
		{-512, 0, 0, 0, 0},
		{-512, 0, 5, 0, 0},
		{-512, 0, 1, 0, 0},
		{-512, 0, 6, 0, 0},
		{-512, 0, 2, 0, 0},
		{-512, 0, 0, 0, 0},
		{512, 0, 3, 0, 0},
		{512, 0, 1, 0, 0},
		{512, 0, 7, 0, 0},
		{512, 0, 5, 0, 0},
		{0, 0, -1, 0, 0},
	},

	.ptr_transitionMeta_csm = 
	{
		&D230.transitionMeta_csm_1P2P,
		&D230.transitionMeta_csm_1P2P,
		&D230.transitionMeta_csm_3P,
		&D230.transitionMeta_csm_4P
	},

	.csm_instPos = {0, 0x28, 0xFA, 0},

	.csm_instRot = {0x800, 0, 0},
	
	.moveModels = 4,

	.unkCharacterWindows = 0x8C,

	.PlayerNumberStrings = 
	{
		&R230.s_1,
		&R230.s_2,
		&R230.s_3,
		&R230.s_4
	},

	.getNextDriver1 = {2, 2, 1, 1},

	.getNextDriver2 = {3, 3, 0, 0},

	.characterSelect_Outline = 0,

	.characterSelect_NeutralColor = 0x808080, 

	.characterSelect_ChosenColor = 0,

	.characterSelect_BlueRectColors = 
	{ 
		0x1b, 0x6a, 0xcb, 0x00, 
		0x9b, 0xd2, 0xf2, 0x40, 
		0xb7, 0xe1, 0xed, 0x43, 
		0x65, 0x4b, 0x03, 0x46, 
		0xa6, 0x83, 0x23, 0x50, 
		0xdf, 0xc8, 0x95, 0x64 
	},

	// TRACK SELECT CONSTS

	.arcadeTracks = 
	{
		// CRASH_COVE
		{3, 0x51, 0x6a, 0xFFFF, 0x1e4, 0x258},
		// ROO_TUBES
		{6, 0x5b, 0x7e, 0xFFFF, 0x1fa, 0x283},
		// TIGER_TEMPLE
		{4, 0x59, 0x7a, 0xFFFF, 0x1e5, 0x31f},
		// COCO_PARK
		{14, 0x43, 0x5c, 0xFFFF, 0x1e5, 0x31f},
		// MYSTERY_CAVES
		{9, 0x4e, 0x64, 0xFFFF, 0x1e9, 0x39b},
		// BLIZZARD_BLUFF
		{2, 0x4f, 0x66, 0xFFFF, 0x1e3, 0x2cd},
		// SEWER_SPEEDWAY
		{8, 0x57, 0x76, 0xFFFF, 0x1e8, 0x373},
		// DINGO_CANYON
		{0, 0x53, 0x6e, 0xFFFF, 0x1e1, 0x2a3},
		// PAPU_PYRAMID
		{5, 0x5a, 0x7c, 0xFFFF, 0x1e6, 0x309},
		// DRAGON_MINES
		{1, 0x54, 0x70, 0xFFFF, 0x1e2, 0x285},
		// POLAR_PASS
		{12, 0x50, 0x68, 0xFFFF, 0x1ec, 0x4ca},
		// CORTEX_CASTLE
		{10, 0x4d, 0x62, 0xFFFF, 0x1ea, 0x41b},
		// TINY_ARENA
		{15, 0x44, 0x5e, 0xFFFF, 0x1ef, 0x58f},
		// HOT_AIR_SKYWAY
		{7, 0x4c, 0x60, 0xFFFF, 0x1e7, 0x4f9},
		// N_GIN_LABS
		{11, 0x52, 0x6c, 0xFFFF, 0x1eb, 0x448},
		// OXIDE_STATION
		{13, 0x58, 0x78, 0xFFFF, 0x1ed, 0x5da},
		// SLIDE_COLISEUM
		{16, 0x55, 0x72, 0xFFFF, 0x1f0, 0x39a},
		// TURBO_TRACK
		{17, 0x56, 0x74, 0x1, 0x1f1, 0x3d5},
	},

	.battleTracks = 
	{
		// NITRO_COURT
		{18, 0x45, 0xFFFF, 0xFFFF, 0x1f2, 0x197},
		// RAMPAGE_RUINS
		{19, 0x46, 0xFFFF, 0xFFFF, 0x1f3, 0x19a},
		// PARKING_LOT
		{20, 0x47, 0xFFFF, 0x2, 0x1f4, 0x199},
		// SKULL_ROCK
		{21, 0x48, 0xFFFF, 0xFFFF, 0x1f5, 0x19a},
		// THE_NORTH_BOWL
		{22, 0x49, 0xFFFF, 0x3, 0x1f5, 0x19a},
		// ROCKY_ROAD
		{23, 0x4a, 0xFFFF, 0xFFFF, 0x1f7, 0x19a},
		// LAB_BASEMENT
		{24, 0x4b, 0xFFFF, 0x4, 0x1f8, 0x19a},
	},

	.transitionMeta_trackSel = 
	{
		{-512, 0, 1, 0, 0},
		{0, -200, 2, 0, 0},
		{0, 200, 3, 0, 0},
		{512, 0, 4, 0, 0},
		{0, 0, -1, 0, 0}
	},

	.lapRowVal = {3, 5, 7, 0},

	.menurow_LapSel = 
	{
		{0x9b, 0,1,0,0},
		{0x9c, 0,2,1,1},
		{0x9d, 1,2,2,2},
		{-1}
	},

	.menubox_LapSel = 
	{
		.stringIndexTitle = 0x9a,
		
		.posX_curr = 0x18C,
		.posY_curr = 0x7c,

		.state = 0x81,
		.rows = &D230.menurow_LapSel,
	},

	.videoCol = 0x808080,

	.timeTrialStarCol = {0xE, 0x16},
	.timeTrialFlagGet = {0x1, 0x2},

	.drawMapOffset =
	{
		{0,0,1},
		{-2,0,3},
		{2,0,3},
		{0,1,3},
		{0,-1,3},
		{12,6,2}
	},

	// CUP SELECT CONSTS

	.transitionMeta_cupSel = 
	{
		{-256, -100, 5, 0, 0},
		{256, -100, 4, 0, 0},
		{-256, 100, 3, 0, 0},
		{256, 100, 2, 0, 0},
		{0, -100, 0, 0, 0},
		{0, 0, -1, 0, 0}
	},

	.cupSel_StarColorIndex = {0x11, 0xE, 0x16, 0},

	.cupSel_StarUnlockFlag = {0xC, 0x10, 0x14, 0},

	.cupSel_Color = 0xC0C0C0,

	// BATTLE CONSTS

	.transitionMeta_battle = 
	{
		{400, 0, 5, 0, 0},
		{-200, 0, 5, 0, 0},
		{400, 0, 4, 0, 0},
		{-200, 0, 4, 0, 0},
		{400, 0, 3, 0, 0},
		{-200, 0, 3, 0, 0},
		{400, 0, 2, 0, 0},
		{-200, 0, 2, 0, 0},
		{400, 0, 0, 0, 0},
		{0, -100, 0, 0, 0},
		{0, 0, -1, 0, 0}
	},

	.battleType_rows = 
	{
		{0x92, 0,1,0,0},
		{0x93, 0,2,1,1},
		{0x94, 1,2,2,2},
		{-1}
	},

	.battleType_box = 
	{
		.stringIndexTitle = -1,

		.state = 0x10280,
		.rows = &D230.battleType_rows,
		.funcPtr = DECOMP_MM_Battle_CloseSubMenu
	},

	.battleLengthLifeTime_rows =
	{
		{0xA4, 0,1,0,0},
		{0xA5, 0,2,1,1},
		{0xA6, 1,2,2,2},
		{-1}
	},

	.battleLengthLifeTime_box = 
	{
		.stringIndexTitle = -1,

		.state = 0x10280,
		.rows = &D230.battleLengthLifeTime_rows,
		.funcPtr = DECOMP_MM_Battle_CloseSubMenu
	},

	.battleLengthTimeTime_rows =
	{
		{0xA7, 0,1,0,0},
		{0xA8, 0,2,1,1},
		{0xA9, 1,2,2,2},
		{-1}
	},

	.battleLengthTimeTime_box = 
	{
		.stringIndexTitle = -1,

		.state = 0x10280,
		.rows = &D230.battleLengthTimeTime_rows,
		.funcPtr = DECOMP_MM_Battle_CloseSubMenu
	},

	.battleLengthPoints_rows =
	{
		{0xA1, 0,1,0,0},
		{0xA2, 0,2,1,1},
		{0xA3, 1,2,2,2},
		{-1}
	},

	.battleLengthPoints_box = 
	{
		.stringIndexTitle = -1,

		.state = 0x10280,
		.rows = &D230.battleLengthPoints_rows,
		.funcPtr = DECOMP_MM_Battle_CloseSubMenu
	},

	.battleLengthLifeLife_rows =
	{
		{0x9e, 0,1,0,0},
		{0x9f, 0,2,1,1},
		{0xA0, 1,2,2,2},
		{-1}
	},

	.battleLengthLifeLife_box = 
	{
		.stringIndexTitle = -1,

		.state = 0x10280,
		.rows = &D230.battleLengthLifeLife_rows,
		.funcPtr = DECOMP_MM_Battle_CloseSubMenu
	},

	.battleStartGame_rows =
	{
		{0xAE, 0,0,0,0},
		{-1}
	},

	.battleStartGame_box = 
	{
		.stringIndexTitle = -1,

		.state = 0x10280,
		.rows = &D230.battleStartGame_rows,
		.funcPtr = DECOMP_MM_Battle_CloseSubMenu
	},

	.battleMenuBoxArray =
	{
		&D230.battleType_box,
		&D230.battleLengthTimeTime_box,
		&D230.battleLengthPoints_box,
		&D230.battleLengthLifeLife_box,
		&D230.battleLengthLifeTime_box
	},

	.battleWeaponsEnabled =
	{
		0x1,    0x2,   0x2,    0x6,
		0x4,    0x7,   0x8,    0x8,
		0x10,   0x9,   0x40,   0xB,
		0x80,   0xC,   0x400,  0xF,
		0x800,  0x10,  0x1000, 0x11,
		0x2000, 0x12
	},

	.FlagesGameMode1_BattleType = {0x4000,0x10000,0x8000},

	.time_3_6_9 = {3,6,9},
	.time_3_6_INF = {3,6,0xFF},
	.lives_3_6_9 = {3,6,9},
	.points_5_10_15 = {3,10,15},

	.color1 = 0x808080,
	.color2 = 0x101010,
	.color3 = 0x806050,

	// HIGH SCORE CONSTS

	.transitionMeta_HighScores =
	{
		{0, -100, 0, 0, 0},
		{-256, 0, 6, 0, 0},
		{-256, 0, 5, 0, 0},
		{-256, 0, 4, 0, 0},
		{-256, 0, 3, 0, 0},
		{-256, 0, 2, 0, 0},
		{-256, 0, 1, 0, 0},
		{256, 0, 3, 0, 0},
		{256, 0, 2, 0, 0},
		{256, 0, 1, 0, 0},
		{256, 0, 0, 0, 0},
		{0, 0, -1, 0, 0}
	},

	.colorIndexArray = {0xE, 0x16},

	.highscore_unkflags = {0x1, 0x2},

	.highscore_iconColor = 0x808080,

	.highScoreRows = 
	{
		{0xAF, 0,1,0,0},
		{0xB1, 0,2,0,0},
		{0xB2, 1,2,0,0},
		{-1}
	},

	.highScoreBox =
	{
		.stringIndexTitle = -1,
		.posX_curr = 0x17C,
		.posY_curr = 0xAF,

		.state = 0x81,
		.rows = &D230.highScoreRows
	},

	.highScore_trackDesired = 0,
	.highScore_rowDesired = 0,
	.highScore_trackCurr = 0,
	.highScore_rowCurr = 0,

#if 0

	.langIndex_Boot = {2,3,4,5,6,7},
	
	.rows_lngBoot = 
	{
		{0x85, 0,1,0,0},
		{0x86, 0,2,1,1},
		{0x87, 1,3,2,2},
		{0x88, 2,4,3,3},
		{0x89, 3,5,4,4},
		{0x8a, 4,5,5,5},
		{-1}
	}

	.menubox_lngBoot = 
	{
		.stringIndexTitle = -1,
		
		.posX_curr = 256,
		.posY_curr = 118,
		
		.state = 0xC03,
		.rows = &D230.rows_lngBoot,
		.funcPtr = DECOMP_MM_MENUBOX_LanguageBoot
	}

#endif

	.titleObj = 0,

	// TRACK SELECT DYN
	.trackSel_changeTrack_frameCount = 0,
	.trackSel_currTrack = 0,
	.trackSel_direction = 0,
	.trackSel_boolOpenLapBox = 0,
	.trackSel_transitionState = 0,
	.trackSel_StartRaceAfterFadeOut = 0,
	.trackSel_transitionFrames = 0,
	.trackSel_video_frameCount = 0,
	.trackSel_video_boolAllocated = 0,
	.trackSel_video_state = 0,
	.trackSel_unk = 0,

	// CUP SELECT DYN
	.cupSel_transitionState = 0,
	.cupSel_postTransition_boolStart = 0,
	.cupSel_transitionFrames = 0,

	// BATTLE DYN
	.battle_transitionState = 0,
	.battle_postTransition_boolStart = 0,
	.battle_transitionFrames = 0,

	// HIGHSCORE DYN
	.highScore_transitionState = 0,
	.highScore_transitionFrames = {0,0,0},
	.highScore_horizontalMove = {0,0},
	.highScore_verticalMove = {0,0},

	// SCRAPBOOK
	.scrapbookState = 0,

	// CHAR SELECT AND TITLE DYN
	.characterSelect_sizeY = 0,
	.desiredMenu = 0,
	.movingToTrackMenu = 0,

	.characterSelect_MoveDir = {0,0,0,0},
	.characterSelect_charIDs_desired = {0,0,0,0},
	.characterSelect_charIDs_curr = {0,0,0,0},
	.characterSelect_angle = {0,0,0,0},
	.characterSelect_transitionState = 0,
	.characterSelect_ptrWindowXY = 0,
	.characterSelectIconLayout = 0,

	.timerInTitle = 0,
	.csm_Active = 0,
	.MM_State = 0,
	.isMenuTransitioning = 0,

	.timerPerPlayer = {0,0,0,0},
#if 0
	.langMenuTimer = 0,
#endif
	.isRosterExpanded = 0,
	.characterSelect_sizeX = 0,
	.ptrIntroCam = 0,
	.textPos = 0,
	.ptrTransitionMeta = 0,
	.countMeta0xD = 0,
	.transitionFrames = 0,

	.s_SliceBuf = "SliceBuf",
	.s_VlcBuf = "VlcBuf",
	.s_RingBuf = "RingBuf",
};