#include "DebugStructs.h"

// from mods/SecretDebugFont

// this should be rewritten with proper PrimMem and OTMem usage
void DebugFont_DrawCharacter(int index, int screenPosX, int screenPosY, int letterX, int letterY, int color)
{
  unsigned short uVar1;
  unsigned int *puVar2;
  unsigned int *puVar3;
  unsigned int uVar4;
  unsigned int uVar5;
  unsigned int uVar6;

  // specific to DEBUG MENU,
  // 8x index, not 7x index
  screenPosX += 8 * index;

  uVar6 = screenPosX + 7 & 0xffff;
  uVar4 = (screenPosY + 7) * 0x10000;

  // primitive memory
  puVar2 = (unsigned int*)sdata->gGT->backBuffer->primMem.curr;

  // OT memory
  puVar3 = (unsigned int*)sdata->gGT->pushBuffer_UI.ptrOT;

  // append memory, so that future polygons draw after
  // what we are about to add in this function
  sdata->gGT->backBuffer->primMem.curr = puVar2 + 10;

// PsyCross has broken transparency in DECOMP_CTR_Box_DrawClearBox,
// and also has does not handle transparency correctly in DebugFont,
// so disable transparency in both places
#ifdef REBUILD_PC
  puVar2[1] = 0x2c000000 | color;
#else
  puVar2[1] = 0x2e000000 | color;
#endif
  
  puVar2[2] = screenPosX & 0xffff | screenPosY << 0x10;
  puVar2[8] = uVar6 | uVar4;
  puVar2[4] = uVar6 | screenPosY << 0x10;
  puVar2[6] = screenPosX & 0xffff | uVar4;

  // each character is 7 pixels wide
  // and 7 pixels tall

  // '0' is 6th character in 2nd row,
  // Get X value of pixel
  // This is the bottom of two bytes
  uVar4 = sdata->debugFont.u + letterX * 7;

  // Get Y value for top of the quad
  // bit shift to top byte
  uVar6 = (sdata->debugFont.v + (letterY*7) ) * 0x100;

  // Get Y value for bottom of the quad
  // bit shift to top byte
  uVar5 = uVar6 + 7 * 0x100;

  // Top Left corner
  puVar2[3] = uVar4 | uVar6;

  // Top Right corner
  puVar2[5] = uVar4 + 7 | uVar6;

  // Bottom Left corner
  puVar2[7] = uVar4 | uVar5;

  // Bottom Right corner
  puVar2[9] = uVar4 + 7 | uVar5;

  // texture page
  uVar1 = sdata->debugFont.tpage;

  // color palette
  *(unsigned short *)((int)puVar2 + 0xe) = sdata->debugFont.clut;

  // optional: (I forget what this does, change color each frame?)
  //*(unsigned short *)((int)puVar2 + 0xe) = sdata->gGT->timer >> 6;

  // texture page
  *(unsigned short *)((int)puVar2 + 0x16) = uVar1;

  *puVar2 = *puVar3 | 0x9000000;
  *puVar3 = (unsigned int)puVar2 & 0xffffff;
}

void DebugFont_DrawLine(char* text, int posX, int posY, int color)
{
	int i = 0;
	char c;

	while(text[i] != 0)
	{
		if(text[i] == ' ')
		{
			i++;
			continue;
		}

		c = text[i];

		if (c == '.') 
		{
			c = 41;
		}
		
		else if (c == '>')
		{
			c = 38;
		}
		
		else if(c >= 'a' && c <= 'z')
		{
			c -= 'a';
		}

		else if(c >= 'A' && c <= 'Z')
		{
			c -= 'A';
		}

		else if(c >= '0' && c <= '9')
		{
			c -= '0';
			c += 26;
		}

		DebugFont_DrawCharacter(i, posX, posY,
			c % 21,
			c / 21,
			color
			);

		i++;
	}
}

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

// Menu for PLAYER SELECT
extern struct DebugRow rowsDbgPlayer[1];
struct DebugMenu menuDbgPlayer =
{
	.parentMenu = 0,
	.currRow = rowsDbgPlayer,
};
struct DebugRow rowsDbgPlayer[] =
{
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