
// this is only for LevInstances,
// NonLev-related entries are empty

void RB_Default_LInB();
void RB_Fruit_LInB();
void RB_Fruit_LThB();
void RB_GenericMine_LInB();
void RB_Crate_Fruit_LThB();
void RB_Crate_Weapon_LThB();
void RB_Crate_Time_LThB();
void RB_FlameJet_LInB();
void RB_Plant_LInB();
void RB_Minecart_LInB();
void RB_Snowball_Init();
void RB_Armadillo_LInB();
void RB_Blade_LInB();
void RB_Seal_Init();
void RB_Orca_LInB();
void RB_Baron_LInB();
void RB_Turtle_Init();
void RB_Turtle_OnCollide(); // LevColl, not ThColl
void RB_Spider_Init();
void RB_Fireball_LInB();
void RB_StartText_Init();
void RB_Banner_LInB();
void RB_CtrLetter_LInB();
void RB_CtrLetter_LThB();
void RB_Crystal_LInB();
void RB_Crystal_LThB();
void RB_StartText_Init();
void RB_Teeth_LInB();
void RB_Teeth_LThB();

void AH_Door_OnInit();
void AH_Sign_OnInit();
void AH_Garage_Init();
void AH_SaveObj_Init();

void CS_LevThread_OnInit();

struct MetaDataModel
{
	// debug
	char* name;
	
	// callback after converting
	// Lev InstDef to Lev Instance
	void* LInB;
	
	// callback after detecting
	// Lev BSP hitbox collision
	void* LThB;
};

// intended use of the system is to birth 
// an unthreaded instance, then LInB always
// does a BSP check for reflective quadblocks

// LThB "should" birth a thread on BSP hitbox collide,
// which can smash and regrow a crate, then thread 
// dies until the next crate collision

// only "constantly alive" instances are justified to 
// birth a thread in LInB, not LThB, like FlameJet,
// Blade, etc

// comments below explain unintended use of the system,
// and how the decomp will optimize the code

// 80081088
struct MetaDataModel mdm[0xe2] =
{
	// 0x00 - NO_FUNC
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x01 - ANIMATE_IF_HIT
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x02 - PU_WUMPA_FRUIT
	// OG game births a thread, calls OnCollide, then dies,
	// DECOMP shouldn't birth in LThB, just trigger HUD
	{ .name = 0, .LInB = RB_Fruit_LInB, .LThB = RB_Fruit_LThB },
	
	// 0x03 - PU_SMALL_BOMB
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x04 - PU_LARGE_BOMB
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x05 - PU_MISSILE
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x06 - PU_EXPLOSIVE_CRATE (nitro)
	// used for Crystal Challenge TNT/Nitro, no BSP collision, 
	// LInB births thread that checks for collision every frame,
	// DECOMP should birth unthreaded instances, and add hitboxes
	{ .name = 0, .LInB = RB_GenericMine_LInB, .LThB = 0 },
	
	// 0x07 - PU_FRUIT_CRATE
	{ .name = 0, .LInB = RB_Default_LInB, .LThB = RB_Crate_Fruit_LThB },
	
	// 0x08 - PU_RANDOM_CRATE (Weapon Box)
	{ .name = 0, .LInB = RB_Default_LInB, .LThB = RB_Crate_Weapon_LThB },
	
	// 0x09 - PU_TIME_CRATE_1 (unused duplicate of 0x5C)
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x0A - PU_TIME_CRATE_2 (unused duplicate of 0x64)
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x0B - PU_TIME_CRATE_3 (unused duplicate of 0x65)
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x0C - PU_POISON
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x0D - PU_SHIELD
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x0E - PU_INVINCIBILITY
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x0F - PU_SPRING
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x10 - PU_CLOCK
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x11 - PU_TURBO
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x12 - FLAME_JET (tiger temple)
	{ .name = 0, .LInB = RB_FlameJet_LInB, .LThB = 0 },
	
	// 0x13 - PIRANHA_PLANT (papu pyramid)
	{ .name = 0, .LInB = RB_Plant_LInB, .LThB = 0 },
	
	// 0x14 - GATE
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x15 - START_LINE
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x16 - SPRING
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x17 - TURBO
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x18 - DYNAMIC_PLAYER (player driver)
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x19 - DYNAMIC_SMALL_BOMB
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x1a - DYNAMIC_LARGE_BOMB
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x1b - DYNAMIC_MISSILE
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x1c - DYNAMIC_EXPLOSIVE_CRATE
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x1d - DYNAMIC_POISON
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x1e - DYNAMIC_INVICIBILITY
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x1f - DYNAMIC_SPLINE_FOLLOWER
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x20 - DYNAMIC_SNOWBALL (demo blizzard bluff)
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x21 - DYNAMIC_MINE_CART
	{ .name = 0, .LInB = RB_Minecart_LInB, .LThB = 0 },
	
	// 0x22 - TEMP_SNOWBALL (blizzard bluff boulder)
	{ .name = 0, .LInB = RB_Snowball_Init, .LThB = 0 },
	
	// 0x23 - FINISH_LINE
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x24 - ARMADILLO (armadillo)
	{ .name = 0, .LInB = RB_Armadillo_LInB, .LThB = 0 },
	
	// 0x25 - BLADE
	{ .name = 0, .LInB = RB_Blade_LInB, .LThB = 0 },
	
	// 0x26 - STATIC_CRATE_EXPLOSION
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x27 - STATIC_CRATE_TNT
	// used for Crystal Challenge TNT/Nitro, no BSP collision, 
	// LInB births thread that checks for collision every frame,
	// DECOMP should birth unthreaded instances, and add hitboxes
	{ .name = 0, .LInB = RB_GenericMine_LInB, .LThB = 0 },
	
	// 0x28 - STATIC_CRATE_NITRO (unused duplicate of 0x6)
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x29 - DYNAMIC_ROCKET "bombtracker"
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x2a - DYNAMIC_BIGROCKET
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x2b - STATIC_WARPEDBURST "explosion2"
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x2c - STATIC_TURBO_EFFECT
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x2d - STATIC_TURBO_EFFECT1
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x2e - STATIC_TURBO_EFFECT2
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x2f - STATIC_TURBO_EFFECT3
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x30 - STATIC_TURBO_EFFECT4
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x31 - STATIC_TURBO_EFFECT5
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x32 - STATIC_TURBO_EFFECT6
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x33 - STATIC_TURBO_EFFECT7
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x34 - STATIC_TURBO_EFFECT_DARK
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x35 - STATIC_SHOCKWAVE
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x36 - DYNAMIC_WARPBALL
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x37 - STATIC_FRUITDISP (HUD)
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x38 - STATIC_BIG1 "Empty" used for Oxide Podium
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x39 - STATIC_AKUAKU
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x3a - STATIC_UKAUKA
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x3b - DYNAMIC_BOMB
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x3c - STATIC_BEAKER
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x3d - STATIC_BEAKERBREAK
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x3e - STATIC_AKUBEAM
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x3f - DYNAMIC_ROBOT_CAR (AI driver)
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x40 - STATIC_UKABEAM
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x41 - STATIC_SHIELD
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x42 - STATIC_CLOUD
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x43 - STATIC_WAKE
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x44 - STATIC_SHOCKWAVE_RED
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x45 - STATIC_SHOCKWAVE_GREEN
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x46 - STATIC_BEAKER_RED
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x47 - STATIC_BEAKER_GREEN
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x48 - STATIC_BEAKERBREAK_RED
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x49 - STATIC_BEAKERBREAK_GREEN
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x4a - LENSFLARE
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x4b - DYNAMIC_GHOST (ghost driver)
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x4c - DYNAMIC_SEAL (polar pass)
	{ .name = 0, .LInB = RB_Seal_Init, .LThB = 0 },
	
	// 0x4d - DYNAMIC_ORCA
	{ .name = 0, .LInB = RB_Orca_LInB, .LThB = 0 },
	
	// 0x4e - DYNAMIC_BARREL (sewer speedway)
	{ .name = 0, .LInB = RB_Snowball_Init, .LThB = 0 },
	
	// 0x4f - DYNAMIC_VONLABASS (unused, hot air skyway)
	{ .name = 0, .LInB = RB_Baron_LInB, .LThB = 0 },
	
	// 0x50 - DYNAMIC_SKUNK (unused, unknown track)
	{ .name = 0, .LInB = RB_Minecart_LInB, .LThB = 0 },
	
	// 0x51 - DYNAMIC_TURTLE (mystery caves)
	{ .name = 0, .LInB = RB_Turtle_Init, .LThB = RB_Turtle_OnCollide },
	
	// 0x52 - DYNAMIC_SPIDER (cortex castle)
	{ .name = 0, .LInB = RB_Spider_Init, .LThB = 0 },
	
	// 0x53 - DYNAMIC_SPIDERSHADOW
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x54 - DYNAMIC_FIREBALL (mystery caves fireball)
	{ .name = 0, .LInB = RB_Fireball_LInB, .LThB = 0 },
	
	// 0x55 - DYNAMIC_DRUM (n gin labs barrel)
	{ .name = 0, .LInB = RB_Baron_LInB, .LThB = 0 },
	
	// 0x56 - DYNAMIC_SHIELD (blue shield)
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x57 - STATIC_PIPE1
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x58 - STATIC_PIPE2
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x59 - STATIC_VENT
	{ .name = 0, .LInB = 0, .LThB = 0 },

	// 0x5a - DYNAMIC_SHIELD_DARK
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x5b - STATIC_CASTLE_SIGN
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x5c - STATIC_TIME_CRATE_01
	{ .name = 0, .LInB = RB_Default_LInB, .LThB = RB_Crate_Time_LThB },
	
	// 0x5d - DYNAMIC_HIGHLIGHT
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x5e - DYNAMIC_SHIELD_GREEN
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x5f - STATIC_GEM
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x60 - STATIC_CRYSTAL
	// LThB should not birth a thread, nor call OnCollide,
	// LThB should only kill LInB's thread and trigger HUD
	{ .name = 0, .LInB = RB_Crystal_LInB, .LThB = RB_Crystal_LThB },
	
	// 0x61 - STATIC_RELIC
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x62 - STATIC_TROPHY
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x63 - STATIC_KEY
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x64 - STATIC_TIME_CRATE_02
	{ .name = 0, .LInB = RB_Default_LInB, .LThB = RB_Crate_Time_LThB },
	
	// 0x65 - STATIC_TIME_CRATE_03
	{ .name = 0, .LInB = RB_Default_LInB, .LThB = RB_Crate_Time_LThB },
	
	// 0x66 - STATIC_INTRO_TROPHY
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x67 - STATIC_INTRO_CRASH
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x68 - STATIC_RINGTOP
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x69 - STATIC_RINGBOTTOM
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x6a - STATIC_CTR
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x6b - STATIC_BANNER
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x6C - STATIC_WARPPAD
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x6D - STATIC_BIG0
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x6e - STATIC_BIG9
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x6f - STATIC_BIGX
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x70 - STATIC_TEETH
	// special exception
	{ .name = 0, .LInB = RB_Teeth_LInB, .LThB = RB_Teeth_LThB },
	
	// 0x71 - STATIC_STARTTEXT
	{ .name = 0, .LInB = RB_StartText_Init, .LThB = 0 },
	
	// 0x72 - STATIC_SAVEOBJ
	{ .name = 0, .LInB = AH_SaveObj_Init, .LThB = 0 },
	
	// 0x73 - STATIC_PINGARAGE
	{ .name = 0, .LInB = AH_Garage_Init, .LThB = 0 },
	
	// 0x74 - STATIC_PAPUGARAGE
	{ .name = 0, .LInB = AH_Garage_Init, .LThB = 0 },
	
	// 0x75 - STATIC_ROOGARAGE
	{ .name = 0, .LInB = AH_Garage_Init, .LThB = 0 },
	
	// 0x76 - STATIC_JOEGARAGE
	{ .name = 0, .LInB = AH_Garage_Init, .LThB = 0 },
	
	// 0x77 - STATIC_OXIDEGARAGE
	{ .name = 0, .LInB = AH_Garage_Init, .LThB = 0 },
	
	// 0x78 - STATIC_SCAN (load/save screen)
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x79 - STATIC_SUBTRACT
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x7a - STATIC_DOOR
	{ .name = 0, .LInB = AH_Door_OnInit, .LThB = 0 },
	
	// 0x7b - STATIC_BEAM (warppad vortex)
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x7c - STATIC_BOTTOMRING (warppad spiral dots)
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x7d - STATIC_TOKEN
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x7e - STATIC_CRASHDANCE
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x7f - STATIC_CORTEXDANCE
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x80 - STATIC_TINYDANCE
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x81 - STATIC_COCODANCE
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x82 - STATIC_NGINDANCE
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x83 - STATIC_DINGODANCE
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x84 - STATIC_POLARDANCE
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x85 - STATIC_PURADANCE
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x86 - STATIC_PINSTRIPEDANCE
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x87 - STATIC_PAPUDANCE
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x88 - STATIC_ROODANCE
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x89 - STATIC_JOEDANCE
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x8a - STATIC_NTROPYDANCE
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x8b - STATIC_PENDANCE
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x8c - STATIC_FAKEDANCE
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x8d - STATIC_OXIDEDANCE
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x8e - STATIC_GARAGETOP
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x8f - STATIC_TAWNA1
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x90 - STATIC_TAWNA2
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x91 - STATIC_TAWNA3
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x92 - STATIC_TAWNA4
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0x93 - STATIC_C
	// LThB should not birth a thread, nor call OnCollide,
	// LThB should only kill LInB's thread and trigger HUD
	{ .name = 0, .LInB = RB_CtrLetter_LInB, .LThB = RB_CtrLetter_LThB },
	
	// 0x94 - STATIC_T
	// LThB should not birth a thread, nor call OnCollide,
	// LThB should only kill LInB's thread and trigger HUD
	{ .name = 0, .LInB = RB_CtrLetter_LInB, .LThB = RB_CtrLetter_LThB },
	
	// 0x95 - STATIC_R
	// LThB should not birth a thread, nor call OnCollide,
	// LThB should only kill LInB's thread and trigger HUD
	{ .name = 0, .LInB = RB_CtrLetter_LInB, .LThB = RB_CtrLetter_LThB },
	
	// 0x96 - STATIC_CRASHINTRO
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0x97 - STATIC_COCOINTRO
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0x98 - STATIC_CORTEXINTRO
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0x99 - STATIC_TINYINTRO
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0x9A - STATIC_POLARINTRO
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0x9B - STATIC_DINGOINTRO
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0x9C - STATIC_OXIDEINTRO
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0x9D - STATIC_SIMPLEKARTINTRO
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0x9E - STATIC_TINYKARTINTRO
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0x9F - STATIC_DINGOKARTINTRO
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0xA0 - STATIC_SIMPLEOBJINTRO
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0xA1 - STATIC_PPOINTTHINGINTRO
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0xA2 - STATIC_PRTHINGINTRO
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0xA3 - STATIC_OXIDELILSHIP
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0xA4 - STATIC_INTROOXIDECAM
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0xA5 - STATIC_INTROOXIDEBODY
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0xa6 - STATIC_STARTBANNERWAVE
	{ .name = 0, .LInB = RB_Banner_LInB, .LThB = 0 },
	
	// 0xa7 - STATIC_DOOR2
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xa8 - STATIC_PODIUM
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xa9 - STATIC_PINHEAD
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xaa - STATIC_PAPUHEAD
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xab - STATIC_ROOHEAD
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xac - STATIC_JOEHEAD
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xad - STATIC_OXIDEHEAD
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xae - STATIC_AKUMOUTH
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xaf - STATIC_DINGOFIRE
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xb0 - STATIC_TOMBSTONE
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xb1 - STATIC_AKUBIG
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xb2 - STATIC_UKABIG
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xb3 - STATIC_UKAMOUTH
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xb4 - STATIC_UNUSED03
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xb5 - STATIC_DOOR3
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xb6 - NDI_BOX_BOX_01
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xb7 - NDI_BOX_BOX_02
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xb8 - NDI_BOX_BOX_02_BOTTOM
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xb9 - NDI_BOX_BOX_02_FRONT
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xba - NDI_BOX_BOX_02A
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xbb - NDI_BOX_BOX_03
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xbc - NDI_BOX_CODE
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xbd - NDI_BOX_GLOW
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xbe - NDI_BOX_LID
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xbf - NDI_BOX_LID2
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xc0 - NDI_BOX_PARTICLES_01
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xc1 - NDI_KART0
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xc2 - NDI_KART1
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xc3 - NDI_KART2
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xc4 - NDI_KART3
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xc5 - NDI_KART4
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xc6 - NDI_KART5
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xc7 - NDI_KART6
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xc8 - NDI_KART7
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xc9 - NDI_BOX_LIDB
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xca - NDI_BOX_LIDC
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xcb - NDI_BOX_LIDD
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xcc - STATIC_INTRO_FLASH
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0xcd - STATIC_INTRODOORS
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0xce - STATIC_CRASHSELECT
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0xcf - STATIC_CORTEXSELECT
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0xd0 - STATIC_TINYSELECT
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0xd1 - STATIC_COCOSELECT
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0xd2 - STATIC_NGINSELECT
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0xd3 - STATIC_DINGOSELECT
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0xd4 - STATIC_POLARSELECT
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0xd5 - STATIC_PURASELECT
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0xd6 - STATIC_ENDDOORS
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0xd7 - STATIC_ENDFLASH
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0xd8 - STATIC_ENDINGOXIDE
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0xd9 - STATIC_ENDIGNOXIDE_02 (mispelled in-game)
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0xda - STATIC_ENDOXIDEBIGSHIP
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0xdb - STATIC_ENDOXIDELILSHIP
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0xdc - STATIC_OXIDECAMEND
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0xdd - STATIC_OXIDECAMEND02
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0xde - STATIC_JLOGO_FLAG
	{ .name = 0, .LInB = 0, .LThB = 0 },
	
	// 0xdf - STATIC_OXIDESPEAKER
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0xe0 - STATIC_INTROSPARKS
	{ .name = 0, .LInB = CS_LevThread_OnInit, .LThB = 0 },
	
	// 0xe1 - STATIC_GNORMALZ
	{ .name = 0, .LInB = AH_Sign_OnInit, .LThB = 0 },
};