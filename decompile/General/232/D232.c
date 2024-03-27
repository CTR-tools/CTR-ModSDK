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
		0x12c00,	// ROCKY_ROAD
		0xe100,		// LAB_BASEMENT (null)
	},
	
	// 800b4ea4
	.saveObjCameraOffset =
	{
		0x800, 0, 0
	},
	
	// 800b4eac
	.primOffsetXY_LoadSave =
	{
		0, 0,
		-2, 0,
		2, 0,
		0, -1,
		0, 1
	},
	
	// 800b4ec0
	.primOffsetXY_HubArrow =
	{
		0, 0,
		-2, 0,
		2, 0,
		0, -1,
		0, 1
	},
	
	// 800b4ed4
	.hubItems_hub1 =
	{
		{0xB780, 0x3D00, 0, 4},
		{0xC824, 0x46e,  0, -2},
		{0xFB50, 0x44c0, 0xc00, -3},
		{0xbcd0, 0x1482, 0x800, 100},
		{-1}
	},
	
	// 800b4efc
	.hubItems_hub2 =
	{
		{0xC178, 0xE493, 0, 0},
		{0xD6FC, 0x1093, 0x800, -1},
		{0xE890, 0xDECC, 0xc00, -4},
		{0xCC0C, 0xE764, 0x400, 100},
		{-1}
	},
	
	// 800b4f24
	.hubItems_hub3 =
	{
		{0x1099, 0x38b3, 0, 1},
		{0x23C9, 0x1ffc, 0, -4},
		{0xDE99, 0x3EB3, 0x400, -1},
		{0xEA6,  0x4556, 0x400, 100},
		{-1}
	},
	
	// 800b4f4c
	.hubItems_hub4 =
	{
		{0x2AF8, 0xEE13, 0, 2},
		{0xd5f8, 0xc993, 0x400, -2},
		{0x1678, 0xc593, 0, -5},
		{0x2ee0, 0x32c8, 0x800, -3},
		{0x109a, 0xdcd8, 0x576, 100},
		{-1}
	},
	
	// 800b4f7c
	.hubItems_hub5 =
	{
		{0x9f8,  0xac93, 0, 3},
		{0x5dc,  0xd493, 0x800, -4},
		{0x157c, 0xab3c, 0, 100},
		{-1}
	},
	
	.hubItemsXY_ptrArray =
	{
		&D232.hubItems_hub1[0],
		&D232.hubItems_hub2[0],
		&D232.hubItems_hub3[0],
		&D232.hubItems_hub4[0],
		&D232.hubItems_hub5[0],
	}
};