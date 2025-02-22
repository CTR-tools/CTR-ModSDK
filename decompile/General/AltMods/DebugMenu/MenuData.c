#include "DebugStructs.h"

void DebugMenu_LoadGame_GivenLevelId(struct GameTracker* gGT, int levelID)
{
	// not in demo, needed for retail
	gGT->gameMode1 &= ~(MAIN_MENU);
	sdata->ptrActiveMenu = 0;
	
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

// Menu for BATTLE SELECT
extern struct DebugRow rowsDbgBattle[10];
struct DebugMenu menuDbgBattle =
{
	.parentMenu = 0,
	.currRow = rowsDbgBattle,
};
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

// Menu for LEVEL SELECT
extern struct DebugRow rowsDbgLevels[18];
struct DebugMenu menuDbgLevels =
{
	.parentMenu = 0,
	.currRow = rowsDbgLevels,
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

// Menu for CHARACTER SELECT
extern struct DebugRow rowsDbgChar[14];
struct DebugMenu menuDbgChar =
{
	.parentMenu = 0,
	.currRow = rowsDbgChar,
};
struct DebugRow rowsDbgChar[] =
{
	{3, 0x0, "CRASH", 		DebugMenu_LoadGame_GivenCharacterId },
	{3, 0x1, "CORTEX", 		DebugMenu_LoadGame_GivenCharacterId },
	{3, 0x2, "TINY", 		DebugMenu_LoadGame_GivenCharacterId },
	{3, 0x3, "COCO", 		DebugMenu_LoadGame_GivenCharacterId },
	{3, 0x4, "NGIN", 		DebugMenu_LoadGame_GivenCharacterId },
	{3, 0x5, "DINGO", 		DebugMenu_LoadGame_GivenCharacterId },
	{3, 0x6, "POLAR", 		DebugMenu_LoadGame_GivenCharacterId },
	{3, 0x7, "PURA", 		DebugMenu_LoadGame_GivenCharacterId },
	{3, 0x8, "PINSTRIPE", 	DebugMenu_LoadGame_GivenCharacterId },
	{3, 0x9, "PAPU", 		DebugMenu_LoadGame_GivenCharacterId },
	{3, 0xA, "ROO", 		DebugMenu_LoadGame_GivenCharacterId },
	{3, 0xB, "JOE", 		DebugMenu_LoadGame_GivenCharacterId },
	{3, 0xC, "NTROPY", 		DebugMenu_LoadGame_GivenCharacterId },
	{0}
};

// Menu for PLAYER SELECT
extern struct DebugRow rowsDbgPlayer[15];
struct DebugMenu menuDbgPlayer =
{
	.parentMenu = 0,
	.currRow = rowsDbgPlayer,
};
struct DebugRow rowsDbgPlayer[] =
{
	{3, 0x1, "1",				DebugMenu_LoadGame_GivenNumPlyr },
	{3, 0x2, "2",				DebugMenu_LoadGame_GivenNumPlyr },
	{3, 0x3, "3",				DebugMenu_LoadGame_GivenNumPlyr },
	{3, 0x4, "4",				DebugMenu_LoadGame_GivenNumPlyr },
	
	{3, 0x4, "RESET POSITIONS",	1 /* Need Func */ },
	{3, 0x5, "START RACE", 		1 /* Need Func */ },
	{3, 0x6, "PLR 1 BUZZ OFF",	1 /* Need Func */ },
	{3, 0x7, "PLR 2 BUZZ OFF",	1 /* Need Func */ },
	{3, 0x8, "PLR 3 BUZZ OFF",	1 /* Need Func */ },
	{3, 0x9, "PLR 4 BUZZ OFF",	1 /* Need Func */ },
	
	{1, 0x0, "LOAD PLR 1...",	&menuDbgChar },
	{1, 0x0, "LOAD PLR 2...", 	&menuDbgChar },
	{1, 0x0, "LOAD PLR 3...",	&menuDbgChar },
	{1, 0x0, "LOAD PLR 4...",	&menuDbgChar },
	{0}
};

// Menu for LEVELS/PLAYERS
extern struct DebugRow rowsDbgMain[3];
struct DebugMenu menuDbgMain =
{
	.parentMenu = 0,
	.currRow = rowsDbgMain,
};
struct DebugRow rowsDbgMain[] =
{
	{ 1, 0x0, "LEVEL...", &menuDbgLevels },
	{ 1, 0x0, "PLAYERS...", &menuDbgPlayer },
	{0}
};

void DbgMenuEnter(struct DebugMenu* dm)
{
	struct DebugRow* firstRow = DMENU_GETROWS(dm);
	
	if(dm == &menuDbgPlayer)
	{
		int rowIndex = ((unsigned int)dm->currRow - (unsigned int)firstRow) >> 4;
		
		// LOAD PLYR 1/2/3/4...
		if(rowIndex >= 10)
		{
			debugPlayerIndex = rowIndex - 10;
			
			for(int i = 0; i < 4; i++)
			{
				firstRow[i+10].subMenu = -1;
			}
			
			firstRow[rowIndex].subMenu = &menuDbgChar;
		}
	}
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