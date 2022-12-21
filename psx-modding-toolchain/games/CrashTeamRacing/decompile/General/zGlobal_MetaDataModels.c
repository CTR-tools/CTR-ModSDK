
// this is only for LevInstances,
// NonLev-related entries are empty

void RB_Default_LInB();
void RB_Fruit_LInB();
void RB_Fruit_LInC();
void RB_GenericMine_LInB();
void RB_Crate_Fruit_LInC();
void RB_Crate_Weapon_LInC();
void RB_Crate_Time_LInC();
void RB_FlameJet_LInB();
void RB_Plant_LInB();
void RB_Minecart_LInB();
void RB_Snowball_LInB();
void RB_Armadillo_LInB();
void RB_Blade_LInB();
void RB_Seal_LInB();
void RB_Orca_LInB();
void RB_Baron_LInB();
void RB_Turtle_LInB();
void RB_Turtle_LInC();
void RB_Spider_LInB();
void RB_Fireball_LInB();
void RB_StartText_LInB();
void RB_Banner_LInB();
void RB_CtrLetter_LInB();
void RB_CtrLetter_LInC();
void RB_Crystal_LInB();
void RB_Crystal_LInC();
void RB_StartText_LInB();
void RB_Teeth_LInB();
void RB_Teeth_LInC();

void AH_Door_LInB();
void AH_Sign_LInB();
void AH_Garage_LInB();
void AH_SaveObj_LInB();

void CS_LevThread_LInB();

struct MetaDataModel
{
	
// debug names should have a remove toggle
#if 1
	// debug
	char* name;
#endif
	
	// Level Instance Birth
	// callback after converting
	// Lev InstDef to Lev Instance
	void* LInB;
	
	// Level Instance Collision
	// callback after detecting
	// Lev BSP hitbox collision
	void* LInC;
};

// This inserts debug names if needed
#if 1
#define SET_MDM(x,y,z) {.name = 0, .LInB = y, .LInC = z}
#else
#define SET_MDM(x,y,z) {.name = x, .LInB = y, .LInC = z}
#endif

// 80081088
struct MetaDataModel mdm[0xe2] =
{
	// 0x00 - NO_FUNC
	SET_MDM(0,0,0),
	
	// 0x01 - ANIMATE_IF_HIT
	SET_MDM(0,0,0),
	
	// 0x02 - PU_WUMPA_FRUIT
	// OG game births a thread, calls OnCollide, then dies,
	// DECOMP shouldn't birth in LInC, just trigger HUD
	SET_MDM(0,RB_Fruit_LInB,RB_Fruit_LInC),
	
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
	SET_MDM(0,RB_Default_LInB,RB_Crate_Fruit_LInC),
	
	// 0x08 - PU_RANDOM_CRATE (Weapon Box)
	SET_MDM(0,RB_Default_LInB,RB_Crate_Weapon_LInC),
	
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
	SET_MDM(0,RB_FlameJet_LInB,0),
	
	// 0x13 - PIRANHA_PLANT (papu pyramid)
	SET_MDM(0,RB_Plant_LInB,0),
	
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
	SET_MDM(0,RB_Minecart_LInB,0),
	
	// 0x22 - TEMP_SNOWBALL (blizzard bluff boulder)
	SET_MDM(0,RB_Snowball_LInB,0),
	
	// 0x23 - FINISH_LINE
	SET_MDM(0,0,0),
	
	// 0x24 - ARMADILLO (armadillo)
	SET_MDM(0,RB_Armadillo_LInB,0),
	
	// 0x25 - BLADE
	SET_MDM(0,RB_Blade_LInB,0),
	
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
	SET_MDM(0,RB_Seal_LInB,0),
	
	// 0x4d - DYNAMIC_ORCA
	SET_MDM(0,RB_Orca_LInB,0),
	
	// 0x4e - DYNAMIC_BARREL (sewer speedway)
	SET_MDM(0,RB_Snowball_LInB,0),
	
	// 0x4f - DYNAMIC_VONLABASS (unused, hot air skyway)
	SET_MDM(0,RB_Baron_LInB,0),
	
	// 0x50 - DYNAMIC_SKUNK (unused, unknown track)
	SET_MDM(0,RB_Minecart_LInB,0),
	
	// 0x51 - DYNAMIC_TURTLE (mystery caves)
	SET_MDM(0,RB_Turtle_LInB,RB_Turtle_LInC),
	
	// 0x52 - DYNAMIC_SPIDER (cortex castle)
	SET_MDM(0,RB_Spider_LInB,0),
	
	// 0x53 - DYNAMIC_SPIDERSHADOW
	SET_MDM(0,0,0),
	
	// 0x54 - DYNAMIC_FIREBALL (mystery caves fireball)
	SET_MDM(0,RB_Fireball_LInB,0),
	
	// 0x55 - DYNAMIC_DRUM (n gin labs barrel)
	SET_MDM(0,RB_Baron_LInB,0),
	
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
	SET_MDM(0,RB_Default_LInB,RB_Crate_Time_LInC),
	
	// 0x5d - DYNAMIC_HIGHLIGHT
	SET_MDM(0,0,0),
	
	// 0x5e - DYNAMIC_SHIELD_GREEN
	SET_MDM(0,0,0),
	
	// 0x5f - STATIC_GEM
	SET_MDM(0,0,0),
	
	// 0x60 - STATIC_CRYSTAL
	// LInC should not birth a thread, nor call OnCollide,
	// LInC should only kill LInB's thread and trigger HUD
	SET_MDM(0,RB_Crystal_LInB,RB_Crystal_LInC),
	
	// 0x61 - STATIC_RELIC
	SET_MDM(0,0,0),
	
	// 0x62 - STATIC_TROPHY
	SET_MDM(0,0,0),
	
	// 0x63 - STATIC_KEY
	SET_MDM(0,0,0),
	
	// 0x64 - STATIC_TIME_CRATE_02
	SET_MDM(0,RB_Default_LInB,RB_Crate_Time_LInC),
	
	// 0x65 - STATIC_TIME_CRATE_03
	SET_MDM(0,RB_Default_LInB,RB_Crate_Time_LInC),
	
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
	SET_MDM(0,RB_Teeth_LInB,RB_Teeth_LInC),
	
	// 0x71 - STATIC_STARTTEXT
	SET_MDM(0,RB_StartText_LInB,0),
	
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
	// LInC should not birth a thread, nor call OnCollide,
	// LInC should only kill LInB's thread and trigger HUD
	SET_MDM(0,RB_CtrLetter_LInB,RB_CtrLetter_LInC),
	
	// 0x94 - STATIC_T
	// LInC should not birth a thread, nor call OnCollide,
	// LInC should only kill LInB's thread and trigger HUD
	SET_MDM(0,RB_CtrLetter_LInB,RB_CtrLetter_LInC),
	
	// 0x95 - STATIC_R
	// LInC should not birth a thread, nor call OnCollide,
	// LInC should only kill LInB's thread and trigger HUD
	SET_MDM(0,RB_CtrLetter_LInB,RB_CtrLetter_LInC),
	
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
};