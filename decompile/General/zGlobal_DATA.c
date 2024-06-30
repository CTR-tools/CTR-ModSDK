#include <common.h>

// this is only for LevInstances,
// NonLev-related entries are empty

void DECOMP_RB_Default_LInB();
void DECOMP_RB_Fruit_LInB();
void DECOMP_RB_Fruit_LInC();
void RB_GenericMine_LInB();
void DECOMP_RB_CrateFruit_LInC();
void DECOMP_RB_CrateWeapon_LInC();
void DECOMP_RB_CrateTime_LInC();
void DECOMP_RB_FlameJet_LInB();
//void DECOMP_RB_Plant_LInB();		-- DONE
//void DECOMP_RB_Minecart_LInB();	-- DONE
//void DECOMP_RB_Snowball_LInB();	-- DONE
//void DECOMP_RB_Armadillo_LInB();	-- DONE
//void DECOMP_RB_Blade_LInB();		-- DONE
//void DECOMP_RB_Seal_LInB();		-- DONE
void RB_Orca_LInB();
//void DECOMP_RB_Baron_LInB();		-- DONE
//void DECOMP_RB_Turtle_LInB();		-- DONE
//void DECOMP_RB_Turtle_LInC();		-- DONE
//void DECOMP_RB_Spider_LInB();		-- DONE
//void DECOMP_RB_Fireball_LInB();	-- DONE
void RB_Banner_LInB();
void DECOMP_RB_CtrLetter_LInB();
void DECOMP_RB_CtrLetter_LInC();
void DECOMP_RB_Crystal_LInB();
void DECOMP_RB_Crystal_LInC();
void DECOMP_RB_Teeth_LInB();
void DECOMP_RB_Teeth_LInC();

void AH_Sign_LInB();
//void DECOMP_AH_Door_LInB();		-- DONE
//void DECOMP_AH_Garage_LInB();		-- DONE
//void DECOMP_AH_SaveObj_LInB();	-- DONE
//void DECOMP_AH_WarpPad_LInB();	-- DONE

void CS_LevThread_LInB();

// temporary, until 231 compiles into PC port
#ifdef REBUILD_PC
void DECOMP_RB_Default_LInB() {}
void DECOMP_RB_Fruit_LInB() {}
void DECOMP_RB_Fruit_LInC() {}
void RB_GenericMine_LInB() {}
void DECOMP_RB_CrateFruit_LInC() {}
void DECOMP_RB_CrateWeapon_LInC() {}
void DECOMP_RB_CrateTime_LInC() {}
void DECOMP_RB_FlameJet_LInB() {}
//void DECOMP_RB_Plant_LInB() {}	-- DONE
//void DECOMP_RB_Minecart_LInB() {}	-- DONE
//void DECOMP_RB_Snowball_LInB() {}	-- DONE
//void DECOMP_RB_Armadillo_LInB() {}-- DONE
//void DECOMP_RB_Blade_LInB() {}	-- DONE
//void DECOMP_RB_Seal_LInB() {}		-- DONE
void RB_Orca_LInB() {}
//void DECOMP_RB_Baron_LInB() {}	-- DONE
//void DECOMP_RB_Turtle_LInB() {}	-- DONE
//void DECOMP_RB_Turtle_LInC() {}	-- DONE
//void DECOMP_RB_Spider_LInB() {}	-- DONE
//void DECOMP_RB_Fireball_LInB() {}	-- DONE
void RB_Banner_LInB() {}
void DECOMP_RB_CtrLetter_LInB() {}
void DECOMP_RB_CtrLetter_LInC() {}
void DECOMP_RB_Crystal_LInB() {}
void DECOMP_RB_Crystal_LInC() {}
void DECOMP_RB_Teeth_LInB() {}
void DECOMP_RB_Teeth_LInC() {}

void AH_Sign_LInB() {}
//void DECOMP_AH_Door_LInB() {}		-- DONE
//void DECOMP_AH_Garage_LInB() {}	-- DONE
//void DECOMP_AH_SaveObj_LInB() {}	-- DONE
//void DECOMP_AH_WarpPad_LInB() {}	-- DONE

void CS_LevThread_LInB() {}
#endif

// Missing from Decomp/General:
// GenericMine, Orca, Spider, Banner, Sign, CS

// This inserts debug names if needed
#if 1
#define SET_MDM(x,y,z) {.name = 0, .LInB = y, .LInC = z}
#else
#define SET_MDM(x,y,z) {.name = x, .LInB = y, .LInC = z}
#endif

struct Data data =
{
	.ArcadeDifficulty =
	{
		[0] =
		{
				.params1 =
				{
						0x0280,0x0300,0x0f00,0x1700,0x1f00,0x2700,0x2f00,0x3f00,0x044c,0xfffffbb4,0x0000,0xfffff060,0xfffffa24,0xfffffe70,
				},
				.params2 =
				{
						0xfffff800,0xfffffc00,0xfffffd00,0x0780,0x0f00,0x18f4,0x22e8,0x2f00,0x0d48,0x04b0,0xfffffe0c,0xffffe890,0xfffff830,0xfffffc18,
				},
		},
		[1] =
		{
				.params1 =
				{
						0x0280,0x0300,0x0f00,0x1700,0x1f00,0x2700,0x2f00,0x3f00,0x044c,0xfffffbb4,0x0000,0xfffff060,0xfffffa24,0xfffffe70,
				},
				.params2 =
				{
						0xfffff800,0xfffffc00,0xfffffd00,0x0780,0x0f00,0x18f4,0x22e8,0x2f00,0x0c80,0x04b0,0xfffffe0c,0xffffe890,0xfffff830,0xfffffc18,
				},
		},
		[2] =
		{
				.params1 =
				{
						0x0280,0x0300,0x0f00,0x1700,0x1f00,0x2700,0x2f00,0x3f00,0x04b0,0xfffffc18,0x0000,0xfffff060,0xfffffa24,0xfffffe70,
				},
				.params2 =
				{
						0xfffff800,0xfffffc00,0xfffffd00,0x0780,0x0f00,0x18f4,0x22e8,0x2f00,0x1194,0x04b0,0xfffffe0c,0xffffe890,0xfffff830,0xfffffc18,
				},
		},
		[3] =
		{
				.params1 =
				{
						0x0280,0x0300,0x0f00,0x1700,0x1f00,0x2700,0x2f00,0x3f00,0x044c,0xfffffbb4,0x0000,0xfffff060,0xfffffda8,0xfffffe70,
				},
				.params2 =
				{
						0xfffff800,0xfffffc00,0xfffffd00,0x0780,0x0f00,0x18f4,0x22e8,0x2f00,0x0fa0,0x04b0,0xfffffe0c,0xffffe890,0xfffffce0,0xfffffc18,
				},
		},
		[4] =
		{
				.params1 =
				{
						0x0280,0x0300,0x0f00,0x1700,0x1f00,0x2700,0x5700,0x3f00,0x044c,0xfffffbb4,0x0000,0xfffff060,0xfffffa24,0xfffffe70,
				},
				.params2 =
				{
						0xfffffc00,0xfffffe00,0xffffff00,0x0600,0x0b00,0x18f4,0x22e8,0x2f00,0x0e74,0x04b0,0xfffffe0c,0xffffe890,0xfffff830,0xfffffc18,
				},
		},
		[5] =
		{
				.params1 =
				{
						0x0280,0x0300,0x0f00,0x1700,0x1f00,0x2700,0x2f00,0x3f00,0x04b0,0xfffffc18,0x0000,0xfffff060,0xfffffa24,0xfffffe70,
				},
				.params2 =
				{
						0xfffffb00,0xfffffc00,0xfffffd00,0x0600,0x0780,0x1700,0x1fc8,0x2f00,0x09c4,0x03e8,0xfffffe0c,0xffffe890,0xfffff830,0xfffffc18,
				},
		},
		[6] =
		{
				.params1 =
				{
						0x0280,0x0300,0x0700,0x1700,0x1f00,0x2700,0x2f00,0x3f00,0x044c,0xfffffbb4,0x0000,0xfffff060,0xfffffa24,0xfffffe70,
				},
				.params2 =
				{
						0xfffffa00,0xfffffd00,0xfffffe00,0x0780,0x0f00,0x18f4,0x22e8,0x2f00,0x0dac,0x04b0,0xfffffe0c,0xffffe890,0xfffff830,0xfffffc18,
				},
		},
		[7] =
		{
				.params1 =
				{
						0x0280,0x0300,0x0f00,0x1700,0x1f00,0x2700,0x2f00,0x3f00,0x044c,0xfffffbb4,0x0000,0xfffff060,0xfffffa24,0xfffffe70,
				},
				.params2 =
				{
						0xfffff800,0xfffffc00,0xfffffd00,0x0780,0x0f00,0x18f4,0x22e8,0x2f00,0x0d48,0x03e8,0xfffffda8,0xffffe890,0xfffff830,0xfffffc18,
				},
		},
		[8] =
		{
				.params1 =
				{
						0x0280,0x0300,0x0f00,0x1700,0x1f00,0x2700,0x2f00,0x3f00,0x041a,0xfffffbb4,0x0000,0xfffff060,0xfffffa24,0xfffffe70,
				},
				.params2 =
				{
						0xfffff800,0xfffffc00,0xfffffd00,0x0780,0x0f00,0x18f4,0x22e8,0x2f00,0x0e10,0x04b0,0xfffffe0c,0xffffe890,0xfffff830,0xfffffc18,
				},
		},
		[9] =
		{
				.params1 =
				{
						0x0280,0x0300,0x0f00,0x1700,0x1f00,0x2700,0x2f00,0x3f00,0x044c,0xfffffbb4,0x0000,0xfffff060,0xfffffa24,0xfffffe70,
				},
				.params2 =
				{
						0xfffff800,0xfffffc00,0xfffffd00,0x0780,0x0f00,0x18f4,0x22e8,0x2f00,0x0fa0,0x04b0,0xfffffe0c,0xffffe890,0xfffff830,0xfffffc18,
				},
		},
		[10] =
		{
				.params1 =
				{
						0x0280,0x0300,0x0f00,0x1700,0x1f00,0x2700,0x2f00,0x3f00,0x04b0,0xfffffbb4,0x0000,0xfffff060,0xfffffa24,0xfffffe70,
				},
				.params2 =
				{
						0xfffff800,0xfffffc00,0xfffffd00,0x0780,0x0f00,0x18f4,0x22e8,0x2f00,0x1004,0x04b0,0xfffffe0c,0xffffe890,0xfffff830,0xfffffc18,
				},
		},
		[11] =
		{
				.params1 =
				{
						0x0280,0x0300,0x0f00,0x1700,0x1f00,0x2700,0x2f00,0x3f00,0x044c,0xfffffbb4,0x0000,0xfffff060,0xfffffa24,0xfffffe70,
				},
				.params2 =
				{
						0xfffff800,0xfffffc00,0xfffffd00,0x0780,0x0f00,0x18f4,0x22e8,0x2f00,0x0fa0,0x04b0,0xfffffe0c,0xffffe890,0xfffff830,0xfffffc18,
				},
		},
		[12] =
		{
				.params1 =
				{
						0x0280,0x0300,0x0f00,0x1700,0x1f00,0x2700,0x2f00,0x3f00,0x044c,0xfffffbb4,0x0000,0xfffff060,0xfffffa24,0xfffffe70,
				},
				.params2 =
				{
						0xfffff800,0xfffffc00,0xfffffd00,0x0780,0x0f00,0x18f4,0x22e8,0x2f00,0x0dac,0x04b0,0xfffffe0c,0xffffe890,0xfffff830,0xfffffc18,
				},
		},
		[13] =
		{
				.params1 =
				{
						0x0280,0x0300,0x0f00,0x1700,0x1f00,0x2700,0x2f00,0x3f00,0x044c,0xfffffbb4,0x0000,0xfffff060,0xfffffa24,0xfffffe70,
				},
				.params2 =
				{
						0xfffff800,0xfffffc00,0xfffffd00,0x0780,0x0f00,0x18f4,0x22e8,0x2f00,0x1004,0x04b0,0xfffffe0c,0xffffe890,0xfffff830,0xfffffc18,
				},
		},
		[14] =
		{
				.params1 =
				{
						0x0280,0x0300,0x0f00,0x1700,0x1f00,0x2700,0x5700,0x3f00,0x044c,0xfffffbb4,0x0000,0xfffff060,0xfffffa24,0xfffffe70,
				},
				.params2 =
				{
						0xfffffa00,0xfffffd00,0xfffffe00,0x0780,0x0f00,0x18f4,0x22e8,0x2f00,0x0fa0,0x04b0,0xfffffe0c,0xffffe890,0xfffff830,0xfffffc18,
				},
		},
		[15] =
		{
				.params1 =
				{
						0x0280,0x0300,0x0f00,0x1700,0x1f00,0x2700,0x2f00,0x3f00,0x044c,0xfffffbb4,0x0000,0xfffff060,0xfffffa24,0xfffffe70,
				},
				.params2 =
				{
						0xfffff800,0xfffffc00,0xfffffd00,0x0780,0x0f00,0x18f4,0x22e8,0x2f00,0x1004,0x04b0,0xfffffe0c,0xffffe890,0xfffff830,0xfffffc18,
				},
		},
		[16] =
		{
				.params1 =
				{
						0x0280,0x0300,0x0f00,0x1700,0x1f00,0x2700,0x2f00,0x3f00,0x044c,0xfffffbb4,0x0000,0xfffff060,0xfffffa24,0xfffffe70,
				},
				.params2 =
				{
						0xfffffb00,0xfffffc00,0xfffffd00,0x0780,0x0f00,0x18f4,0x22e8,0x2f00,0x0f3c,0x04b0,0xfffffe0c,0xffffe890,0xfffff830,0xfffffc18,
				},
		},
		[17] =
		{
				.params1 =
				{
						0x0280,0x0300,0x0f00,0x1700,0x1f00,0x2700,0x2f00,0x3f00,0x044c,0xfffffbb4,0x0000,0xfffff060,0xfffffa24,0xfffffe70,
				},
				.params2 =
				{
						0xfffff800,0xfffffc00,0xfffffd00,0x0680,0x0f00,0x18f4,0x22e8,0x2f00,0x0e74,0x04b0,0xfffffe0c,0xffffe890,0xfffff830,0xfffffc18,
				},
		},
	},

	.BossDifficulty =
	{
		[0] =
		{
				.params1 =
				{
						0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0x0dac,0xfffffbb4,0xfffff254,0xfffffc18,0xfffffed4,0x0320,
				},
				.params2 =
				{
						0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0x1194,0xfffffbb4,0xfffff830,0xfffffc18,0xfffffe0c,0xffffff9c,
				},
		},
		[1] =
		{
				.params1 =
				{
						0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0x0dac,0xfffffbb4,0xfffff254,0xfffffc18,0xfffffed4,0x0320,
				},
				.params2 =
				{
						0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0x1194,0xfffffbb4,0xfffff830,0xfffffc18,0xfffffe0c,0xffffff9c,
				},
		},
		[2] =
		{
				.params1 =
				{
						0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0x0dac,0xfffffbb4,0xfffff254,0xfffffc18,0xfffffed4,0x0320,
				},
				.params2 =
				{
						0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0x1194,0xfffffbb4,0xfffff830,0xfffffc18,0xfffffe0c,0xffffff9c,
				},
		},
		[3] =
		{
				.params1 =
				{
						0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0x0ed8,0xfffffbb4,0xfffff254,0xfffffc18,0xfffffed4,0x0320,
				},
				.params2 =
				{
						0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0x1194,0xfffffbb4,0xfffff830,0xfffffc18,0xfffffe0c,0xffffff9c,
				},
		},
		[4] =
		{
				.params1 =
				{
						0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0x0ed8,0xfffffbb4,0xfffff254,0xfffffc18,0xfffffed4,0x0320,
				},
				.params2 =
				{
						0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0x1194,0xfffffbb4,0xfffff830,0xfffffc18,0xfffffe0c,0xffffff9c,
				},
		},
		[5] =
		{
				.params1 =
				{
						0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0x0ed8,0xfffffbb4,0xfffff254,0xfffffc18,0xfffffed4,0x0320,
				},
				.params2 =
				{
						0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0xfffffa00,0x1194,0xfffffbb4,0xfffff830,0xfffffc18,0xfffffe0c,0xffffff9c,
				},
		},
	},

	.advDifficulty =
	{
		0x0, 0x3, 0x6, 0xB, 0x13, 0x1D,
		0x29, 0x38, 0x4A, 0x60, 0x79, 0x0
	},

	.kartSpawnOrder =
	{
		// attempt to "feel" random
		.VS_2P_1 = 0x4020100,
		.VS_2P_2 = 0x7030605,

		// default
		.VS_3P_4P_1 = 0x3020100,
		.VS_3P_4P_2 = 0x7060504,

		// spawn center of track
		.time_trial_1 = 0x3000201,
		.time_trial_2 = 0x7060504,

		// default
		.crystal_challenge_1 = 0x3020100,
		.crystal_challenge_2 = 0x7060504,

		// default
		.boss_challenge_1 = 0x3020100,
		.boss_challenge_2 = 0x7060504,

		// default
		.purple_cup_1 = 0x3020100,
		.purple_cup_2 = 0x7060504,

		// default
		.arcade_1 = 0x3020100,
		.arcade_2 = 0x7060504,
	},

	.botsThrottle =
	{
		// one per NavPath, Hot Air Skyway
		0x1CC,
		0x1BD,
		0x1B4,

		// one per NavPath, Polar Pass
		0x15E,
		0x151,
		0x156,

		// one per NavPath, Papu Pyramid
		0xF0,
		0xE9,
		0xF6,

		// one per NavPath, Slide Col
		0x8C,
		0x85,
		0x8B
	},

	// used for BOTS
	.identity =
	{
		.m =
		{
			{0x1000, 0x0, 0x0},
			{0x0, 0x1000, 0x0},
			{0x0, 0x0, 0x1000},
		},

		.t = {0,-0x20,0}
	},

	.NearCam4x3 =
	{
		.distMin = 0xB3,
		.distMax = 0xE0,
		.speedMin = 0x400,
		.speedMax = 0x1400,
		.percentage1 = 0xF0, // 90%
		.percentage2 = 0xFF, // 99%
		.angle[0] = 0x80,
		.angle[1] = 0xE0,
		.angle[2] = 0x70,
		.vertDistance = 0x40
	},

	.NearCam8x3 =
	{
		.distMin = 0x133,
		.distMax = 0x14c,
		.speedMin = 0x400,
		.speedMax = 0x1400,
		.percentage1 = 0xF0, // 90%
		.percentage2 = 0xFF, // 99%
		.angle[0] = 0x80,
		.angle[1] = 0xE0,
		.angle[2] = 0x60,
		.vertDistance = 0x60
	},

	.FarCam4x3 =
	{
		.distMin = 0xE0,
		.distMax = 0x120,
		.speedMin = 0x400,
		.speedMax = 0x1400,
		.percentage1 = 0xF0, // 90%
		.percentage2 = 0xFF, // 99%
		.angle[0] = 0x80,
		.angle[1] = 0xE0,
		.angle[2] = 0x60,
		.vertDistance = 0x60
	},

	.FarCam8x3 =
	{
		.distMin = 0x180,
		.distMax = 0x1B3,
		.speedMin = 0x400,
		.speedMax = 0x1400,
		.percentage1 = 0xF0, // 90%
		.percentage2 = 0xFF, // 99%
		.angle[0] = 0x80,
		.angle[1] = 0xE0,
		.angle[2] = 0x60,
		.vertDistance = 0xA0
	},

	.EndOfRace_Camera_Size =
	{
		0,		// mode 0 (CAM_FollowDriver_Normal)
		-1,		// mode 1 (doesn't exist)
		-1,		// mode 2 (doesn't exist)
		0xC,	// mode 3 (freecam)
		0x6, 	// mode 4 (lookAt and frozen)
		-1,		// mode 5 (doesn't exist)
		-1,		// mode 6 (doesn't exist)
		0x6,	// mode 7
		0xC,	// mode 8
		0x10,	// mode 9 (trackSel and follow path)
		0x6,	// mode A (CAM_FollowDriver_Spin360)
		0xC,	// mode B (LookAt and ???)
		0x14,	// mode C (TransitionTo)
		0x10,	// mode D (lookAt and follow path)
		0xC,	// mode E
		0,		// mode F (first person)
		0,		// mode 10 (first person)
	},

	.Spin360_heightOffset_cameraPos =
	{
		0,		// not possible
		0x80,	// 1P
		0x60,	// 2P
		0x80,	// 3P
		0x80	// 4P
	},

	.Spin360_heightOffset_driverPos =
	{
		0,		// not possible
		0x60,	// 1P
		0x40,	// 2P
		0x60,	// 3P
		0x60	// 4P
	},

	.s_XA_ENG_XNF 	= "\\XA\\ENG.XNF;1",
	.s_XA_MUSIC 	= "\\XA\\MUSIC\\S00.XA;1",
	.s_XA_ENG_EXTRA	= "\\XA\\ENG\\EXTRA\\S00.XA;1",
	.s_XA_ENG_GAME	= "\\XA\\ENG\\GAME\\S00.XA;1",

	.xaLanguagePtrs =
	{
		sdata_static.s_JPN,
		sdata_static.s_ENG,
		sdata_static.s_FRN,
		sdata_static.s_GRM,
		sdata_static.s_ITL,
		sdata_static.s_SPN,
		sdata_static.s_DCH
	},

	.audioMeta[0] =
	{
		.stringIndex_char1 = 0xB,
		.stringIndex_char2 = 0xC,

		.name = data.s_XA_MUSIC
	},

	.audioMeta[1] =
	{
		.stringIndex_char1 = 0xF,
		.stringIndex_char2 = 0x10,

		.name = data.s_XA_ENG_EXTRA
	},

	.audioMeta[2] =
	{
		.stringIndex_char1 = 0xE,
		.stringIndex_char2 = 0xF,

		.name = data.s_XA_ENG_GAME
	},

	.MetaDataModels =
	{
		// turn off for rebuild_ps1,
		// leave on for rebuild_pc,
		// leave on for decomp/General
		#if 1

		// 0x00 - NO_FUNC
		SET_MDM(0,0,0),

		// 0x01 - ANIMATE_IF_HIT
		SET_MDM(0,0,0),

		// 0x02 - PU_WUMPA_FRUIT
		// OG game births a thread, calls ThCollide, then dies,
		// DECOMP shouldn't birth in LInC, just trigger HUD,
		// Use Crystal_LInC, optimized for Crystal and Fruit
		SET_MDM(0,DECOMP_RB_Fruit_LInB,DECOMP_RB_Crystal_LInC),

		// 0x03 - PU_SMALL_BOMB
		SET_MDM(0,0,0),

		// 0x04 - PU_LARGE_BOMB
		SET_MDM(0,0,0),

		// 0x05 - PU_MISSILE
		SET_MDM(0,0,0),

		// 0x06 - PU_EXPLOSIVE_CRATE (nitro)
		// used for Crystal Challenge TNT/Nitro, no BSP collision,
		// LInB births thread that checks for collision every frame,
		// DECOMP should birth unthreaded instances, and add hitboxes
		SET_MDM(0,RB_GenericMine_LInB,0),

		// 0x07 - PU_FRUIT_CRATE
		SET_MDM(0,DECOMP_RB_Default_LInB,DECOMP_RB_CrateFruit_LInC),

		// 0x08 - PU_RANDOM_CRATE (Weapon Box)
		SET_MDM(0,DECOMP_RB_Default_LInB,DECOMP_RB_CrateWeapon_LInC),

		// 0x09 - PU_TIME_CRATE_1 (unused duplicate of 0x5C)
		SET_MDM(0,0,0),

		// 0x0A - PU_TIME_CRATE_2 (unused duplicate of 0x64)
		SET_MDM(0,0,0),

		// 0x0B - PU_TIME_CRATE_3 (unused duplicate of 0x65)
		SET_MDM(0,0,0),

		// 0x0C - PU_POISON
		SET_MDM(0,0,0),

		// 0x0D - PU_SHIELD
		SET_MDM(0,0,0),

		// 0x0E - PU_INVINCIBILITY
		SET_MDM(0,0,0),

		// 0x0F - PU_SPRING
		SET_MDM(0,0,0),

		// 0x10 - PU_CLOCK
		SET_MDM(0,0,0),

		// 0x11 - PU_TURBO
		SET_MDM(0,0,0),

		// 0x12 - FLAME_JET (tiger temple)
		SET_MDM(0,DECOMP_RB_FlameJet_LInB,0),

		// 0x13 - PIRANHA_PLANT (papu pyramid)
		SET_MDM(0,DECOMP_RB_Plant_LInB,0),

		// 0x14 - GATE
		SET_MDM(0,0,0),

		// 0x15 - START_LINE
		SET_MDM(0,0,0),

		// 0x16 - SPRING
		SET_MDM(0,0,0),

		// 0x17 - TURBO
		SET_MDM(0,0,0),

		// 0x18 - DYNAMIC_PLAYER (player driver)
		SET_MDM(0,0,0),

		// 0x19 - DYNAMIC_SMALL_BOMB
		SET_MDM(0,0,0),

		// 0x1a - DYNAMIC_LARGE_BOMB
		SET_MDM(0,0,0),

		// 0x1b - DYNAMIC_MISSILE
		SET_MDM(0,0,0),

		// 0x1c - DYNAMIC_EXPLOSIVE_CRATE
		SET_MDM(0,0,0),

		// 0x1d - DYNAMIC_POISON
		SET_MDM(0,0,0),

		// 0x1e - DYNAMIC_INVICIBILITY
		SET_MDM(0,0,0),

		// 0x1f - DYNAMIC_SPLINE_FOLLOWER
		SET_MDM(0,0,0),

		// 0x20 - DYNAMIC_SNOWBALL (demo blizzard bluff)
		SET_MDM(0,0,0),

		// 0x21 - DYNAMIC_MINE_CART
		SET_MDM(0,DECOMP_RB_Minecart_LInB,0),

		// 0x22 - TEMP_SNOWBALL (blizzard bluff boulder)
		SET_MDM(0,DECOMP_RB_Snowball_LInB,0),

		// 0x23 - FINISH_LINE
		SET_MDM(0,0,0),

		// 0x24 - ARMADILLO (armadillo)
		SET_MDM(0,DECOMP_RB_Armadillo_LInB,0),

		// 0x25 - BLADE
		SET_MDM(0,DECOMP_RB_Blade_LInB,0),

		// 0x26 - STATIC_CRATE_EXPLOSION
		SET_MDM(0,0,0),

		// 0x27 - STATIC_CRATE_TNT
		// used for Crystal Challenge TNT/Nitro, no BSP collision,
		// LInB births thread that checks for collision every frame,
		// DECOMP should birth unthreaded instances, and add hitboxes
		SET_MDM(0,RB_GenericMine_LInB,0),

		// 0x28 - STATIC_CRATE_NITRO (unused duplicate of 0x6)
		SET_MDM(0,0,0),

		// 0x29 - DYNAMIC_ROCKET "bombtracker"
		SET_MDM(0,0,0),

		// 0x2a - DYNAMIC_BIGROCKET
		SET_MDM(0,0,0),

		// 0x2b - STATIC_WARPEDBURST "explosion2"
		SET_MDM(0,0,0),

		// 0x2c - STATIC_TURBO_EFFECT
		SET_MDM(0,0,0),

		// 0x2d - STATIC_TURBO_EFFECT1
		SET_MDM(0,0,0),

		// 0x2e - STATIC_TURBO_EFFECT2
		SET_MDM(0,0,0),

		// 0x2f - STATIC_TURBO_EFFECT3
		SET_MDM(0,0,0),

		// 0x30 - STATIC_TURBO_EFFECT4
		SET_MDM(0,0,0),

		// 0x31 - STATIC_TURBO_EFFECT5
		SET_MDM(0,0,0),

		// 0x32 - STATIC_TURBO_EFFECT6
		SET_MDM(0,0,0),

		// 0x33 - STATIC_TURBO_EFFECT7
		SET_MDM(0,0,0),

		// 0x34 - STATIC_TURBO_EFFECT_DARK
		SET_MDM(0,0,0),

		// 0x35 - STATIC_SHOCKWAVE
		SET_MDM(0,0,0),

		// 0x36 - DYNAMIC_WARPBALL
		SET_MDM(0,0,0),

		// 0x37 - STATIC_FRUITDISP (HUD)
		SET_MDM(0,0,0),

		// 0x38 - STATIC_BIG1 "Empty" used for Oxide Podium
		SET_MDM(0,0,0),

		// 0x39 - STATIC_AKUAKU
		SET_MDM(0,0,0),

		// 0x3a - STATIC_UKAUKA
		SET_MDM(0,0,0),

		// 0x3b - DYNAMIC_BOMB
		SET_MDM(0,0,0),

		// 0x3c - STATIC_BEAKER
		SET_MDM(0,0,0),

		// 0x3d - STATIC_BEAKERBREAK
		SET_MDM(0,0,0),

		// 0x3e - STATIC_AKUBEAM
		SET_MDM(0,0,0),

		// 0x3f - DYNAMIC_ROBOT_CAR (AI driver)
		SET_MDM(0,0,0),

		// 0x40 - STATIC_UKABEAM
		SET_MDM(0,0,0),

		// 0x41 - STATIC_SHIELD
		SET_MDM(0,0,0),

		// 0x42 - STATIC_CLOUD
		SET_MDM(0,0,0),

		// 0x43 - STATIC_WAKE
		SET_MDM(0,0,0),

		// 0x44 - STATIC_SHOCKWAVE_RED
		SET_MDM(0,0,0),

		// 0x45 - STATIC_SHOCKWAVE_GREEN
		SET_MDM(0,0,0),

		// 0x46 - STATIC_BEAKER_RED
		SET_MDM(0,0,0),

		// 0x47 - STATIC_BEAKER_GREEN
		SET_MDM(0,0,0),

		// 0x48 - STATIC_BEAKERBREAK_RED
		SET_MDM(0,0,0),

		// 0x49 - STATIC_BEAKERBREAK_GREEN
		SET_MDM(0,0,0),

		// 0x4a - LENSFLARE
		SET_MDM(0,0,0),

		// 0x4b - DYNAMIC_GHOST (ghost driver)
		SET_MDM(0,0,0),

		// 0x4c - DYNAMIC_SEAL (polar pass)
		SET_MDM(0,DECOMP_RB_Seal_LInB,0),

		// 0x4d - DYNAMIC_ORCA (unused, polar pass)
		SET_MDM(0,0 /*RB_Orca_LInB*/,0),

		// 0x4e - DYNAMIC_BARREL (sewer speedway)
		SET_MDM(0,DECOMP_RB_Snowball_LInB,0),

		// 0x4f - DYNAMIC_VONLABASS (unused, hot air skyway)
		SET_MDM(0,DECOMP_RB_Baron_LInB,0),

		// 0x50 - DYNAMIC_SKUNK (unused, unknown track)
		SET_MDM(0,0 /*RB_Minecart_LInB*/,0),

		// 0x51 - DYNAMIC_TURTLE (mystery caves)
		SET_MDM(0,DECOMP_RB_Turtle_LInB,DECOMP_RB_Turtle_LInC),

		// 0x52 - DYNAMIC_SPIDER (cortex castle)
		SET_MDM(0,DECOMP_RB_Spider_LInB,0),

		// 0x53 - DYNAMIC_SPIDERSHADOW
		SET_MDM(0,0,0),

		// 0x54 - DYNAMIC_FIREBALL (mystery caves fireball)
		// DECOMP version removed LInC, it does nothing
		SET_MDM(0,DECOMP_RB_Fireball_LInB,0),

		// 0x55 - DYNAMIC_DRUM (n gin labs barrel)
		SET_MDM(0,DECOMP_RB_Baron_LInB,0),

		// 0x56 - DYNAMIC_SHIELD (blue shield)
		SET_MDM(0,0,0),

		// 0x57 - STATIC_PIPE1
		SET_MDM(0,0,0),

		// 0x58 - STATIC_PIPE2
		SET_MDM(0,0,0),

		// 0x59 - STATIC_VENT
		SET_MDM(0,0,0),

		// 0x5a - DYNAMIC_SHIELD_DARK
		SET_MDM(0,0,0),

		// 0x5b - STATIC_CASTLE_SIGN
		SET_MDM(0,0,0),

		// 0x5c - STATIC_TIME_CRATE_01
		SET_MDM(0,DECOMP_RB_Default_LInB,DECOMP_RB_CrateTime_LInC),

		// 0x5d - DYNAMIC_HIGHLIGHT
		SET_MDM(0,0,0),

		// 0x5e - DYNAMIC_SHIELD_GREEN
		SET_MDM(0,0,0),

		// 0x5f - STATIC_GEM
		SET_MDM(0,0,0),

		// 0x60 - STATIC_CRYSTAL
		// LInC should not birth a thread, nor call ThCollide,
		// LInC should only kill LInB's thread and trigger HUD
		SET_MDM(0,DECOMP_RB_Crystal_LInB,DECOMP_RB_Crystal_LInC),

		// 0x61 - STATIC_RELIC
		SET_MDM(0,0,0),

		// 0x62 - STATIC_TROPHY
		SET_MDM(0,0,0),

		// 0x63 - STATIC_KEY
		SET_MDM(0,0,0),

		// 0x64 - STATIC_TIME_CRATE_02
		SET_MDM(0,DECOMP_RB_Default_LInB,DECOMP_RB_CrateTime_LInC),

		// 0x65 - STATIC_TIME_CRATE_03
		SET_MDM(0,DECOMP_RB_Default_LInB,DECOMP_RB_CrateTime_LInC),

		// 0x66 - STATIC_INTRO_TROPHY
		SET_MDM(0,0,0),

		// 0x67 - STATIC_INTRO_CRASH
		SET_MDM(0,0,0),

		// 0x68 - STATIC_RINGTOP
		SET_MDM(0,0,0),

		// 0x69 - STATIC_RINGBOTTOM
		SET_MDM(0,0,0),

		// 0x6a - STATIC_CTR
		SET_MDM(0,0,0),

		// 0x6b - STATIC_BANNER
		SET_MDM(0,0,0),

		// 0x6C - STATIC_WARPPAD
		SET_MDM(0,DECOMP_AH_WarpPad_LInB,0),

		// 0x6D - STATIC_BIG0
		SET_MDM(0,0,0),

		// 0x6e - STATIC_BIG9
		SET_MDM(0,0,0),

		// 0x6f - STATIC_BIGX
		SET_MDM(0,0,0),

		// 0x70 - STATIC_TEETH
		SET_MDM(0,DECOMP_RB_Teeth_LInB,DECOMP_RB_Teeth_LInC),

		// 0x71 - STATIC_STARTTEXT
		SET_MDM(0,0/*RB_StartText_LInB*/,0),

		// 0x72 - STATIC_SAVEOBJ
		SET_MDM(0,DECOMP_AH_SaveObj_LInB,0),

		// 0x73 - STATIC_PINGARAGE
		SET_MDM(0,DECOMP_AH_Garage_LInB,0),

		// 0x74 - STATIC_PAPUGARAGE
		SET_MDM(0,DECOMP_AH_Garage_LInB,0),

		// 0x75 - STATIC_ROOGARAGE
		SET_MDM(0,DECOMP_AH_Garage_LInB,0),

		// 0x76 - STATIC_JOEGARAGE
		SET_MDM(0,DECOMP_AH_Garage_LInB,0),

		// 0x77 - STATIC_OXIDEGARAGE
		SET_MDM(0,DECOMP_AH_Garage_LInB,0),

		// 0x78 - STATIC_SCAN (load/save screen)
		SET_MDM(0,0,0),

		// 0x79 - STATIC_SUBTRACT
		SET_MDM(0,0,0),

		// 0x7a - STATIC_DOOR
		SET_MDM(0,DECOMP_AH_Door_LInB,0),

		// 0x7b - STATIC_BEAM (warppad vortex)
		SET_MDM(0,0,0),

		// 0x7c - STATIC_BOTTOMRING (warppad spiral dots)
		SET_MDM(0,0,0),

		// 0x7d - STATIC_TOKEN
		SET_MDM(0,0,0),

		// 0x7e - STATIC_CRASHDANCE
		SET_MDM(0,0,0),

		// 0x7f - STATIC_CORTEXDANCE
		SET_MDM(0,0,0),

		// 0x80 - STATIC_TINYDANCE
		SET_MDM(0,0,0),

		// 0x81 - STATIC_COCODANCE
		SET_MDM(0,0,0),

		// 0x82 - STATIC_NGINDANCE
		SET_MDM(0,0,0),

		// 0x83 - STATIC_DINGODANCE
		SET_MDM(0,0,0),

		// 0x84 - STATIC_POLARDANCE
		SET_MDM(0,0,0),

		// 0x85 - STATIC_PURADANCE
		SET_MDM(0,0,0),

		// 0x86 - STATIC_PINSTRIPEDANCE
		SET_MDM(0,0,0),

		// 0x87 - STATIC_PAPUDANCE
		SET_MDM(0,0,0),

		// 0x88 - STATIC_ROODANCE
		SET_MDM(0,0,0),

		// 0x89 - STATIC_JOEDANCE
		SET_MDM(0,0,0),

		// 0x8a - STATIC_NTROPYDANCE
		SET_MDM(0,0,0),

		// 0x8b - STATIC_PENDANCE
		SET_MDM(0,0,0),

		// 0x8c - STATIC_FAKEDANCE
		SET_MDM(0,0,0),

		// 0x8d - STATIC_OXIDEDANCE
		SET_MDM(0,0,0),

		// 0x8e - STATIC_GARAGETOP
		SET_MDM(0,0,0),

		// 0x8f - STATIC_TAWNA1
		SET_MDM(0,0,0),

		// 0x90 - STATIC_TAWNA2
		SET_MDM(0,0,0),

		// 0x91 - STATIC_TAWNA3
		SET_MDM(0,0,0),

		// 0x92 - STATIC_TAWNA4
		SET_MDM(0,0,0),

		// 0x93 - STATIC_C
		// LInC should not birth a thread, nor call ThCollide,
		// LInC should only kill LInB's thread and trigger HUD
		SET_MDM(0,DECOMP_RB_CtrLetter_LInB,DECOMP_RB_CtrLetter_LInC),

		// 0x94 - STATIC_T
		// LInC should not birth a thread, nor call ThCollide,
		// LInC should only kill LInB's thread and trigger HUD
		SET_MDM(0,DECOMP_RB_CtrLetter_LInB,DECOMP_RB_CtrLetter_LInC),

		// 0x95 - STATIC_R
		// LInC should not birth a thread, nor call ThCollide,
		// LInC should only kill LInB's thread and trigger HUD
		SET_MDM(0,DECOMP_RB_CtrLetter_LInB,DECOMP_RB_CtrLetter_LInC),

		// 0x96 - STATIC_CRASHINTRO
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0x97 - STATIC_COCOINTRO
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0x98 - STATIC_CORTEXINTRO
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0x99 - STATIC_TINYINTRO
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0x9A - STATIC_POLARINTRO
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0x9B - STATIC_DINGOINTRO
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0x9C - STATIC_OXIDEINTRO
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0x9D - STATIC_SIMPLEKARTINTRO
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0x9E - STATIC_TINYKARTINTRO
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0x9F - STATIC_DINGOKARTINTRO
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0xA0 - STATIC_SIMPLEOBJINTRO
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0xA1 - STATIC_PPOINTTHINGINTRO
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0xA2 - STATIC_PRTHINGINTRO
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0xA3 - STATIC_OXIDELILSHIP
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0xA4 - STATIC_INTROOXIDECAM
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0xA5 - STATIC_INTROOXIDEBODY
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0xa6 - STATIC_STARTBANNERWAVE
		SET_MDM(0,RB_Banner_LInB,0),

		// 0xa7 - STATIC_DOOR2
		SET_MDM(0,0,0),

		// 0xa8 - STATIC_PODIUM
		SET_MDM(0,0,0),

		// 0xa9 - STATIC_PINHEAD
		SET_MDM(0,0,0),

		// 0xaa - STATIC_PAPUHEAD
		SET_MDM(0,0,0),

		// 0xab - STATIC_ROOHEAD
		SET_MDM(0,0,0),

		// 0xac - STATIC_JOEHEAD
		SET_MDM(0,0,0),

		// 0xad - STATIC_OXIDEHEAD
		SET_MDM(0,0,0),

		// 0xae - STATIC_AKUMOUTH
		SET_MDM(0,0,0),

		// 0xaf - STATIC_DINGOFIRE
		SET_MDM(0,0,0),

		// 0xb0 - STATIC_TOMBSTONE
		SET_MDM(0,0,0),

		// 0xb1 - STATIC_AKUBIG
		SET_MDM(0,0,0),

		// 0xb2 - STATIC_UKABIG
		SET_MDM(0,0,0),

		// 0xb3 - STATIC_UKAMOUTH
		SET_MDM(0,0,0),

		// 0xb4 - STATIC_UNUSED03
		SET_MDM(0,0,0),

		// 0xb5 - STATIC_DOOR3
		SET_MDM(0,0,0),

		// 0xb6 - NDI_BOX_BOX_01
		SET_MDM(0,0,0),

		// 0xb7 - NDI_BOX_BOX_02
		SET_MDM(0,0,0),

		// 0xb8 - NDI_BOX_BOX_02_BOTTOM
		SET_MDM(0,0,0),

		// 0xb9 - NDI_BOX_BOX_02_FRONT
		SET_MDM(0,0,0),

		// 0xba - NDI_BOX_BOX_02A
		SET_MDM(0,0,0),

		// 0xbb - NDI_BOX_BOX_03
		SET_MDM(0,0,0),

		// 0xbc - NDI_BOX_CODE
		SET_MDM(0,0,0),

		// 0xbd - NDI_BOX_GLOW
		SET_MDM(0,0,0),

		// 0xbe - NDI_BOX_LID
		SET_MDM(0,0,0),

		// 0xbf - NDI_BOX_LID2
		SET_MDM(0,0,0),

		// 0xc0 - NDI_BOX_PARTICLES_01
		SET_MDM(0,0,0),

		// 0xc1 - NDI_KART0
		SET_MDM(0,0,0),

		// 0xc2 - NDI_KART1
		SET_MDM(0,0,0),

		// 0xc3 - NDI_KART2
		SET_MDM(0,0,0),

		// 0xc4 - NDI_KART3
		SET_MDM(0,0,0),

		// 0xc5 - NDI_KART4
		SET_MDM(0,0,0),

		// 0xc6 - NDI_KART5
		SET_MDM(0,0,0),

		// 0xc7 - NDI_KART6
		SET_MDM(0,0,0),

		// 0xc8 - NDI_KART7
		SET_MDM(0,0,0),

		// 0xc9 - NDI_BOX_LIDB
		SET_MDM(0,0,0),

		// 0xca - NDI_BOX_LIDC
		SET_MDM(0,0,0),

		// 0xcb - NDI_BOX_LIDD
		SET_MDM(0,0,0),

		// 0xcc - STATIC_INTRO_FLASH
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0xcd - STATIC_INTRODOORS
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0xce - STATIC_CRASHSELECT
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0xcf - STATIC_CORTEXSELECT
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0xd0 - STATIC_TINYSELECT
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0xd1 - STATIC_COCOSELECT
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0xd2 - STATIC_NGINSELECT
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0xd3 - STATIC_DINGOSELECT
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0xd4 - STATIC_POLARSELECT
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0xd5 - STATIC_PURASELECT
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0xd6 - STATIC_ENDDOORS
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0xd7 - STATIC_ENDFLASH
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0xd8 - STATIC_ENDINGOXIDE
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0xd9 - STATIC_ENDIGNOXIDE_02 (mispelled in-game)
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0xda - STATIC_ENDOXIDEBIGSHIP
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0xdb - STATIC_ENDOXIDELILSHIP
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0xdc - STATIC_OXIDECAMEND
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0xdd - STATIC_OXIDECAMEND02
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0xde - STATIC_JLOGO_FLAG
		SET_MDM(0,0,0),

		// 0xdf - STATIC_OXIDESPEAKER
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0xe0 - STATIC_INTROSPARKS
		SET_MDM(0,CS_LevThread_LInB,0),

		// 0xe1 - STATIC_GNORMALZ
		SET_MDM(0,AH_Sign_LInB,0),

		#endif
	},

	.ptrRenderedQuadblockDestination_forEachPlayer =
	{
		&sdata_static.quadBlocksRendered[0],
		&sdata_static.quadBlocksRendered[0x40],
		&sdata_static.quadBlocksRendered[0x80],
		&sdata_static.quadBlocksRendered[0xC0]
	},

	.ptrRenderedQuadblockDestination_again =
	{
		&sdata_static.quadBlocksRendered[0],
		&sdata_static.quadBlocksRendered[0x40],
		&sdata_static.quadBlocksRendered[0x80],
		&sdata_static.quadBlocksRendered[0xC0]
	},

	.colors =
	{
		{0xC8FF, 0xC8FF, 0xFF, 0xFF},				// ORANGE
		{0xFFC8C8, 0xFFC8C8, 0xE1A0A0, 0xE1A0A0},	// PERIWINKLE
		{0xC880, 0xC880, 0x80, 0x80},				// ORANGE_DARKENED
		{0xFF, 0xFF, 0x80, 0x80},					// RED
		{0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF},	// WHITE

		#define ALL4(x) {x,x,x,x}
		ALL4(0xF56600),	// CRASH_BLUE
		ALL4(0xF6),		// CORTEX_RED
		ALL4(0xDC5B),	// TINY_GREEN
		ALL4(0xF500F5),	// COCO_MAGENTA
		ALL4(0xFF00A9), // N_GIN_PURPLE
		ALL4(0xCCAA),	// DINGODILE_OLIVE
		ALL4(0xE6E600),	// POLAR_CYAN
		ALL4(0xFF0055),	// PURA_VIOLET
		ALL4(0x806040),	// PINSTRIPE_PALE_DARK_BLUE
		ALL4(0xD3E6),	// PAPU_YELLOW
		ALL4(0x7FFF),	// ROO_ORANGE
		ALL4(0x4797CC), // JOE_COLOR
		ALL4(0xFFBF40),	// TROPY_LIGHT_BLUE
		ALL4(0xFFFFFF),	// PENTA_WHITE
		ALL4(0x808080),	// FAKE_CRASH_GRAY
		ALL4(0x50E680),	// OXIDE_LIGHT_GREEN

		{0,0,0,0},									// BLACK
		{0x404040, 0xFFFFFF, 0xFFFFFF, 0x404040},	// SILVER
		{0x808080, 0x808080, 0x808080, 0x808080},	// GRAY

		ALL4(0xFF4800),	// PLAYER_BLUE
		ALL4(0x7F4),	// PLAYER_RED
		ALL4(0xAA00),	// PLAYER_GREEN
		ALL4(0xBCFF),	// PLAYER_YELLOW

		{0xC0, 0xC0, 0x80, 0x80},					// DARK_RED
		{0x88FF88, 0x88FF88, 0x208120, 0x208120},	// LIGHT_GREEN
		{0x28CF28, 0x28CF28, 0x4100, 0x4100},		// FORREST_GREEN
		{0x28CF28, 0x28CF28, 0x4100, 0x4100},		// CREDITS_FADE (dynamic)

		#if BUILD >= UsaRetail
		{0xFFD207, 0xFFD207, 0xFF6200, 0xFF6200},	// BLUE
		{0xEE6D, 0xEE6D, 0x8E09, 0x8E09},			// LIME_GREEN
		{0x40FF, 0x40FF, 0xC0, 0xC0},				// ORANGE_RED
		#endif
	},

	.ptrColor =
	{
		&data.colors[0][0], &data.colors[1][0], &data.colors[2][0], &data.colors[3][0],
		&data.colors[4][0], &data.colors[5][0], &data.colors[6][0], &data.colors[7][0],
		&data.colors[8][0], &data.colors[9][0], &data.colors[10][0], &data.colors[11][0],
		&data.colors[12][0], &data.colors[13][0], &data.colors[14][0], &data.colors[15][0],
		&data.colors[16][0], &data.colors[17][0], &data.colors[18][0], &data.colors[19][0],
		&data.colors[20][0], &data.colors[21][0], &data.colors[22][0], &data.colors[23][0],
		&data.colors[24][0], &data.colors[25][0], &data.colors[26][0], &data.colors[27][0],
		&data.colors[28][0], &data.colors[29][0], &data.colors[30][0], &data.colors[31][0],

		#if BUILD >= UsaRetail
		&data.colors[32][0], &data.colors[33][0], &data.colors[34][0],
		#endif
	},

	// These numbers have no meaning, just a scrambler table,
	// ND probably could have done something else and it would
	// have been just as much random, without "this" much memory
	.ghostScrambleData =
	{
		0x0009, 0x0009,
		0x000a, 0x000d,
		0x000d, 0x000d,
		0x0020, 0x0020,
		0x0021, 0x0021,
		0x0022, 0x0022,
		0x0025, 0x0025,
		0x0027, 0x0027,
		0x0028, 0x002d,
		0x0029, 0x002d,
		0x002a, 0x002a,
		0x002b, 0x002b,
		0x002c, 0x002c,
		0x002d, 0x002d,
		0x002e, 0x002e,
		0x002f, 0x002f,
		0x0030, 0x0030,
		0x0031, 0x0031,
		0x0032, 0x0032,
		0x0033, 0x0033,
		0x0034, 0x0034,
		0x0035, 0x0035,
		0x0036, 0x0036,
		0x0037, 0x0037,
		0x0038, 0x0038,
		0x0039, 0x0039,
		0x003a, 0x003a,
		0x003c, 0x003c,
		0x003d, 0x003d,
		0x003e, 0x003e,
		0x003f, 0x003f,
		0x0040, 0x0040,
		0x0041, 0x0041,
		0x0042, 0x0042,
		0x0043, 0x0043,
		0x0044, 0x0044,
		0x0045, 0x0045,
		0x0046, 0x0046,
		0x0047, 0x0047,
		0x0048, 0x0048,
		0x0049, 0x0049,
		0x004a, 0x004a,
		0x004b, 0x004b,
		0x004c, 0x004c,
		0x004d, 0x004d,
		0x004e, 0x004e,
		0x004f, 0x004f,
		0x0050, 0x0050,
		0x0051, 0x0051,
		0x0052, 0x0052,
		0x0053, 0x0053,
		0x0054, 0x0054,
		0x0055, 0x0055,
		0x0056, 0x0056,
		0x0057, 0x0057,
		0x0058, 0x0058,
		0x0059, 0x0059,
		0x005a, 0x005a,
		0x005b, 0x005b,
		0x005c, 0x005c,
		0x005e, 0x005e,
		0x005f, 0x005f,
		0x0061, 0x0061,
		0x0062, 0x0062,
		0x0063, 0x0063,
		0x0064, 0x0064,
		0x0065, 0x0065,
		0x0066, 0x0066,
		0x0067, 0x0067,
		0x0068, 0x0068,
		0x0069, 0x0069,
		0x006a, 0x006a,
		0x006b, 0x006b,
		0x006c, 0x006c,
		0x006d, 0x006d,
		0x006e, 0x006e,
		0x006f, 0x006f,
		0x0070, 0x0070,
		0x0071, 0x0071,
		0x0072, 0x0072,
		0x0073, 0x0073,
		0x0074, 0x0074,
		0x0075, 0x0075,
		0x0076, 0x0076,
		0x0077, 0x0077,
		0x0078, 0x0078,
		0x0079, 0x0079,
		0x007a, 0x007a,
		0x007e, 0x007e,
		0x00a1, 0x0023,
		0x00b0, 0x0026,
		0x00ba, 0x0026,
		0x00bf, 0x0024,
		0x00c1, 0x0041,
		0x00cb, 0x0045,
		0x00cf, 0x0049,
		0x00d1, 0x004e,
		0x00d6, 0x004f,
		0x00dc, 0x0055,
		0x8140, 0x0020,
		0x8141, 0x00bb,
		0x8142, 0x00ba,
		0x8143, 0x00bb,
		0x8144, 0x00ba,
		0x8145, 0x00be,
		0x8146, 0x003a,
		0x8148, 0x003f,
		0x8149, 0x0021,
		0x815b, 0x002d,
		0x815e, 0x002f,
		0x8175, 0x00b8,
		0x8176, 0x00b9,
		0x817c, 0x002d,
		0x817d, 0x002b,
		0x8181, 0x003d,
		0x8193, 0x0023,
		0x81a8, 0x003e,
		0x81a9, 0x003c,
		0x824f, 0x0030,
		0x8250, 0x0031,
		0x8251, 0x0032,
		0x8252, 0x0033,
		0x8253, 0x0034,
		0x8254, 0x0035,
		0x8255, 0x0036,
		0x8256, 0x0037,
		0x8257, 0x0038,
		0x8258, 0x0039,
		0x8260, 0x0041,
		0x8261, 0x0042,
		0x8262, 0x0043,
		0x8263, 0x0044,
		0x8264, 0x0045,
		0x8265, 0x0046,
		0x8266, 0x0047,
		0x8267, 0x0048,
		0x8268, 0x0049,
		0x8269, 0x004a,
		0x826a, 0x004b,
		0x826b, 0x004c,
		0x826c, 0x004d,
		0x826d, 0x004e,
		0x826e, 0x004f,
		0x826f, 0x0050,
		0x8270, 0x0051,
		0x8271, 0x0052,
		0x8272, 0x0053,
		0x8273, 0x0054,
		0x8274, 0x0055,
		0x8275, 0x0056,
		0x8276, 0x0057,
		0x8277, 0x0058,
		0x8278, 0x0059,
		0x8279, 0x005a,
		0x8281, 0x0061,
		0x8282, 0x0062,
		0x8283, 0x0063,
		0x8284, 0x0064,
		0x8285, 0x0065,
		0x8286, 0x0066,
		0x8287, 0x0067,
		0x8288, 0x0068,
		0x8289, 0x0069,
		0x828a, 0x006a,
		0x828b, 0x006b,
		0x828c, 0x006c,
		0x828d, 0x006d,
		0x828e, 0x006e,
		0x828f, 0x006f,
		0x8290, 0x0070,
		0x8291, 0x0071,
		0x8292, 0x0072,
		0x8293, 0x0073,
		0x8294, 0x0074,
		0x8295, 0x0075,
		0x8296, 0x0076,
		0x8297, 0x0077,
		0x8298, 0x0078,
		0x8299, 0x0079,
		0x829a, 0x007a,
		0x829f, 0x00ae,
		0x82a0, 0x0080,
		0x82a1, 0x00af,
		0x82a2, 0x0081,
		0x82a3, 0x00b0,
		0x82a4, 0x0082,
		0x82a5, 0x00b1,
		0x82a6, 0x0083,
		0x82a7, 0x00b2,
		0x82a8, 0x0084,
		0x82a9, 0x0085,
		0x82aa, 0x0185,
		0x82ab, 0x0086,
		0x82ac, 0x0186,
		0x82ad, 0x0087,
		0x82ae, 0x0187,
		0x82af, 0x0088,
		0x82b0, 0x0188,
		0x82b1, 0x0089,
		0x82b2, 0x0189,
		0x82b3, 0x008a,
		0x82b4, 0x018a,
		0x82b5, 0x008b,
		0x82b6, 0x018b,
		0x82b7, 0x008c,
		0x82b8, 0x018c,
		0x82b9, 0x008d,
		0x82ba, 0x018d,
		0x82bb, 0x008e,
		0x82bc, 0x018e,
		0x82bd, 0x008f,
		0x82be, 0x018f,
		0x82bf, 0x0090,
		0x82c0, 0x0190,
		0x82c1, 0x00b6,
		0x82c2, 0x0091,
		0x82c3, 0x0191,
		0x82c4, 0x0092,
		0x82c5, 0x0192,
		0x82c6, 0x0093,
		0x82c7, 0x0193,
		0x82c8, 0x0094,
		0x82c9, 0x0095,
		0x82ca, 0x0096,
		0x82cb, 0x0097,
		0x82cc, 0x0098,
		0x82cd, 0x0099,
		0x82ce, 0x0199,
		0x82cf, 0x0299,
		0x82d0, 0x009a,
		0x82d1, 0x019a,
		0x82d2, 0x029a,
		0x82d3, 0x009b,
		0x82d4, 0x019b,
		0x82d5, 0x029b,
		0x82d6, 0x009c,
		0x82d7, 0x019c,
		0x82d8, 0x029c,
		0x82d9, 0x009d,
		0x82da, 0x019d,
		0x82db, 0x029d,
		0x82dc, 0x009e,
		0x82dd, 0x009f,
		0x82de, 0x00a0,
		0x82df, 0x00a1,
		0x82e0, 0x00a2,
		0x82e1, 0x00b3,
		0x82e2, 0x00a3,
		0x82e3, 0x00b4,
		0x82e4, 0x00a4,
		0x82e5, 0x00b5,
		0x82e6, 0x00a5,
		0x82e7, 0x00a6,
		0x82e8, 0x00a7,
		0x82e9, 0x00a8,
		0x82ea, 0x00a9,
		0x82eb, 0x00aa,
		0x82ed, 0x00ab,
		0x82f0, 0x00ac,
		0x82f1, 0x00ad,
		0x8340, 0x00ee,
		0x8341, 0x00c0,
		0x8342, 0x00ef,
		0x8343, 0x00c1,
		0x8344, 0x00f0,
		0x8345, 0x00c2,
		0x8346, 0x00f1,
		0x8347, 0x00c3,
		0x8348, 0x00f2,
		0x8349, 0x00c4,
		0x834a, 0x00c5,
		0x834b, 0x01c5,
		0x834c, 0x00c6,
		0x834d, 0x01c6,
		0x834e, 0x00c7,
		0x834f, 0x01c7,
		0x8350, 0x00c8,
		0x8351, 0x01c8,
		0x8352, 0x00c9,
		0x8353, 0x01c9,
		0x8354, 0x00ca,
		0x8355, 0x01ca,
		0x8356, 0x00cb,
		0x8357, 0x01cb,
		0x8358, 0x00cc,
		0x8359, 0x01cc,
		0x835a, 0x00cd,
		0x835b, 0x01cd,
		0x835c, 0x00ce,
		0x835d, 0x01ce,
		0x835e, 0x00cf,
		0x835f, 0x01cf,
		0x8360, 0x00d0,
		0x8361, 0x01d0,
		0x8362, 0x00f6,
		0x8363, 0x00d1,
		0x8364, 0x01d1,
		0x8365, 0x00d2,
		0x8366, 0x01d2,
		0x8367, 0x00d3,
		0x8368, 0x01d3,
		0x8369, 0x00d4,
		0x836a, 0x00d5,
		0x836b, 0x00d6,
		0x836c, 0x00d7,
		0x836d, 0x00d8,
		0x836e, 0x00d9,
		0x836f, 0x01d9,
		0x8370, 0x02d9,
		0x8371, 0x00da,
		0x8372, 0x01da,
		0x8373, 0x02da,
		0x8374, 0x00db,
		0x8375, 0x01db,
		0x8376, 0x02db,
		0x8377, 0x00dc,
		0x8378, 0x01dc,
		0x8379, 0x02dc,
		0x837a, 0x00dd,
		0x837b, 0x01dd,
		0x837c, 0x02dd,
		0x837d, 0x00de,
		0x837e, 0x00df,
		0x8380, 0x00e0,
		0x8381, 0x00e1,
		0x8382, 0x00e2,
		0x8383, 0x00f3,
		0x8384, 0x00e3,
		0x8385, 0x00f4,
		0x8386, 0x00e4,
		0x8387, 0x00f5,
		0x8388, 0x00e5,
		0x8389, 0x00e6,
		0x838a, 0x00e7,
		0x838b, 0x00e8,
		0x838c, 0x00e9,
		0x838d, 0x00ea,
		0x838f, 0x00eb,
		0x8392, 0x00ec,
		0x8393, 0x00ed,
		0x8394, 0x01c2,
		0x93fc, 0x003f,

		// null terminator
		0xffff, 0xffff,
	},

	.font_IconGroupID =
	{
		0, // DEBUG (removed)
		4, // BIG
		5, // SMALL
		4, // CREDITS
	},

	.font_charPixWidth =
	{
		0,	// DEBUG (removed)
		WIDE_34(17),	// BIG
		WIDE_34(13),	// SMALL
		WIDE_34(14),	// CREDITS
	},

	#if BUILD >= UsaRetail
	.font_charPixHeight =
	{
		0,	// DEBUG (removed)
		17,	// BIG
		8,	// SMALL
		17,	// CREDITS
	},
	#endif

	.font_puncPixWidth =
	{
		0,	// DEBUG (removed)
		WIDE_34(11),	// BIG
		WIDE_34(7),	// SMALL
		WIDE_34(11),	// CREDITS
	},

	// starts at ascii 0x21 '!'
	.font_characterIconID =
	{
		0x25, // !
		0xFF, // "
		0xFF, // #
		0xFF, // $
		0x2B, // %
		0xFF, // &
		0x24, // '
		0xFF, // (
		0xFF, // )
		0x34, // * (cross)
		0x2D, // +
		0x27, // ,
		0x2A, // -
		0x2C, // .
		0x30, // /

		// '0' to '9'
		0,1,2,3,4,5,6,7,8,9,

		0x26, // :
		0xFF, // ;
		0x28, // <
		0x29, // =
		0x2A, // >
		0x2E, // ?
		0x33, // @ (circle)

		// lowercase 'A' to 'Z'
		0x0A, 0x0B, 0x0C, 0x0D,
		0x0E, 0x0F, 0x10, 0x11,
		0x12, 0x13, 0x14, 0x15,
		0x16, 0x17, 0x18, 0x19,
		0x1A, 0x1B, 0x1C, 0x1D,
		0x1E, 0x1F, 0x20, 0x21,
		0x22, 0x23,

		0x35, // [ (square)
		0xFF, // slash
		0xFF, // ]
		0x36, // ^ (triangle)
		0x2F, // _
		0xFF, // `

		// lowercase 'a' to 'z'
		0x0A, 0x0B, 0x0C, 0x0D,
		0x0E, 0x0F, 0x10, 0x11,
		0x12, 0x13, 0x14, 0x15,
		0x16, 0x17, 0x18, 0x19,
		0x1A, 0x1B, 0x1C, 0x1D,
		0x1E, 0x1F, 0x20, 0x21,
		0x22, 0x23,

		0xFF, // {
		0xFF, // |
		0xFF, // }
		0xFF, // ~
		0xFF, // DEL

		#if BUILD != EurRetail

		// jpn characters
		0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
		0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
		0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
		0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F,
		0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7,
		0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF,
		0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xEE,
		0xEF, 0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xFF,
		0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE,
		0xBF, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6,
		0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE,
		0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6,
		0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE,
		0xDF, 0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6,
		0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,

		#endif
	},

	.font_buttonScale =
	{
		0,		// DEBUG (removed)
		0x1000,	// BIG
		0x1000,	// SMALL
		0,		// CREDITS
	},

	.font_buttonPixWidth =
	{
		0,		// DEBUG (removed)
		0x10,	// BIG
		0x2,	// SMALL
		0,		// CREDITS
	},

	// delta to adjust height
	.font_buttonPixHeight =
	{
		0,	// DEBUG (removed)
		0,	// BIG
		-1,	// SMALL
		0,	// CREDITS
	},

	.font_indentIconID =
	{
		0, 0,		// DEBUG (removed)
		0xF4, 0xF3,	// BIG
		0xF4, 0xF3,	// SMALL
		0xF4, 0xF3,	// CREDITS
	},

	.font_indentPixDimensions =
	{
		0, 0,	// DEBUG (removed)
		3, -3,	// BIG
		2, -2,	// SMALL
		3, -3,	// CREDITS
	},

	.pauseScreenStrip =
	{
		0x8466, 0x8C87, 0x90C9, 0x94EB,
		0x9D2C, 0xA16E, 0xA58F, 0xADD1,
		0xB1F2, 0xBA13, 0xBE34, 0xC675,
		0xCA96, 0xD2B7, 0xD6F8, 0xDF19,
	},

	.gamepadMapBtn =
	{
		{
			// RAW_BTN_UP = 0x10
			.input = {0, 0x10, 0, 0x10},

			.output = BTN_UP
		},

		{
			// RAW_BTN_DOWN = 0x40
			.input = {0, 0x40, 0, 0x40},

			.output = BTN_DOWN
		},

		{
			// RAW_BTN_LEFT = 0x80
			.input = {0, 0x80, 0, 0x80},

			.output = BTN_LEFT
		},

		{
			// RAW_BTN_RIGHT = 0x20
			.input = {0, 0x20, 0, 0x20},

			.output = BTN_RIGHT
		},

		{
			// RAW_BTN_TRIANGLE = 0x1000
			.input = {0x10, 0, 8, 0},

			.output = BTN_TRIANGLE
		},

		{
			// RAW_BTN_CROSS = 0x4000
			.input = {0x40, 0, 0x40, 0},

			.output = BTN_CROSS_one
		},

		{
			// RAW_BTN_SQUARE = 0x8000
			.input = {0x80, 0, 0x4, 0},

			.output = BTN_SQUARE_one
		},

		{
			// RAW_BTN_CIRCLE = 0x2000
			.input = {0x20, 0, 0x20, 0},

			.output = BTN_CIRCLE
		},

		{
			// RAW_BTN_L2 = 0x100
			.input = {1, 0, 1, 0},

			.output = BTN_L2_one
		},

		// remove ND duplicate
		#if 0
		{
			// RAW_BTN_L2 = 0x100
			.input = {1, 0, 1, 0},

			.output = BTN_L2_two
		},
		#endif

		{
			// RAW_BTN_R2 = 0x200
			.input = {2, 0, 0x80, 0},

			.output = BTN_R2
		},

		{
			// RAW_BTN_START = 8
			.input = {0, 8, 0, 8},

			.output = BTN_START
		},

		{
			// RAW_BTN_SELECT = 1
			.input = {0, 1, 0, 1},

			.output = BTN_SELECT
		},

		// remove ND duplicate
		#if 0
		{
			// RAW_BTN_CROSS = 0x4000
			.input = {0x40, 0, 0x40, 0},

			.output = BTN_CROSS_two
		},
		#endif

		// remove ND duplicate
		#if 0
		{
			// RAW_BTN_SQUARE = 0x8000
			.input = {0x80, 0, 4, 0},

			.output = BTN_SQUARE_two
		},
		#endif

		{
			// RAW_BTN_L1 = 0x400
			.input = {4, 0, 2, 0},

			.output = BTN_L1
		},

		{
			// RAW_BTN_R1 = 0x800
			.input = {8, 0, 0x10, 0},

			.output = BTN_R1
		},

		{
			// RAW_BTN_L3 = 0x2
			.input = {0, 2, 0, 2},

			.output = BTN_L3
		},

		{
			// RAW_BTN_R3 = 0x4
			.input = {0, 4, 0, 4},

			.output = BTN_R3
		},

		//{} - null
	},

	.reverbParams =
	{
		{
			.mask = 1,
			.mode = 0x109,
			.depth = {0x2DFF, 0x2DFF},
			.delay = 0,
			.feedback = 0
		},

		{
			.mask = 1,
			.mode = 0x101,
			.depth = {0x4FFF, 0x4FFF},
			.delay = 0,
			.feedback = 0
		},

		{
			.mask = 1,
			.mode = 0x103,
			.depth = {0x37FF, 0x37FF},
			.delay = 0,
			.feedback = 0
		},

		{
			.mask = 1,
			.mode = 0x103,
			.depth = {0x37FF, 0x37FF},
			.delay = 0,
			.feedback = 0
		},

		{
			.mask = 1,
			.mode = 0x102,
			.depth = {0x37FF, 0x37FF},
			.delay = 0,
			.feedback = 0
		},
	},

	.distortConst_Engine =
	{
		0x4000, 0x40B2, 0x4166, 0x421D, 0x42D5, 0x438F, 0x444C, 0x450A, 0x45CA, 0x468D, 0x4752, 0x4818, 0x48E1, 0x49AD, 0x4A7A, 0x4B4A,
		0x4C1B, 0x4CF0, 0x4DC6, 0x4E9F, 0x4F7A, 0x5058, 0x5138, 0x521A, 0x52FF, 0x53E6, 0x54D0, 0x55BD, 0x56AC, 0x579D, 0x5891, 0x5988,
		0x5A82, 0x5B7E, 0x5C7D, 0x5D7F, 0x5E84, 0x5F8B, 0x6096, 0x61A3, 0x62B3, 0x63C6, 0x64DC, 0x65F6, 0x6712, 0x6831, 0x6954, 0x6A79,
		0x6BA2, 0x6CCE, 0x6DFD, 0x6F30, 0x7066, 0x719F, 0x72DC, 0x741C, 0x7560, 0x76A7, 0x77F2, 0x7940, 0x7A92, 0x7BE8, 0x7D41, 0x7E9F,
		0x8000, 0x8164, 0x82CD, 0x843A, 0x85AA, 0x871F, 0x8898, 0x8A14, 0x8B95, 0x8D1A, 0x8EA4, 0x9031, 0x91C3, 0x935A, 0x94F4, 0x9694,
		0x9837, 0x99E0, 0x9B8D, 0x9D3E, 0x9EF5, 0xA0B0, 0xA270, 0xA435, 0xA5FE, 0xA7CD, 0xA9A1, 0xAB7A, 0xAD58, 0xAF3B, 0xB123, 0xB311,
		0xB504, 0xB6FD, 0xB8FB, 0xBAFF, 0xBD08, 0xBF17, 0xC12C, 0xC346, 0xC567, 0xC78D, 0xC9B9, 0xCBEC, 0xCE24, 0xD063, 0xD2A8, 0xD4F3,
		0xD744, 0xD99D, 0xDBFB, 0xDE60, 0xE0CC, 0xE33F, 0xE5B9, 0xE839, 0xEAC0, 0xED4F, 0xEFE4, 0xF281, 0xF525, 0xF7D0, 0xFA83, 0xFD3E,

		0x10000, 0x102C9, 0x1059B, 0x10874, 0x10B55, 0x10E3E, 0x11130, 0x11429, 0x1172B, 0x11A35, 0x11D48, 0x12063, 0x12387, 0x126B4, 0x129E9, 0x12D28,
		0x1306F, 0x133C0, 0x1371A, 0x13A7D, 0x13DEA, 0x14160, 0x144E0, 0x1486A, 0x14BFD, 0x14F9B, 0x15342, 0x156F4, 0x15AB0, 0x15E76, 0x16247, 0x16623,
		0x16A09, 0x16DFB, 0x171F7, 0x175FE, 0x17A11, 0x17E2F, 0x18258, 0x1868D, 0x18ACE, 0x18F1A, 0x19373, 0x197D8, 0x19C49, 0x1A0C6, 0x1A550, 0x1A9E6,
		0x1AE89, 0x1B33A, 0x1B7F7, 0x1BCC1, 0x1C199, 0x1C67F, 0x1CB72, 0x1D072, 0x1D581, 0x1DA9E, 0x1DFC9, 0x1E502, 0x1EA4A, 0x1EFA1, 0x1F507, 0x1FA7C,
		0x20000, 0x20593, 0x20B36, 0x210E8, 0x216AB, 0x21C7D, 0x22260, 0x22853, 0x22E57, 0x2346B, 0x23A90, 0x240C7, 0x2470F, 0x24D68, 0x253D3, 0x25A50,
		0x260DF, 0x26781, 0x26E34, 0x274FB, 0x27BD4, 0x282C1, 0x289C1, 0x290D4, 0x297FB, 0x29F36, 0x2A685, 0x2ADE8, 0x2B560, 0x2BCED, 0x2C48F, 0x2CC47,
		0x2D413, 0x2DBF6, 0x2E3EE, 0x2EBFD, 0x2F422, 0x2FC5E, 0x304B1, 0x30D1B, 0x3159C, 0x31E35, 0x326E6, 0x32FB0, 0x33892, 0x3418C, 0x34AA0, 0x353CD,
		0x35D13, 0x36674, 0x36FEE, 0x37983, 0x38333, 0x38CFE, 0x396E4, 0x3A0E5, 0x3AB03, 0x3B53C, 0x3BF92, 0x3CA05, 0x3D495, 0x3DF43, 0x3EA0E, 0x3F4F8
	},

	.distortConst_OtherFX =
	{
		0x8000, 0x80B1, 0x8164, 0x8218, 0x82CD, 0x8383, 0x843A, 0x84F1, 0x85AA, 0x8664, 0x871F, 0x87DB, 0x8898, 0x8955, 0x8A14, 0x8AD4,
		0x8B95, 0x8C57, 0x8D1A, 0x8DDF, 0x8EA4, 0x8F6A, 0x9031, 0x90FA, 0x91C3, 0x928E, 0x935A, 0x9426, 0x94F4, 0x95C3, 0x9694, 0x9765,
		0x9837, 0x990B, 0x99E0, 0x9AB6, 0x9B8D, 0x9C65, 0x9D3E, 0x9E19, 0x9EF5, 0x9FD2, 0xA0B0, 0xA18F, 0xA270, 0xA352, 0xA435, 0xA519,
		0xA5FE, 0xA6E5, 0xA7CD, 0xA8B6, 0xA9A1, 0xAA8D, 0xAB7A, 0xAC68, 0xAD58, 0xAE49, 0xAF3B, 0xB02F, 0xB123, 0xB21A, 0xB311, 0xB40A,
		0xB504, 0xB600, 0xB6FD, 0xB7FB, 0xB8FB, 0xB9FC, 0xBAFF, 0xBC03, 0xBD08, 0xBE0F, 0xBF17, 0xC021, 0xC12C, 0xC238, 0xC346, 0xC456,
		0xC567, 0xC679, 0xC78D, 0xC8A2, 0xC9B9, 0xCAD2, 0xCBEC, 0xCD07, 0xCE24, 0xCF43, 0xD063, 0xD184, 0xD2A8, 0xD3CC, 0xD4F3, 0xD61B,
		0xD744, 0xD870, 0xD99D, 0xDACB, 0xDBFB, 0xDD2D, 0xDE60, 0xDF96, 0xE0CC, 0xE205, 0xE33F, 0xE47B, 0xE5B9, 0xE6F8, 0xE839, 0xE97C,
		0xEAC0, 0xEC07, 0xED4F, 0xEE99, 0xEFE4, 0xF132, 0xF281, 0xF3D2, 0xF525, 0xF67A, 0xF7D0, 0xF929, 0xFA83, 0xFBDF, 0xFD3E, 0xFE9E,

		0x10000, 0x10163, 0x102C9, 0x10431, 0x1059B, 0x10706, 0x10874, 0x109E3, 0x10B55, 0x10CC9, 0x10E3E, 0x10FB6, 0x11130, 0x112AB, 0x11429, 0x115A9,
		0x1172B, 0x118AF, 0x11A35, 0x11BBE, 0x11D48, 0x11ED5, 0x12063, 0x121F4, 0x12387, 0x1251C, 0x126B4, 0x1284D, 0x129E9, 0x12B87, 0x12D28, 0x12ECA,
		0x1306F, 0x13217, 0x133C0, 0x1356C, 0x1371A, 0x138CA, 0x13A7D, 0x13C32, 0x13DEA, 0x13FA4, 0x14160, 0x1431F, 0x144E0, 0x146A4, 0x1486A, 0x14A32,
		0x14BFD, 0x14DCB, 0x14F9B, 0x1516D, 0x15342, 0x1551A, 0x156F4, 0x158D1, 0x15AB0, 0x15C92, 0x15E76, 0x1605E, 0x16247, 0x16434, 0x16623, 0x16815,
		0x16A09, 0x16C01, 0x16DFB, 0x16FF7, 0x171F7, 0x173F9, 0x175FE, 0x17806, 0x17A11, 0x17C1E, 0x17E2F, 0x18042, 0x18258, 0x18471, 0x1868D, 0x188AC,
		0x18ACE, 0x18CF3, 0x18F1A, 0x19145, 0x19373, 0x195A4, 0x197D8, 0x19A0F, 0x19C49, 0x19E86, 0x1A0C6, 0x1A309, 0x1A550, 0x1A799, 0x1A9E6, 0x1AC36,
		0x1AE89, 0x1B0E0, 0x1B33A, 0x1B597, 0x1B7F7, 0x1BA5B, 0x1BCC1, 0x1BF2C, 0x1C199, 0x1C40A, 0x1C67F, 0x1C8F6, 0x1CB72, 0x1CDF0, 0x1D072, 0x1D2F8,
		0x1D581, 0x1D80E, 0x1DA9E, 0x1DD32, 0x1DFC9, 0x1E264, 0x1E502, 0x1E7A5, 0x1EA4A, 0x1ECF4, 0x1EFA1, 0x1F252, 0x1F507, 0x1F7BF, 0x1FA7C, 0x1FD3C
	},

	.volumeLR =
	{
		0x00, 0x01, 0x03, 0x04, 0x06, 0x07, 0x09, 0x0A, 0x0C, 0x0E, 0x0F, 0x11, 0x12, 0x14, 0x15, 0x17,
		0x19, 0x1A, 0x1C, 0x1D, 0x1F, 0x20, 0x22, 0x24, 0x25, 0x27, 0x28, 0x2A, 0x2B, 0x2D, 0x2E, 0x30,
		0x31, 0x33, 0x35, 0x36, 0x38, 0x39, 0x3B, 0x3C, 0x3E, 0x3F, 0x41, 0x42, 0x44, 0x45, 0x47, 0x48,
		0x4A, 0x4B, 0x4D, 0x4E, 0x50, 0x51, 0x53, 0x54, 0x56, 0x57, 0x59, 0x5A, 0x5C, 0x5D, 0x5F, 0x60,
		0x61, 0x63, 0x64, 0x66, 0x67, 0x69, 0x6A, 0x6C, 0x6D, 0x6E, 0x70, 0x71, 0x73, 0x74, 0x75, 0x77,
		0x78, 0x7A, 0x7B, 0x7C, 0x7E, 0x7F, 0x80, 0x82, 0x83, 0x84, 0x86, 0x87, 0x88, 0x8A, 0x8B, 0x8C,
		0x8E, 0x8F, 0x90, 0x92, 0x93, 0x94, 0x95, 0x97, 0x98, 0x99, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0xA1,
		0xA2, 0xA3, 0xA4, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3,
		0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4,
		0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD3,
		0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDD, 0xDE, 0xDF, 0xE0, 0xE1,
		0xE1, 0xE2, 0xE3, 0xE3, 0xE4, 0xE5, 0xE6, 0xE6, 0xE7, 0xE8, 0xE8, 0xE9, 0xEA, 0xEA, 0xEB, 0xEB,
		0xEC, 0xED, 0xED, 0xEE, 0xEE, 0xEF, 0xEF, 0xF0, 0xF1, 0xF1, 0xF2, 0xF2, 0xF3, 0xF3, 0xF4, 0xF4,
		0xF4, 0xF5, 0xF5, 0xF6, 0xF6, 0xF7, 0xF7, 0xF7, 0xF8, 0xF8, 0xF9, 0xF9, 0xF9, 0xFA, 0xFA, 0xFA,
		0xFB, 0xFB, 0xFB, 0xFB, 0xFC, 0xFC, 0xFC, 0xFC, 0xFD, 0xFD, 0xFD, 0xFD, 0xFE, 0xFE, 0xFE, 0xFE,
		0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	},

	.noteFrequency =
	{
		0x0080, 0x0087, 0x008F, 0x0098, 0x00A1, 0x00AA, 0x00B5, 0x00BF, 0x00CB, 0x00D7, 0x00E4, 0x00F1,
		0x0100, 0x010F, 0x011F, 0x0130, 0x0142, 0x0155, 0x016A, 0x017F, 0x0196, 0x01AE, 0x01C8, 0x01E3,
		0x0200, 0x021E, 0x023E, 0x0260, 0x0285, 0x02AB, 0x02D4, 0x02FF, 0x032C, 0x035D, 0x0390, 0x03C6,
		0x0400, 0x043C, 0x047D, 0x04C1, 0x050A, 0x0556, 0x05A8, 0x05FE, 0x0659, 0x06BA, 0x0720, 0x078D,
		0x0800, 0x0879, 0x08FA, 0x0983, 0x0A14, 0x0AAD, 0x0B50, 0x0BFC, 0x0CB2, 0x0D74, 0x0E41, 0x0F1A,
		0x1000, 0x10F3, 0x11F5, 0x1306, 0x1428, 0x155B, 0x16A0, 0x17F9, 0x1965, 0x1AE8, 0x1C82, 0x1E34,
		0x2000, 0x21E7, 0x23EB, 0x260D, 0x2851, 0x2AB7, 0x2D41, 0x2FF2, 0x32CB, 0x35D1, 0x3904, 0x3C68,
		0x4000, 0x43CE, 0x47D6, 0x4C1B, 0x50A2, 0x556E, 0x5A82, 0x5FE4, 0x6597, 0x6BA2, 0x7208, 0x78D0,
		0x8000, 0x879C, 0x8FAC, 0x9837, 0xA145, 0xAADC, 0xB504, 0xBFC8, 0xCB2F, 0xD744, 0xE411, 0xF1A1
	},

	#if BUILD >= UsaRetail
	.distortConst_Music =
	{
		0x0000, 0x03B2, 0x0766, 0x0B1A, 0x0ED0, 0x1286, 0x163D, 0x19F5,
		0x1DAE, 0x2168, 0x2522, 0x28DD, 0x2C9A, 0x3057, 0x3415, 0x37D4,
		0x3B93, 0x3F54, 0x4315, 0x46D8, 0x4A9B, 0x4E5F, 0x5224, 0x55EA,
		0x59B0, 0x5D78, 0x6140, 0x650A, 0x68D4, 0x6C9F, 0x706B, 0x7437,
		0x7805, 0x7BD4, 0x7FA3, 0x8373, 0x8745, 0x8B17, 0x8EEA, 0x92BD,
		0x9692, 0x9A68, 0x9E3E, 0xA216, 0xA5EE, 0xA9C7, 0xADA1, 0xB17C,
		0xB558, 0xB935, 0xBD12, 0xC0F1, 0xC4D0, 0xC8B0, 0xCC92, 0xD074,
		0xD457, 0xD83B, 0xDC1F, 0xE005, 0xE3EC, 0xE7D3, 0xEBBC, 0xEFA5
	},
	#endif

	.opcodeFunc =
	{
		DECOMP_cseq_opcode00_empty, // should remove
		DECOMP_cseq_opcode01_noteoff,
		DECOMP_cseq_opcode02_empty, // should remove
		DECOMP_cseq_opcode03,
		DECOMP_cseq_opcode04_empty, // should remove
		DECOMP_cseq_opcode05_noteon,
		DECOMP_cseq_opcode06,
		DECOMP_cseq_opcode07,
		DECOMP_cseq_opcode08,
		DECOMP_cseq_opcode09,
		DECOMP_cseq_opcode0a
	},

	.opcodeOffset =
	{
		0x01, 0x02, 0x02, 0x01, 0x02, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02
	},

	.voiceData =
	{
		[0] =
		{
			.index =
			{
				0, 1, 2, 3,
				4, 5, 6, 7,
				8, 9, 10, 11,
				12, 13, 14, 15,
				16, 0, 17, 0, 18, 0
			},

			.voiceSet =
			{
				{&data.voiceData[0].index[0], 2},
				{&data.voiceData[0].index[2], 2},
				{&data.voiceData[0].index[4], 2},
				{&data.voiceData[0].index[6], 2},
				{&data.voiceData[0].index[8], 2},
				{&data.voiceData[0].index[10], 2},
				{&data.voiceData[0].index[12], 2},
				{&data.voiceData[0].index[14], 2},
				{&data.voiceData[0].index[16], 1},
				{&data.voiceData[0].index[18], 1},
				{&data.voiceData[0].index[20], 1},
			}
		},
		[1] =
		{
			.index =
			{
				19, 20, 21, 22,
				23, 24, 25, 26,
				27, 28, 29, 30,
				31, 32, 33, 34,
				35, 0, 36, 0, 37, 0
			},

			.voiceSet =
			{
				{&data.voiceData[1].index[0], 2},
				{&data.voiceData[1].index[2], 2},
				{&data.voiceData[1].index[4], 2},
				{&data.voiceData[1].index[6], 2},
				{&data.voiceData[1].index[8], 2},
				{&data.voiceData[1].index[10], 2},
				{&data.voiceData[1].index[12], 2},
				{&data.voiceData[1].index[14], 2},
				{&data.voiceData[1].index[16], 1},
				{&data.voiceData[1].index[18], 1},
				{&data.voiceData[1].index[20], 1},
			}
		},
		[2] =
		{
			.index =
			{
				38, 39, 40, 41,
				42, 43, 44, 45,
				46, 47, 48, 49,
				50, 51, 52, 53,
				54, 0, 55, 0, 56, 0
			},

			.voiceSet =
			{
				{&data.voiceData[2].index[0], 2},
				{&data.voiceData[2].index[2], 2},
				{&data.voiceData[2].index[4], 2},
				{&data.voiceData[2].index[6], 2},
				{&data.voiceData[2].index[8], 2},
				{&data.voiceData[2].index[10], 2},
				{&data.voiceData[2].index[12], 2},
				{&data.voiceData[2].index[14], 2},
				{&data.voiceData[2].index[16], 1},
				{&data.voiceData[2].index[18], 1},
				{&data.voiceData[2].index[20], 1},
			}
		},
		[3] =
		{
			.index =
			{
				57, 58, 59, 60,
				61, 62, 63, 64,
				65, 66, 67, 68,
				69, 70, 71, 72,
				73, 0, 74, 0, 75, 0
			},

			.voiceSet =
			{
				{&data.voiceData[3].index[0], 2},
				{&data.voiceData[3].index[2], 2},
				{&data.voiceData[3].index[4], 2},
				{&data.voiceData[3].index[6], 2},
				{&data.voiceData[3].index[8], 2},
				{&data.voiceData[3].index[10], 2},
				{&data.voiceData[3].index[12], 2},
				{&data.voiceData[3].index[14], 2},
				{&data.voiceData[3].index[16], 1},
				{&data.voiceData[3].index[18], 1},
				{&data.voiceData[3].index[20], 1},
			}
		},
		[4] =
		{
			.index =
			{
				76, 77, 78, 79,
				80, 81, 82, 83,
				84, 85, 86, 87,
				88, 89, 90, 91,
				92, 0, 93, 0, 94, 0
			},

			.voiceSet =
			{
				{&data.voiceData[4].index[0], 2},
				{&data.voiceData[4].index[2], 2},
				{&data.voiceData[4].index[4], 2},
				{&data.voiceData[4].index[6], 2},
				{&data.voiceData[4].index[8], 2},
				{&data.voiceData[4].index[10], 2},
				{&data.voiceData[4].index[12], 2},
				{&data.voiceData[4].index[14], 2},
				{&data.voiceData[4].index[16], 1},
				{&data.voiceData[4].index[18], 1},
				{&data.voiceData[4].index[20], 1},
			}
		},
		[5] =
		{
			.index =
			{
				95, 96, 97, 98,
				99, 100, 101, 102,
				103, 104, 105, 106,
				107, 108, 109, 110,
				111, 0, 112, 0, 113, 0
			},

			.voiceSet =
			{
				{&data.voiceData[5].index[0], 2},
				{&data.voiceData[5].index[2], 2},
				{&data.voiceData[5].index[4], 2},
				{&data.voiceData[5].index[6], 2},
				{&data.voiceData[5].index[8], 2},
				{&data.voiceData[5].index[10], 2},
				{&data.voiceData[5].index[12], 2},
				{&data.voiceData[5].index[14], 2},
				{&data.voiceData[5].index[16], 1},
				{&data.voiceData[5].index[18], 1},
				{&data.voiceData[5].index[20], 1},
			}
		},
		[6] =
		{
			.index =
			{
				114, 115, 116, 117,
				118, 119, 120, 121,
				122, 123, 124, 125,
				126, 127, 128, 129,
				130, 0, 131, 0, 132, 0
			},

			.voiceSet =
			{
				{&data.voiceData[6].index[0], 2},
				{&data.voiceData[6].index[2], 2},
				{&data.voiceData[6].index[4], 2},
				{&data.voiceData[6].index[6], 2},
				{&data.voiceData[6].index[8], 2},
				{&data.voiceData[6].index[10], 2},
				{&data.voiceData[6].index[12], 2},
				{&data.voiceData[6].index[14], 2},
				{&data.voiceData[6].index[16], 1},
				{&data.voiceData[6].index[18], 1},
				{&data.voiceData[6].index[20], 1},
			}
		},
		[7] =
		{
			.index =
			{
				133, 134, 135, 136,
				137, 138, 139, 140,
				141, 142, 143, 144,
				145, 146, 147, 148,
				149, 0, 150, 0, 151, 0
			},

			.voiceSet =
			{
				{&data.voiceData[7].index[0], 2},
				{&data.voiceData[7].index[2], 2},
				{&data.voiceData[7].index[4], 2},
				{&data.voiceData[7].index[6], 2},
				{&data.voiceData[7].index[8], 2},
				{&data.voiceData[7].index[10], 2},
				{&data.voiceData[7].index[12], 2},
				{&data.voiceData[7].index[14], 2},
				{&data.voiceData[7].index[16], 1},
				{&data.voiceData[7].index[18], 1},
				{&data.voiceData[7].index[20], 1},
			}
		},
		[8] =
		{
			.index =
			{
				152, 153, 154, 155,
				156, 157, 158, 159,
				160, 161, 162, 163,
				164, 165, 166, 167,
				168, 0, 169, 0, 170, 0
			},

			.voiceSet =
			{
				{&data.voiceData[8].index[0], 2},
				{&data.voiceData[8].index[2], 2},
				{&data.voiceData[8].index[4], 2},
				{&data.voiceData[8].index[6], 2},
				{&data.voiceData[8].index[8], 2},
				{&data.voiceData[8].index[10], 2},
				{&data.voiceData[8].index[12], 2},
				{&data.voiceData[8].index[14], 2},
				{&data.voiceData[8].index[16], 1},
				{&data.voiceData[8].index[18], 1},
				{&data.voiceData[8].index[20], 1},
			}
		},
		[9] =
		{
			.index =
			{
				171, 172, 173, 174,
				175, 176, 177, 178,
				179, 180, 181, 182,
				183, 184, 185, 186,
				187, 0, 188, 0, 189, 0
			},

			.voiceSet =
			{
				{&data.voiceData[9].index[0], 2},
				{&data.voiceData[9].index[2], 2},
				{&data.voiceData[9].index[4], 2},
				{&data.voiceData[9].index[6], 2},
				{&data.voiceData[9].index[8], 2},
				{&data.voiceData[9].index[10], 2},
				{&data.voiceData[9].index[12], 2},
				{&data.voiceData[9].index[14], 2},
				{&data.voiceData[9].index[16], 1},
				{&data.voiceData[9].index[18], 1},
				{&data.voiceData[9].index[20], 1},
			}
		},

		// This one breaks the pattern,
		// index is out of order
		[10] =
		{
			.index =
			{
				0xc8, 0xc9, 0xc0, 0xc1,
				0xc2, 0xc3, 0xc4, 0xc5,
				0xc6, 0xc7, 0xc8, 0xc9,
				0xcA, 0xcB, 0xcC, 0xcD,
				0xcE, 0, 0xcF, 0, 0xd0, 0
			},

			.voiceSet =
			{
				{&data.voiceData[10].index[0], 2},
				{&data.voiceData[10].index[2], 2},
				{&data.voiceData[10].index[4], 2},
				{&data.voiceData[10].index[6], 2},
				{&data.voiceData[10].index[8], 2},
				{&data.voiceData[10].index[10], 2},
				{&data.voiceData[10].index[12], 2},
				{&data.voiceData[10].index[14], 2},
				{&data.voiceData[10].index[16], 1},
				{&data.voiceData[10].index[18], 1},
				{&data.voiceData[10].index[20], 1},
			}
		},

		[11] =
		{
			.index =
			{
				209, 210, 211, 212,
				213, 214, 215, 216,
				217, 218, 219, 220,
				221, 222, 223, 224,
				225, 0, 226, 0, 227, 0
			},

			.voiceSet =
			{
				{&data.voiceData[11].index[0], 2},
				{&data.voiceData[11].index[2], 2},
				{&data.voiceData[11].index[4], 2},
				{&data.voiceData[11].index[6], 2},
				{&data.voiceData[11].index[8], 2},
				{&data.voiceData[11].index[10], 2},
				{&data.voiceData[11].index[12], 2},
				{&data.voiceData[11].index[14], 2},
				{&data.voiceData[11].index[16], 1},
				{&data.voiceData[11].index[18], 1},
				{&data.voiceData[11].index[20], 1},
			}
		},
		[12] =
		{
			.index =
			{
				228, 229, 230, 231,
				232, 233, 234, 235,
				236, 237, 238, 239,
				240, 241, 242, 243,
				244, 0, 245, 0, 246, 0
			},

			.voiceSet =
			{
				{&data.voiceData[12].index[0], 2},
				{&data.voiceData[12].index[2], 2},
				{&data.voiceData[12].index[4], 2},
				{&data.voiceData[12].index[6], 2},
				{&data.voiceData[12].index[8], 2},
				{&data.voiceData[12].index[10], 2},
				{&data.voiceData[12].index[12], 2},
				{&data.voiceData[12].index[14], 2},
				{&data.voiceData[12].index[16], 1},
				{&data.voiceData[12].index[18], 1},
				{&data.voiceData[12].index[20], 1},
			}
		},
		[13] =
		{
			.index =
			{
				247, 248, 249, 250,
				251, 252, 253, 254,
				255, 256, 257, 258,
				259, 260, 261, 262,
				263, 0, 264, 0, 265, 0
			},

			.voiceSet =
			{
				{&data.voiceData[13].index[0], 2},
				{&data.voiceData[13].index[2], 2},
				{&data.voiceData[13].index[4], 2},
				{&data.voiceData[13].index[6], 2},
				{&data.voiceData[13].index[8], 2},
				{&data.voiceData[13].index[10], 2},
				{&data.voiceData[13].index[12], 2},
				{&data.voiceData[13].index[14], 2},
				{&data.voiceData[13].index[16], 1},
				{&data.voiceData[13].index[18], 1},
				{&data.voiceData[13].index[20], 1},
			}
		},
		[14] =
		{
			.index =
			{
				266, 267, 268, 269,
				270, 271, 272, 273,
				274, 275, 276, 277,
				278, 279, 280, 281,
				282, 0, 283, 0, 284, 0
			},

			.voiceSet =
			{
				{&data.voiceData[14].index[0], 2},
				{&data.voiceData[14].index[2], 2},
				{&data.voiceData[14].index[4], 2},
				{&data.voiceData[14].index[6], 2},
				{&data.voiceData[14].index[8], 2},
				{&data.voiceData[14].index[10], 2},
				{&data.voiceData[14].index[12], 2},
				{&data.voiceData[14].index[14], 2},
				{&data.voiceData[14].index[16], 1},
				{&data.voiceData[14].index[18], 1},
				{&data.voiceData[14].index[20], 1},
			}
		},
		[15] =
		{
			.index =
			{
				285, 286, 287, 288,
				289, 290, 291, 292,
				293, 294, 295, 296,
				297, 298, 299, 300,
				301, 0, 302, 0, 303, 0
			},

			.voiceSet =
			{
				{&data.voiceData[15].index[0], 2},
				{&data.voiceData[15].index[2], 2},
				{&data.voiceData[15].index[4], 2},
				{&data.voiceData[15].index[6], 2},
				{&data.voiceData[15].index[8], 2},
				{&data.voiceData[15].index[10], 2},
				{&data.voiceData[15].index[12], 2},
				{&data.voiceData[15].index[14], 2},
				{&data.voiceData[15].index[16], 1},
				{&data.voiceData[15].index[18], 1},
				{&data.voiceData[15].index[20], 1},
			}
		}
	},

	.voiceSetPtr =
	{
		&data.voiceData[0].voiceSet,
		&data.voiceData[1].voiceSet,
		&data.voiceData[2].voiceSet,
		&data.voiceData[3].voiceSet,
		&data.voiceData[4].voiceSet,
		&data.voiceData[5].voiceSet,
		&data.voiceData[6].voiceSet,
		&data.voiceData[7].voiceSet,
		&data.voiceData[8].voiceSet,
		&data.voiceData[9].voiceSet,
		&data.voiceData[10].voiceSet,
		&data.voiceData[11].voiceSet,
		&data.voiceData[12].voiceSet,
		&data.voiceData[13].voiceSet,
		&data.voiceData[14].voiceSet,
		&data.voiceData[15].voiceSet
	},

	.voiceID =
	{
		4, 1, 5, 2, 1, 1, 1, 3, 6, 6,
		7, 7, 7, 7, 7, 4, 0, 0, 0, 0,
		0, 8, 8, 8
	},

	.advHubSongSetBytes =
	{
		0x1f, 0x17, 0x08, 0x1f, 0x10, 0x1f, 0x01, 0x08,
		0x01, 0x10, 0x01, 0x1f, 0x04, 0x04, 0x02, 0x1f,
		0x10, 0x08, 0x10, 0x02,
	},

	.nTropyXA =
	{
		0x47, 0x44, 0x40, 0x41, 0x42, 0x45
	},

	.reverbMode =
	{
		0x02, 0x01, 0x00, 0x01, 0x01, 0x01, 0x03, 0x00,
		0x03, 0x01, 0x01, 0x01, 0x04, 0x03, 0x04, 0x04,
		0x01, 0x01, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
		0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00,
		0x0d, 0x00, 0x06, 0x00, 0x05, 0x00, 0x01, 0x00,
		0x07, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
		0x01, 0x00, 0x02, 0x00, 0x03, 0x00, 0x00, 0x00,
	},

	.levBank_FX =
	{
		0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
		0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10,
		0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
		0x19, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x00, 0x00,
	},

	.levBank_Song =
	{
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
		0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
		0x18, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x00, 0x00,
	},

	.levAmbientSound =
	{
		0x83, 0x00, 0x84, 0x00, 0x00, 0x00, 0x83, 0x85,
		0x00, 0x00, 0x83, 0x00, 0x00, 0x00, 0x89, 0x8a,
		0x00, 0x00, 0x86, 0x8c, 0x89, 0x00, 0x8d, 0x8e,
		0x00, 0x00, 0x8f, 0x90, 0x83, 0x00, 0x91, 0x92,
		0x91, 0x92, 0x91, 0x92, 0x00, 0x00, 0x00, 0x00,

		// all zero?
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
	},

	.driverModel_lowLOD[0] = 0,
	.driverModel_lowLOD[1] = 0,
	.driverModel_lowLOD[2] = 0,

	.podiumModel_firstPlace = 0,
	.podiumModel_secondPlace = 0,
	.podiumModel_thirdPlace = 0,
	.podiumModel_tawna = 0,

	.podiumModel_unk1 = 0,
	.podiumModel_dingoFire = 0,
	.podiumModel_unk2 = 0,
	.podiumModel_podiumStands = 0,

	.currSlot =
	{
		.ptrBigfileCdPos = 0,
		.flags = 0,
		.type = 0,
		.subfileIndex = -1,
		.ptrDestination = 0,
		.size = 0,
		.callback.flags = 0
	},

	.characterIDs_2P_AIs =
	{
		// polar, ngin, tiny, coco
		6, 4, 2, 3,

		// crash, polar, coco, dingo
		0, 6, 3, 5,

		// crash, polar, cortex, tiny
		0, 6, 1, 2,

		// crash, polar, ngin, pura
		0, 6, 4, 7,

		// cortex, tiny, coco, dingo
		1, 2, 3, 5,

		// ngin, pura, coco, dingo
		4, 7, 3, 5,

		// ngin, pura cortex, coco
		4, 7, 1, 2,
	},

	.overlayCallbackFuncs =
	{
		DECOMP_LOAD_Callback_Overlay_230,
		DECOMP_LOAD_Callback_Overlay_231,
		DECOMP_LOAD_Callback_Overlay_232,
		DECOMP_LOAD_Callback_Overlay_233
	},

	// leave name_Debug out, dont need it
	.metaDataLEV =
	{
		[0] =
		{
			.hubID = 2,
			//.name_Debug = 0x8008d298,
			.name_LNG = 110,
			.timeTrial = 110400,
			.numTrophiesToOpen = 7,
			.ctrTokenGroupID = 3,
			.characterID_Boss = -1,
			.characterID_Champion = 5
		},
		[1] =
		{
			.hubID = 3,
			//.name_Debug = 0x8008d290,
			.name_LNG = 111,
			.timeTrial = 110400,
			.numTrophiesToOpen = 9,
			.ctrTokenGroupID = 2,
			.characterID_Boss = 11,
			.characterID_Champion = 11
		},
		[2] =
		{
			.hubID = 3,
			//.name_Debug = 0x8008d288,
			.name_LNG = 112,
			.timeTrial = 106560,
			.numTrophiesToOpen = 8,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = 13
		},
		[3] =
		{
			.hubID = 1,
			//.name_Debug = 0x8008d280,
			.name_LNG = 113,
			.timeTrial = 103680,
			.numTrophiesToOpen = 0,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = 0
		},
		[4] =
		{
			.hubID = 2,
			//.name_Debug = 0x8008d278,
			.name_LNG = 114,
			.timeTrial = 130560,
			.numTrophiesToOpen = 4,
			.ctrTokenGroupID = 2,
			.characterID_Boss = -1,
			.characterID_Champion = 7
		},
		[5] =
		{
			.hubID = 2,
			//.name_Debug = 0x8008d270,
			.name_LNG = 115,
			.timeTrial = 127680,
			.numTrophiesToOpen = 6,
			.ctrTokenGroupID = 0,
			.characterID_Boss = 9,
			.characterID_Champion = 9
		},
		[6] =
		{
			.hubID = 1,
			//.name_Debug = 0x8008d268,
			.name_LNG = 116,
			.timeTrial = 105600,
			.numTrophiesToOpen = 0,
			.ctrTokenGroupID = 1,
			.characterID_Boss = 10,
			.characterID_Champion = 10
		},
		[7] =
		{
			.hubID = 4,
			//.name_Debug = 0x8008d260,
			.name_LNG = 117,
			.timeTrial = 208320,
			.numTrophiesToOpen = 14,
			.ctrTokenGroupID = 3,
			.characterID_Boss = 8,
			.characterID_Champion = 8
		},
		[8] =
		{
			.hubID = 1,
			//.name_Debug = 0x8008d258,
			.name_LNG = 118,
			.timeTrial = 138240,
			.numTrophiesToOpen = 3,
			.ctrTokenGroupID = 2,
			.characterID_Boss = -1,
			.characterID_Champion = 12
		},
		[9] =
		{
			.hubID = 1,
			//.name_Debug = 0x8008d250,
			.name_LNG = 119,
			.timeTrial = 145920,
			.numTrophiesToOpen = 1,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = 14
		},
		[10] =
		{
			.hubID = 4,
			//.name_Debug = 0x8008d248,
			.name_LNG = 120,
			.timeTrial = 157440,
			.numTrophiesToOpen = 12,
			.ctrTokenGroupID = 1,
			.characterID_Boss = -1,
			.characterID_Champion = 1
		},
		[11] =
		{
			.hubID = 4,
			//.name_Debug = 0x8008d240,
			.name_LNG = 121,
			.timeTrial = 177600,
			.numTrophiesToOpen = 12,
			.ctrTokenGroupID = 2,
			.characterID_Boss = -1,
			.characterID_Champion = 4
		},
		[12] =
		{
			.hubID = 3,
			//.name_Debug = 0x8008d238,
			.name_LNG = 122,
			.timeTrial = 188160,
			.numTrophiesToOpen = 10,
			.ctrTokenGroupID = 1,
			.characterID_Boss = -1,
			.characterID_Champion = 6
		},
		[13] =
		{
			.hubID = 4,
			//.name_Debug = 0x8008d230,
			.name_LNG = 123,
			.timeTrial = 204480,
			.numTrophiesToOpen = 15,
			.ctrTokenGroupID = 3,
			.characterID_Boss = 15,
			.characterID_Champion = 15
		},
		[14] =
		{
			.hubID = 2,
			//.name_Debug = 0x8001138c,
			.name_LNG = 124,
			.timeTrial = 103680,
			.numTrophiesToOpen = 4,
			.ctrTokenGroupID = 1,
			.characterID_Boss = -1,
			.characterID_Champion = 3
		},
		[15] =
		{
			.hubID = 3,
			//.name_Debug = 0x80011380,
			.name_LNG = 125,
			.timeTrial = 232320,
			.numTrophiesToOpen = 11,
			.ctrTokenGroupID = 3,
			.characterID_Boss = -1,
			.characterID_Champion = 2
		},
		[16] =
		{
			.hubID = 0,
			//.name_Debug = 0x8008d228,
			.name_LNG = 126,
			.timeTrial = 138240,
			.numTrophiesToOpen = 10,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = 0
		},
		[17] =
		{
			.hubID = 0,
			//.name_Debug = 0x8008d220,
			.name_LNG = 127,
			.timeTrial = 144000,
			.numTrophiesToOpen = 15,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = 0
		},
		[18] =
		{
			.hubID = 4,
			//.name_Debug = 0x8008d218,
			.name_LNG = 98,
			.timeTrial = 172800,
			.numTrophiesToOpen = 4,
			.ctrTokenGroupID = 4,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[19] =
		{
			.hubID = 2,
			//.name_Debug = 0x8008d210,
			.name_LNG = 99,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 4,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[20] =
		{
			.hubID = -1,
			//.name_Debug = 0x8008d208,
			.name_LNG = 100,
			.timeTrial = 172800,
			.numTrophiesToOpen = 0,
			.ctrTokenGroupID = 4,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[21] =
		{
			.hubID = 1,
			//.name_Debug = 0x8008d200,
			.name_LNG = 101,
			.timeTrial = 172800,
			.numTrophiesToOpen = 1,
			.ctrTokenGroupID = 4,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[22] =
		{
			.hubID = -1,
			//.name_Debug = 0x8008d1f8,
			.name_LNG = 102,
			.timeTrial = 172800,
			.numTrophiesToOpen = 0,
			.ctrTokenGroupID = 4,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[23] =
		{
			.hubID = 3,
			//.name_Debug = 0x8008d1f0,
			.name_LNG = 103,
			.timeTrial = 172800,
			.numTrophiesToOpen = 3,
			.ctrTokenGroupID = 4,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[24] =
		{
			.hubID = -1,
			//.name_Debug = 0x8008d1e8,
			.name_LNG = 104,
			.timeTrial = 172800,
			.numTrophiesToOpen = 0,
			.ctrTokenGroupID = 4,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[25] =
		{
			.hubID = -1,
			//.name_Debug = 0x8008d1e0,
			.name_LNG = 128,
			.timeTrial = 172800,
			.numTrophiesToOpen = 0,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[26] =
		{
			.hubID = -1,
			//.name_Debug = 0x8008d1d8,
			.name_LNG = 129,
			.timeTrial = 172800,
			.numTrophiesToOpen = 0,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[27] =
		{
			.hubID = -1,
			//.name_Debug = 0x8008d1d0,
			.name_LNG = 130,
			.timeTrial = 172800,
			.numTrophiesToOpen = 0,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[28] =
		{
			.hubID = -1,
			//.name_Debug = 0x8008d1c8,
			.name_LNG = 131,
			.timeTrial = 172800,
			.numTrophiesToOpen = 1,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[29] =
		{
			.hubID = -1,
			//.name_Debug = 0x8008d1c0,
			.name_LNG = 132,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[30] =
		{
			.hubID = -1,
			//.name_Debug = 0x8008d1b8,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[31] =
		{
			.hubID = -1,
			//.name_Debug = 0x8008d1b0,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[32] =
		{
			.hubID = -1,
			//.name_Debug = 0x8008d1a8,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[33] =
		{
			.hubID = -1,
			//.name_Debug = 0x8008d1a0,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[34] =
		{
			.hubID = -1,
			//.name_Debug = 0x8008d198,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[35] =
		{
			.hubID = -1,
			//.name_Debug = 0x8008d190,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[36] =
		{
			.hubID = -1,
			//.name_Debug = 0x8008d188,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[37] =
		{
			.hubID = -1,
			//.name_Debug = 0x8008d180,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[38] =
		{
			.hubID = -1,
			//.name_Debug = 0x8008d178,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[39] =
		{
			.hubID = -1,
			//.name_Debug = 0x80011374,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[40] =
		{
			.hubID = -1,
			//.name_Debug = 0x8008d170,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[41] =
		{
			.hubID = -1,
			//.name_Debug = 0x8008d16c,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[42] =
		{
			.hubID = -1,
			//.name_Debug = 0x8008d164,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[43] =
		{
			.hubID = -1,
			//.name_Debug = 0x8008d15c,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[44] =
		{
			.hubID = -1,
			//.name_Debug = 0x8008d154,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[45] =
		{
			.hubID = -1,
			//.name_Debug = 0x8008d14c,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[46] =
		{
			.hubID = -1,
			//.name_Debug = 0x8008d144,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[47] =
		{
			.hubID = -1,
			//.name_Debug = 0x8008d13c,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[48] =
		{
			.hubID = -1,
			//.name_Debug = 0x8008d134,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[49] =
		{
			.hubID = -1,
			//.name_Debug = 0x8008d12c,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[50] =
		{
			.hubID = -1,
			//.name_Debug = 0x8008d124,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[51] =
		{
			.hubID = -1,
			//.name_Debug = 0x8008d11c,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[52] =
		{
			.hubID = -1,
			//.name_Debug = 0x8008d114,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[53] =
		{
			.hubID = -1,
			//.name_Debug = 0x80011368,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[54] =
		{
			.hubID = -1,
			//.name_Debug = 0x8001135c,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[55] =
		{
			.hubID = -1,
			//.name_Debug = 0x80011350,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[56] =
		{
			.hubID = -1,
			//.name_Debug = 0x80011344,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[57] =
		{
			.hubID = -1,
			//.name_Debug = 0x80011338,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[58] =
		{
			.hubID = -1,
			//.name_Debug = 0x8001132c,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[59] =
		{
			.hubID = -1,
			//.name_Debug = 0x80011320,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[60] =
		{
			.hubID = -1,
			//.name_Debug = 0x80011314,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[61] =
		{
			.hubID = -1,
			//.name_Debug = 0x80011308,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[62] =
		{
			.hubID = -1,
			//.name_Debug = 0x800112fc,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[63] =
		{
			.hubID = -1,
			//.name_Debug = 0x800112f0,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
		[64] =
		{
			.hubID = -1,
			//.name_Debug = 0x800112e4,
			.name_LNG = 0,
			.timeTrial = 172800,
			.numTrophiesToOpen = 2,
			.ctrTokenGroupID = 0,
			.characterID_Boss = -1,
			.characterID_Champion = -1
		},
	},

	.BeatBossPrize =
	{
		0x62, 0x5E, 0x5F, 0x60, 0x61
	},

	.advCupTrackIDs =
	{
		// Red Gem Cup
		CRASH_COVE, MYSTERY_CAVES, BLIZZARD_BLUFF, PAPU_PYRAMID,

		// Green Gem Cup
		ROO_TUBES, COCO_PARK, POLAR_PASS, CORTEX_CASTLE,

		// Blue Gem Cup
		TIGER_TEMPLE, SEWER_SPEEDWAY, DRAGON_MINES, N_GIN_LABS,

		// Yellow Gem Cup
		DINGO_CANYON, TINY_ARENA, HOT_AIR_SKYWAY, OXIDE_STATION,

		// Purple Gem Cup
		ROO_TUBES, PAPU_PYRAMID, DRAGON_MINES, HOT_AIR_SKYWAY
	},

	.advHubTrackIDs =
	{
		// N Sane Beach
		CRASH_COVE, ROO_TUBES, MYSTERY_CAVES, SEWER_SPEEDWAY,

		// Lost Ruins
		TIGER_TEMPLE, COCO_PARK, DINGO_CANYON, PAPU_PYRAMID,

		// Glacier Park
		BLIZZARD_BLUFF, DRAGON_MINES, POLAR_PASS, TINY_ARENA,

		// Citadel City
		CORTEX_CASTLE, HOT_AIR_SKYWAY, N_GIN_LABS, OXIDE_STATION
	},

	.AdvCups =
	{
		// Red Gem Cup
		{0xB9, {0x6c, 8, 8}},

		// Green Gem Cup
		{0xBA, {8, 0x6c, 8}},

		// Blue Gem Cup
		{0xBB, {0, 0, 0x80}},

		// Yellow Gem Cup
		{0xBC, {0x80, 0x80, 0}},

		// Purple Gem Cup
		{0xBD, {0x6c, 8, 0x6c}},
	},

	.lng_challenge =
	{
		0x163, 0x164, 0x165, 0x166, 0x167, 0x168
	},

	.ArcadeCups =
	{
		// Wumpa Cup
		{
			.lngIndex_CupName = 0xC0,
			.CupTrack =
			{
				0x3, 0x51, // Crash Cove
				0x4, 0x59, // Tiger Temple
				0x2, 0x4F, // Blizzard Bluff
				0xE, 0x43 // Coco Park
			}
		},

		{
			.lngIndex_CupName = 0xC1,
			.CupTrack =
			{
				0x6, 0x5B, // Roo Tubes
				0x0, 0x53, // Dingo Canyon
				0x1, 0x54, // Dragon Mines
				0x8, 0x57 // Sewer Speedway
			}
		},

		{
			.lngIndex_CupName = 0xC2,
			.CupTrack =
			{
				0x9, 0x4e, // Mystery Caves
				0x5, 0x5A, // Papu Pyramid
				0xA, 0x4D, // Cortex Castle
				0xF, 0x44 // Tiny Arena
			}
		},

		{
			.lngIndex_CupName = 0xC3,
			.CupTrack =
			{
				0xC, 0x50, // Polar Pass
				0xB, 0x52, // N Gin Labs
				0x7, 0x4C, // Hot Air Skyway
				0x10, 0x55 // Slide Col
			}
		}
	},

	.menuRacingWheelConfig =
	{
		.stringIndexTitle = 0xFFFF,
		.posX_curr = 0x100,
		.posY_curr = 0x6c,
		.unk1 = 0,
		.state = 0x88A3,
		.rows = 0,
		.funcPtr = 0x80038b5c,
		.drawStyle = 4,

		// the rest initializes as zeros
	},

	.rowsQuit =
	{
		{0xD2, 0, 1, 0, 0}, // YES
		{0xD3, 0, 1, 1, 1}, // NO
		{-1,   0, 0, 0, 0} // NULL
	},

	.menuQuit =
	{
		.stringIndexTitle = 3,
		.posX_curr = 0x100,
		.posY_curr = 0x6c,
		.unk1 = 0,
		.state = 0x8C83,
		.rows = &data.rowsQuit[0],
		.funcPtr = DECOMP_MainFreeze_MenuPtrQuit,
		.drawStyle = 4,

		// the rest initializes as zeros
	},

	.rwd =
	{
		{0x80, 7, 0x5F},
		{0x80, 7, 0x5F},
		{0x80, 7, 0x5F},
		{0x80, 7, 0x5F}
	},

	.kartHwlPath = "\\sounds\\kart.hwl;1",

	// empty
	//.PtrClipBuffer = {},

	#if BUILD >= UsaRetail
		#if BUILD <= JpnRetail
		.lngIndex_unused_multiplayerDirections =
		{
			0x25, 0x26, 0x27,
			0x28, 0x29, 0x2A
		},
		#endif

	.lngIndex_gamepadUnplugged =
	{
		0x1F, 0x20, 0x21,
		0x22, 0x23, 0x24
	},

	.errorPosY = {0x46, 0x8C, 0x14, 0},
	#endif

	// different #IF, dont combine with previous
	#if BUILD >= UsaRetail

	.raceConfig_DeadZone =
	{
		// "0", "3", "5", "7"
		{0x224, 0x00, 0x00},
		{0x225, 0x44, 0x04},
		{0x226, 0x71, 0x07},
		{0x227, 0x9f, 0x09},
	},

	.raceConfig_Range =
	{
		// "30", "45", "90", "135", "180"
		{0x229, 0x155, 0x15},
		{0x22a, 0x200, 0x1f},
		{0x22b, 0x400, 0x3f},
		{0x22c, 0x600, 0x5f},
		{0x22d, 0x800, 0x7f},
	},

	.raceConfig_unk80084290 =
	{
		0x03,
		0x04,
		0x10,
		-3,
		0x00,
		0x00,
		0x10,
		0x03,
		-16,
		-3,
		0x00,
		0x00,
		-16,
		0x03,
	},
	.raceConfig_colors_arrows =
	{
		0xff, 0x00, 0x00, 0x00,
		0xff, 0xc8, 0x00, 0x00,
		0xff, 0x00, 0x00, 0x00,
	},
	.raceConfig_colors_blueRect =
	{
		0x04, 0x3a, 0x94, 0x00, 0xb1, 0xcf, 0xff, 0x17,
		0xff, 0xff, 0xff, 0x22, 0xff, 0xff, 0xff, 0x27,
		0xb1, 0xcf, 0xff, 0x37, 0x04, 0x3a, 0x94, 0x64,
	},
	#endif

	#if BUILD <= JpnTrial
	.unkNamcoGamepadRwdTriangleColors =
	{
		0x5a, 0x5a, 0x6e, 0x00, 0x82, 0x82, 0x96, 0x00,
		0x32, 0x32, 0x46, 0x00
	},

	.unkNamcoGamepad_800842DC =
	{

		0x00,
		0x00,
		0x02,
		0x01,
		-2,
		-1,
		0x03,
		0x01,
		0x1b,
		-1,
		0x28,
		0x01,
		0x5a5a,
		0x6e,
		0x8282,
		0x96,
		0x3232,
		0x46,
		0x00,
		0x00,
		-2,
		-1,
		0x02,
		0x01,
	},
	#endif

	.gGT_gameMode1_VibPerPlayer =
	{
		0x100, 0x200, 0x400, 0x800
	},

	.Options_StringIDs_Gamepads =
	{
		0x151, 0x152, 0x153,
		0x154, 0x155, 0x156
	},

	.Options_StringIDs_Audio =
	{
		0x147, 0x148, 0x149, 0
	},

	.Options_VolumeSlider_Colors =
	{
		0, 0, 0x20, 0,
		0x80, 0x80, 0xFF, 0,
		0x80, 0x80, 0xFF, 0,
		0xFF, 0xFF, 0xFF, 0,
		0, 0, 0, 0
	},

	.Options_HighlightBar =
	{
		{0x001c, 0x000b}, // FX
		{0x0026, 0x000b}, // Music
		{0x0030, 0x000b}, // Voice
		{0x003b, 0x0009}, // Mode
		{0x004f, 0x0009}, // Controller 1
		{0x0059, 0x0009}, // Controller 2
		{0x0063, 0x0009}, // Controller 3
		{0x006d, 0x0009}, // Controller 4
		{0x0077, 0x0009}, // Exit
	},

	.rowsAdvHub =
	{
		{0x2, 3, 1, 0, 0}, // RESUME
		{0xB, 0, 2, 1, 1}, // AKU AKU HINTS
		{0x3, 1, 3, 2, 2}, // QUIT
		{0xE, 2, 0, 3, 3}, // OPTIONS
		{-1,  0, 0, 0, 0}  // NULL
	},

	.menuAdvHub =
	{
		.stringIndexTitle = 0xFFFF,
		.posX_curr = 0x100,
		.posY_curr = 0xAF,
		.unk1 = 0,
		.state = 0x8C83,
		.rows = &data.rowsAdvHub[0],
		.funcPtr = DECOMP_MainFreeze_MenuPtrDefault,
		.drawStyle = 4,
	},

	.rowsAdvRace =
	{
		{0x2, 3, 1, 0, 0}, // RESUME
		{0x1, 0, 2, 1, 1}, // RESTART
		{0xD, 1, 3, 2, 2}, // EXIT TO MAP
		{0xE, 2, 0, 3, 3}, // OPTIONS
		{-1,  0, 0, 0, 0}  // NULL
	},

	.menuAdvRace =
	{
		.stringIndexTitle = 0, // PAUSED
		.posX_curr = 0x100,
		.posY_curr = 0x6c,
		.unk1 = 0,
		.state = 0xc883,
		.rows = &data.rowsAdvRace[0],
		.funcPtr = DECOMP_MainFreeze_MenuPtrDefault,
		.drawStyle = 4,
	},

	.rowsAdvCup =
	{
		{0x2, 2, 1, 0, 0}, // RESUME
		{0xD, 0, 2, 1, 1}, // EXIT TO MAP
		{0xE, 1, 0, 2, 2}, // OPTIONS
		{-1,  0, 0, 0, 0}  // NULL
	},

	.menuAdvCup =
	{
		.stringIndexTitle = 0, // PAUSED
		.posX_curr = 0x100,
		.posY_curr = 0x6c,
		.unk1 = 0,
		.state = 0xc883,
		.rows = &data.rowsAdvCup[0],
		.funcPtr = DECOMP_MainFreeze_MenuPtrDefault,
		.drawStyle = 6,
	},

	.rowsBattle =
	{
		{0x2, 6, 1, 0, 0}, // RESUME
		{0x1, 0, 2, 1, 1}, // RESTART
		{0x5, 1, 3, 2, 2}, // CHANGE CHARACTER
		{0x6, 2, 4, 3, 3}, // CHANGE LEVEL
		{0xA, 3, 5, 4, 4}, // CHANGE SETUP
		{0x3, 4, 6, 5, 5}, // QUIT
		{0xE, 5, 0, 6, 6}, // OPTIONS
		{-1,  0, 0, 0, 0}  // NULL
	},

	.menuBattle =
	{
		.stringIndexTitle = 0, // PAUSED
		.posX_curr = 0x100,
		.posY_curr = 0x6c,
		.unk1 = 0,
		.state = 0xcc83,
		.rows = &data.rowsBattle[0],
		.funcPtr = DECOMP_MainFreeze_MenuPtrDefault,
		.drawStyle = 4,
	},

	.rowsArcadeCup =
	{
		{0x2, 2, 1, 0, 0}, // RESUME
		{0x3, 0, 2, 1, 1}, // QUIT
		{0xE, 1, 0, 2, 2}, // OPTIONS
		{-1,  0, 0, 0, 0}  // NULL
	},

	.menuArcadeCup =
	{
		.stringIndexTitle = 0, // PAUSED
		.posX_curr = 0x100,
		.posY_curr = 0x6c,
		.unk1 = 0,
		.state = 0xcc83,
		.rows = &data.rowsArcadeCup[0],
		.funcPtr = DECOMP_MainFreeze_MenuPtrDefault,
		.drawStyle = 4,
	},

	.rowsArcadeRace =
	{
		{0x2, 5, 1, 0, 0}, // RESUME
		{0x1, 0, 2, 1, 1}, // RESTART
		{0x5, 1, 3, 2, 2}, // CHANGE CHARACTER
		{0x6, 2, 4, 3, 3}, // CHANGE LEVEL
		{0x3, 3, 5, 4, 4}, // QUIT
		{0xE, 4, 0, 5, 5}, // OPTIONS
		{-1,  0, 0, 0, 0}  // NULL
	},

	.menuArcadeRace =
	{
		.stringIndexTitle = 0, // PAUSED
		.posX_curr = 0x100,
		.posY_curr = 0x6c,
		.unk1 = 0,
		.state = 0xcc83,
		.rows = &data.rowsArcadeRace[0],
		.funcPtr = DECOMP_MainFreeze_MenuPtrDefault,
		.drawStyle = 4,
	},

	.bitIndex_timeTrialFlags_saveData =
	{
		.nTropyOpen = 1,
		.nOxideOpen = 2,
	},

	.bitIndex_timeTrialFlags_flashingText =
	{
		.nTropyOpen = 0x8000000 | 0x800000,
		.nOxideOpen = 0x8000000 | 0x10000000,
	},

	.primMem_SizePerLEV_1P =
	{
		0x5f, 0x67, 0x67, 0x5f, 0x6e, 0x5f, 0x67, 0x67,
		0x67, 0x5f, 0x67, 0x5f, 0x5f, 0x5f, 0x5f, 0x67,
		0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f,
		0x5f, 0x00, 0x00, 0x00
	},

	.primMem_SizePerLEV_2P =
	{
		0xdc, 0x78, 0xa0, 0x88, 0x78, 0x78, 0xaa, 0x7d,
		0x78, 0x78, 0x8a, 0x7a, 0x7e, 0x78, 0xdc, 0x91,
		0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78,
		0x78, 0x00, 0x00, 0x00
	},

	.primMem_SizePerLEV_4P =
	{
		0x96, 0x96, 0x96, 0x96, 0x96, 0x96, 0x96, 0x96,
		0x96, 0x96, 0x96, 0x96, 0x91, 0x96, 0x96, 0x96,
		0x96, 0x96, 0x96, 0x96, 0x96, 0x96, 0x96, 0x96,
		0x96, 0x00, 0x00, 0x00
	},

	.trigApprox =
	{
		{0x0000, 0x1000}, {0x0006, 0x0fff}, {0x000c, 0x0fff}, {0x0012, 0x0fff}, {0x0019, 0x0fff}, {0x001f, 0x0fff}, {0x0025, 0x0fff}, {0x002b, 0x0fff},
		{0x0032, 0x0fff}, {0x0038, 0x0fff}, {0x003e, 0x0fff}, {0x0045, 0x0fff}, {0x004b, 0x0fff}, {0x0051, 0x0fff}, {0x0057, 0x0fff}, {0x005e, 0x0ffe},
		{0x0064, 0x0ffe}, {0x006a, 0x0ffe}, {0x0071, 0x0ffe}, {0x0077, 0x0ffe}, {0x007d, 0x0ffe}, {0x0083, 0x0ffd}, {0x008a, 0x0ffd}, {0x0090, 0x0ffd},
		{0x0096, 0x0ffd}, {0x009d, 0x0ffc}, {0x00a3, 0x0ffc}, {0x00a9, 0x0ffc}, {0x00af, 0x0ffc}, {0x00b6, 0x0ffb}, {0x00bc, 0x0ffb}, {0x00c2, 0x0ffb},
		{0x00c8, 0x0ffb}, {0x00cf, 0x0ffa}, {0x00d5, 0x0ffa}, {0x00db, 0x0ffa}, {0x00e2, 0x0ff9}, {0x00e8, 0x0ff9}, {0x00ee, 0x0ff9}, {0x00f4, 0x0ff8},
		{0x00fb, 0x0ff8}, {0x0101, 0x0ff7}, {0x0107, 0x0ff7}, {0x010d, 0x0ff7}, {0x0114, 0x0ff6}, {0x011a, 0x0ff6}, {0x0120, 0x0ff5}, {0x0127, 0x0ff5},
		{0x012d, 0x0ff4}, {0x0133, 0x0ff4}, {0x0139, 0x0ff3}, {0x0140, 0x0ff3}, {0x0146, 0x0ff2}, {0x014c, 0x0ff2}, {0x0152, 0x0ff1}, {0x0159, 0x0ff1},
		{0x015f, 0x0ff0}, {0x0165, 0x0ff0}, {0x016b, 0x0fef}, {0x0172, 0x0fef}, {0x0178, 0x0fee}, {0x017e, 0x0fee}, {0x0184, 0x0fed}, {0x018b, 0x0fec},
		{0x0191, 0x0fec}, {0x0197, 0x0feb}, {0x019d, 0x0feb}, {0x01a4, 0x0fea}, {0x01aa, 0x0fe9}, {0x01b0, 0x0fe9}, {0x01b6, 0x0fe8}, {0x01bd, 0x0fe7},
		{0x01c3, 0x0fe7}, {0x01c9, 0x0fe6}, {0x01cf, 0x0fe5}, {0x01d6, 0x0fe4}, {0x01dc, 0x0fe4}, {0x01e2, 0x0fe3}, {0x01e8, 0x0fe2}, {0x01ef, 0x0fe1},
		{0x01f5, 0x0fe1}, {0x01fb, 0x0fe0}, {0x0201, 0x0fdf}, {0x0208, 0x0fde}, {0x020e, 0x0fde}, {0x0214, 0x0fdd}, {0x021a, 0x0fdc}, {0x0221, 0x0fdb},
		{0x0227, 0x0fda}, {0x022d, 0x0fd9}, {0x0233, 0x0fd9}, {0x0239, 0x0fd8}, {0x0240, 0x0fd7}, {0x0246, 0x0fd6}, {0x024c, 0x0fd5}, {0x0252, 0x0fd4},
		{0x0259, 0x0fd3}, {0x025f, 0x0fd2}, {0x0265, 0x0fd1}, {0x026b, 0x0fd0}, {0x0271, 0x0fcf}, {0x0278, 0x0fce}, {0x027e, 0x0fcd}, {0x0284, 0x0fcc},
		{0x028a, 0x0fcb}, {0x0290, 0x0fca}, {0x0297, 0x0fc9}, {0x029d, 0x0fc8}, {0x02a3, 0x0fc7}, {0x02a9, 0x0fc6}, {0x02af, 0x0fc5}, {0x02b6, 0x0fc4},
		{0x02bc, 0x0fc3}, {0x02c2, 0x0fc2}, {0x02c8, 0x0fc1}, {0x02ce, 0x0fc0}, {0x02d5, 0x0fbf}, {0x02db, 0x0fbe}, {0x02e1, 0x0fbd}, {0x02e7, 0x0fbb},
		{0x02ed, 0x0fba}, {0x02f3, 0x0fb9}, {0x02fa, 0x0fb8}, {0x0300, 0x0fb7}, {0x0306, 0x0fb6}, {0x030c, 0x0fb4}, {0x0312, 0x0fb3}, {0x0318, 0x0fb2},
		{0x031f, 0x0fb1}, {0x0325, 0x0fb0}, {0x032b, 0x0fae}, {0x0331, 0x0fad}, {0x0337, 0x0fac}, {0x033d, 0x0fab}, {0x0344, 0x0fa9}, {0x034a, 0x0fa8},
		{0x0350, 0x0fa7}, {0x0356, 0x0fa5}, {0x035c, 0x0fa4}, {0x0362, 0x0fa3}, {0x0368, 0x0fa1}, {0x036f, 0x0fa0}, {0x0375, 0x0f9f}, {0x037b, 0x0f9d},
		{0x0381, 0x0f9c}, {0x0387, 0x0f9b}, {0x038d, 0x0f99}, {0x0393, 0x0f98}, {0x0399, 0x0f96}, {0x03a0, 0x0f95}, {0x03a6, 0x0f94}, {0x03ac, 0x0f92},
		{0x03b2, 0x0f91}, {0x03b8, 0x0f8f}, {0x03be, 0x0f8e}, {0x03c4, 0x0f8c}, {0x03ca, 0x0f8b}, {0x03d0, 0x0f89}, {0x03d7, 0x0f88}, {0x03dd, 0x0f86},
		{0x03e3, 0x0f85}, {0x03e9, 0x0f83}, {0x03ef, 0x0f82}, {0x03f5, 0x0f80}, {0x03fb, 0x0f7f}, {0x0401, 0x0f7d}, {0x0407, 0x0f7b}, {0x040d, 0x0f7a},
		{0x0413, 0x0f78}, {0x041a, 0x0f77}, {0x0420, 0x0f75}, {0x0426, 0x0f73}, {0x042c, 0x0f72}, {0x0432, 0x0f70}, {0x0438, 0x0f6e}, {0x043e, 0x0f6d},
		{0x0444, 0x0f6b}, {0x044a, 0x0f69}, {0x0450, 0x0f68}, {0x0456, 0x0f66}, {0x045c, 0x0f64}, {0x0462, 0x0f63}, {0x0468, 0x0f61}, {0x046e, 0x0f5f},
		{0x0474, 0x0f5d}, {0x047a, 0x0f5c}, {0x0480, 0x0f5a}, {0x0486, 0x0f58}, {0x048c, 0x0f56}, {0x0492, 0x0f55}, {0x0498, 0x0f53}, {0x049e, 0x0f51},
		{0x04a5, 0x0f4f}, {0x04ab, 0x0f4d}, {0x04b1, 0x0f4b}, {0x04b7, 0x0f4a}, {0x04bd, 0x0f48}, {0x04c3, 0x0f46}, {0x04c9, 0x0f44}, {0x04cf, 0x0f42},
		{0x04d5, 0x0f40}, {0x04db, 0x0f3e}, {0x04e0, 0x0f3c}, {0x04e6, 0x0f3b}, {0x04ec, 0x0f39}, {0x04f2, 0x0f37}, {0x04f8, 0x0f35}, {0x04fe, 0x0f33},
		{0x0504, 0x0f31}, {0x050a, 0x0f2f}, {0x0510, 0x0f2d}, {0x0516, 0x0f2b}, {0x051c, 0x0f29}, {0x0522, 0x0f27}, {0x0528, 0x0f25}, {0x052e, 0x0f23},
		{0x0534, 0x0f21}, {0x053a, 0x0f1f}, {0x0540, 0x0f1d}, {0x0546, 0x0f1b}, {0x054c, 0x0f18}, {0x0552, 0x0f16}, {0x0558, 0x0f14}, {0x055d, 0x0f12},
		{0x0563, 0x0f10}, {0x0569, 0x0f0e}, {0x056f, 0x0f0c}, {0x0575, 0x0f0a}, {0x057b, 0x0f08}, {0x0581, 0x0f05}, {0x0587, 0x0f03}, {0x058d, 0x0f01},
		{0x0593, 0x0eff}, {0x0599, 0x0efd}, {0x059e, 0x0efa}, {0x05a4, 0x0ef8}, {0x05aa, 0x0ef6}, {0x05b0, 0x0ef4}, {0x05b6, 0x0ef2}, {0x05bc, 0x0eef},
		{0x05c2, 0x0eed}, {0x05c7, 0x0eeb}, {0x05cd, 0x0ee8}, {0x05d3, 0x0ee6}, {0x05d9, 0x0ee4}, {0x05df, 0x0ee2}, {0x05e5, 0x0edf}, {0x05eb, 0x0edd},
		{0x05f0, 0x0edb}, {0x05f6, 0x0ed8}, {0x05fc, 0x0ed6}, {0x0602, 0x0ed4}, {0x0608, 0x0ed1}, {0x060e, 0x0ecf}, {0x0613, 0x0ecd}, {0x0619, 0x0eca},
		{0x061f, 0x0ec8}, {0x0625, 0x0ec5}, {0x062b, 0x0ec3}, {0x0630, 0x0ec0}, {0x0636, 0x0ebe}, {0x063c, 0x0ebc}, {0x0642, 0x0eb9}, {0x0648, 0x0eb7},
		{0x064d, 0x0eb4}, {0x0653, 0x0eb2}, {0x0659, 0x0eaf}, {0x065f, 0x0ead}, {0x0664, 0x0eaa}, {0x066a, 0x0ea8}, {0x0670, 0x0ea5}, {0x0676, 0x0ea3},
		{0x067b, 0x0ea0}, {0x0681, 0x0e9e}, {0x0687, 0x0e9b}, {0x068d, 0x0e98}, {0x0692, 0x0e96}, {0x0698, 0x0e93}, {0x069e, 0x0e91}, {0x06a3, 0x0e8e},
		{0x06a9, 0x0e8b}, {0x06af, 0x0e89}, {0x06b5, 0x0e86}, {0x06ba, 0x0e84}, {0x06c0, 0x0e81}, {0x06c6, 0x0e7e}, {0x06cb, 0x0e7c}, {0x06d1, 0x0e79},
		{0x06d7, 0x0e76}, {0x06dc, 0x0e74}, {0x06e2, 0x0e71}, {0x06e8, 0x0e6e}, {0x06ed, 0x0e6b}, {0x06f3, 0x0e69}, {0x06f9, 0x0e66}, {0x06fe, 0x0e63},
		{0x0704, 0x0e60}, {0x070a, 0x0e5e}, {0x070f, 0x0e5b}, {0x0715, 0x0e58}, {0x071b, 0x0e55}, {0x0720, 0x0e53}, {0x0726, 0x0e50}, {0x072b, 0x0e4d},
		{0x0731, 0x0e4a}, {0x0737, 0x0e47}, {0x073c, 0x0e44}, {0x0742, 0x0e42}, {0x0748, 0x0e3f}, {0x074d, 0x0e3c}, {0x0753, 0x0e39}, {0x0758, 0x0e36},
		{0x075e, 0x0e33}, {0x0763, 0x0e30}, {0x0769, 0x0e2d}, {0x076f, 0x0e2b}, {0x0774, 0x0e28}, {0x077a, 0x0e25}, {0x077f, 0x0e22}, {0x0785, 0x0e1f},
		{0x078a, 0x0e1c}, {0x0790, 0x0e19}, {0x0795, 0x0e16}, {0x079b, 0x0e13}, {0x07a0, 0x0e10}, {0x07a6, 0x0e0d}, {0x07ac, 0x0e0a}, {0x07b1, 0x0e07},
		{0x07b7, 0x0e04}, {0x07bc, 0x0e01}, {0x07c2, 0x0dfe}, {0x07c7, 0x0dfb}, {0x07cd, 0x0df8}, {0x07d2, 0x0df5}, {0x07d7, 0x0df2}, {0x07dd, 0x0dee},
		{0x07e2, 0x0deb}, {0x07e8, 0x0de8}, {0x07ed, 0x0de5}, {0x07f3, 0x0de2}, {0x07f8, 0x0ddf}, {0x07fe, 0x0ddc}, {0x0803, 0x0dd9}, {0x0809, 0x0dd5},
		{0x080e, 0x0dd2}, {0x0813, 0x0dcf}, {0x0819, 0x0dcc}, {0x081e, 0x0dc9}, {0x0824, 0x0dc6}, {0x0829, 0x0dc2}, {0x082e, 0x0dbf}, {0x0834, 0x0dbc},
		{0x0839, 0x0db9}, {0x083f, 0x0db6}, {0x0844, 0x0db2}, {0x0849, 0x0daf}, {0x084f, 0x0dac}, {0x0854, 0x0da9}, {0x085a, 0x0da5}, {0x085f, 0x0da2},
		{0x0864, 0x0d9f}, {0x086a, 0x0d9b}, {0x086f, 0x0d98}, {0x0874, 0x0d95}, {0x087a, 0x0d91}, {0x087f, 0x0d8e}, {0x0884, 0x0d8b}, {0x088a, 0x0d87},
		{0x088f, 0x0d84}, {0x0894, 0x0d81}, {0x0899, 0x0d7d}, {0x089f, 0x0d7a}, {0x08a4, 0x0d77}, {0x08a9, 0x0d73}, {0x08af, 0x0d70}, {0x08b4, 0x0d6c},
		{0x08b9, 0x0d69}, {0x08be, 0x0d65}, {0x08c4, 0x0d62}, {0x08c9, 0x0d5f}, {0x08ce, 0x0d5b}, {0x08d3, 0x0d58}, {0x08d9, 0x0d54}, {0x08de, 0x0d51},
		{0x08e3, 0x0d4d}, {0x08e8, 0x0d4a}, {0x08ee, 0x0d46}, {0x08f3, 0x0d43}, {0x08f8, 0x0d3f}, {0x08fd, 0x0d3c}, {0x0902, 0x0d38}, {0x0908, 0x0d35},
		{0x090d, 0x0d31}, {0x0912, 0x0d2d}, {0x0917, 0x0d2a}, {0x091c, 0x0d26}, {0x0921, 0x0d23}, {0x0927, 0x0d1f}, {0x092c, 0x0d1c}, {0x0931, 0x0d18},
		{0x0936, 0x0d14}, {0x093b, 0x0d11}, {0x0940, 0x0d0d}, {0x0945, 0x0d09}, {0x094b, 0x0d06}, {0x0950, 0x0d02}, {0x0955, 0x0cfe}, {0x095a, 0x0cfb},
		{0x095f, 0x0cf7}, {0x0964, 0x0cf3}, {0x0969, 0x0cf0}, {0x096e, 0x0cec}, {0x0973, 0x0ce8}, {0x0978, 0x0ce5}, {0x097d, 0x0ce1}, {0x0982, 0x0cdd},
		{0x0987, 0x0cd9}, {0x098d, 0x0cd6}, {0x0992, 0x0cd2}, {0x0997, 0x0cce}, {0x099c, 0x0cca}, {0x09a1, 0x0cc7}, {0x09a6, 0x0cc3}, {0x09ab, 0x0cbf},
		{0x09b0, 0x0cbb}, {0x09b5, 0x0cb7}, {0x09ba, 0x0cb4}, {0x09bf, 0x0cb0}, {0x09c4, 0x0cac}, {0x09c9, 0x0ca8}, {0x09ce, 0x0ca4}, {0x09d3, 0x0ca0},
		{0x09d7, 0x0c9d}, {0x09dc, 0x0c99}, {0x09e1, 0x0c95}, {0x09e6, 0x0c91}, {0x09eb, 0x0c8d}, {0x09f0, 0x0c89}, {0x09f5, 0x0c85}, {0x09fa, 0x0c81},
		{0x09ff, 0x0c7d}, {0x0a04, 0x0c79}, {0x0a09, 0x0c76}, {0x0a0e, 0x0c72}, {0x0a12, 0x0c6e}, {0x0a17, 0x0c6a}, {0x0a1c, 0x0c66}, {0x0a21, 0x0c62},
		{0x0a26, 0x0c5e}, {0x0a2b, 0x0c5a}, {0x0a30, 0x0c56}, {0x0a35, 0x0c52}, {0x0a39, 0x0c4e}, {0x0a3e, 0x0c4a}, {0x0a43, 0x0c46}, {0x0a48, 0x0c42},
		{0x0a4d, 0x0c3e}, {0x0a51, 0x0c3a}, {0x0a56, 0x0c36}, {0x0a5b, 0x0c31}, {0x0a60, 0x0c2d}, {0x0a65, 0x0c29}, {0x0a69, 0x0c25}, {0x0a6e, 0x0c21},
		{0x0a73, 0x0c1d}, {0x0a78, 0x0c19}, {0x0a7c, 0x0c15}, {0x0a81, 0x0c11}, {0x0a86, 0x0c0d}, {0x0a8b, 0x0c08}, {0x0a8f, 0x0c04}, {0x0a94, 0x0c00},
		{0x0a99, 0x0bfc}, {0x0a9d, 0x0bf8}, {0x0aa2, 0x0bf4}, {0x0aa7, 0x0bef}, {0x0aac, 0x0beb}, {0x0ab0, 0x0be7}, {0x0ab5, 0x0be3}, {0x0aba, 0x0bdf},
		{0x0abe, 0x0bda}, {0x0ac3, 0x0bd6}, {0x0ac8, 0x0bd2}, {0x0acc, 0x0bce}, {0x0ad1, 0x0bca}, {0x0ad5, 0x0bc5}, {0x0ada, 0x0bc1}, {0x0adf, 0x0bbd},
		{0x0ae3, 0x0bb8}, {0x0ae8, 0x0bb4}, {0x0aec, 0x0bb0}, {0x0af1, 0x0bac}, {0x0af6, 0x0ba7}, {0x0afa, 0x0ba3}, {0x0aff, 0x0b9f}, {0x0b03, 0x0b9a},
		{0x0b08, 0x0b96}, {0x0b0c, 0x0b92}, {0x0b11, 0x0b8d}, {0x0b15, 0x0b89}, {0x0b1a, 0x0b85}, {0x0b1f, 0x0b80}, {0x0b23, 0x0b7c}, {0x0b28, 0x0b78},
		{0x0b2c, 0x0b73}, {0x0b31, 0x0b6f}, {0x0b35, 0x0b6a}, {0x0b3a, 0x0b66}, {0x0b3e, 0x0b62}, {0x0b42, 0x0b5d}, {0x0b47, 0x0b59}, {0x0b4b, 0x0b54},
		{0x0b50, 0x0b50}, {0x0b54, 0x0b4b}, {0x0b59, 0x0b47}, {0x0b5d, 0x0b42}, {0x0b62, 0x0b3e}, {0x0b66, 0x0b3a}, {0x0b6a, 0x0b35}, {0x0b6f, 0x0b31},
		{0x0b73, 0x0b2c}, {0x0b78, 0x0b28}, {0x0b7c, 0x0b23}, {0x0b80, 0x0b1f}, {0x0b85, 0x0b1a}, {0x0b89, 0x0b15}, {0x0b8d, 0x0b11}, {0x0b92, 0x0b0c},
		{0x0b96, 0x0b08}, {0x0b9a, 0x0b03}, {0x0b9f, 0x0aff}, {0x0ba3, 0x0afa}, {0x0ba7, 0x0af6}, {0x0bac, 0x0af1}, {0x0bb0, 0x0aec}, {0x0bb4, 0x0ae8},
		{0x0bb8, 0x0ae3}, {0x0bbd, 0x0adf}, {0x0bc1, 0x0ada}, {0x0bc5, 0x0ad5}, {0x0bca, 0x0ad1}, {0x0bce, 0x0acc}, {0x0bd2, 0x0ac8}, {0x0bd6, 0x0ac3},
		{0x0bda, 0x0abe}, {0x0bdf, 0x0aba}, {0x0be3, 0x0ab5}, {0x0be7, 0x0ab0}, {0x0beb, 0x0aac}, {0x0bef, 0x0aa7}, {0x0bf4, 0x0aa2}, {0x0bf8, 0x0a9d},
		{0x0bfc, 0x0a99}, {0x0c00, 0x0a94}, {0x0c04, 0x0a8f}, {0x0c08, 0x0a8b}, {0x0c0d, 0x0a86}, {0x0c11, 0x0a81}, {0x0c15, 0x0a7c}, {0x0c19, 0x0a78},
		{0x0c1d, 0x0a73}, {0x0c21, 0x0a6e}, {0x0c25, 0x0a69}, {0x0c29, 0x0a65}, {0x0c2d, 0x0a60}, {0x0c31, 0x0a5b}, {0x0c36, 0x0a56}, {0x0c3a, 0x0a51},
		{0x0c3e, 0x0a4d}, {0x0c42, 0x0a48}, {0x0c46, 0x0a43}, {0x0c4a, 0x0a3e}, {0x0c4e, 0x0a39}, {0x0c52, 0x0a35}, {0x0c56, 0x0a30}, {0x0c5a, 0x0a2b},
		{0x0c5e, 0x0a26}, {0x0c62, 0x0a21}, {0x0c66, 0x0a1c}, {0x0c6a, 0x0a17}, {0x0c6e, 0x0a12}, {0x0c72, 0x0a0e}, {0x0c76, 0x0a09}, {0x0c79, 0x0a04},
		{0x0c7d, 0x09ff}, {0x0c81, 0x09fa}, {0x0c85, 0x09f5}, {0x0c89, 0x09f0}, {0x0c8d, 0x09eb}, {0x0c91, 0x09e6}, {0x0c95, 0x09e1}, {0x0c99, 0x09dc},
		{0x0c9d, 0x09d7}, {0x0ca0, 0x09d3}, {0x0ca4, 0x09ce}, {0x0ca8, 0x09c9}, {0x0cac, 0x09c4}, {0x0cb0, 0x09bf}, {0x0cb4, 0x09ba}, {0x0cb7, 0x09b5},
		{0x0cbb, 0x09b0}, {0x0cbf, 0x09ab}, {0x0cc3, 0x09a6}, {0x0cc7, 0x09a1}, {0x0cca, 0x099c}, {0x0cce, 0x0997}, {0x0cd2, 0x0992}, {0x0cd6, 0x098d},
		{0x0cd9, 0x0987}, {0x0cdd, 0x0982}, {0x0ce1, 0x097d}, {0x0ce5, 0x0978}, {0x0ce8, 0x0973}, {0x0cec, 0x096e}, {0x0cf0, 0x0969}, {0x0cf3, 0x0964},
		{0x0cf7, 0x095f}, {0x0cfb, 0x095a}, {0x0cfe, 0x0955}, {0x0d02, 0x0950}, {0x0d06, 0x094b}, {0x0d09, 0x0945}, {0x0d0d, 0x0940}, {0x0d11, 0x093b},
		{0x0d14, 0x0936}, {0x0d18, 0x0931}, {0x0d1c, 0x092c}, {0x0d1f, 0x0927}, {0x0d23, 0x0921}, {0x0d26, 0x091c}, {0x0d2a, 0x0917}, {0x0d2d, 0x0912},
		{0x0d31, 0x090d}, {0x0d35, 0x0908}, {0x0d38, 0x0902}, {0x0d3c, 0x08fd}, {0x0d3f, 0x08f8}, {0x0d43, 0x08f3}, {0x0d46, 0x08ee}, {0x0d4a, 0x08e8},
		{0x0d4d, 0x08e3}, {0x0d51, 0x08de}, {0x0d54, 0x08d9}, {0x0d58, 0x08d3}, {0x0d5b, 0x08ce}, {0x0d5f, 0x08c9}, {0x0d62, 0x08c4}, {0x0d65, 0x08be},
		{0x0d69, 0x08b9}, {0x0d6c, 0x08b4}, {0x0d70, 0x08af}, {0x0d73, 0x08a9}, {0x0d77, 0x08a4}, {0x0d7a, 0x089f}, {0x0d7d, 0x0899}, {0x0d81, 0x0894},
		{0x0d84, 0x088f}, {0x0d87, 0x088a}, {0x0d8b, 0x0884}, {0x0d8e, 0x087f}, {0x0d91, 0x087a}, {0x0d95, 0x0874}, {0x0d98, 0x086f}, {0x0d9b, 0x086a},
		{0x0d9f, 0x0864}, {0x0da2, 0x085f}, {0x0da5, 0x085a}, {0x0da9, 0x0854}, {0x0dac, 0x084f}, {0x0daf, 0x0849}, {0x0db2, 0x0844}, {0x0db6, 0x083f},
		{0x0db9, 0x0839}, {0x0dbc, 0x0834}, {0x0dbf, 0x082e}, {0x0dc2, 0x0829}, {0x0dc6, 0x0824}, {0x0dc9, 0x081e}, {0x0dcc, 0x0819}, {0x0dcf, 0x0813},
		{0x0dd2, 0x080e}, {0x0dd5, 0x0809}, {0x0dd9, 0x0803}, {0x0ddc, 0x07fe}, {0x0ddf, 0x07f8}, {0x0de2, 0x07f3}, {0x0de5, 0x07ed}, {0x0de8, 0x07e8},
		{0x0deb, 0x07e2}, {0x0dee, 0x07dd}, {0x0df2, 0x07d7}, {0x0df5, 0x07d2}, {0x0df8, 0x07cd}, {0x0dfb, 0x07c7}, {0x0dfe, 0x07c2}, {0x0e01, 0x07bc},
		{0x0e04, 0x07b7}, {0x0e07, 0x07b1}, {0x0e0a, 0x07ac}, {0x0e0d, 0x07a6}, {0x0e10, 0x07a0}, {0x0e13, 0x079b}, {0x0e16, 0x0795}, {0x0e19, 0x0790},
		{0x0e1c, 0x078a}, {0x0e1f, 0x0785}, {0x0e22, 0x077f}, {0x0e25, 0x077a}, {0x0e28, 0x0774}, {0x0e2b, 0x076f}, {0x0e2d, 0x0769}, {0x0e30, 0x0763},
		{0x0e33, 0x075e}, {0x0e36, 0x0758}, {0x0e39, 0x0753}, {0x0e3c, 0x074d}, {0x0e3f, 0x0748}, {0x0e42, 0x0742}, {0x0e44, 0x073c}, {0x0e47, 0x0737},
		{0x0e4a, 0x0731}, {0x0e4d, 0x072b}, {0x0e50, 0x0726}, {0x0e53, 0x0720}, {0x0e55, 0x071b}, {0x0e58, 0x0715}, {0x0e5b, 0x070f}, {0x0e5e, 0x070a},
		{0x0e60, 0x0704}, {0x0e63, 0x06fe}, {0x0e66, 0x06f9}, {0x0e69, 0x06f3}, {0x0e6b, 0x06ed}, {0x0e6e, 0x06e8}, {0x0e71, 0x06e2}, {0x0e74, 0x06dc},
		{0x0e76, 0x06d7}, {0x0e79, 0x06d1}, {0x0e7c, 0x06cb}, {0x0e7e, 0x06c6}, {0x0e81, 0x06c0}, {0x0e84, 0x06ba}, {0x0e86, 0x06b5}, {0x0e89, 0x06af},
		{0x0e8b, 0x06a9}, {0x0e8e, 0x06a3}, {0x0e91, 0x069e}, {0x0e93, 0x0698}, {0x0e96, 0x0692}, {0x0e98, 0x068d}, {0x0e9b, 0x0687}, {0x0e9e, 0x0681},
		{0x0ea0, 0x067b}, {0x0ea3, 0x0676}, {0x0ea5, 0x0670}, {0x0ea8, 0x066a}, {0x0eaa, 0x0664}, {0x0ead, 0x065f}, {0x0eaf, 0x0659}, {0x0eb2, 0x0653},
		{0x0eb4, 0x064d}, {0x0eb7, 0x0648}, {0x0eb9, 0x0642}, {0x0ebc, 0x063c}, {0x0ebe, 0x0636}, {0x0ec0, 0x0630}, {0x0ec3, 0x062b}, {0x0ec5, 0x0625},
		{0x0ec8, 0x061f}, {0x0eca, 0x0619}, {0x0ecd, 0x0613}, {0x0ecf, 0x060e}, {0x0ed1, 0x0608}, {0x0ed4, 0x0602}, {0x0ed6, 0x05fc}, {0x0ed8, 0x05f6},
		{0x0edb, 0x05f0}, {0x0edd, 0x05eb}, {0x0edf, 0x05e5}, {0x0ee2, 0x05df}, {0x0ee4, 0x05d9}, {0x0ee6, 0x05d3}, {0x0ee8, 0x05cd}, {0x0eeb, 0x05c7},
		{0x0eed, 0x05c2}, {0x0eef, 0x05bc}, {0x0ef2, 0x05b6}, {0x0ef4, 0x05b0}, {0x0ef6, 0x05aa}, {0x0ef8, 0x05a4}, {0x0efa, 0x059e}, {0x0efd, 0x0599},
		{0x0eff, 0x0593}, {0x0f01, 0x058d}, {0x0f03, 0x0587}, {0x0f05, 0x0581}, {0x0f08, 0x057b}, {0x0f0a, 0x0575}, {0x0f0c, 0x056f}, {0x0f0e, 0x0569},
		{0x0f10, 0x0563}, {0x0f12, 0x055d}, {0x0f14, 0x0558}, {0x0f16, 0x0552}, {0x0f18, 0x054c}, {0x0f1b, 0x0546}, {0x0f1d, 0x0540}, {0x0f1f, 0x053a},
		{0x0f21, 0x0534}, {0x0f23, 0x052e}, {0x0f25, 0x0528}, {0x0f27, 0x0522}, {0x0f29, 0x051c}, {0x0f2b, 0x0516}, {0x0f2d, 0x0510}, {0x0f2f, 0x050a},
		{0x0f31, 0x0504}, {0x0f33, 0x04fe}, {0x0f35, 0x04f8}, {0x0f37, 0x04f2}, {0x0f39, 0x04ec}, {0x0f3b, 0x04e6}, {0x0f3c, 0x04e0}, {0x0f3e, 0x04db},
		{0x0f40, 0x04d5}, {0x0f42, 0x04cf}, {0x0f44, 0x04c9}, {0x0f46, 0x04c3}, {0x0f48, 0x04bd}, {0x0f4a, 0x04b7}, {0x0f4b, 0x04b1}, {0x0f4d, 0x04ab},
		{0x0f4f, 0x04a5}, {0x0f51, 0x049e}, {0x0f53, 0x0498}, {0x0f55, 0x0492}, {0x0f56, 0x048c}, {0x0f58, 0x0486}, {0x0f5a, 0x0480}, {0x0f5c, 0x047a},
		{0x0f5d, 0x0474}, {0x0f5f, 0x046e}, {0x0f61, 0x0468}, {0x0f63, 0x0462}, {0x0f64, 0x045c}, {0x0f66, 0x0456}, {0x0f68, 0x0450}, {0x0f69, 0x044a},
		{0x0f6b, 0x0444}, {0x0f6d, 0x043e}, {0x0f6e, 0x0438}, {0x0f70, 0x0432}, {0x0f72, 0x042c}, {0x0f73, 0x0426}, {0x0f75, 0x0420}, {0x0f77, 0x041a},
		{0x0f78, 0x0413}, {0x0f7a, 0x040d}, {0x0f7b, 0x0407}, {0x0f7d, 0x0401}, {0x0f7f, 0x03fb}, {0x0f80, 0x03f5}, {0x0f82, 0x03ef}, {0x0f83, 0x03e9},
		{0x0f85, 0x03e3}, {0x0f86, 0x03dd}, {0x0f88, 0x03d7}, {0x0f89, 0x03d0}, {0x0f8b, 0x03ca}, {0x0f8c, 0x03c4}, {0x0f8e, 0x03be}, {0x0f8f, 0x03b8},
		{0x0f91, 0x03b2}, {0x0f92, 0x03ac}, {0x0f94, 0x03a6}, {0x0f95, 0x03a0}, {0x0f96, 0x0399}, {0x0f98, 0x0393}, {0x0f99, 0x038d}, {0x0f9b, 0x0387},
		{0x0f9c, 0x0381}, {0x0f9d, 0x037b}, {0x0f9f, 0x0375}, {0x0fa0, 0x036f}, {0x0fa1, 0x0368}, {0x0fa3, 0x0362}, {0x0fa4, 0x035c}, {0x0fa5, 0x0356},
		{0x0fa7, 0x0350}, {0x0fa8, 0x034a}, {0x0fa9, 0x0344}, {0x0fab, 0x033d}, {0x0fac, 0x0337}, {0x0fad, 0x0331}, {0x0fae, 0x032b}, {0x0fb0, 0x0325},
		{0x0fb1, 0x031f}, {0x0fb2, 0x0318}, {0x0fb3, 0x0312}, {0x0fb4, 0x030c}, {0x0fb6, 0x0306}, {0x0fb7, 0x0300}, {0x0fb8, 0x02fa}, {0x0fb9, 0x02f3},
		{0x0fba, 0x02ed}, {0x0fbb, 0x02e7}, {0x0fbd, 0x02e1}, {0x0fbe, 0x02db}, {0x0fbf, 0x02d5}, {0x0fc0, 0x02ce}, {0x0fc1, 0x02c8}, {0x0fc2, 0x02c2},
		{0x0fc3, 0x02bc}, {0x0fc4, 0x02b6}, {0x0fc5, 0x02af}, {0x0fc6, 0x02a9}, {0x0fc7, 0x02a3}, {0x0fc8, 0x029d}, {0x0fc9, 0x0297}, {0x0fca, 0x0290},
		{0x0fcb, 0x028a}, {0x0fcc, 0x0284}, {0x0fcd, 0x027e}, {0x0fce, 0x0278}, {0x0fcf, 0x0271}, {0x0fd0, 0x026b}, {0x0fd1, 0x0265}, {0x0fd2, 0x025f},
		{0x0fd3, 0x0259}, {0x0fd4, 0x0252}, {0x0fd5, 0x024c}, {0x0fd6, 0x0246}, {0x0fd7, 0x0240}, {0x0fd8, 0x0239}, {0x0fd9, 0x0233}, {0x0fd9, 0x022d},
		{0x0fda, 0x0227}, {0x0fdb, 0x0221}, {0x0fdc, 0x021a}, {0x0fdd, 0x0214}, {0x0fde, 0x020e}, {0x0fde, 0x0208}, {0x0fdf, 0x0201}, {0x0fe0, 0x01fb},
		{0x0fe1, 0x01f5}, {0x0fe1, 0x01ef}, {0x0fe2, 0x01e8}, {0x0fe3, 0x01e2}, {0x0fe4, 0x01dc}, {0x0fe4, 0x01d6}, {0x0fe5, 0x01cf}, {0x0fe6, 0x01c9},
		{0x0fe7, 0x01c3}, {0x0fe7, 0x01bd}, {0x0fe8, 0x01b6}, {0x0fe9, 0x01b0}, {0x0fe9, 0x01aa}, {0x0fea, 0x01a4}, {0x0feb, 0x019d}, {0x0feb, 0x0197},
		{0x0fec, 0x0191}, {0x0fec, 0x018b}, {0x0fed, 0x0184}, {0x0fee, 0x017e}, {0x0fee, 0x0178}, {0x0fef, 0x0172}, {0x0fef, 0x016b}, {0x0ff0, 0x0165},
		{0x0ff0, 0x015f}, {0x0ff1, 0x0159}, {0x0ff1, 0x0152}, {0x0ff2, 0x014c}, {0x0ff2, 0x0146}, {0x0ff3, 0x0140}, {0x0ff3, 0x0139}, {0x0ff4, 0x0133},
		{0x0ff4, 0x012d}, {0x0ff5, 0x0127}, {0x0ff5, 0x0120}, {0x0ff6, 0x011a}, {0x0ff6, 0x0114}, {0x0ff7, 0x010d}, {0x0ff7, 0x0107}, {0x0ff7, 0x0101},
		{0x0ff8, 0x00fb}, {0x0ff8, 0x00f4}, {0x0ff9, 0x00ee}, {0x0ff9, 0x00e8}, {0x0ff9, 0x00e2}, {0x0ffa, 0x00db}, {0x0ffa, 0x00d5}, {0x0ffa, 0x00cf},
		{0x0ffb, 0x00c8}, {0x0ffb, 0x00c2}, {0x0ffb, 0x00bc}, {0x0ffb, 0x00b6}, {0x0ffc, 0x00af}, {0x0ffc, 0x00a9}, {0x0ffc, 0x00a3}, {0x0ffc, 0x009d},
		{0x0ffd, 0x0096}, {0x0ffd, 0x0090}, {0x0ffd, 0x008a}, {0x0ffd, 0x0083}, {0x0ffe, 0x007d}, {0x0ffe, 0x0077}, {0x0ffe, 0x0071}, {0x0ffe, 0x006a},
		{0x0ffe, 0x0064}, {0x0ffe, 0x005e}, {0x0fff, 0x0057}, {0x0fff, 0x0051}, {0x0fff, 0x004b}, {0x0fff, 0x0045}, {0x0fff, 0x003e}, {0x0fff, 0x0038},
		{0x0fff, 0x0032}, {0x0fff, 0x002b}, {0x0fff, 0x0025}, {0x0fff, 0x001f}, {0x0fff, 0x0019}, {0x0fff, 0x0012}, {0x0fff, 0x000c}, {0x0fff, 0x0006},
	},

	.memcardIcon_CrashHead =
	{
		0x00114353, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0xf4d9f819, 0xffddff2d, 0xfb99ffff, 0xec1698c6, 0x83ff8c63, 0xd812dcb4, 0xbc2dd193, 0xb00ade36,
		0x34432100, 0x00000005, 0x43443200, 0x00000053, 0x63336520, 0x00000053, 0x86388627, 0x77777758,
		0x98389827, 0x77777558, 0x4444432a, 0x7777a534, 0x4444432a, 0xbbbb5344, 0x5885432a, 0xbbbb3444,
		0x8854332b, 0xbba54444, 0x4443352b, 0xbc544444, 0x3333552d, 0xc5344443, 0x333552ed, 0x55444443,
		0x335552cd, 0xc5333333, 0x55552cdd, 0xdd555555, 0xfd52cdff, 0xfdde5222, 0xffffffff, 0xffffffff,
	},

	.memcardIcon_Ghost =
	{
		0x00114353, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x84b2fca0, 0x8959886c, 0xfbdf8422, 0x8525adad, 0xbe18ce9d, 0x9cf1e8a0, 0xbc61e2f8, 0xc881b596,
		0x21110000, 0x30002112, 0x11111000, 0x33221121, 0x12200000, 0x21344411, 0x20000000, 0x02131442,
		0x44400000, 0x02211543, 0x65233330, 0x08836753, 0x47132000, 0x88994753, 0x1122aaaa, 0xa9bbb931,
		0x333aaaaa, 0xab266b93, 0x99331dcc, 0xae2996b9, 0xeee314df, 0xf82c5c6b, 0x222fffff, 0xf82c55c6,
		0xefffffff, 0xf8888889, 0xeebfffff, 0xfee9999e, 0x889bdddd, 0xdddeee88, 0xdddddddd, 0xdddddddd,
	},

	.memcardIcon_PsyqHand =
	{
		0x00114353, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x7fff0000, 0x03e07c00, 0x31b52973, 0x5b1d469c, 0x7bdf6f7f, 0x03c07800, 0x001e7bc0, 0x03ff781e,
		0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x9fffffff, 0xffffffff,
		0x89ffffff, 0xffffff56, 0x778fffff, 0xffffff56, 0x7579ffff, 0xffffff56, 0x56778fff, 0xffff7886,
		0x767578ff, 0xfff67779, 0x565678ff, 0xff576676, 0x65677fff, 0xff577556, 0x76566fff, 0xff567777,
		0x7777ffff, 0xfff56677, 0x7776ffff, 0xffff5566, 0x777fffff, 0xfffff566, 0x777fffff, 0xfffff566,
	},

	.BossWeaponOxide =
	{
		{0x00, 0x02, 0x66, 0x01, 0x02, 0x00},
		{0x10, 0x02, 0x64, 0x01, 0x02, 0x00},
		{0x21, 0x03, 0x03, 0x01, 0x0c, 0x01},
		{0x2f, 0x03, 0x01, 0x01, 0x0c, 0x00},
		{0x3b, 0x02, 0x0f, 0x01, 0x0c, 0x01},
		{0x40, 0x03, 0x01, 0x01, 0x0c, 0x00},
		{0x46, 0x02, 0x04, 0x01, 0x0c, 0x01},
		{0x56, 0x02, 0x0f, 0x01, 0x0c, 0x01},
		{0x5d, 0x02, 0x04, 0x01, 0x0c, 0x01},
		{0x60, 0x02, 0x0f, 0x01, 0x0c, 0x01},
		{0x65, 0x02, 0x04, 0x01, 0x0c, 0x01},
		{0x66, 0x02, 0x0f, 0x01, 0x0c, 0x01},
		{0x7f, 0x02, 0x04, 0x01, 0x0c, 0x01},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	},

	.BossWeaponRoo =
	{
		{0x00, 0x03, 0x03, 0x00, 0x0f, 0x00},
		{0x10, 0x03, 0x03, 0x00, 0x0f, 0x00},
		{0x21, 0x03, 0x03, 0x00, 0x0f, 0x00},
		{0x2f, 0x03, 0x03, 0x00, 0x0f, 0x00},
		{0x46, 0x03, 0x03, 0x00, 0x0f, 0x00},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	},

	.BossWeaponPapu =
	{
		{0x00, 0x02, 0x66, 0x01, 0x0c, 0x02},
		{0x0f, 0x02, 0x0f, 0x01, 0x0c, 0x02},
		{0x22, 0x02, 0x66, 0x01, 0x0c, 0x02},
		{0x53, 0x02, 0x0f, 0x01, 0x0c, 0x02},
		{0x5d, 0x02, 0x66, 0x01, 0x0c, 0x02},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	},

	.BossWeaponJoe =
	{
		{0x00, 0x02, 0x64, 0x00, 0x11, 0x02},
		{0x10, 0x02, 0x64, 0x00, 0x11, 0x02},
		{0x2a, 0x02, 0x0f, 0x00, 0x11, 0x02},
		{0x39, 0x02, 0x64, 0x00, 0x11, 0x02},
		{0x46, 0x02, 0x64, 0x00, 0x11, 0x02},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	},

	.BossWeaponPinstripe =
	{
		{0x00, 0x03, 0x01, 0x01, 0x0f, 0x00},
		{0x10, 0x03, 0x01, 0x01, 0x0f, 0x00},
		{0x21, 0x03, 0x0f, 0x01, 0x0f, 0x00},
		{0x2f, 0x03, 0x01, 0x01, 0x0f, 0x00},
		{0x46, 0x03, 0x01, 0x01, 0x0f, 0x00},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	},

	.bossWeaponMetaPtr =
	{
		&data.BossWeaponOxide,
		&data.BossWeaponRoo,
		&data.BossWeaponPapu,
		&data.BossWeaponJoe,
		&data.BossWeaponPinstripe,
	},

	.s_BASCUS_94426_SLOTS = "BASCUS-94426-SLOTS",

	.data38 =
	{
		0x82, 0x62, 0x82, 0x73,
		0x82, 0x71, 0x81, 0x46,
		0x82, 0x72, 0x82, 0x81,
		0x82, 0x96, 0x82, 0x85,
		0x82, 0x84, 0x81, 0x40,
		0x82, 0x66, 0x82, 0x81,
		0x82, 0x8d, 0x82, 0x85,
		0x82, 0x93, 0x81, 0x40,
		0x82, 0x81, 0x82, 0x8e,
		0x82, 0x84, 0x81, 0x40,
		0x82, 0x72, 0x82, 0x83,
		0x82, 0x8f, 0x82, 0x92,
		0x82, 0x85, 0x82, 0x93,
		0x00, 0x00, 0x00, 0x00, // null terminator
	},

	.s_BASCUS_94426G_Question = "BASCUS-94426G??????",
	.s_BASCUS_94426G_Star = "BASCUS-94426G*",

	.rowsSaveGame =
	{
		{0xD2, 0, 1, 0, 0}, // YES
		{0xD3, 0, 1, 1, 1}, // NO
		{-1,  0, 0, 0, 0}  // NULL
	},

	.menuSaveGame =
	{
		.stringIndexTitle = 0x235,
		.posX_curr = 0x100,
		.posY_curr = 0x96,
		.unk1 = 0,
		.state = 0xC81,
		.rows = &data.rowsSaveGame[0],
		.funcPtr = 0x8004B258,
		.drawStyle = 4,
	},

	.menuQueueLoadTrack =
	{
		.stringIndexTitle = 0xFFFF,
		.state = 0x20, // no input, just funcPtr
		.funcPtr = DECOMP_QueueLoadTrack_MenuProc
	},

	.matrixTitleFlag =
	{
		.m =
		{
			{-0xe93, -0x2aa, -0x607},
			{0xEA, -0x8cc, 0x1A9},
			{-0x662, 0x214, 0xE84},
		},

		.t = {0,0,0}
	},

	.checkerFlagVariables =
	{
		0, 0x96, 0, 0xB4, 0
	},

	.PlayerCommentBoxParams =
	{
		0, 0x19, 0xD, 0x13,
		0, 0x5, 0x3, 0x2
	},

	.messageScreens =
	{
		0x1010f,
		0x10118,
		0x100e1,
		0x100ea,
		0x100f3,
		0x105,
		0x10121,
		0x1012a,
		0x1ffff,
		0x10133,
	},

	.lngIndex_FinishOrLoser =
	{
		0x13C, // FINISHED!
		0xFFFF,
		0xFFFF,
		0xFFFF
	},

	.rowsGreenLoadSave =
	{
		{0xCB, 0, 1, 0, 0}, // LOAD
		{0xCC, 0, 2, 1, 1}, // SAVE
		{0xCD, 1, 3, 2, 2}, // DELETE
		{0xCE, 2, 3, 3, 3}, // EXIT
		{-1,  0, 0, 0, 0}  // NULL
	},

	.menuGreenLoadSave =
	{
		.stringIndexTitle = -1,
		.posX_curr = 0x100,
		.posY_curr = 0x7A,
		.unk1 = 0,
		.state = 0xC81,
		.rows = &data.rowsGreenLoadSave[0],
		.funcPtr = 0x80048960,
		.drawStyle = 0x10, // GREEN
	},

	.menuFourAdvProfiles =
	{
		.stringIndexTitle = -1,
		.state = 0x2820,
		.funcPtr = 0x800490c4,
	},

	.menuGhostSelection =
	{
		.stringIndexTitle = -1,
		.state = 0x2820,
		.funcPtr = 0x800490c4,
	},

	.menuWarning2 =
	{
		.stringIndexTitle = -1,
		.state = 0x2820,
		.funcPtr = 0x800490c4,
	},

	.menuSubmitName =
	{
		.stringIndexTitle = -1,
		.state = 0x820,
		.funcPtr = DECOMP_SubmitName_MenuProc,
	},

	.menuQueueLoadHub =
	{
		.stringIndexTitle = -1,
		.state = 0x20,
		.funcPtr = 0x80047da8,
	},

	.MetaDataLoadSave =
	{
		{0x61, 0x400, 0xF368, 0x99F, 0x232, 0x60, 0xA5, 0xFF},
		{0x62, 0x600},
		{0x63, 0x400, 0xF368, 0x99F, -0x2d8, 0xDC, 0xA6, 0x0},

		{0x61, 0x400, 0xF368, 0x99F, 0x232, 0x60, 0xA5, 0xFF},
		{0x62, 0x600},
		{0x63, 0x400, 0xF368, 0x99F, -0x2d8, 0xDC, 0xA6, 0x0},

		{0x61, 0x400, 0xF368, 0x99F, 0x232, 0x60, 0xA5, 0xFF},
		{0x62, 0x600},
		{0x63, 0x400, 0xF368, 0x99F, -0x2d8, 0xDC, 0xA6, 0x0},

		{0x61, 0x400, 0xF368, 0x99F, 0x232, 0x60, 0xA5, 0xFF},
		{0x62, 0x600},
		{0x63, 0x400, 0xF368, 0x99F, -0x2d8, 0xDC, 0xA6, 0x0},
	},

	.unk_80085d0c_LoadSave =
	{0x155, 0xF55, 0, 0},

	.lngIndex_LoadSave =
	{0xDC, 0xDD, 0xDA, 0xDB},

	// same as saveGame
	.rowsOverwrite =
	{
		{0xD2, 0, 1, 0, 0}, // YES
		{0xD3, 0, 1, 1, 1}, // NO
		{-1,  0, 0, 0, 0}  // NULL
	},

	.menuOverwriteAdv =
	{
		.stringIndexTitle = 0xD1, // overwrite?
		.posX_curr = 0x100,
		.posY_curr = 0x86,
		.unk1 = 0,
		.state = 0x8A1,
		.rows = &data.rowsOverwrite[0],
		.funcPtr = 0,
		.drawStyle = 0x10, // GREEN
	},

	.menuOverwriteGhost =
	{
		.stringIndexTitle = 0xD1, // overwrite?
		.posX_curr = 0x100,
		.posY_curr = 0x82,
		.unk1 = 0,
		.state = 0x8A1,
		.rows = &data.rowsOverwrite[0],
		.funcPtr = 0,
		.drawStyle = 0, // NORMAL
	},

	.lngStringsSaveLoadDelete =
	{
		0xD6, 0xD7, 0xD4,
		0xD5, 0xD8, 0xD9
	},

	.unicodeAscii =
	{
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
		'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
		'Y', 'Z', '0', '1', '2', '3', '4', '5',
		'6', '7', '8', '9', '.', '_', '<', 0
	},

	.soundIndexArray =
	{
		0, 0, 1, 2, 3, 5
	},

	.hud_1P_P1 =
	{
		{232,5,0,4096},
		{484,8,0,0},
		{50,191,256,5120},
		{316,24,512,4096},
		{336,16,0,0},
		{70,171,0,0},
		{491,206,0,0},
		{475,164,0,0},
		{490,206,0,0},
		{414,145,0,4096},
		{20,57,0,4096},
		{209,-5,0,4096},
		{286,9,0,2457},
		{454,8,0,0},
		{50,24,256,1536},
		{256,24,512,3072},
		{406,24,512,6144},
		{389,30,512,2048},
		{145,30,512,2048},
		{200,30,256,768},
	},

	.hud_2P_P1 =
	{
		// weapon
		{20,8,0,4096},

		// lap count
		#ifdef USE_NEW2P
		{501-0x103,181,0,0},
		#else
		{501,71,0,0},
		#endif

		// bignum
		#ifdef USE_NEW2P
		{40,194,256,4096},
		#else
		{40,83,256,4096},
		#endif

		// wumpa and shine
		#ifdef USE_NEW2P
		{430-0x103,18,512,4096},
		{454-0x103,10,0,0},
		#else
		{430,18,512,4096},
		{454,10,0,0},
		#endif

		// suffix
		#ifdef USE_NEW2P
		{60,191,0,0},
		#else
		{60,80,0,0},
		#endif

		{490,67,0,0},
		{461,72,0,0},

		// drift meter
		#ifdef USE_NEW2P
		{498-0x103+3,212,0,0},
		#else
		{498,102,0,0},
		#endif

		{414,22,0,2730},
		{20,112,0,4096},

		{-3,-2,0,4096},

		// relative to view, not screen
		#ifdef USE_NEW2P
		{0x8D,4,0,2457},
		#else
		{397,4,0,2457},
		#endif

		// battle points
		#ifdef USE_NEW2P
		{425-0x103,193,0,0},
		#else
		{425,83,0,0},
		#endif

		{430,18,256,2048},
		{40,83,256,4096},
		{430,18,512,4096},
		{430,18,512,4096},
		{430,18,512,4096},
		{430,18,512,4096},
	},

	.hud_2P_P2 =
	{
		// weapon
		#ifdef USE_NEW2P
		{20+0x103,8,0,4096},
		#else
		{20,112,0,4096},
		#endif

		// lap count
		{501,181,0,0},

		// bignum
		#ifdef USE_NEW2P
		{40+0x103,194,257,4112},
		#else
		{40,194,257,4112},
		#endif

		// wumpa and shine
		#ifdef USE_NEW2P
		{430,18,512,4096},
		{454,10,0,0},
		#else
		{430,122,512,4096},
		{454,114,0,0},
		#endif

		// suffix
		#ifdef USE_NEW2P
		{60+0x103,191,0,0},
		#else
		{60,191,0,0},
		#endif

		{490,177,0,0},
		{461,182,0,0},

		// drift meter
		#ifdef USE_NEW2P
		{498+3,212,0,0},
		#else
		{498,212,0,0},
		#endif

		{414,132,0,2730},
		{461,182,0,0},

		#ifdef USE_NEW2P
		{-3,-2,0,4096},
		#else
		{-3,-8,0,4096},
		#endif

		// relative to view, not screen
		#ifdef USE_NEW2P
		{0x8D,4,0,2457},
		#else
		{402,-2,0,2457},
		#endif

		// battle points
		{425,193,0,0},

		{430,122,256,2048},
		{40,194,257,4112},
		{430,122,512,4096},
		{430,122,512,4096},
		{430,122,512,4096},
		{430,122,512,4096},
	},

	.hud_4P_P1 =
	{
		{10,5,0,3072},
		{207,83,0,4096},
		{10,80,256,3584},
		{225,14,512,3072},
		{213,11,0,0},
		{38,77,0,0},
		{10,72,0,0},
		{10,77,0,0},

		// drift
		#ifdef USE_NEW2P
		{244-8,102,0,0},
		#else
		{244,102,0,0},
		#endif

		{10,77,0,0},
		{20,112,0,4096},
		{-8,-1,0,3072},
		{203,3,0,1843},
		{185,87,0,4096},
		{225,14,256,1536},
		{10,80,256,3584},
		{225,14,512,3072},
		{225,14,512,3072},
		{225,14,512,3072},
		{225,14,512,3072},
	},

	.hud_4P_P2 =
	{
		{470,5,0,3072},
		{267,83,0,4096},
		{434,80,256,3584},
		{279,14,512,3072},
		{267,11,0,0},
		{462,77,0,0},
		{490,72,0,0},
		{461,77,0,0},

		// drift
		#ifdef USE_NEW2P
		{315-8,102,0,0},
		#else
		{315,102,0,0},
		#endif

		{461,77,0,0},
		{461,77,0,0},
		{194,-1,0,3072},
		{-1,3,0,1843},
		{267,87,0,4096},
		{279,14,256,1536},
		{434,80,256,3584},
		{279,14,512,3072},
		{279,14,512,3072},
		{279,14,512,3072},
		{279,14,512,3072},
	},

	.hud_4P_P3 =
	{
		{10,112,0,3072},
		{207,193,0,4096},
		{10,192,256,3584},
		{225,120,512,3072},
		{213,117,0,0},
		{38,189,0,0},
		{10,181,0,0},
		{10,186,0,0},

		// drift
		#ifdef USE_NEW2P
		{244-8,212,0,0},
		#else
		{244,212,0,0},
		#endif

		{10,186,0,0},
		{10,186,0,0},
		{-8,-4,0,3072},
		{203,-1,0,1843},
		{185,197,0,4096},
		{225,120,256,1536},
		{10,192,256,3584},
		{225,120,512,3072},
		{225,120,512,3072},
		{225,120,512,3072},
		{225,120,512,3072},
	},

	.hud_4P_P4 =
	{
		{470,112,0,3072},
		{267,193,0,4096},
		{434,192,256,3584},
		{279,120,512,3072},
		{267,117,0,0},
		{462,189,0,0},
		{490,181,0,0},
		{461,186,0,0},

		// drift
		#ifdef USE_NEW2P
		{315-8,212,0,0},
		#else
		{315,212,0,0},
		#endif

		{461,186,0,0},
		{461,186,0,0},
		{194,-4,0,3072},
		{-1,-1,0,1843},
		{267,197,0,4096},
		{279,120,256,1536},
		{434,192,256,3584},
		{279,120,512,3072},
		{279,120,512,3072},
		{279,120,512,3072},
		{279,120,512,3072},
	},

	.hudStructPtr =
	{
		&data.hud_1P_P1,
		&data.hud_2P_P1,
		&data.hud_4P_P1,
		&data.hud_4P_P1,
	},

	.trackerAnim1 =
	{
		0x1000, 0x1000,
		0xe66, 0x10cc,
		0xccc, 0x1199,
		0x10d3, 0xe66,
		0x14d9, 0xb33,
		0x13b1, 0x12b5,
		0x1000, 0x1a38,
		0x8bb, 0x1063,
	},

	.trackerAnim2 =
	{
		0xd09, 0x199,
		0x1a12, 0x199,
		0x2000, 0x199,
		0x2000, 0x199,
		0x2000, 0x199,
		0x2000, 0x555,
		0x2000, 0xc44,
		0x2000, 0x1000,
		0x2000, 0x1000,
		0x1692, 0x13f8,
		0xccc, 0x1666,
	},

	.rankIconsDesired =
	{
		0,1,2,3,4,5,6,7
	},

	.rankIconsCurr =
	{
		0,1,2,3,4,5,6,7
	},

	.rankIconsTransitionTimer = {0},
	.trackerTimer = {0},
	.trackerType = {0},

	.rowsRetryExit =
	{
		{0x4, 0, 1, 0, 0}, // Retry
		{0xD, 0, 1, 1, 1}, // Exit To Map
		{-1,  0, 0, 0, 0}  // NULL
	},

	.menuRetryExit =
	{
		.stringIndexTitle = -1,
		.posX_curr = 0x100,
		.posY_curr = 0xB4,
		.unk1 = 0,
		.state = 0x803,
		.rows = &data.rowsRetryExit[0],
		.funcPtr = 0x80055c90,
		.drawStyle = 4,
	},

	.RelicTime =
	{
		// one row per track,
		// sapphire, gold, plat
		0x00013ec0, 0x000102c0, 0x0000c6c0,
		0x00014a00, 0x00010a40, 0x0000ca80,
		0x00015180, 0x0000ff00, 0x0000a8c0,
		0x000120c0, 0x0000f3c0, 0x0000c300,
		0x00012c00, 0x0000e880, 0x0000a140,
		0x00016080, 0x000102c0, 0x00009d80,
		0x00011940, 0x0000f3c0, 0x0000ce40,
		0x0002b5c0, 0x00024180, 0x0001c980,
		0x00015cc0, 0x0000f3c0, 0x00008ac0,
		0x0001af40, 0x00018600, 0x00015900,
		0x00024540, 0x0001d100, 0x00015900,
		0x0001fa40, 0x00016080, 0x0000c6c0,
		0x0002a300, 0x00023dc0, 0x0001d4c0,
		0x0002e2c0, 0x00029400, 0x00024180,
		0x00016440, 0x00010e00, 0x0000b7c0,
		0x00034bc0, 0x0002f580, 0x00029b80,
		0x0001af40, 0x000189c0, 0x00017700,
		0x000189c0, 0x00015900, 0x00012840,
	},

	.playerIconAdvMap =
	{
		.unk_playerAdvMap = {0, 0xFFF8, 0xFFF8},
		.unk2_playerAdvMap = {8, 8, 8},

		.vertCol1 = {0xFFFF, 0xFF, 0xFF},
		.vertCol2 = {0xFFFF80, 0xFF, 0xFF},
	},

	.stringIndexSuffix =
	{
		// st, nd, rd, th, th, th...
		0x19, 0x1A, 0x1B,
		0x1C, 0x1C, 0x1C, 0x1C, 0x1C
	},

	.battleScoreColor =
	{
		{1, 0, 0, 0},
		{0x8001, 0x8001, 0, 0},
		{0x8001, 0x8001, 0x8001, 0x8001},
		{0x8001, 0x8001, 0x8001, 0x8001},
	},

	.speedometerBG_vertData =
	{
		{
			{ .x = WIDE_34(-65), .y = 16 },  { .x = WIDE_34(-54), .y = 13 },
			{ .x = WIDE_34(-70), .y = 0 },   { .x = WIDE_34(-58), .y = 0 },
			{ .x = WIDE_34(-65), .y = -16 }, { .x = WIDE_34(-54), .y = -13 },
			{ .x = WIDE_34(-50), .y = -29 }, { .x = WIDE_34(-42), .y = -24 },
			{ .x = WIDE_34(-25), .y = -39 }, { .x = WIDE_34(-21), .y = -32 },
			{ .x = WIDE_34(0), .y = -42 },   { .x = WIDE_34(0), .y = -35 },
			{ .x = WIDE_34(25), .y = -39 },  { .x = WIDE_34(21), .y = -32 },
		},
		{
			{ .x = WIDE_34(-65), .y = 16 },  { .x = WIDE_34(-48), .y = 11 },
			{ .x = WIDE_34(-70), .y = 0 },   { .x = WIDE_34(-51), .y = 0 },
			{ .x = WIDE_34(-65), .y = -16 }, { .x = WIDE_34(-48), .y = -11 },
			{ .x = WIDE_34(-50), .y = -29 }, { .x = WIDE_34(-37), .y = -21 },
			{ .x = WIDE_34(-25), .y = -39 }, { .x = WIDE_34(-18), .y = -29 },
			{ .x = WIDE_34(0), .y = -42 },   { .x = WIDE_34(0), .y = -31 },
			{ .x = WIDE_34(25), .y = -39 },  { .x = WIDE_34(18), .y = -29 },
		},
	},

	// All QUIP data
	.data850 =
	{
		0xb8, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xb9, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xba, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xbb, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xbc, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xbd, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xbe, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xbf, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xc0, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xc1, 0x01, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xc2, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xc3, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xc4, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xc5, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xc6, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xc7, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xc8, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xc9, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xca, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xcb, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xcc, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xcd, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xce, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xcf, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xd0, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xd1, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xd2, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xd3, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xd4, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xd5, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xd6, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xd7, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xd8, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xd9, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xda, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xdb, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xdc, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xdd, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xde, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xdf, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xe0, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xe1, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xe2, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xe3, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xe4, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xe5, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xdc, 0x64, 0x08, 0x80, 0xe4, 0x64, 0x08, 0x80, 0x00, 0x00, 0x01, 0x00, 0x28, 0x00, 0x00, 0x00,
		0x54, 0x05, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xe4, 0x64, 0x08, 0x80, 0xec, 0x64, 0x08, 0x80,
		0x01, 0x00, 0x01, 0x00, 0xc0, 0x12, 0x00, 0x00, 0x3c, 0x05, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
		0xec, 0x64, 0x08, 0x80, 0xf4, 0x64, 0x08, 0x80, 0x00, 0x00, 0x01, 0x00, 0x00, 0x0f, 0x00, 0x00,
		0x30, 0x05, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xf4, 0x64, 0x08, 0x80, 0xfc, 0x64, 0x08, 0x80,
		0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x5d, 0x05, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
		0xfc, 0x64, 0x08, 0x80, 0x04, 0x65, 0x08, 0x80, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0x5e, 0x05, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0x65, 0x08, 0x80, 0x0c, 0x65, 0x08, 0x80,
		0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x68, 0x05, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
		0x0c, 0x65, 0x08, 0x80, 0x14, 0x65, 0x08, 0x80, 0x01, 0x00, 0x00, 0x00, 0xa0, 0x0f, 0x00, 0x00,
		0x18, 0x05, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x14, 0x65, 0x08, 0x80, 0x1c, 0x65, 0x08, 0x80,
		0x00, 0x00, 0x01, 0x00, 0x40, 0x0b, 0x00, 0x00, 0x40, 0x05, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
		0x1c, 0x65, 0x08, 0x80, 0x24, 0x65, 0x08, 0x80, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
		0x7c, 0x05, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x24, 0x65, 0x08, 0x80, 0x2c, 0x65, 0x08, 0x80,
		0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x60, 0x05, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
		0x2c, 0x65, 0x08, 0x80, 0x34, 0x65, 0x08, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00,
		0x74, 0x05, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x34, 0x65, 0x08, 0x80, 0x3c, 0x65, 0x08, 0x80,
		0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x6a, 0x05, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
		0x3c, 0x65, 0x08, 0x80, 0x44, 0x65, 0x08, 0x80, 0x01, 0x00, 0x01, 0x00, 0x06, 0x00, 0x00, 0x00,
		0x69, 0x05, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x44, 0x65, 0x08, 0x80, 0x4c, 0x65, 0x08, 0x80,
		0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x5f, 0x05, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
		0x4c, 0x65, 0x08, 0x80, 0x54, 0x65, 0x08, 0x80, 0x00, 0x00, 0x01, 0x00, 0x00, 0x0f, 0x00, 0x00,
		0x24, 0x05, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x54, 0x65, 0x08, 0x80, 0x5c, 0x65, 0x08, 0x80,
		0x00, 0x00, 0x00, 0x00, 0x40, 0x0b, 0x00, 0x00, 0x48, 0x05, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
		0x5c, 0x65, 0x08, 0x80, 0x64, 0x65, 0x08, 0x80, 0x00, 0x00, 0x01, 0x00, 0x00, 0x0f, 0x00, 0x00,
		0x4c, 0x05, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x64, 0x65, 0x08, 0x80, 0x6c, 0x65, 0x08, 0x80,
		0x00, 0x00, 0x01, 0x00, 0xc0, 0x12, 0x00, 0x00, 0x44, 0x05, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
		0x6c, 0x65, 0x08, 0x80, 0x74, 0x65, 0x08, 0x80, 0x00, 0x00, 0x01, 0x00, 0x00, 0x1e, 0x00, 0x00,
		0x20, 0x05, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x74, 0x65, 0x08, 0x80, 0x7c, 0x65, 0x08, 0x80,
		0x00, 0x00, 0x01, 0x00, 0xc0, 0x12, 0x00, 0x00, 0x1c, 0x05, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
		0x7c, 0x65, 0x08, 0x80, 0x84, 0x65, 0x08, 0x80, 0x00, 0x00, 0x01, 0x00, 0x00, 0x4b, 0x00, 0x00,
		0x34, 0x05, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x84, 0x65, 0x08, 0x80, 0x8c, 0x65, 0x08, 0x80,
		0x00, 0x00, 0x01, 0x00, 0x00, 0x4b, 0x00, 0x00, 0x38, 0x05, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
		0x8c, 0x65, 0x08, 0x80, 0x94, 0x65, 0x08, 0x80, 0x00, 0x00, 0x01, 0x00, 0x00, 0x1e, 0x00, 0x00,
		0x3c, 0x05, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x94, 0x65, 0x08, 0x80, 0x9c, 0x65, 0x08, 0x80,
		0x00, 0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x50, 0x05, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0x9c, 0x65, 0x08, 0x80, 0xa4, 0x65, 0x08, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x56, 0x05, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xa4, 0x65, 0x08, 0x80, 0xac, 0x65, 0x08, 0x80,
		0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x57, 0x05, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
		0xac, 0x65, 0x08, 0x80, 0xb4, 0x65, 0x08, 0x80, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00,
		0x68, 0x05, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xb4, 0x65, 0x08, 0x80, 0xbc, 0x65, 0x08, 0x80,
		0x00, 0x00, 0x00, 0x00, 0xa0, 0x0f, 0x00, 0x00, 0x18, 0x05, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
		0xbc, 0x65, 0x08, 0x80, 0xc4, 0x65, 0x08, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
		0x59, 0x05, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xc4, 0x65, 0x08, 0x80, 0xcc, 0x65, 0x08, 0x80,
		0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x7c, 0x05, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
		0xcc, 0x65, 0x08, 0x80, 0xd4, 0x65, 0x08, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00,
		0x74, 0x05, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xd4, 0x65, 0x08, 0x80, 0xdc, 0x65, 0x08, 0x80,
		0x00, 0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x52, 0x05, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xdc, 0x65, 0x08, 0x80, 0xe4, 0x65, 0x08, 0x80, 0x00, 0x00, 0x01, 0x00, 0xc0, 0x12, 0x00, 0x00,
		0x2c, 0x05, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xe4, 0x65, 0x08, 0x80, 0xec, 0x65, 0x08, 0x80,
		0x00, 0x00, 0x01, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x69, 0x05, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
		0xec, 0x65, 0x08, 0x80, 0xf4, 0x65, 0x08, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x25, 0x00, 0x00,
		0x78, 0x05, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xf4, 0x65, 0x08, 0x80, 0xfc, 0x65, 0x08, 0x80,
		0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x58, 0x05, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
		0xfc, 0x65, 0x08, 0x80, 0x04, 0x66, 0x08, 0x80, 0x05, 0x00, 0x00, 0x00, 0x80, 0x25, 0x00, 0x00,
		0x14, 0x05, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x66, 0x08, 0x80, 0x0c, 0x66, 0x08, 0x80,
		0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x5b, 0x05, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
		0x0c, 0x66, 0x08, 0x80, 0x4c, 0x66, 0x08, 0x80, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x59, 0x05, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xe6, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xe7, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xe8, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xe9, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xea, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xeb, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xec, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xed, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xee, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xef, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xf0, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xf1, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xf2, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xf3, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xf4, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xf5, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xf6, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xf7, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xf8, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xf9, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xfa, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xfb, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xfc, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xfd, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xff, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0x01, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0x03, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xde, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xdf, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xe0, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xe1, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xe2, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xe3, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xe4, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xe5, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0x05, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x06, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0x07, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x08, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0x09, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0a, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0x0b, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0c, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0x0d, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0e, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0x0f, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x10, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0x11, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x12, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0x13, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x14, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0x15, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x16, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0x17, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x18, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0x19, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x1a, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0x1b, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x1c, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0x1d, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x1e, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0x1f, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x21, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0x64, 0x6b, 0x08, 0x80, 0xcc, 0x6b, 0x08, 0x80, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x59, 0x05, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x24, 0x6b, 0x08, 0x80, 0x64, 0x6b, 0x08, 0x80,
		0x07, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x59, 0x05, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
		0xf4, 0x69, 0x08, 0x80, 0x2c, 0x6a, 0x08, 0x80, 0x08, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x59, 0x05, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xcc, 0x6b, 0x08, 0x80, 0xd4, 0x6b, 0x08, 0x80,
		0x08, 0x00, 0x02, 0x00, 0x0f, 0x00, 0x00, 0x00, 0xf6, 0x04, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xd4, 0x6b, 0x08, 0x80, 0xdc, 0x6b, 0x08, 0x80, 0x04, 0x00, 0x06, 0x00, 0x02, 0x00, 0x00, 0x00,
		0x59, 0x05, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xdc, 0x6b, 0x08, 0x80, 0xe4, 0x6b, 0x08, 0x80,
		0x00, 0x00, 0x06, 0x00, 0x03, 0x00, 0x00, 0x00, 0xf2, 0x04, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xe4, 0x6b, 0x08, 0x80, 0xec, 0x6b, 0x08, 0x80, 0x00, 0x00, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xf4, 0x04, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xec, 0x6b, 0x08, 0x80, 0xf4, 0x6b, 0x08, 0x80,
		0x08, 0x00, 0x06, 0x00, 0x06, 0x00, 0x00, 0x00, 0xf0, 0x04, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0xf4, 0x6b, 0x08, 0x80, 0xfc, 0x6b, 0x08, 0x80, 0x08, 0x00, 0x06, 0x00, 0x04, 0x00, 0x00, 0x00,
		0xf0, 0x04, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xfc, 0x6b, 0x08, 0x80, 0x04, 0x6c, 0x08, 0x80,
		0x08, 0x00, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0xf0, 0x04, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0x04, 0x6c, 0x08, 0x80, 0x0c, 0x6c, 0x08, 0x80, 0x06, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x57, 0x05, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x2c, 0x6a, 0x08, 0x80, 0x24, 0x6b, 0x08, 0x80,
		0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x59, 0x05, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
	},

	.advCupStringIndex =
	{
		0xB9, // RED
		0xBA, // GREEN
		0xBB, // BLUE
		0xBC, // YELLOW
		0xBD, // PURPLE
		0
	},

	.arcadeVsCupStringIndex =
	{
		0xC0, // WUMPA
		0xC1, // CRYSTAL
		0xC2, // NITRO
		0xC3, // CRASH
		0, 0
	},

	.cupPositionPerPlayer =
	{
		0,1,2,3,4,5,6,7
	},

	.cupPointsPerPosition =
	{
		// more optimal version than
		// OG game, see usage for details

		// Arcade
		9,6,3,1,

		// VS
		3,2,1,0
	},

	// By default, can NOT remove rdata name_Debug,
	// the strings are needed for model lookup
	.MetaDataCharacters =
	{
		[0] =
		{
#ifndef REBUILD_PC
			.name_Debug = &rdata.s_crash[0],
#endif
			.name_LNG_long = 44,
			.name_LNG_short = 60,
			.iconID = 32,
			.engineID = 0,
		},
		[1] =
		{
#ifndef REBUILD_PC
			.name_Debug = &rdata.s_cortex[0],
#endif
			.name_LNG_long = 45,
			.name_LNG_short = 61,
			.iconID = 33,
			.engineID = 0,
		},
		[2] =
		{
#ifndef REBUILD_PC
			.name_Debug = &rdata.s_tiny[0],
#endif
			.name_LNG_long = 46,
			.name_LNG_short = 62,
			.iconID = 34,
			.engineID = 2,
		},
		[3] =
		{
#ifndef REBUILD_PC
			.name_Debug = &rdata.s_coco[0],
#endif
			.name_LNG_long = 47,
			.name_LNG_short = 63,
			.iconID = 35,
			.engineID = 1,
		},
		[4] =
		{
#ifndef REBUILD_PC
			.name_Debug = &rdata.s_ngin[0],
#endif
			.name_LNG_long = 48,
			.name_LNG_short = 64,
			.iconID = 36,
			.engineID = 1,
		},
		[5] =
		{
#ifndef REBUILD_PC
			.name_Debug = &rdata.s_dingo[0],
#endif
			.name_LNG_long = 49,
			.name_LNG_short = 65,
			.iconID = 37,
			.engineID = 2,
		},
		[6] =
		{
#ifndef REBUILD_PC
			.name_Debug = &rdata.s_polar[0],
#endif
			.name_LNG_long = 50,
			.name_LNG_short = 66,
			.iconID = 38,
			.engineID = 3,
		},
		[7] =
		{
#ifndef REBUILD_PC
			.name_Debug = &rdata.s_pura[0],
#endif
			.name_LNG_long = 51,
			.name_LNG_short = 67,
			.iconID = 39,
			.engineID = 3,
		},
		[8] =
		{
#ifndef REBUILD_PC
			.name_Debug = &rdata.s_pinstripe[0],
#endif
			.name_LNG_long = 52,
			.name_LNG_short = 68,
			.iconID = 43,
			.engineID = 1,
		},
		[9] =
		{
#ifndef REBUILD_PC
			.name_Debug = &rdata.s_papu[0],
#endif
			.name_LNG_long = 53,
			.name_LNG_short = 69,
			.iconID = 41,
			.engineID = 2,
		},
		[10] =
		{
#ifndef REBUILD_PC
			.name_Debug = &rdata.s_roo[0],
#endif
			.name_LNG_long = 54,
			.name_LNG_short = 70,
			.iconID = 40,
			.engineID = 3,
		},
		[11] =
		{
#ifndef REBUILD_PC
			.name_Debug = &rdata.s_joe[0],
#endif
			.name_LNG_long = 55,
			.name_LNG_short = 71,
			.iconID = 42,
			.engineID = 0,
		},
		[12] =
		{
#ifndef REBUILD_PC
			.name_Debug = &rdata.s_ntropy[0],
#endif
			.name_LNG_long = 56,
			.name_LNG_short = 72,
			.iconID = 44,
			.engineID = 2,
		},
		[13] =
		{
#ifndef REBUILD_PC
			.name_Debug = &rdata.s_pen[0],
#endif
			.name_LNG_long = 58,
			.name_LNG_short = 74,
			.iconID = 53,

			#if (BUILD >= JpnTrial) || defined(USE_PENTA)
			.engineID = 4,
			#else
			.engineID = 3,
			#endif
		},
		[14] =
		{
#ifndef REBUILD_PC
			.name_Debug = &rdata.s_fake[0],
#endif
			.name_LNG_long = 59,
			.name_LNG_short = 75,
			.iconID = 54,
			.engineID = 0,
		},
		[15] =
		{
#ifndef REBUILD_PC
			.name_Debug = &rdata.s_oxide[0],
#endif
			.name_LNG_long = 57,
			.name_LNG_short = 73,
			.iconID = 55,
			.engineID = 0,
		}
	},

	.characterIDs =
	{
		0,1,2,3,4,5,6,7
	},

	.matArr01 =
	{
	[0] =
	{
		.m =
		{
			{0,-19,-537},
			{0,-26,0},
			{0,0,4096},
		},
		.extraShort = 4262, // Sneaky ND trick
		.t = {3686,0,0}
	},
	[1] =
	{
		.m =
		{
			{0,45,-789},
			{0,-53,0},
			{0,0,4096},
		},
		.extraShort = 4429, // Sneaky ND trick
		.t = {3276,0,0}
	},
	[2] =
	{
		.m =
		{
			{0,359,-162},
			{0,-82,0},
			{0,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {3596,0,0}
	},
	[3] =
	{
		.m =
		{
			{0,779,720},
			{0,-112,0},
			{0,0,4096},
		},
		.extraShort = 4420, // Sneaky ND trick
		.t = {4300,0,0}
	},
	[4] =
	{
		.m =
		{
			{0,1234,1471},
			{0,-142,0},
			{0,0,4096},
		},
		.extraShort = 4217, // Sneaky ND trick
		.t = {5004,0,0}
	},
	[5] =
	{
		.m =
		{
			{0,1685,1994},
			{0,-171,0},
			{0,0,4096},
		},
		.extraShort = 3974, // Sneaky ND trick
		.t = {5324,0,0}
	},
	[6] =
	{
		.m =
		{
			{0,2093,1958},
			{0,-198,0},
			{0,0,4096},
		},
		.extraShort = 3771, // Sneaky ND trick
		.t = {5233,0,0}
	},
	[7] =
	{
		.m =
		{
			{0,2385,1690},
			{0,-222,0},
			{0,0,4096},
		},
		.extraShort = 3686, // Sneaky ND trick
		.t = {5006,0,0}
	},
	[8] =
	{
		.m =
		{
			{0,2431,1398},
			{0,-243,0},
			{0,0,4096},
		},
		.extraShort = 3750, // Sneaky ND trick
		.t = {4710,0,0}
	},
	[9] =
	{
		.m =
		{
			{0,2361,1115},
			{0,-259,0},
			{0,0,4096},
		},
		.extraShort = 3891, // Sneaky ND trick
		.t = {4414,0,0}
	},
	[10] =
	{
		.m =
		{
			{0,2232,946},
			{0,-269,0},
			{0,0,4096},
		},
		.extraShort = 4032, // Sneaky ND trick
		.t = {4186,0,0}
	},
	},

	.matArr02 =
	{
	[0] =
	{
		.m =
		{
			{0,2132,879},
			{0,-273,0},
			{0,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	},

	.matArr03 =
	{
	[0] =
	{
		.m =
		{
			{0,1896,865},
			{0,-243,0},
			{0,0,4096},
		},
		.extraShort = 4057, // Sneaky ND trick
		.t = {4171,0,0}
	},
	[1] =
	{
		.m =
		{
			{0,1502,844},
			{0,-171,0},
			{0,0,4096},
		},
		.extraShort = 3974, // Sneaky ND trick
		.t = {4338,0,0}
	},
	[2] =
	{
		.m =
		{
			{0,716,792},
			{0,-82,0},
			{0,0,4096},
		},
		.extraShort = 3891, // Sneaky ND trick
		.t = {4505,0,0}
	},
	[3] =
	{
		.m =
		{
			{0,481,1014},
			{0,-2,0},
			{0,0,4915},
		},
		.extraShort = 3276, // Sneaky ND trick
		.t = {4915,0,0}
	},
	[4] =
	{
		.m =
		{
			{0,297,541},
			{0,-2,0},
			{0,0,4596},
		},
		.extraShort = 3595, // Sneaky ND trick
		.t = {4596,0,0}
	},
	[5] =
	{
		.m =
		{
			{0,-22,-203},
			{0,-2,0},
			{0,0,4005},
		},
		.extraShort = 4186, // Sneaky ND trick
		.t = {4005,0,0}
	},
	[6] =
	{
		.m =
		{
			{0,-224,-389},
			{0,-2,0},
			{0,0,3686},
		},
		.extraShort = 4505, // Sneaky ND trick
		.t = {3686,0,0}
	},
	[7] =
	{
		.m =
		{
			{0,-287,-439},
			{0,-2,0},
			{0,0,3792},
		},
		.extraShort = 4399, // Sneaky ND trick
		.t = {3792,0,0}
	},
	[8] =
	{
		.m =
		{
			{0,-142,-220},
			{0,-2,0},
			{0,0,3989},
		},
		.extraShort = 4202, // Sneaky ND trick
		.t = {3989,0,0}
	},
	},

	.matArr04 =
	{
	[0] =
	{
		.m =
		{
			{0,5954,491},
			{0,341,0},
			{0,0,5632},
		},
		.extraShort = 3328, // Sneaky ND trick
		.t = {4403,0,0}
	},
	[1] =
	{
		.m =
		{
			{0,11000,4199},
			{0,682,0},
			{0,0,7168},
		},
		.extraShort = 2560, // Sneaky ND trick
		.t = {4710,0,0}
	},
	[2] =
	{
		.m =
		{
			{0,10893,3886},
			{0,682,0},
			{0,0,6345},
		},
		.extraShort = 3011, // Sneaky ND trick
		.t = {4524,0,0}
	},
	[3] =
	{
		.m =
		{
			{0,10546,3394},
			{0,682,0},
			{0,0,4816},
		},
		.extraShort = 3849, // Sneaky ND trick
		.t = {4179,0,0}
	},
	[4] =
	{
		.m =
		{
			{0,9675,2322},
			{0,633,0},
			{0,0,3993},
		},
		.extraShort = 4300, // Sneaky ND trick
		.t = {3993,0,0}
	},
	[5] =
	{
		.m =
		{
			{0,8182,1161},
			{0,507,0},
			{0,0,4020},
		},
		.extraShort = 4247, // Sneaky ND trick
		.t = {4020,0,0}
	},
	[6] =
	{
		.m =
		{
			{0,5619,171},
			{0,338,0},
			{0,0,4069},
		},
		.extraShort = 4149, // Sneaky ND trick
		.t = {4069,0,0}
	},
	[7] =
	{
		.m =
		{
			{0,2727,-357},
			{0,158,0},
			{0,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[8] =
	{
		.m =
		{
			{0,182,0},
			{0,0,0},
			{0,0,4710},
		},
		.extraShort = 3788, // Sneaky ND trick
		.t = {4710,0,0}
	},
	[9] =
	{
		.m =
		{
			{0,1255,-108},
			{0,69,0},
			{0,0,5324},
		},
		.extraShort = 3481, // Sneaky ND trick
		.t = {5324,0,0}
	},
	[10] =
	{
		.m =
		{
			{0,2330,-218},
			{0,139,0},
			{0,0,5057},
		},
		.extraShort = 3690, // Sneaky ND trick
		.t = {5057,0,0}
	},
	[11] =
	{
		.m =
		{
			{0,2818,-267},
			{0,170,0},
			{0,0,4468},
		},
		.extraShort = 4151, // Sneaky ND trick
		.t = {4468,0,0}
	},
	[12] =
	{
		.m =
		{
			{0,2342,-331},
			{0,158,0},
			{0,0,3879},
		},
		.extraShort = 4612, // Sneaky ND trick
		.t = {3879,0,0}
	},
	[13] =
	{
		.m =
		{
			{0,1665,-315},
			{0,126,0},
			{0,0,3612},
		},
		.extraShort = 4821, // Sneaky ND trick
		.t = {3612,0,0}
	},
	[14] =
	{
		.m =
		{
			{0,1019,-270},
			{0,84,0},
			{0,0,3737},
		},
		.extraShort = 4633, // Sneaky ND trick
		.t = {3737,0,0}
	},
	[15] =
	{
		.m =
		{
			{0,487,-112},
			{0,39,0},
			{0,0,3970},
		},
		.extraShort = 4284, // Sneaky ND trick
		.t = {3970,0,0}
	},
	},

	.matArr05 =
	{
	[0] =
	{
		.m =
		{
			{0,3091,0},
			{0,0,0},
			{0,0,4096},
		},
		.extraShort = 2227, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[1] =
	{
		.m =
		{
			{0,3896,0},
			{0,0,0},
			{0,0,3704},
		},
		.extraShort = 4456, // Sneaky ND trick
		.t = {3704,0,0}
	},
	[2] =
	{
		.m =
		{
			{0,4418,0},
			{0,0,0},
			{0,0,3200},
		},
		.extraShort = 5869, // Sneaky ND trick
		.t = {3200,0,0}
	},
	[3] =
	{
		.m =
		{
			{0,4636,0},
			{0,0,0},
			{0,0,3086},
		},
		.extraShort = 6116, // Sneaky ND trick
		.t = {3086,0,0}
	},
	[4] =
	{
		.m =
		{
			{0,4418,0},
			{0,0,0},
			{0,0,3200},
		},
		.extraShort = 5869, // Sneaky ND trick
		.t = {3200,0,0}
	},
	[5] =
	{
		.m =
		{
			{0,3338,0},
			{0,0,0},
			{0,0,3758},
		},
		.extraShort = 5251, // Sneaky ND trick
		.t = {3758,0,0}
	},
	[6] =
	{
		.m =
		{
			{0,1669,0},
			{0,0,0},
			{0,0,4550},
		},
		.extraShort = 4217, // Sneaky ND trick
		.t = {4550,0,0}
	},
	[7] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,4952},
		},
		.extraShort = 3246, // Sneaky ND trick
		.t = {4952,0,0}
	},
	[8] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,4670},
		},
		.extraShort = 2816, // Sneaky ND trick
		.t = {4670,0,0}
	},
	[9] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,4049},
		},
		.extraShort = 3073, // Sneaky ND trick
		.t = {4049,0,0}
	},
	[10] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,3427},
		},
		.extraShort = 3639, // Sneaky ND trick
		.t = {3427,0,0}
	},
	[11] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,3145},
		},
		.extraShort = 4205, // Sneaky ND trick
		.t = {3145,0,0}
	},
	[12] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,3294},
		},
		.extraShort = 4463, // Sneaky ND trick
		.t = {3294,0,0}
	},
	[13] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,3620},
		},
		.extraShort = 4367, // Sneaky ND trick
		.t = {3620,0,0}
	},
	[14] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,3947},
		},
		.extraShort = 4191, // Sneaky ND trick
		.t = {3947,0,0}
	},
	},

	.matArr06 =
	{
	[0] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[1] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[2] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[3] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[4] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[5] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[6] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[7] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[8] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[9] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[10] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[11] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[12] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[13] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[14] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[15] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[16] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[17] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[18] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[19] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[20] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[21] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[22] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[23] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[24] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[25] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[26] =
	{
		.m =
		{
			{0,0,0},
			{0,0,0},
			{0,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	},

	.matArr07 =
	{
	[0] =
	{
		.m =
		{
			{-209,664,179},
			{0,-3,2},
			{-41,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[1] =
	{
		.m =
		{
			{-672,2127,574},
			{0,-6,9},
			{-132,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[2] =
	{
		.m =
		{
			{-1133,3591,969},
			{0,-10,15},
			{-224,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[3] =
	{
		.m =
		{
			{-1343,4255,1149},
			{0,-11,18},
			{-265,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	},

	.matArr08 =
	{
	[0] =
	{
		.m =
		{
			{-157,43,121},
			{0,-49,0},
			{-27,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[1] =
	{
		.m =
		{
			{-503,137,389},
			{0,-153,0},
			{-88,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[2] =
	{
		.m =
		{
			{-849,231,656},
			{0,-256,0},
			{-148,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[3] =
	{
		.m =
		{
			{-1006,275,778},
			{0,-303,0},
			{-176,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	},

	.matArr09 =
	{
	[0] =
	{
		.m =
		{
			{78,328,-103},
			{0,35,0},
			{-17,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[1] =
	{
		.m =
		{
			{252,1051,-330},
			{0,113,0},
			{-56,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[2] =
	{
		.m =
		{
			{425,1774,-557},
			{0,192,0},
			{-96,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[3] =
	{
		.m =
		{
			{505,2103,-659},
			{0,227,0},
			{-113,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	},

	.matArr0A =
	{
	[0] =
	{
		.m =
		{
			{-83,252,0},
			{0,-20,0},
			{-10,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[1] =
	{
		.m =
		{
			{-267,808,0},
			{0,-62,0},
			{-32,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[2] =
	{
		.m =
		{
			{-452,1364,0},
			{0,-103,0},
			{-54,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[3] =
	{
		.m =
		{
			{-536,1617,0},
			{0,-121,0},
			{-64,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	},

	.matArr0B =
	{
	[0] =
	{
		.m =
		{
			{11,176,-96},
			{0,19,0},
			{-13,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[1] =
	{
		.m =
		{
			{38,566,-310},
			{0,60,0},
			{-44,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[2] =
	{
		.m =
		{
			{62,954,-524},
			{0,102,0},
			{-74,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[3] =
	{
		.m =
		{
			{74,1131,-621},
			{0,121,0},
			{-88,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	},

	.matArr0C =
	{
	[0] =
	{
		.m =
		{
			{-107,313,-298},
			{0,31,0},
			{-14,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[1] =
	{
		.m =
		{
			{-342,1004,-954},
			{0,100,0},
			{-44,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[2] =
	{
		.m =
		{
			{-576,1693,-1610},
			{0,169,0},
			{-75,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[3] =
	{
		.m =
		{
			{-684,2008,-1909},
			{0,201,0},
			{-89,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	},

	.matArr0D =
	{
	[0] =
	{
		.m =
		{
			{-61,81,115},
			{0,-20,0},
			{-11,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[1] =
	{
		.m =
		{
			{-196,259,369},
			{0,-64,0},
			{-37,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[2] =
	{
		.m =
		{
			{-331,437,625},
			{0,-108,0},
			{-63,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[3] =
	{
		.m =
		{
			{-393,519,740},
			{0,-128,0},
			{-75,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	},

	.matArr0E =
	{
	[0] =
	{
		.m =
		{
			{-62,180,-81},
			{0,20,0},
			{-9,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[1] =
	{
		.m =
		{
			{-199,578,-260},
			{0,65,0},
			{-30,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[2] =
	{
		.m =
		{
			{-336,976,-440},
			{0,111,0},
			{-51,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[3] =
	{
		.m =
		{
			{-399,1157,-521},
			{0,131,0},
			{-61,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	},

	.matArr0F =
	{
	[0] =
	{
		.m =
		{
			{-150,114,0},
			{0,-4,0},
			{-28,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[1] =
	{
		.m =
		{
			{-481,363,0},
			{0,-13,0},
			{-92,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[2] =
	{
		.m =
		{
			{-812,613,0},
			{0,-22,0},
			{-155,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[3] =
	{
		.m =
		{
			{-963,727,0},
			{0,-26,0},
			{-184,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	},

	.matArr10 =
	{
	[0] =
	{
		.m =
		{
			{0,57,38},
			{0,-7,0},
			{-2,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[1] =
	{
		.m =
		{
			{0,199,132},
			{0,-25,0},
			{-7,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[2] =
	{
		.m =
		{
			{0,374,247},
			{0,-47,0},
			{-14,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[3] =
	{
		.m =
		{
			{0,533,352},
			{0,-67,0},
			{-20,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	},

	.matArr11 =
	{
	[0] =
	{
		.m =
		{
			{0,238,-83},
			{0,18,0},
			{-6,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[1] =
	{
		.m =
		{
			{0,761,-267},
			{0,58,0},
			{-20,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[2] =
	{
		.m =
		{
			{0,1284,-450},
			{0,98,0},
			{-34,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[3] =
	{
		.m =
		{
			{0,1523,-534},
			{0,117,0},
			{-40,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	},

	.matArr12 =
	{
	[0] =
	{
		.m =
		{
			{-145,0,148},
			{0,-19,0},
			{-14,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[1] =
	{
		.m =
		{
			{-463,0,475},
			{0,-62,0},
			{-45,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[2] =
	{
		.m =
		{
			{-782,0,803},
			{0,-105,0},
			{-76,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[3] =
	{
		.m =
		{
			{-927,0,951},
			{0,-125,0},
			{-91,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	},

	.matArr13 =
	{
	[0] =
	{
		.m =
		{
			{-237,373,55},
			{0,-10,0},
			{-19,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[1] =
	{
		.m =
		{
			{-760,1196,174},
			{0,-34,0},
			{-62,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[2] =
	{
		.m =
		{
			{-1281,2018,294},
			{0,-58,0},
			{-105,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	[3] =
	{
		.m =
		{
			{-1520,2392,349},
			{0,-69,0},
			{-125,0,4096},
		},
		.extraShort = 4096, // Sneaky ND trick
		.t = {4096,0,0}
	},
	},

	.bakedGteMath =
	{
		// first one is empty
		{0, 0},

		{&data.matArr01[0], 0xB},
		{&data.matArr02[0], 0x1},
		{&data.matArr03[0], 0x9},
		{&data.matArr04[0], 0x10},
		{&data.matArr05[0], 0xF},
		{&data.matArr06[0], 0x1B},

		{&data.matArr07[0], 0x4},
		{&data.matArr08[0], 0x4},
		{&data.matArr09[0], 0x4},
		{&data.matArr0A[0], 0x4},
		{&data.matArr0B[0], 0x4},
		{&data.matArr0C[0], 0x4},
		{&data.matArr0D[0], 0x4},
		{&data.matArr0E[0], 0x4},
		{&data.matArr0F[0], 0x4},
		{&data.matArr10[0], 0x4},
		{&data.matArr11[0], 0x4},
		{&data.matArr12[0], 0x4},
		{&data.matArr13[0], 0x4},
	},

	.MetaDataScrub =
	{
		// SOLID
		{0, 0x3, 0xD00, 700},

		// RUBBER
		{0, 0x1, 0xD00, 0},

		// SANDBAG
		{0, 0x3, 0xD00, 0x100},

		// SLOWDOWN
		{0, 0xC, 0xF00, 0},

		// NO EFFECT
		{0, 0xC, 0x3E800, 0},

		// ROAD
		{0, 0xD, 0x3E800, 0},

		// NO SCRUB
		{0, 0x3, 0x3E800, 700},
	},

	.emSet_DirtLR =
	{
		{
			.flags = 1,
			.initOffset = 12,
			.InitTypes.FuncInit =
			{
					.particle_funcPtr = 0x00000000,
					.particle_colorFlags = 0x58a2,
					.particle_lifespan = 0x000a,
					.particle_Type = 0,
			}
		},

		{
			.flags = 27,
			.initOffset = 0,
			.InitTypes.AxisInit =
			{
					.baseValue =
					{
							.startVal = -2560,
							.velocity = -500,
							.accel = 0,
					},
					.rngSeed =
					{
							.startVal = 5120,
							.velocity = 1000,
							.accel = 0,
					}
			}
		},

		{
			.flags = 27,
			.initOffset = 2,
			.InitTypes.AxisInit =
			{
					.baseValue =
					{
							.startVal = -2560,
							.velocity = -500,
							.accel = 0,
					},
					.rngSeed =
					{
							.startVal = 5120,
							.velocity = 1000,
							.accel = 0,
					}
			}
		},

		{
			.flags = 23,
			.initOffset = 1,
			.InitTypes.AxisInit =
			{
					.baseValue =
					{
							.startVal = 2560,
							.velocity = 1500,
							.accel = -300,
					},
					.rngSeed =
					{
							.startVal = 0,
							.velocity = 400,
							.accel = 0,
					}
			}
		},

		{
			.flags = 3,
			.initOffset = 7,
			.InitTypes.AxisInit =
			{
					.baseValue =
					{
							.startVal = 65280,
							.velocity = -2048,
							.accel = 0,
					},
					.rngSeed =
					{
							.startVal = 0,
							.velocity = 0,
							.accel = 0,
					}
			}
		},

		{
			.flags = 3,
			.initOffset = 8,
			.InitTypes.AxisInit =
			{
					.baseValue =
					{
							.startVal = 32768,
							.velocity = -1024,
							.accel = 0,
					},
					.rngSeed =
					{
							.startVal = 0,
							.velocity = 0,
							.accel = 0,
					}
			}
		},

		{
			.flags = 1,
			.initOffset = 9,
			.InitTypes.AxisInit =
			{
					.baseValue =
					{
							.startVal = 1,
							.velocity = 0,
							.accel = 0,
					},
					.rngSeed =
					{
							.startVal = 0,
							.velocity = 0,
							.accel = 0,
					}
			}
		},

		// null terminator
		//{},
	},

	.emSet_GrassL =
	{
		{
			.flags = 1,
			.initOffset = 12,
			.InitTypes.FuncInit =
			{
					.particle_funcPtr = 0x00000000,
					.particle_colorFlags = 0x1800,
					.particle_lifespan = 0x000a,
					.particle_Type = 0,
			}
		},

		{
			.flags = 27,
			.initOffset = 0,
			.InitTypes.AxisInit =
			{
					.baseValue =
					{
							.startVal = -2560,
							.velocity = -500,
							.accel = 0,
					},
					.rngSeed =
					{
							.startVal = 5120,
							.velocity = 1000,
							.accel = 0,
					}
			}
		},

		{
			.flags = 27,
			.initOffset = 2,
			.InitTypes.AxisInit =
			{
					.baseValue =
					{
							.startVal = -2560,
							.velocity = -500,
							.accel = 0,
					},
					.rngSeed =
					{
							.startVal = 5120,
							.velocity = 1000,
							.accel = 0,
					}
			}
		},

		{
			.flags = 23,
			.initOffset = 1,
			.InitTypes.AxisInit =
			{
					.baseValue =
					{
							.startVal = 2560,
							.velocity = 2000,
							.accel = -300,
					},
					.rngSeed =
					{
							.startVal = 0,
							.velocity = 400,
							.accel = 0,
					}
			}
		},

		{
			.flags = 64,
			.initOffset = 1,

			// memcpy into particle
			.data =
			{
				0x4, 0, 0, 0,
				0, 0x96, 0, 0,
				0, 1, 0, 0x10,
				1, 0, 0, 2
			}
		},

		{
			.flags = 1,
			.initOffset = 5,
			.InitTypes.AxisInit =
			{
					.baseValue =
					{
							.startVal = 131072,
							.velocity = 0,
							.accel = 0,
					},
					.rngSeed =
					{
							.startVal = 0,
							.velocity = 0,
							.accel = 0,
					}
			}
		},

		{
			.flags = 1,
			.initOffset = 7,
			.InitTypes.AxisInit =
			{
					.baseValue =
					{
							.startVal = 15360,
							.velocity = 0,
							.accel = 0,
					},
					.rngSeed =
					{
							.startVal = 0,
							.velocity = 0,
							.accel = 0,
					}
			}
		},

		{
			.flags = 1,
			.initOffset = 8,
			.InitTypes.AxisInit =
			{
					.baseValue =
					{
							.startVal = 65280,
							.velocity = 0,
							.accel = 0,
					},
					.rngSeed =
					{
							.startVal = 0,
							.velocity = 0,
							.accel = 0,
					}
			}
		},

		{
			.flags = 0,
			.initOffset = 9,
			.InitTypes.AxisInit =
			{
					.baseValue =
					{
							.startVal = 0,
							.velocity = 0,
							.accel = 0,
					},
					.rngSeed =
					{
							.startVal = 0,
							.velocity = 0,
							.accel = 0,
					}
			}
		},

		// null terminator
		//{},
	},

	.emSet_GrassR =
	{
		{
			.flags = 1,
			.initOffset = 12,
			.InitTypes.FuncInit =
			{
					.particle_funcPtr = 0x00000000,
					.particle_colorFlags = 0x1800,
					.particle_lifespan = 0x000a,
					.particle_Type = 0,
			}
		},

		{
			.flags = 27,
			.initOffset = 0,
			.InitTypes.AxisInit =
			{
					.baseValue =
					{
							.startVal = -2560,
							.velocity = -500,
							.accel = 0,
					},
					.rngSeed =
					{
							.startVal = 5120,
							.velocity = 1000,
							.accel = 0,
					}
			}
		},

		{
			.flags = 27,
			.initOffset = 2,
			.InitTypes.AxisInit =
			{
					.baseValue =
					{
							.startVal = -2560,
							.velocity = -500,
							.accel = 0,
					},
					.rngSeed =
					{
							.startVal = 5120,
							.velocity = 1000,
							.accel = 0,
					}
			}
		},

		{
			.flags = 23,
			.initOffset = 1,
			.InitTypes.AxisInit =
			{
					.baseValue =
					{
							.startVal = 2560,
							.velocity = 2000,
							.accel = -300,
					},
					.rngSeed =
					{
							.startVal = 0,
							.velocity = 400,
							.accel = 0,
					}
			}
		},

		{
			.flags = 64,
			.initOffset = 1,

			// memcpy into particle
			.data =
			{
				0x4, 0, 0, 0,
				0, 0x96, 0, 0,
				0, 1, 0, 0x10,
				1, 0, 0, 2
			}
		},

		{
			.flags = 1,
			.initOffset = 5,
			.InitTypes.AxisInit =
			{
					.baseValue =
					{
							.startVal = 131072,
							.velocity = 0,
							.accel = 0,
					},
					.rngSeed =
					{
							.startVal = 0,
							.velocity = 0,
							.accel = 0,
					}
			}
		},

		{
			.flags = 1,
			.initOffset = 7,
			.InitTypes.AxisInit =
			{
					.baseValue =
					{
							.startVal = 1,
							.velocity = 0,
							.accel = 0,
					},
					.rngSeed =
					{
							.startVal = 0,
							.velocity = 0,
							.accel = 0,
					}
			}
		},

		{
			.flags = 1,
			.initOffset = 8,
			.InitTypes.AxisInit =
			{
					.baseValue =
					{
							.startVal = 40960,
							.velocity = 0,
							.accel = 0,
					},
					.rngSeed =
					{
							.startVal = 0,
							.velocity = 0,
							.accel = 0,
					}
			}
		},

		{
			.flags = 0,
			.initOffset = 9,
			.InitTypes.AxisInit =
			{
					.baseValue =
					{
							.startVal = 0,
							.velocity = 0,
							.accel = 0,
					},
					.rngSeed =
					{
							.startVal = 0,
							.velocity = 0,
							.accel = 0,
					}
			}
		},

		// null terminator
		//{},
	},

	.emSet_SnowLR =
	{
		{
				.flags = 1,
				.initOffset = 12,
				.InitTypes.FuncInit =
				{
						.particle_funcPtr = 0x00000000,
						.particle_colorFlags = 0x58a2,
						.particle_lifespan = 0x000a,
						.particle_Type = 0,
				}
		},

		{
				.flags = 27,
				.initOffset = 0,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = -2560,
								.velocity = -500,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 5120,
								.velocity = 1000,
								.accel = 0,
						}
				}
		},

		{
				.flags = 27,
				.initOffset = 2,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = -2560,
								.velocity = -500,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 5120,
								.velocity = 1000,
								.accel = 0,
						}
				}
		},

		{
				.flags = 23,
				.initOffset = 1,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 2560,
								.velocity = 2000,
								.accel = -300,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 400,
								.accel = 0,
						}
				}
		},

		{
				.flags = 1,
				.initOffset = 7,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 65280,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},

		// null terminator
		//{},
	},

	.MetaDataTerrain =
	{
		// asphalt
		[0] =
		{
				0, 64, 256,
				256, 256, 256,
				0,0,
				256, 256, 256,
				0, 0, 0, 0,
				17, -1, 0xffff, 0x0040, 0x0100, 0x0100, 0x0100
		},

		// dirt
		[1] =
		{
				0, 0, 140,
				180, 256, 256,
				&data.emSet_DirtLR[0], &data.emSet_DirtLR[0],
				256, 256, 256,
				4, 5, 4, 64,
				18, 24, 0xffff, 0x0000, 0x008c, 0x00b4, 0x0100
		},

		// grass
		[2] =
		{
				0, 0, 140,
				180, 256, 256,
				&data.emSet_GrassL[0], &data.emSet_GrassR[0],
				256, 256, 256,
				4, 4, 4, 56,
				18, 24, 0xffff, 0x0000, 0x008c, 0x00b4, 0x0100
		},

		// wood
		[3] =
		{
				0, 33, 256,
				256, 256, 256,
				0,0,
				256, 256, 256,
				0, 0, 4, 64,
				17, 21, 0xffff, 0x0021, 0x0100, 0x0100, 0x0100
		},

		// water
		[4] =
		{
				0, 0, 180,
				200, 256, 256,
				0,0,
				256, 256, 256,
				4, 3, 4, 56,
				-1, 25, 0xffff, 0x0000, 0x00b4, 0x00c8, 0x0100
		},

		// stone
		[5] =
		{
				0, 64, 256,
				256, 256, 256,
				0,0,
				256, 256, 256,
				0, 0, 0, 0,
				17, -1, 0xffff, 0x0040, 0x0100, 0x0100, 0x0100
		},

		// ice
		[6] =
		{
				0, 28, 256,
				100, 0, 0,
				0,0,
				32, 128, 32,
				0, 0, 0, 0,
				-1, 22, 0xffff, 0x001c, 0x0100, 0x0064, 0x0020
		},

		// track
		[7] =
		{
				0, 33, 140,
				180, 256, 256,
				0,0,
				256, 256, 256,
				0, 0, 4, 64,
				17, 21, 0xffff, 0x0021, 0x008c, 0x00b4, 0x0100
		},

		// icy road
		[8] =
		{
				0, 64, 256,
				256, 256, 256,
				0,0,
				128, 256, 256,
				0, 0, 0, 0,
				19, -1, 0xffff, 0x0040, 0x0100, 0x0100, 0x0080
		},

		// snow
		[9] =
		{
				0, 0, 140,
				180, 256, 256,
				&data.emSet_SnowLR[0], &data.emSet_SnowLR[0],
				128, 256, 256,
				0, 0, 4, 56,
				19, 23, 0xffff, 0x0000, 0x008c, 0x00b4, 0x0080
		},

		// none
		[10] =
		{
				0, 0, 256,
				256, 0, 256,
				0,0,
				256, 256, 256,
				0, 0, 0, 0,
				-1, -1, 0xffff, 0x0000, 0x0100, 0x0100, 0x0100
		},

		// hardpack
		[11] =
		{
				0, 0, 256,
				256, 256, 256,
				0,0,
				256, 256, 256,
				0, 0, 0, 0,
				18, -1, 0xffff, 0x0000, 0x0100, 0x0100, 0x0100
		},

		// metal
		[12] =
		{
				0, 64, 256,
				256, 256, 256,
				0,0,
				256, 256, 256,
				4, 10, 0, 0,
				17, 26, 0xffff, 0x0040, 0x0100, 0x0100, 0x0100
		},

		// fastwater
		[13] =
		{
				0, 0, 256,
				256, 256, 256,
				0,0,
				256, 256, 256,
				4, 3, 4, 56,
				-1, 25, 0xffff, 0x0000, 0x0100, 0x0100, 0x0100
		},

		// mud
		[14] =
		{
				0, 128, 140,
				180, 256, 256,
				0,0,
				512, 256, 256,
				4, 5, 4, 64,
				-1, 27, 0xffff, 0x0080, 0x008c, 0x00b4, 0x0200
		},

		// sideslip
		[15] =
		{
				0, 320, 256,
				256, 256, 256,
				0,0,
				256, 256, 256,
				0, 0, 0, 0,
				17, -1, 0xffff, 0x0140, 0x0100, 0x0100, 0x0100
		},

		// riverasphalt
		[16] =
		{
				0, 64, 256,
				256, 256, 256,
				0,0,
				256, 256, 256,
				0, 0, 0, 0,
				17, -1, 0x0088, 0x0040, 0x0100, 0x0100, 0x0100
		},

		// steamasphalt
		[17] =
		{
				0, 64, 256,
				256, 256, 256,
				0,0,
				256, 256, 256,
				0, 0, 0, 0,
				17, -1, 0x008b, 0x0040, 0x0100, 0x0100, 0x0100
		},

		// oceanasphalt
		[18] =
		{
				0, 64, 256,
				256, 256, 256,
				0,0,
				256, 256, 256,
				0, 0, 0, 0,
				17, -1, 0x0087, 0x0040, 0x0100, 0x0100, 0x0100
		},

		// slowgrass
		[19] =
		{
				0, 0, 100,
				180, 256, 256,
				&data.emSet_GrassL[0], &data.emSet_GrassR[0],
				256, 256, 256,
				4, 4, 4, 56,
				18, 24, 0xffff, 0x0000, 0x0064, 0x00b4, 0x0100
		},

		// slowdirt
		[20] =
		{
				0, 0, 100,
				180, 256, 256,
				&data.emSet_DirtLR[0], &data.emSet_DirtLR[0],
				256, 256, 256,
				4, 5, 4, 64,
				18, 24, 0xffff, 0x0000, 0x0064, 0x00b4, 0x0100
		},
	},

// one way for this to fail,
// EurRetail and JpnRetail dont start
// gravity at offset 0x416, it starts at 0x41a,
// need to make the offets compatible later on
	#define PHYSWRAP(b, c, d, e, f, g, h) \
		.offset = b, 		\
		.size = c, 			\
		.value[0] = d, 		\
		.value[1] = e, 		\
		.value[2] = f, 		\
		.value[3] = g,		\
		.value[4] = h


	.metaPhys =
	{
		{PHYSWRAP(0x416, 2, 900, 900, 900, 900, 900)},
		{PHYSWRAP(0x418, 2, 4596, 4596, 4596, 4596, 4596)},
		{PHYSWRAP(0x41a, 2, 350, 350, 350, 350, 350)},
		{PHYSWRAP(0x41c, 2, 120, 120, 120, 120, 120)},
		{PHYSWRAP(0x41e, 2, 425, 425, 425, 425, 425)},
		{PHYSWRAP(0x420, 2, 120, 120, 120, 120, 120)},
		{PHYSWRAP(0x422, 2, 260, 260, 260, 260, 260)},
		{PHYSWRAP(0x424, 2, 120, 120, 120, 120, 120)},
		{PHYSWRAP(0x426, 2, 120, 120, 120, 120, 120)},
		{PHYSWRAP(0x428, 2, 480, 544, 448, 512, 544)},
		{PHYSWRAP(0x42a, 2, 1152, 1152, 1152, 1152, 1152)},
		{PHYSWRAP(0x42c, 2, 13140, 13520, 13900, 12950, 13900)},
		{PHYSWRAP(0x42e, 2, 14640, 15020, 15400, 14450, 15400)},
		{PHYSWRAP(0x430, 2, 2048, 2048, 2048, 2048, 2048)},
		{PHYSWRAP(0x432, 2, 4096, 4096, 4096, 4096, 4096)},
		{PHYSWRAP(0x434, 2, 5120, 5120, 5120, 5120, 5120)},
		{PHYSWRAP(0x436, 2, 3900, 3900, 3900, 3900, 3900)},
		{PHYSWRAP(0x438, 2, 4096, 4096, 4096, 4096, 4096)},
		{PHYSWRAP(0x43a, 1, 28, 26, 24, 30, 30)},
		{PHYSWRAP(0x43b, 1, 48, 48, 48, 48, 48)},
		{PHYSWRAP(0x43c, 2, 4080, 9080, 5666, 7252, 7252)},
		{PHYSWRAP(0x43e, 2, 5000, 4500, 4000, 5500, 5500)},
		{PHYSWRAP(0x440, 2, 1000, 750, 500, 1250, 1250)},
		{PHYSWRAP(0x442, 2, 20480, 20480, 20480, 20480, 20480)},
		{PHYSWRAP(0x444, 2, 256, 256, 256, 256, 256)},
		{PHYSWRAP(0x446, 1, 64, 64, 64, 64, 64)},
		{PHYSWRAP(0x447, 1, 4, 4, 4, 4, 4)},
		{PHYSWRAP(0x448, 1, 8, 8, 8, 8, 8)},
		{PHYSWRAP(0x44a, 2, 3072, 3072, 3072, 3072, 3072)},
		{PHYSWRAP(0x44c, 2, 0, 0, 0, 0, 0)},
		{PHYSWRAP(0x44e, 2, 128, 128, 128, 128, 128)},
		{PHYSWRAP(0x450, 2, 0, 0, 0, 0, 0)},
		{PHYSWRAP(0x452, 2, 350, 350, 350, 350, 350)},
		{PHYSWRAP(0x454, 2, 450, 450, 450, 450, 450)},
		{PHYSWRAP(0x457, 1, 30, 30, 30, 30, 30)},
		{PHYSWRAP(0x458, 1, 20, 20, 20, 20, 20)},
		{PHYSWRAP(0x459, 1, 60, 60, 60, 60, 60)},
		{PHYSWRAP(0x45a, 1, 10, 10, 10, 10, 10)},
		{PHYSWRAP(0x45c, 1, 32, 32, 32, 32, 32)},
		{PHYSWRAP(0x45d, 1, 224, 224, 224, 224, 224)},
		{PHYSWRAP(0x45e, 1, -10, -10, -10, -10, -10)},
		{PHYSWRAP(0x45f, 1, 22, 22, 22, 22, 22)},
		{PHYSWRAP(0x460, 1, 14, 10, 5, 18, 18)},
		{PHYSWRAP(0x461, 1, 100, 100, 100, 100, 100)},
		{PHYSWRAP(0x462, 1, 60, 60, 60, 60, 60)},
		{PHYSWRAP(0x463, 1, 60, 60, 60, 60, 60)},
		{PHYSWRAP(0x464, 2, 3000, 3000, 3000, 3000, 3000)},
		{PHYSWRAP(0x466, 2, 500, 500, 500, 500, 500)},
		{PHYSWRAP(0x468, 2, 384, 384, 384, 384, 384)},
		{PHYSWRAP(0x46a, 1, 16, 16, 16, 16, 16)},
		{PHYSWRAP(0x46b, 1, 15, 15, 15, 15, 15)},
		{PHYSWRAP(0x46c, 2, 8192, 8192, 8192, 8192, 8192)},
		{PHYSWRAP(0x46e, 2, 8192, 8192, 8192, 8192, 8192)},
		{PHYSWRAP(0x470, 2, 300, 300, 300, 300, 300)},
		{PHYSWRAP(0x472, 2, -128, -128, -128, -128, -128)},
		{PHYSWRAP(0x474, 2, 768, 768, 768, 768, 768)},
		{PHYSWRAP(0x476, 1, 30, 30, 30, 30, 30)},
		{PHYSWRAP(0x477, 1, 15, 15, 15, 15, 15)},
		{PHYSWRAP(0x478, 1, 60, 60, 60, 60, 60)},
		{PHYSWRAP(0x479, 1, 15, 15, 15, 15, 15)},
		{PHYSWRAP(0x47a, 1, 36, 36, 36, 36, 36)},
		{PHYSWRAP(0x47c, 2, 256, 256, 300, 200, 200)},
		{PHYSWRAP(0x47e, 2, 5120, 5120, 5120, 5120, 5120)},
		{PHYSWRAP(0x480, 2, 2560, 2560, 2560, 2560, 2560)},
		{PHYSWRAP(0x484, 4, 15, 15, 15, 15, 15)},
	},

	.emSet_Exhaust_Water =
	{
		[0] =
		{
				.flags = 1,
				.initOffset = 12,
				.InitTypes.FuncInit =
				{
						.particle_funcPtr = 0x00000000,
						.particle_colorFlags = 0x08a0,
						.particle_lifespan = 0x001e,
						.particle_Type = 0,
				}
		},
		[1] =
		{
				.flags = 27,
				.initOffset = 0,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = -512,
								.velocity = -512,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 1024,
								.velocity = 1024,
								.accel = 0,
						}
				}
		},
		[2] =
		{
				.flags = 36,
				.initOffset = 1,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 100,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 200,
						}
				}
		},
		[3] =
		{
				.flags = 27,
				.initOffset = 2,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = -512,
								.velocity = -512,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 1024,
								.velocity = 1024,
								.accel = 0,
						}
				}
		},
		[4] =
		{
				.flags = 1,
				.initOffset = 5,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 512,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[5] =
		{
				.flags = 1,
				.initOffset = 4,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 1,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},

		// null
		//[6] = {},
	},

	.emSet_Exhaust_High =
	{
		[0] =
		{
				.flags = 1,
				.initOffset = 12,
				.InitTypes.FuncInit =
				{
						.particle_funcPtr = 0x00000000,
						.particle_colorFlags = 0x08a3,
						.particle_lifespan = 0x0005,
						.particle_Type = 0,
				}
		},
		[1] =
		{
				.flags = 18,
				.initOffset = 0,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = -250,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 500,
								.accel = 0,
						}
				}
		},
		[2] =
		{
				.flags = 22,
				.initOffset = 1,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = -250,
								.accel = -256,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 500,
								.accel = 0,
						}
				}
		},
		[3] =
		{
				.flags = 18,
				.initOffset = 2,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = -250,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 500,
								.accel = 0,
						}
				}
		},
		[4] =
		{
				.flags = 3,
				.initOffset = 5,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 1536,
								.velocity = 400,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[5] =
		{
				.flags = 3,
				.initOffset = 7,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 16384,
								.velocity = -2560,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[6] =
		{
				.flags = 26,
				.initOffset = 4,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = 256,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = -512,
								.velocity = -512,
								.accel = 0,
						}
				}
		},

		// null
		//[7] = {},
	},

	.emSet_Exhaust_Med =
	{
		[0] =
		{
				.flags = 1,
				.initOffset = 12,
				.InitTypes.FuncInit =
				{
						.particle_funcPtr = 0x00000000,
						.particle_colorFlags = 0x08a3,
						.particle_lifespan = 0x0005,
						.particle_Type = 0,
				}
		},
		[1] =
		{
				.flags = 18,
				.initOffset = 0,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = -200,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 400,
								.accel = 0,
						}
				}
		},
		[2] =
		{
				.flags = 22,
				.initOffset = 1,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = -200,
								.accel = -256,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 400,
								.accel = 0,
						}
				}
		},
		[3] =
		{
				.flags = 18,
				.initOffset = 2,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = -200,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 400,
								.accel = 0,
						}
				}
		},
		[4] =
		{
				.flags = 3,
				.initOffset = 5,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 1736,
								.velocity = 400,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[5] =
		{
				.flags = 3,
				.initOffset = 7,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 32768,
								.velocity = -4608,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[6] =
		{
				.flags = 26,
				.initOffset = 4,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = 200,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = -512,
								.velocity = -400,
								.accel = 0,
						}
				}
		},

		// null
		//[7] = {},
	},

	.emSet_Exhaust_Low =
	{
		[0] =
		{
				.flags = 1,
				.initOffset = 12,
				.InitTypes.FuncInit =
				{
						.particle_funcPtr = 0x00000000,
						.particle_colorFlags = 0x08a3,
						.particle_lifespan = 0x0005,
						.particle_Type = 0,
				}
		},
		[1] =
		{
				.flags = 18,
				.initOffset = 0,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = -1,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 2,
								.accel = 0,
						}
				}
		},
		[2] =
		{
				.flags = 22,
				.initOffset = 1,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = -1,
								.accel = -256,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 2,
								.accel = 0,
						}
				}
		},
		[3] =
		{
				.flags = 18,
				.initOffset = 2,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = -1,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 2,
								.accel = 0,
						}
				}
		},
		[4] =
		{
				.flags = 3,
				.initOffset = 5,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 2000,
								.velocity = 200,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[5] =
		{
				.flags = 3,
				.initOffset = 7,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 40960,
								.velocity = -6144,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[6] =
		{
				.flags = 26,
				.initOffset = 4,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = 64,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = -512,
								.velocity = -128,
								.accel = 0,
						}
				}
		},

		// null
		//[7] = {},
	},

	.emSet_GroundSparks =
	{
		[0] =
		{
				.flags = 1,
				.initOffset = 12,
				.InitTypes.FuncInit =
				{
						.particle_funcPtr = 0x00000000,
						.particle_colorFlags = 0x58a2,
						.particle_lifespan = 0x0008,
						.particle_Type = 0,
				}
		},
		[1] =
		{
				.flags = 18,
				.initOffset = 0,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = -500,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 1000,
								.accel = 0,
						}
				}
		},
		[2] =
		{
				.flags = 18,
				.initOffset = 2,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = -500,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 1000,
								.accel = 0,
						}
				}
		},
		[3] =
		{
				.flags = 55,
				.initOffset = 1,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 2048,
								.velocity = 1000,
								.accel = -300,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 800,
								.accel = 100,
						}
				}
		},
		[4] =
		{
				.flags = 17,
				.initOffset = 5,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 131072,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 200,
								.accel = 0,
						}
				}
		},
		[5] =
		{
				.flags = 3,
				.initOffset = 7,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 65280,
								.velocity = -7680,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[6] =
		{
				.flags = 3,
				.initOffset = 8,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 65280,
								.velocity = -7680,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[7] =
		{
				.flags = 3,
				.initOffset = 9,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 32768,
								.velocity = -3840,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},

		// null
		//[8] = {},
	},

	.emSet_WallSparks =
	{
		[0] =
		{
				.flags = 1,
				.initOffset = 12,
				.InitTypes.FuncInit =
				{
						.particle_funcPtr = 0x00000000,
						.particle_colorFlags = 0x58a2,
						.particle_lifespan = 0x0008,
						.particle_Type = 0,
				}
		},
		[1] =
		{
				.flags = 18,
				.initOffset = 0,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = -500,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 1000,
								.accel = 0,
						}
				}
		},
		[2] =
		{
				.flags = 18,
				.initOffset = 2,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = -500,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 1000,
								.accel = 0,
						}
				}
		},
		[3] =
		{
				.flags = 22,
				.initOffset = 1,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = 2000,
								.accel = -200,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 400,
								.accel = 0,
						}
				}
		},
		[4] =
		{
				.flags = 1,
				.initOffset = 5,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 131072,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[5] =
		{
				.flags = 3,
				.initOffset = 7,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 65280,
								.velocity = -2048,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[6] =
		{
				.flags = 3,
				.initOffset = 8,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 65280,
								.velocity = -3072,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[7] =
		{
				.flags = 1,
				.initOffset = 9,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 1,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},

		// null
		//[8] = {},
	},

	.emSet_MudSplash =
	{
		[0] =
		{
				.flags = 1,
				.initOffset = 12,
				.InitTypes.FuncInit =
				{
						.particle_funcPtr = 0x00000000,
						.particle_colorFlags = 0x8880,
						.particle_lifespan = 0x000f,
						.particle_Type = 0,
				}
		},
		[1] =
		{
				.flags = 27,
				.initOffset = 0,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = -512,
								.velocity = -512,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 1024,
								.velocity = 1024,
								.accel = 0,
						}
				}
		},
		[2] =
		{
				.flags = 27,
				.initOffset = 2,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = -512,
								.velocity = -512,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 1024,
								.velocity = 1024,
								.accel = 0,
						}
				}
		},
		[3] =
		{
				.flags = 62,
				.initOffset = 1,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = 1536,
								.accel = -200,
						},
						.rngSeed =
						{
								.startVal = 2048,
								.velocity = 128,
								.accel = -60,
						}
				}
		},
		[4] =
		{
				.flags = 11,
				.initOffset = 5,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 2048,
								.velocity = -100,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 300,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[5] =
		{
				.flags = 19,
				.initOffset = 4,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 4096,
								.velocity = -128,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 512,
								.accel = 0,
						}
				}
		},
		[6] =
		{
				.flags = 1,
				.initOffset = 7,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 16384,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[7] =
		{
				.flags = 1,
				.initOffset = 8,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 9216,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[8] =
		{
				.flags = 1,
				.initOffset = 9,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 4352,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},

		// null
		//[9] = {},
	},

	.emSet_BurnSmoke =
	{
		[0] =
		{
				.flags = 1,
				.initOffset = 12,
				.InitTypes.FuncInit =
				{
						.particle_funcPtr = 0x00000000,
						.particle_colorFlags = 0x08c2,
						.particle_lifespan = 0x000a,
						.particle_Type = 0,
				}
		},
		[1] =
		{
				.flags = 27,
				.initOffset = 0,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = -8192,
								.velocity = -2048,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 16384,
								.velocity = 4096,
								.accel = 0,
						}
				}
		},
		[2] =
		{
				.flags = 27,
				.initOffset = 1,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 4096,
								.velocity = -2048,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 8192,
								.velocity = 4096,
								.accel = 0,
						}
				}
		},
		[3] =
		{
				.flags = 27,
				.initOffset = 2,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = -8192,
								.velocity = -2048,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 16384,
								.velocity = 4096,
								.accel = 0,
						}
				}
		},
		[4] =
		{
				.flags = 9,
				.initOffset = 5,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 4096,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 300,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[5] =
		{
				.flags = 9,
				.initOffset = 4,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 50,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = -100,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[6] =
		{
				.flags = 3,
				.initOffset = 7,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 32768,
								.velocity = -3072,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},

		// null
		//[7] = {},
	},

	.emSet_Falling =
	{
		[0] =
		{
				.flags = 1,
				.initOffset = 12,
				.InitTypes.FuncInit =
				{
						.particle_funcPtr = 0x00000000,
						.particle_colorFlags = 0x88a0,
						.particle_lifespan = 0x000f,
						.particle_Type = 0,
				}
		},
		[1] =
		{
				.flags = 27,
				.initOffset = 0,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = -8192,
								.velocity = -2048,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 16384,
								.velocity = 4096,
								.accel = 0,
						}
				}
		},
		[2] =
		{
				.flags = 27,
				.initOffset = 2,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = -8192,
								.velocity = -2048,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 16384,
								.velocity = 4096,
								.accel = 0,
						}
				}
		},
		[3] =
		{
				.flags = 62,
				.initOffset = 1,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = 4096,
								.accel = -600,
						},
						.rngSeed =
						{
								.startVal = 2048,
								.velocity = 2048,
								.accel = -200,
						}
				}
		},
		[4] =
		{
				.flags = 9,
				.initOffset = 5,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 1024,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 300,
								.velocity = 0,
								.accel = 0,
						}
				}
		},

		// null
		//[5] = {},
	},

	.RNG_itemSetRace1 =
	{
		// 8/20 potion
		// 8/20 tnt
		// 2/20 bomb
		// 1/20 turbo
		// 1/20 shield
		4, 4, 4, 4, 4, 4, 4, 4,
		3, 3, 3, 3, 3, 3, 3, 3,
		1, 1,
		0,
		6,
	},

	.RNG_itemSetRace2 =
	{
		// 10/52 potion
		// 8/52 tnt
		// 5/52 bomb
		// 3/52 bomb x3
		// 5/52 turbo
		// 3/52 shield
		// 3/52 missile
		// 2/52 missile x3
		// 5/52 warpball
		// 7/52 mask
		// 1/52 n tropy clock

		4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
		3, 3, 3, 3, 3, 3, 3, 3,
		1, 1, 1, 1, 1,
		10, 10, 10,
		0, 0, 0, 0, 0,
		6, 6, 6,
		2, 2, 2,
		11, 11,
		9, 9, 9, 9, 9,
		7, 7, 7, 7, 7, 7, 7,
		8,
	},

	.RNG_itemSetRace3 =
	{
		4, 3, 1, 10, 10, 0, 0, 6, 2, 2, 11, 9, 9, 9, 7, 7, 7, 7, 7, 8,
	},

	.RNG_itemSetRace4 =
	{
		0, 6, 2, 11, 9, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 0,
	},

	.RNG_itemSetBossrace =
	{
		4, 3, 1, 10, 10, 0, 0, 6, 2, 11, 9, 9, 9, 7, 7, 7, 7, 7, 8, 8,
	},

	.RNG_itemSetBattleDefault =
	{
		4, 3, 1, 1, 1, 10, 10, 6, 6, 2, 2, 2, 2, 2, 7, 7, 7, 13, 13, 12,
	},

	// 0xB
	.emSet_Warpball =
	{
		[0] =
		{
				.flags = 1,
				.initOffset = 12,
				.InitTypes.FuncInit =
				{
						.particle_funcPtr = 0x00000000,
						.particle_colorFlags = 0x0000,
						.particle_lifespan = 0xffffffff,
						.particle_Type = 1,
				}
		},
		[1] =
		{
				.flags = 1,
				.initOffset = 0,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 1,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[2] =
		{
				.flags = 1,
				.initOffset = 1,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 1,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[3] =
		{
				.flags = 1,
				.initOffset = 2,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 1,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[4] =
		{
				.flags = 1,
				.initOffset = 7,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 32768,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[5] =
		{
				.flags = 1,
				.initOffset = 8,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 32768,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[6] =
		{
				.flags = 1,
				.initOffset = 9,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 32768,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[7] =
		{
				.flags = 1,
				.initOffset = 3,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 8192,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[8] =
		{
				.flags = 1,
				.initOffset = 4,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 6144,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[9] =
		{
				.flags = 1,
				.initOffset = 5,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 4096,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},

		// null
		//[10] = {},
	},

	// 0x1C
	.emSet_Maskgrab =
	{
		[0] =
		{
				.flags = 1,
				.initOffset = 12,
				.InitTypes.FuncInit =
				{
						.particle_funcPtr = 0x00000000,
						.particle_colorFlags = 0x50a2,
						.particle_lifespan = 0x0020,
						.particle_Type = 0,
				}
		},
		[1] =
		{
				.flags = 18,
				.initOffset = 0,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = -900,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 1800,
								.accel = 0,
						}
				}
		},
		[2] =
		{
				.flags = 18,
				.initOffset = 2,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = -900,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 1800,
								.accel = 0,
						}
				}
		},
		[3] =
		{
				.flags = 23,
				.initOffset = 1,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 16384,
								.velocity = 3500,
								.accel = -400,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 700,
								.accel = 0,
						}
				}
		},
		[4] =
		{
				.flags = 1,
				.initOffset = 5,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 131072,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[5] =
		{
				.flags = 3,
				.initOffset = 7,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 32512,
								.velocity = -1024,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[6] =
		{
				.flags = 3,
				.initOffset = 9,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 65280,
								.velocity = -2048,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},

		// null
		//[7] = {},

		[8] =
		{
				.flags = 1,
				.initOffset = 12,
				.InitTypes.FuncInit =
				{
						.particle_funcPtr = 0x00000000,
						.particle_colorFlags = 0x00a3,
						.particle_lifespan = 0x0014,
						.particle_Type = 0,
				}
		},
		[9] =
		{
				.flags = 16,
				.initOffset = 0,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 400,
								.accel = 0,
						}
				}
		},
		[10] =
		{
				.flags = 18,
				.initOffset = 1,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = 2500,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 500,
								.accel = 0,
						}
				}
		},
		[11] =
		{
				.flags = 16,
				.initOffset = 2,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 4096,
								.accel = 0,
						}
				}
		},
		[12] =
		{
				.flags = 1,
				.initOffset = 5,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 3000,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[13] =
		{
				.flags = 11,
				.initOffset = 7,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 8192,
								.velocity = -512,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 16384,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[14] =
		{
				.flags = 11,
				.initOffset = 8,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 8192,
								.velocity = -512,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 16384,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[15] =
		{
				.flags = 11,
				.initOffset = 9,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 8192,
								.velocity = -512,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 16384,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[16] =
		{
				.flags = 26,
				.initOffset = 4,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = 256,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = -512,
								.velocity = -512,
								.accel = 0,
						}
				}
		},

		// null
		//[17] = {},

		[18] =
		{
				.flags = 1,
				.initOffset = 12,
				.InitTypes.FuncInit =
				{
						.particle_funcPtr = 0x00000000,
						.particle_colorFlags = 0x00c3,
						.particle_lifespan = 0x0014,
						.particle_Type = 0,
				}
		},
		[19] =
		{
				.flags = 16,
				.initOffset = 0,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 400,
								.accel = 0,
						}
				}
		},
		[20] =
		{
				.flags = 1,
				.initOffset = 1,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 1024,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[21] =
		{
				.flags = 16,
				.initOffset = 2,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 4096,
								.accel = 0,
						}
				}
		},
		[22] =
		{
				.flags = 1,
				.initOffset = 5,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 3000,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[23] =
		{
				.flags = 11,
				.initOffset = 7,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 16384,
								.velocity = -512,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 16384,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[24] =
		{
				.flags = 11,
				.initOffset = 8,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 16384,
								.velocity = -512,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 16384,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[25] =
		{
				.flags = 11,
				.initOffset = 9,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 8192,
								.velocity = -512,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 16384,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[26] =
		{
				.flags = 26,
				.initOffset = 4,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = 256,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = -512,
								.velocity = -512,
								.accel = 0,
						}
				}
		},

		// null
		//[27] = {}
	},

	// 0x8
	.emSet_Warppad =
	{
		[0] =
		{
				.flags = 1,
				.initOffset = 12,
				.InitTypes.FuncInit =
				{
						.particle_funcPtr = 0x00000000,
						.particle_colorFlags = 0x00c2,
						.particle_lifespan = 0x0014,
						.particle_Type = 0,
				}
		},
		[1] =
		{
				.flags = 16,
				.initOffset = 0,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 256,
								.accel = 0,
						}
				}
		},
		[2] =
		{
				.flags = 2,
				.initOffset = 1,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = 512,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[3] =
		{
				.flags = 16,
				.initOffset = 2,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 256,
								.accel = 0,
						}
				}
		},
		[4] =
		{
				.flags = 3,
				.initOffset = 5,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 2000,
								.velocity = 100,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[5] =
		{
				.flags = 3,
				.initOffset = 7,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 32768,
								.velocity = -2560,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = 0,
								.velocity = 0,
								.accel = 0,
						}
				}
		},
		[6] =
		{
				.flags = 26,
				.initOffset = 4,
				.InitTypes.AxisInit =
				{
						.baseValue =
						{
								.startVal = 0,
								.velocity = 128,
								.accel = 0,
						},
						.rngSeed =
						{
								.startVal = -512,
								.velocity = -256,
								.accel = 0,
						}
				}
		},

		// null
		//[7] = {},
	},

	// .confetti = {}
};