struct Overlay_230 o230 =
{
	// start at MAIN MENU CONST
	
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
		.rows = rows_mainMenu_Basic,
		.funcPtr = MM_MENUBOX_Main,
		
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
		
		.state = 8,
		.rows = rows_players1P2P,
		.funcPtr = MM_MENUBOX_1p2p,	
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
		
		.state = 8,
		.rows = rows_players2P3P4P,
		.funcPtr = MM_MENUBOX_2p3p4p,	
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
		.rows = rows_difficulty,
		.funcPtr = MM_MENUBOX_Difficulty,	
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
		.rows = rows_raceType,
		.funcPtr = MM_MENUBOX_SingleCup,	
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
		.rows = rows_adventure,
		.funcPtr = MM_MENUBOX_NewLoad,	
	},
	
	.menubox_characterSelect =
	{
		.stringIndexTitle = -1,
		
		.state = 0x28,
		.funcPtr = MM_Characters_MenuBox,
	},
	
	.menubox_trackSelect =
	{
		.stringIndexTitle = -1,
		
		.state = 0x28,
		.funcPtr = MM_TrackSelect_MenuBox,
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
		.rows = rows_cupSelect,
		.funcPtr = MM_CupSelect_MenuBox,	
	},
	
	.menubox_battleWeapons =
	{
		.stringIndexTitle = -1,
		
		.state = 0x28,
		.funcPtr = MM_Battle_MenuBox,
	},
	
	.menubox_highScores =
	{
		.stringIndexTitle = -1,
		
		.state = 0x28,
		.funcPtr = MM_HighScore_MenuBox,
	},
	
	.menubox_scrapbook =
	{
		.stringIndexTitle = -1,
		
		.state = 0x20,
		.funcPtr = MM_Scrapbook_PlayMovie,
	},
	
	.ptrMenuBoxes =
	{
		&menubox_mainMenu,
		&menubox_players1P2P,
		&menubox_players2P3P4P,
		&menubox_adventure,
		&menubox_characterSelect,
		&menubox_trackSelect,
		&menubox_cupSelect,
		&menubox_battleWeapons,
		&menubox_highScores
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
		{0x200, 0, 0, 0, 0},
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
	
	// Character Select
	
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
		&characterSelectWindowPos[0],
		&characterSelectWindowPos[2],
		&characterSelectWindowPos[6],
		&characterSelectWindowPos[9],
		
		// small menus, 1p2p
		&characterSelectWindowPos[1],
		&characterSelectWindowPos[4],
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
	}
};