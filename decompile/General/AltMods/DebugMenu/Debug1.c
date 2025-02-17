#include "DebugStructs.h"

void DebugMenu_LoadGame_GivenLevelId(struct GameTracker* gGT, int levelID)
{
	gGT->levelID = levelID;
	DECOMP_MainRaceTrack_RequestLoad(gGT->levelID);
}

void DebugMenu_LoadGame_GivenIndexE3(struct GameTracker* gGT, int index)
{
	/*
		Row 1: 1P Dingo Canyon, P1 Crash
		Row 2: 1P Crash Cove, P1 Coco
		Row 3: 1P Blizzard Bluff, P1 Tiny
		Row 4: 1P Tiger Temple, P1 Polar
		Row 5: 1P Papu Pyramid, P1 Cortex
		Row 6: 2P Papu Pyramid, drivers are Crash, Cortex, Tiny, Coco, NGin, Dingo (standard 2 players 4 AIs)
		Row 7: 4P Tiger Temple, Crash Cortex Tiny Coco
		Row 8: 4P Blizzard Bluff, Crash Cortex Tiny Coco
	*/
	
	DECOMP_MainRaceTrack_RequestLoad(gGT->levelID);
}

// Set by menu
static int debugPlayerIndex = 0;

void DebugMenu_LoadGame_GivenCharacterId(struct GameTracker* gGT, int charID)
{
	data.characterIDs[debugPlayerIndex] = charID;
	DECOMP_MainRaceTrack_RequestLoad(gGT->levelID);
}

void DebugMenu_LoadGame_GivenNumPlyr(struct GameTracker* gGT, int numPlyr)
{
	gGT->numPlyrNextGame = numPlyr;
	DECOMP_MainRaceTrack_RequestLoad(gGT->levelID);
}

void DebugMenu_SetLapCount(struct GameTracker* gGT, int numLaps)
{
	gGT->numLaps = numLaps;
}

#if 0
static int debugModeArr[6] =
{
	ADVENTURE_MODE,
	ADVENTURE_MODE | ADVENTURE_ARENA,
	TIME_TRIAL,
	BATTLE_MODE,
	ARCADE_MODE,
	0x0, // VS mode
};

void DebugMenu_SetGameMode(struct GameTracker* gGT, int index)
{
	int removeBits = ~(
        ADVENTURE_MODE |
        ADVENTURE_ARENA |
        TIME_TRIAL |
        BATTLE_MODE |
        ARCADE_MODE
	);
	
	gGT->gameMode1 &= removeBits;
	gGT->gameMode1 |= debugModeArr[index];
};
#endif

struct DebugRow rowsDbgBattle[] =
{
	{3, 0x12, sdata_static.s_battle1, 	DebugMenu_LoadGame_GivenLevelId },
	{3, 0x13, sdata_static.s_battle2, 	DebugMenu_LoadGame_GivenLevelId },
	{3, 0x14, sdata_static.s_battle3, 	DebugMenu_LoadGame_GivenLevelId },
	{3, 0x15, sdata_static.s_battle4, 	DebugMenu_LoadGame_GivenLevelId },
	{3, 0x16, sdata_static.s_battle5, 	DebugMenu_LoadGame_GivenLevelId },
	{3, 0x17, sdata_static.s_battle6, 	DebugMenu_LoadGame_GivenLevelId },
	{3, 0x18, sdata_static.s_battle7, 	DebugMenu_LoadGame_GivenLevelId },
	{3, 0x10, sdata_static.s_secret1, 	DebugMenu_LoadGame_GivenLevelId },
	{3, 0x11, sdata_static.s_secret2, 	DebugMenu_LoadGame_GivenLevelId },
	{0}
};

struct DebugMenu menuDbgBattle =
{
	.parentMenu = 0,
	.rowArr = rowsDbgBattle,
};

struct DebugRow rowsDbgLevels[] =
{
	{1, 0x0, "BATTLE...", &menuDbgBattle },
	{3, 0x0, sdata_static.s_proto8, 	DebugMenu_LoadGame_GivenLevelId },
	{3, 0x1, sdata_static.s_proto9, 	DebugMenu_LoadGame_GivenLevelId },
	{3, 0x2, sdata_static.s_desert2, 	DebugMenu_LoadGame_GivenLevelId },
	{3, 0x3, sdata_static.s_island1, 	DebugMenu_LoadGame_GivenLevelId },
	{3, 0x4, sdata_static.s_temple1, 	DebugMenu_LoadGame_GivenLevelId },
	{3, 0x5, sdata_static.s_temple2, 	DebugMenu_LoadGame_GivenLevelId },
	{3, 0x6, sdata_static.s_tube1, 		DebugMenu_LoadGame_GivenLevelId },
	{3, 0x7, sdata_static.s_blimp1, 	DebugMenu_LoadGame_GivenLevelId },
	{3, 0x8, sdata_static.s_sewer1, 	DebugMenu_LoadGame_GivenLevelId },
	{3, 0x9, sdata_static.s_cave1, 		DebugMenu_LoadGame_GivenLevelId },
	{3, 0xA, sdata_static.s_castle1, 	DebugMenu_LoadGame_GivenLevelId },
	{3, 0xB, sdata_static.s_labs1, 		DebugMenu_LoadGame_GivenLevelId },
	{3, 0xC, sdata_static.s_ice1, 		DebugMenu_LoadGame_GivenLevelId },
	{3, 0xD, sdata_static.s_space, 		DebugMenu_LoadGame_GivenLevelId },
	{3, 0xE, "asphalt1", 				DebugMenu_LoadGame_GivenLevelId },
	{3, 0xF, "asphalt2", 				DebugMenu_LoadGame_GivenLevelId },
	{0}
};

struct DebugMenu menuDbgLevels =
{
	.parentMenu = 0,
	.rowArr = rowsDbgLevels,
};

struct DebugRow rowsDbgMain[] =
{
	{ 1, 0x0, "LEVEL...", &menuDbgLevels },
	
	// TODO: Change back to 1
	{ 3, 0x0, "PLAYERS...", 0 }, // TODO: Submenu
	{0}
};

struct DebugMenu menuDbgMain =
{
	.parentMenu = 0,
	.rowArr = rowsDbgMain,
};

void DebugMenu_InitMenuPositionSize(
	struct DebugMenu* dm, 
	int charSizeX, int charSizeY, 
	int posX, int posY)
{
	int len = 0;
	int rowCount = 0;
	struct DebugRow* dr;
	
	dm->posX = posX;
	dm->posY = posY;
	
	dr = dm->rowArr;
	while(dr->actionFlag != 0)
	{
		int rowLen = strlen(dr->rowText);
		
		if (len < (rowLen+1))
			len = rowLen+1;
		
		dr++;
		rowCount++;
	}
	
	dm->sizeX = (charSizeX * len) + 6;
	dm->sizeY = (charSizeY * rowCount) + 6;
	
	dr = dm->rowArr;
	while(dr->actionFlag != 0)
	{
		if(dr->actionFlag == 1)
		{
			DebugMenu_InitMenuPositionSize(
				dr->subMenu,
				charSizeX, charSizeY,
				dm->posX + dm->sizeX + 10,
				posY);
		}
		
		dr++;
	}
}

void DebugMenu_Init()
{
	DebugMenu_InitMenuPositionSize(
		&menuDbgMain,8,8,0x14,0x41);
}

void DebugMenu_DrawIfOpen()
{
	struct GameTracker* gGT = sdata->gGT;
	
	int buttonTap = sdata->gGamepads->gamepad[0].buttonsTapped;

	if ((buttonTap & BTN_SELECT) != 0)
		gGT->gameMode1 ^= DEBUG_MENU;

	if ((gGT->gameMode1 & DEBUG_MENU) == 0)
		return;
	
	void DebugMenu_Draw(struct DebugMenu* dm);
	DebugMenu_Draw(&menuDbgMain);
}

// June 1999
// 800828F0 - Battle submenu
// 80082b10 - Levels submenu
// 80082d24 - Character submenu (reload level)
// 80082f38 - Character submenu (mid-race swap?)
// 8008314c - Players submenu (1/2/3/4/ResetPositions/StartRace)
// 80083360 - Ghost submenu
// 80083570 - Various Options (save, laps, game modes)
// 80083788 - Levels/Players Menu

// E3 demos were stripped