#define DATA_DEV 1
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
void DECOMP_RB_Plant_LInB();
void DECOMP_RB_Minecart_LInB();
void DECOMP_RB_Snowball_LInB();
void DECOMP_RB_Armadillo_LInB();
void DECOMP_RB_Blade_LInB();
void DECOMP_RB_Seal_LInB();
void RB_Orca_LInB();
void DECOMP_RB_Baron_LInB();
void DECOMP_RB_Turtle_LInB();
void DECOMP_RB_Turtle_LInC();
void RB_Spider_LInB();
void DECOMP_RB_Fireball_LInB();
void RB_Banner_LInB();
void DECOMP_RB_CtrLetter_LInB();
void DECOMP_RB_CtrLetter_LInC();
void DECOMP_RB_Crystal_LInB();
void DECOMP_RB_Crystal_LInC();
void DECOMP_RB_Teeth_LInB();
void DECOMP_RB_Teeth_LInC();

void AH_Door_LInB();
void AH_Sign_LInB();
void AH_Garage_LInB();
void AH_SaveObj_LInB();
void AH_WarpPad_LInB();

void CS_LevThread_LInB();

// This inserts debug names if needed
#if 1
#define SET_MDM(x,y,z) {.name = 0, .LInB = y, .LInC = z}
#else
#define SET_MDM(x,y,z) {.name = x, .LInB = y, .LInC = z}
#endif

struct Data data =
{
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
	
	.audioData[0] =
	{
		.stringIndex_char1 = 0xB,
		.stringIndex_char2 = 0xC,
		
		.name = data.s_XA_MUSIC
	},
	
	.audioData[1] =
	{
		.stringIndex_char1 = 0xF,
		.stringIndex_char2 = 0x10,
		
		.name = data.s_XA_ENG_EXTRA
	},
	
	.audioData[2] =
	{
		.stringIndex_char1 = 0xE,
		.stringIndex_char2 = 0xF,
		
		.name = data.s_XA_ENG_GAME
	},
	
	.MetaDataModels =
	{
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
		SET_MDM(0,RB_Spider_LInB,0),
		
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
		SET_MDM(0,AH_WarpPad_LInB,0),
		
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
		SET_MDM(0,AH_SaveObj_LInB,0),
		
		// 0x73 - STATIC_PINGARAGE
		SET_MDM(0,AH_Garage_LInB,0),
		
		// 0x74 - STATIC_PAPUGARAGE
		SET_MDM(0,AH_Garage_LInB,0),
		
		// 0x75 - STATIC_ROOGARAGE
		SET_MDM(0,AH_Garage_LInB,0),
		
		// 0x76 - STATIC_JOEGARAGE
		SET_MDM(0,AH_Garage_LInB,0),
		
		// 0x77 - STATIC_OXIDEGARAGE
		SET_MDM(0,AH_Garage_LInB,0),
		
		// 0x78 - STATIC_SCAN (load/save screen)
		SET_MDM(0,0,0),
		
		// 0x79 - STATIC_SUBTRACT
		SET_MDM(0,0,0),
		
		// 0x7a - STATIC_DOOR
		SET_MDM(0,AH_Door_LInB,0),
		
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
		17,	// BIG
		13,	// SMALL
		14,	// CREDITS
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
		11,	// BIG
		7,	// SMALL
		11,	// CREDITS
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
};