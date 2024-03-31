#include <common.h>

void DECOMP_AH_HintMenu_MenuProc();
void DECOMP_AH_WarpPad_MenuProc();

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
	.rowsTokenRelic =
	{
		{0x176, 0, 1, 0, 0}, // CTR CHALLENGE
		{0xb8,  0, 1, 1, 1}, // RELIC RACE
		{-1,  0, 0, 0, 0}  // NULL
	},

	// 800b4e50
	.menuTokenRelic =
	{
		.stringIndexTitle = 0xb6,
		.posX_curr = 0x100,
		.posY_curr = 0x6c,
		.unk1 = 0,
		.state = 0x100803,
		.rows = &D232.rowsTokenRelic[0],
		.funcPtr = DECOMP_AH_WarpPad_MenuProc,
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
	},
	
	.hubArrowXY_Inner =
	{
		3, 4,
		6, 2,
		5, 4
	},
	
	.hubArrowXY_Outter =
	{
		0, 3,
		-2, 1,
		0, 0,
		2, 1,
	},
	
	.loadSave_pos =
	{
		-4, -2,
		4, -2,
		-4, 2,
		4, 2,
	},
	
	.loadSave_col =
	{
		0xBEFFBE,
		0xFF00,
		0xFF00,
		0xBEFFBE,
	},
	
	.hubArrow_pos =
	{
		0, 0xFFF8,
		0xFFF8, 8,
		8, 8
	},
	
	.hubArrow_col1 =
	{
		0xFF00FF,
		0xFF0000,
		0xFF0000,
	},
	
	.hubArrow_col2 =
	{
		0x80FFFF,
		0xFF0000,
		0xFF0000,
	},
	
	.hubArrowGray1 =
	{
		0x808080,
		0x808080,
		0x808080,
	},
	
	.hubArrowGray2 =
	{
		0x808080,
		0x808080,
		0x808080,
	},
	
	.advPausePages =
	{
		// hubs and bosses
		{0x19, -1, 0, 0xF},
		{0x1A, -1, 0, 0xA},
		{0x1B, -1, 0, 0x9},
		{0x1C, -1, 0, 0xB},
		{0x1D, -1, 0, 0x8},
		
		// gems and relics
		{-1, 0x10, 1, 0},
		{-1, 0x11, 2, 0},
	},
	
	.advPauseInst =
	{
		// gems: red, green, blue, yellow, purple
		{0x5F, 0xAF0, 0x8086c,  USE_SPECULAR_LIGHT, {0xfa5b, 0xf0f, 0xfe1f, 0}},
		{0x5F, 0xAF0, 0x86c08,  USE_SPECULAR_LIGHT, {0xfa5b, 0xf0f, 0xfe1f, 0}},
		{0x5F, 0xAF0, 0x808000, USE_SPECULAR_LIGHT, {0xfa5b, 0xf0f, 0xfe1f, 0}},
		{0x5F, 0xAF0, 0x8080,   USE_SPECULAR_LIGHT, {0xfa5b, 0xf0f, 0xfe1f, 0}},
		{0x5F, 0xAF0, 0x6c086c, USE_SPECULAR_LIGHT, {0xfa5b, 0xf0f, 0xfe1f, 0}},
		
		// key
		{0x63, 0x30D, 0xA6DC, USE_SPECULAR_LIGHT, {0xf368, 0x99f, 0xfd28}},
		
		// relic: blue, gold, platinum
		{0x61, 0x30D, 0xFFA560, USE_SPECULAR_LIGHT, {0xf368, 0x99f, 0x232}},
		{0x61, 0x30D, 0x9d2d8,  USE_SPECULAR_LIGHT, {0xf368, 0x99f, 0x232}},
		{0x61, 0x30D, 0xe9edff, USE_SPECULAR_LIGHT, {0xf368, 0x99f, 0x232}},
		
		// token: red, green, blue, yellow, purple
		{0x7d, 0x500, 0x8086c,  USE_SPECULAR_LIGHT, {0xf5f6, 0x787, 0xa0a, 0}},
		{0x7d, 0x500, 0x86c08,  USE_SPECULAR_LIGHT, {0xf5f6, 0x787, 0xa0a, 0}},
		{0x7d, 0x500, 0x800000, USE_SPECULAR_LIGHT, {0xf5f6, 0x787, 0xa0a, 0}},
		{0x7d, 0x500, 0x8080,   USE_SPECULAR_LIGHT, {0xf5f6, 0x787, 0xa0a, 0}},
		{0x7d, 0x500, 0x6c086c, USE_SPECULAR_LIGHT, {0xf5f6, 0x787, 0xa0a, 0}},
		
		// trophy
		{0x62, 0x500, 0x808080, 0, {0xf368, 0x99f, 0x232}}
	},
	
	.menuHintMenu =
	{
		.stringIndexTitle = 0xFFFF,
		.posX_curr = 0x100,
		.posY_curr = 0x6c, 
		
		.unk1 = 0,
		
		.state = 0x8A3,
		.rows = 0,
		.funcPtr = DECOMP_AH_HintMenu_MenuProc,
		.drawStyle = 4,
	
		// rest of variables all default zero
	},
	
	.fiveArrow_pos =
	{
		0, -5,
		-0x18, 6,
		0x18, 6
	},
	
	.fiveArrow_col1 =
	{
		0xC8FF, 0xFF, 0xFF
	},
	
	.fiveArrow_col2 =
	{
		0x80c8ff, 0x80ff, 0x80ff
	},
	
	.maskPos =
	{
		-0xA0, -0xA, 0x100
	},
	
	.maskRot =
	{
		0, 0x180, 0
	},
	
	.maskScale = 0x1000,
	
	.maskOffsetPos =
	{
		-0x14, 0, 0x50
	},
	
	.maskOffsetRot =
	{
		0x7AF, 0x258, 0x78
	},
	
	.maskVars =
	{
		// pos1
		-0x46, 0, 0x140,
		
		// pos2
		-0x3C, 0, 0x118,
		
		// rot1
		0x7af, 0x258, 0x78,
		
		// rot2
		0x800, 0x64, 0
	},
	
	.maskFrameCurr = 0,
	
	.emSet_maskSpawn =
	{
		[0] =
		{
				.flags = 1,
				.initOffset = 12,
				.InitTypes.FuncInit =
				{
						.particle_funcPtr = 0x00000000,
						.particle_colorFlags = 0xA1,
						.particle_lifespan = 0x14,
						.particle_Type = 0,
				}
		},
		
		[1] =
		{
			.flags = 0x1B,
			
			// posX
			.initOffset = 0,
			
			.InitTypes.AxisInit =
			{
				.baseValue =
				{
					.startVal = -0x1900,
					.velocity = -0x640,
					.accel = 0,
				},
				
				.rngSeed =
				{
					.startVal = 0x3200,
					.velocity = 0xc80,
					.accel = 0,
				}
			}
			
			// last 0x10 are blank
		},
		
		[2] =
		{
			.flags = 0x1B,
			
			// posZ
			.initOffset = 2,
			
			.InitTypes.AxisInit =
			{
				.baseValue =
				{
					.startVal = -0x1900,
					.velocity = -0x640,
					.accel = 0,
				},
				
				.rngSeed =
				{
					.startVal = 0x3200,
					.velocity = 0xc80,
					.accel = 0,
				}
			}
			
			// last 0x10 are blank
		},
		
		[3] =
		{
			.flags = 0x1B,
			
			// posY
			.initOffset = 1,
			
			.InitTypes.AxisInit =
			{
				.baseValue =
				{
					.startVal = -0xC80,
					.velocity = 0x190,
					.accel = 0,
				},
				
				.rngSeed =
				{
					.startVal = 0x1900,
					.velocity = 0x640,
					.accel = 0,
				}
			}
			
			// last 0x10 are blank
		},
		
		[4] =
		{
			.flags = 3,
			
			// Scale
			.initOffset = 5,
			
			// 50% scale
			.InitTypes.AxisInit.baseValue.startVal = 0x800,
			.InitTypes.AxisInit.baseValue.velocity = -0x20,
			
			// all the rest is untouched
		},
		
		[5] =
		{
			.flags = 9,
			
			// RotX?
			.initOffset = 4,
			
			.InitTypes.AxisInit.baseValue.startVal = 1,
			.InitTypes.AxisInit.rngSeed.startVal = 0x1000,
			
			// all the rest is untouched
		},
		
		[6] =
		{
			.flags = 5,
			
			// colorR
			.initOffset = 7,
			
			.InitTypes.AxisInit.baseValue.startVal = 0x8000,
			.InitTypes.AxisInit.baseValue.accel = -0x100,
			
			// all the rest is untouched
		},
		
		[7] =
		{
			.flags = 5,
			
			// colorG
			.initOffset = 8,
			
			.InitTypes.AxisInit.baseValue.startVal = 0x8000,
			.InitTypes.AxisInit.baseValue.accel = -0x100,
			
			// all the rest is untouched
		},
		
		[8] =
		{
			.flags = 5,
			
			// colorB
			.initOffset = 9,
			
			.InitTypes.AxisInit.baseValue.startVal = 0x8000,
			.InitTypes.AxisInit.baseValue.accel = -0x100,
			
			// all the rest is untouched
		},
		
		// null terminator
		[9] = {}
	},
	
	.emSet_maskLeave =
	{
		[0] =
		{
				.flags = 1,
				.initOffset = 12,
				.InitTypes.FuncInit =
				{
						.particle_funcPtr = 0x00000000,
						.particle_colorFlags = 0xA1,
						.particle_lifespan = 0x14,
						.particle_Type = 0,
				}
		},
		
		[1] =
		{
			.flags = 0x1B,
			
			// posX
			.initOffset = 0,
			
			.InitTypes.AxisInit =
			{
				.baseValue =
				{
					.startVal = -0x640,
					.velocity = -0xC80,
					.accel = 0,
				},
				
				.rngSeed =
				{
					.startVal = 0xc80,
					.velocity = 0x1900,
					.accel = 0,
				}
			}
			
			// last 0x10 are blank
		},
		
		[2] =
		{
			.flags = 0x1B,
			
			// posZ
			.initOffset = 2,
			
			.InitTypes.AxisInit =
			{
				.baseValue =
				{
					.startVal = -0x640,
					.velocity = -0xC80,
					.accel = 0,
				},
				
				.rngSeed =
				{
					.startVal = 0xc80,
					.velocity = 0x1900,
					.accel = 0,
				}
			}
			
			// last 0x10 are blank
		},
		
		[3] =
		{
			.flags = 0x1B,
			
			// posY
			.initOffset = 1,
			
			.InitTypes.AxisInit =
			{
				.baseValue =
				{
					.startVal = -0x190,
					.velocity = -0x4B0,
					.accel = 0,
				},
				
				.rngSeed =
				{
					.startVal = 0xc80,
					.velocity = 0xc80,
					.accel = 0,
				}
			}
			
			// last 0x10 are blank
		},
		
		[4] =
		{
			.flags = 3,
			
			// Scale
			.initOffset = 5,
			
			// 100% scale
			.InitTypes.AxisInit.baseValue.startVal = 0x1000,
			.InitTypes.AxisInit.baseValue.velocity = -0x80,
			
			// all the rest is untouched
		},
		
		[5] =
		{
			.flags = 9,
			
			// RotX?
			.initOffset = 4,
			
			.InitTypes.AxisInit.baseValue.startVal = 1,
			.InitTypes.AxisInit.rngSeed.startVal = 0x1000,
			
			// all the rest is untouched
		},
		
		[6] =
		{
			.flags = 5,
			
			// colorR
			.initOffset = 7,
			
			.InitTypes.AxisInit.baseValue.startVal = 0x8000,
			.InitTypes.AxisInit.baseValue.accel = -0x100,
			
			// all the rest is untouched
		},
		
		[7] =
		{
			.flags = 5,
			
			// colorG
			.initOffset = 8,
			
			.InitTypes.AxisInit.baseValue.startVal = 0x8000,
			.InitTypes.AxisInit.baseValue.accel = -0x100,
			
			// all the rest is untouched
		},
		
		[8] =
		{
			.flags = 5,
			
			// colorB
			.initOffset = 9,
			
			.InitTypes.AxisInit.baseValue.startVal = 0x8000,
			.InitTypes.AxisInit.baseValue.accel = -0x100,
			
			// all the rest is untouched
		},
		
		// null terminator
		[9] = {}
	},
	
	.maskAudioSettings =
	{
		0x0, 0x28, 0xFF
	},
	
	.hintMenu_lngIndexArr =
	{
		0x17d, 0x17f, 0x181, 0x183, 0x185, 0x189,
		0x19f, 0x187, 0x197, 0x199, 0x19b, 0x19d,
		0x1a7, 0x1a9, 0x1ab, 0x1ad, 0x1af, 0x1b1,
		0x1b3, 0x1b5, -1, 0
	},
	
	.eyePos =
	{
		0x6d, 0x84, 0x85
	},
	
	.lookAtPos =
	{
		-0x2E5, -0x12D, -0xF1
	}
	
	// the rest all initialize to zeros
};