#include <common.h>

void DECOMP_AH_WarpPad_MenuBoxFuncPtr();

struct OverlayDATA_232 D232 =
{
	// 800b4ddc
	.specLightGem = 
	{
		0xA0A, 0xF5F6, 0x787,
		0xA0A, 0xF5F6, 0x787,
		0xA0A, 0xF5F6, 0x787,
		0xA0A, 0xF5F6, 0x787,
		0xA0A, 0xF5F6, 0x787
	},
	
	// 800b4dfc
	.specLightRelic = 
	{
		0x690, 0xD20, 0x690,
		0x690, 0xD20, 0x690,
		0x690, 0xD20, 0x690,
		0x690, 0xD20, 0x690,
		0x690, 0xD20, 0x690,
	},
	
	// 800b4e1c
	.specLightToken = 
	{
		0xF5F6, 0x787, 0xA0A,
		0xF5F6, 0x787, 0xA0A,
		0xF5F6, 0x787, 0xA0A,
		0xF5F6, 0x787, 0xA0A,
		0xF5F6, 0x787, 0xA0A,
	},

	// 800b4e3c
	.menuRow_TokenRelic =
	{
		{0x176, 0, 1, 0, 0}, // CTR CHALLENGE
		{0xb8,  0, 1, 1, 1}, // RELIC RACE
		{-1,  0, 0, 0, 0}  // NULL
	},

	// 800b4e50
	.menuBox_TokenRelic =
	{
		.stringIndexTitle = 0xb6,
		.posX_curr = 0x100,
		.posY_curr = 0x6c,
		.unk1 = 0,
		.state = 0x100803,
		.rows = &D232.menuRow_TokenRelic[0],
		.funcPtr = DECOMP_AH_WarpPad_MenuBoxFuncPtr,
		.drawStyle = 4,
	},

	// 800b4e7c
	.arrKeysNeeded = 
	{
		2, 1, 2, 3, 4
	},

	// 800b4e86
	.levelID = -1,

	// 800b4e88
	.timeCrystalChallenge =
	{
		0x1c200,	// NITRO_COURT
		0x13ec0,	// RAMPAGE_RUINS
		0xe100,		// PARKING_LOT (null)
		0x13740,	// SKULL_ROCK
		0xe100,		// THE_NORTH_BOWL (null)
		0x1c200,	// ROCKY_ROAD
		0xe100,		// LAB_BASEMENT (null)
	},
	
	// 800b4ea4
	.saveObjCameraOffset =
	{
		0x800, 0, 0
	}
};