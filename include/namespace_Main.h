enum GameMode1 
{
	PAUSE_1				= 0x1,
	PAUSE_2				= 0x2,	// unused, debug
	PAUSE_3				= 0x4,	// unused, debug
	PAUSE_4				= 0x8,	// unused, debug
	PAUSE_ALL           = 0xF,
	PAUSE_THREADS		= 0x10,
	BATTLE_MODE         = 0x20,
	START_OF_RACE 		= 0x40,
	// 0x80?
	P1_VIBRATE			= 0x100,
	P2_VIBRATE			= 0x200,
	P3_VIBRATE			= 0x400,
	P4_VIBRATE			= 0x800,
	WARPBALL_HELD       = 0x1000,
	MAIN_MENU           = 0x2000,
	POINT_LIMIT			= 0x4000,
	LIFE_LIMIT			= 0x8000,
	TIME_LIMIT			= 0x10000,
	TIME_TRIAL          = 0x20000,
	// 0x40000?
	ADVENTURE_MODE      = 0x80000,
	ADVENTURE_ARENA     = 0x100000,
	END_OF_RACE 		= 0x200000,
	ARCADE_MODE         = 0x400000,
	ROLLING_ITEM        = 0x800000,
	AKU_SONG			= 0x1000000,
	UKA_SONG			= 0x2000000,
	RELIC_RACE			= 0x4000000,
	CRYSTAL_CHALLENGE   = 0x8000000,
	ADVENTURE_CUP       = 0x10000000,
	GAME_CUTSCENE      	= 0x20000000,
	LOADING             = 0x40000000,
	ADVENTURE_BOSS      = 0x80000000
};

enum GameMode2
{
	SPAWN_AT_BOSS = 1,
	
	VEH_FREEZE_PODIUM = 4,
	TOKEN_RACE 		= 0x8,
	CUP_ANY_KIND 	= 0x10,
	LEV_SWAP 		= 0x20,
	// 0x40?
	CREDITS 		= 0x80,
	
	DISABLE_LEV_INSTANCE = 0x100,
	
	CHEAT_WUMPA 	= 0x200,
	CHEAT_MASK 		= 0x400,
	CHEAT_TURBO		= 0x800,
	
	// & 0x1000 - FIRST_TIME_WIN_CUP
	// & 0x2000 - FIRST_TIME_UNLOCK_BATTLE_MAP
	
	VEH_FREEZE_DOOR = 0x4000,
	CHEAT_INVISIBLE	= 0x8000,
	CHEAT_ENGINE	= 0x10000,
	GARAGE_OSK		= 0x20000,
	CHEAT_ADV		= 0x40000,
	CHEAT_ICY		= 0x80000,
	CHEAT_TURBOPAD	= 0x100000,
	CHEAT_SUPERHARD	= 0x200000,
	CHEAT_BOMBS		= 0x400000,
	CHEAT_ONELAP	= 0x800000,
	INC_RELIC		= 0x1000000,
	INC_KEY			= 0x2000000,
	INC_TROPHY		= 0x4000000,
	CHEAT_TURBOCOUNT= 0x8000000
	// & 0x10000000 - LNG_CHANGE (EurRetail Only)
};

// real ND name
struct GameTracker
{
	// 0x0
	int gameMode1;

	// 0x4
	int gameMode1_prevFrame;

	// 0x8
	int gameMode2;

	// 0xC
	int swapchainIndex; // 0 or 1

	// 0x10
	struct DB* backBuffer;	// the one you render to

	// 0x14
	struct DB* frontBuffer;	// the one being sent to screen

	// 0x18
	struct DB db[2];			/* packet double buffer */

	// The LEV being drawn
	// 0x160
	struct Level* level1;		// real ND name

	// The LEV being loaded while
	// the other LEV is being drawn,
	// used in Adv Hub
	struct Level* level2;		// real ND name

	// Four window structs, each 0x110
	// vec3s pos, vec3s rot, shown in FreecamCTR
	// not sure if this is window, or camera, but
	// there are also dynamically allocated cameras
	// 0x168
	struct PushBuffer pushBuffer[4];

	// 0x5A8
	// see 80023784
	// Each of these is a "pixel LOD" driver, if all drivers see each other, there's
	// three drivers on each screen, which can all have pixelLOD if far enough away,
	struct
	{
		// 0x0
		// 0x4
		char data[6];

		// 0x6
		short boolUpdatedThisFrame;

		// 0x8
		struct Instance* inst;

		// 0xC
		char data2[0x100];

		// 0x10C and 0x110
		int ptrOT1;
		int ptrOT2;

		// 0x114
		char data3[0x14];

		// 0x120
		// InstDrawPerPlayer ID

		// 0x128 - size

	} DecalMP[3*4];

	// 0x1388
	struct PushBuffer pushBuffer_UI;

	// 0x1498
	struct CameraDC cameraDC[4];

	// 0x1808
	struct
	{
		// every quadblockrendered pointer in P1
		// will be 80096404, P2 has their own, etc,
		// there really only needs to be one pointer per player

		// 1P2P lists (might change in 3P4P)
		// [0] - 0x00: Force4x4
		// [1] - 0x08: DynamicSubdiv
		// [2] - 0x10: Force4x2
		// [3] - 0x18: Force4x1
		// [4] - 0x20: Water
		struct
		{
			void* ptrQuadBlocksRendered;
			struct BSP** bspListStart;
		} list[5];

		// 0x28
		struct BSP** bspListStart_FullDynamic;
		void* ptrQuadBlocksRendered_FullDynamic;

		// 0x30 large

	// one for each player
	} LevRenderLists[4];

	// pointers to OT memory,
	// used in ClearOTagR
	// 0x18c8
	// 0x18cc
	// one for each DB
	void* otSwapchainDB[2];

	// 0x18d0
	struct
	{
		struct JitPool thread;		// 0x18d0
		struct JitPool instance;	// 0x18f8
		struct JitPool smallStack;	// 0x1920, used for items
		struct JitPool mediumStack;	// 0x1948, used for ???
		struct JitPool largeStack;	// 0x1970, used for drivers
		struct JitPool particle;	// 0x1998
		struct JitPool oscillator;	// 0x19c0
		struct JitPool rain;		// 0x19e8
	} JitPools;

	// 1a10
	int levelID;

	// 1a14
	#if BUILD == SepReview
	char levelName[0xC];
	#elif BUILD >= UsaRetail
	char levelName[0x24];
	#endif

	// according to FUN_8003af84,
	// 0x1a38 is offset 400 (0x190) of LEV

	// 0x1a38
	// This "region" is only in EurRetail and JpnRetail,
	// while the other "region" goes back to JpnTrial
	#if BUILD >= EurRetail
	char s_region_8byte[8];
	#endif

	// 0x1a38 -- UsaRetail
	// 0x1a40 -- EurRetail, JpnRetail
	struct VisMem* visMem1;
	struct VisMem* visMem2;

	// 0x1a40 -- UsaRetail
	// one for each player
	struct RainBuffer rainBuffer[4];

	// 0x1b00 -- UsaRetail
	struct
	{
		// 0x1b00
		short numParticles_curr;

		// previous frame?
		short unk1;

		// 0x1b04
		short numParticles_max;

		short unk2;

		// 0x1b08
		int velY; // negative
	} confetti;

	// 0x1b0c
	struct
	{
		// 0x1b0c
		short numStars;

		// 0x1b0e
		short unk[3];

		// 1b14
		int offsetOT;

	} stars;

	// 1b18
	unsigned int ptrClod;

	// 1b1c
	unsigned int ptrDustpuff;

	// 1b20
	unsigned int ptrSmoking;

	// 1b24
	unsigned int ptrSparkle;

	// 1b28
	// handles character icons,
	// traffic light sprites, etc
	unsigned int mpkIcons;

	// 0x1b2c - 0x1c93
	struct ThreadBucket threadBuckets[NUM_BUCKETS];

	// 1c94
	void* ptrRenderBucketInstance;

	 // 1c98
	int unk_1c98;

	// 1c9c
	// exhaust, fire, etc
	void* particleList_ordinary;

	// 1ca0
	// distorts screen above fire
	void* particleList_heatWarp;

	// 1ca4
	int numParticles;

	// 1c40 -- SepReview
	// 1ca8 -- UsaRetail, JpnTrial
	// 1cb0 -- EurRetail, JpnRetail

	// 1ca8, 1ca9
	char numPlyrCurrGame;
	char numPlyrNextGame;

	// 1caa, 1cab
	char numBotsCurrGame;
	char numBotsNextGame;

	// 1cac
	int unk1cac[5];

	// 1cc0
	int bspLeafsDrawn;
	
	// 1cc4
	int unk1cc4[6];

	// 1cdc
	int countTotalTime;

	// 1ce0
	int vSync_between_drawSync;

	// 1ce4
	int frameTimer_VsyncCallback;

	// 1ce8
	int frameTimer_notPaused;

	// 1cec
	// frameTimer_sinceBoot??
	int timer;

	// 1cf0
	int frameTimer_Confetti;

	int unk1cf4;

	// 1cf8
	int frameTimer_MainFrame_ResetDB;

	// 1cfc
	// frames since end of loading
	int framesInThisLEV;

	// 1d00
	// Naughty Dog Box Scene timer
	// milliseconds since end of loading
	int msInThisLEV;

	// 1d04
	// milliseconds per frame
	int elapsedTimeMS;

	// 1d08
	// microseconds per frame?
	int anotherTimer;

	// 1d0c
	// 0xf00 - normal start of race
	// 0 - start race instantly
	// 0xfffffc40 - already off screen
	int trafficLightsTimer;

	// 1d10
	int elapsedEventTime;

	// 1d14
	// arcade, relic, time trial,
	// intended to find best lap,
	// P1 and P2 overwrite each other in 2P arcade,
	// probably not intended for arcade use
	int lapTime[7];

	// 1d30
	char bool_DrawOTag_InProgress;

	// 1d31
	u_char hudFlags;

	// 1d32
	char boolDemoMode;

	// 1d33
	char numLaps;

	// 1d34
	// Variable is never given a value
	// unused???
	short unk_timerCooldown_similarTo_1d36;

	// 1d36
	// used to make comments appear
	short timerEndOfRaceVS;

	// 1d38
	char cooldownfromPauseUntilUnpause;

	// 1d38 and 1d39 make sure you dont
	// spam pause and unpause, or have
	// input from gameplay and pause menu
	// mixing together

	// 1d39
	char cooldownFromUnpauseUntilPause;

	// 1d3a
	// value is from 0 to 6
	short advPausePage;

	// ======== High Score related \/  \/ =============

	// 1d3c
	int bestLapTime;

	// 1d40
	// can be 0,1,2
	int lapIndexNewBest;

	// 1d44
	u_int unknownFlags_1d44;

	// 1d48
	char unknown_1d48_notFound;

	// sep 0x1ce1 -- found
	// usa 0x1d49 -- found
	char newHighScoreIndex;

#if BUILD >= UsaRetail
	// 0x1d4a
	short notFoundInCode1;
#endif

	// sep 0x1ce2
	// usa 0x1d4c
	// on-screen keyboard
	short typeCursorPosition;


#if BUILD >= UsaRetail
	// 0x1d4e
	short notFoundInCode2;

	// 0x1d50
	short langIndex;
#endif

	// sep 1ce4 -- found
	// usa 1d52 -- found
	short constVal_9000;

	// sep 1ce6
	// usa 1d54
	char prevNameEntered[0x11];

	// sep 1cf7
	// usa 1d65
	char currNameEntered[0x11];

	#if BUILD >= UsaRetail
	// 1d76
	// 1d77
	short nameEnterPadding;
	#endif

	// usa 1d78 -- found
	int timeToBeatInTimeTrial_ForCurrentEvent;

	// usa 1d7c
	int trackLength_x_numLaps_x_8;

	// ========================================

	// Time Trial ^^^^

	// Battle \/    \/

	// ========================================

	// 1d80
	int battleLifeLimit;

	// 1d84
	// for countdown timers in Battle and Crystal Challenge
	int originalEventTime;

	// 1d88
	struct
	{
	// 1d88
	int lifeLimit; // 3,6,9

	// 1d8c
	int killLimit; // 5,10,15

	// 1d90
	int pointsPerTeam[4];

	// 1da0
	int enabledWeapons;

	// 1da4
	char teamOfEachPlayer[4];

	// 1da8
	int finishedRankOfEachTeam[4];
	
	// 1db8
	int unk1DB8[4];

	// 1dc8
	int unk1dc8[4];

	// 1dd8
	// 0b0001 for everyone on team 1
	// 0b0101 for some on team 1 and some on team 3
	// 0b1111 for all four teams active
	// etc
	u_int teamFlags;

	// 1ddc
	int numTeams;

	// 1de0
	int unk_afterTeams[4];

	// 1df0
	int numWeapons;

	// 1df4
	// for custom set of weapons
	int RNG_itemSetCustom[0xb];

	} battleSetup;

	// 1e20
	int frozenTimeRemaining;

	// 1e24
	int timeCrateTypeSmashed;

	// +1e28
	int numCrystalsInLEV;

	// +1e2c
	int timeCratesInLEV;

	struct
	{
		// 1e30
		int numTrophies;
	
		// 1e34
		int numRelics;
	
		// 1e38
		int numKeys;
	
		// 1e3c
		struct
		{
			int total;
			int red;
			int green;
			int blue;
			int yellow;
			int purple;
		} numCtrTokens;
	
		// 1e54
		int completionPercent; // 0 to 101

	} currAdvProfile;

	struct
	{
		// 1e58
		int cupID; // 0-3, or 4 for Purple cup
		
		// 1e5c
		int trackIndex; // 0-3
		
		// 1e60
		int points[8];

	} cup;

	// 0x1e80
	// how many times each player (4)
	// came in 1st, 2nd, or 3rd (3)
	// Used in VS Standings and Battle Standings
	int standingsPoints[4*3];

	// 1eb0
	// trackSel, AdvHubProfile, battle, cups, etc
	// does not record LEV when driving between AdvHubs
	int currLEV;

	// 1eb4
	int prevLEV;

	// 1eb8
	// 0 - Ripper Roo's Challenge
	// 1 - Papu Papu's Challenge
	// ...
	// 4 - Oxide's Challenge
	// 5 - Oxide's Final Challenge
	int bossID;

	// 1ebc
	int arcadeDifficulty;

	#if BUILD >= UsaRetail
	// 1ec0
	unsigned int numMissiles;
	// 1ec4
	int numPlayersWith3Missiles;
	#endif

	// 1e50 sep
	// 1ec8 usa
	// Only used in Tiger Temple and Cortex Castle,
	// watch it change when you go into a room, it
	// change to zero when rain stops, and gets a
	// new value when no roof is over your head (rain)
	int rainSoundID;

	// 1ecc
	// RedOff, RedOn, GreenOff, GreenOn
	struct Icon* trafficLightIcon[4];

	// 1edc
	// In retail versions of the game, this is
	// used to end "Demo Mode" where you watch AIs drive.
	// In real demos (june 1999, spyro2), this is used to
	// end the demo while inactive, and reboot game. Both
	// are exactly 4 bytes after GreenOn
	unsigned int demoCountdownTimer;

	// 1ee0
	int unk1ee0;
	int unk1ee4;
	int unk1ee8;

	// 0x1e74 sep3
	// 0x1eec UsaRetail
	struct Icon* ptrIcons[0x88];

	// internal name first, followed by what it is
	// except for current map top and bottom, they're pointers to several icons that get loaded depending on lev

	// 0 - shadow1 -- half of kart shadow
	// 1 - shadow2 -- half of kart shadow
	// 2 - turbo -- Turbo cannister item icon
	// 0x03 - Current Map Top -- map-island1-01, map-tube1-01, map-temple1-01, map-asphalt1-01, map-cave1-01, map-desert2-01, map-sewer1-01, map-proto8-01, map-temple2-01, map-proto9-01, map-ice1-01, map-castle1-01, map-asphalt2-01, map-blimp1-01, map-labs1-01, map-space1-01, map-secret1-01, map-secret2-01
	// 0x04 - Current Map Bottom -- map-island1-02, map-tube1-02, map-temple1-02, map-asphalt1-02, map-cave1-02, map-desert2-02, map-sewer1-02, map-proto8-02, map-temple2-02, map-proto9-02, map-ice1-02, map-castle1-02, map-asphalt2-02, map-blimp1-02, map-labs1-02, map-space1-02, map-secret1-02, map-secret2-02
	// 0x05 - turbonew -- Duplicate of turbo cannister?
	// 0x06 - bomb
	// 0x07 - bomb-tracker -- Missile
	// 0x08 - nitro -- TNT Icon
	// 0x09 - poison -- Green Beaker Icon
	// 0x0a - --- nullptr --- Spring Icon
	// 0x0b - shield -- Green Shield Icon
	// 0x0c - doctor -- Aku Aku item icon
	// 0x0d - clock -- Clock Icon
	// 0x0e - missile -- Warpball Icon
	// 0x0f - bomb3 -- Triple Bomb Icon?
	// 0x10 - bomb-tracker3 -- Triple Missile Icon?
	// 0x11 - invisible -- Invisibility Icon
	// 0x12 - engine -- Super Engine Icon
	// 0x13 -
	// 0x14 - nitroj -- Nitro Icon
	// 0x15 - poisonj -- Red Beaker Icon
	// 0x16 -
	// 0x17 - shieldj -- Blue Shield Icon
	// 0x18 -
	// 0x19 - first -- big 1, used to have st in early builds
	// 0x1a - second -- big 2, used to have nd in early builds
	// 0x1b - third -- big 3, used to have rd in early builds
	// 0x1c - fourth -- big 4, used to have th in early builds
	// 0x1d -
	// 0x1e -
	// 0x1f -
	// 0x20 - crash -- Crash Bandicoot
	// 0x21 - cortex -- Dr. Neo Cortex
	// 0x22 - tiny -- Tiny Tiger
	// 0x23 - coco -- Coco Bandicoot
	// 0x24 - ngin -- N. Gin
	// 0x25 - dingo -- Dingodile
	// 0x26 - polar -- Polar
	// 0x27 - pura -- Pura
	// 0x28 - roo -- Ripper Roo
	// 0x29 - papu -- Papu Papu
	// 0x2a - komodojoe -- Komodo Joe
	// 0x2b - pinstripe -- Pinstripe
	// 0x2c - ntropy -- Dr. N. Tropy
	// 0x2d - target -- Missile lock-on icon
	// 0x2e -
	// 0x2f - tread -- tire skids
	// 0x30 -
	// 0x31 - poweredup -- Juiced-up weapon flash
	// 0x32 - ukauka -- Uka Uka item icon
	// 0x33 -
	// 0x34 -
	// 0x35 - penguin -- Penta Penguin
	// 0x36 - fakecrash -- Fake Crash
	// 0x37 - oxide -- Nitros Oxide
	// 0x38 -
	// 0x39 -
	// 0x3a -
	// 0x3b - small_circlebtn -- Circle button (small font)
	// 0x3c - small_crossbtn -- Cross button (small font)
	// 0x3d - small_squarebtn -- Square button (small font)
	// 0x3e - small_triangleb -- Triangle button (small font)
	// 0x3f - movie1 -- blue sky texture, used as placeholder for track thumbnail
	// 0x40 -
	// 0x41 -
	// 0x42 - debugfont -- search "0x1ff4"
	// 0x43 - asphalt1 -- Coco Park Track Icon
	// 0x44 - asphalt2 -- Tiny Arena Track Icon
	// 0x45 - battle1 -- Nitro Court Track Icon
	// 0x46 - battle2 -- Rampage Ruins Track Icon
	// 0x47 - battle3 -- Parking Lot Track Icon
	// 0x48 - battle4 -- Skull Rock Track Icon
	// 0x49 - battle5 -- North Bowl Track Icon
	// 0x4a - battle6 -- Rocky Road Track Icon
	// 0x4b - battle7 -- Lab Basement Track Icon
	// 0x4c - blimp1 -- Hot Air Skyway Track Icon
	// 0x4d - castle1 -- Cortex Castle Track Icon
	// 0x4e - cave1 -- Mystery Caves Track Icon
	// 0x4f - desert2 -- Blizzard Bluff Track Icon
	// 0x50 - ice1 -- Polar Pass Track Icon
	// 0x51 - island1 -- Crash Cove Track Icon
	// 0x52 - labs1 -- N Gin Labs Track Icon
	// 0x53 - proto8 -- Dingo Canyon Track Icon
	// 0x54 - proto9 -- Dragon Mines Track Icon
	// 0x55 - secret1 -- Slide Coliseum Track Icon
	// 0x56 - secret2 -- Turbo Track Track Icon
	// 0x57 - sewer1 -- Sewer Speedway Track Icon
	// 0x58 - space -- Oxide Station Track Icon
	// 0x59 - temple1 -- Tiger Temple Track Icon
	// 0x5a - temple2 -- Papu Pyramid Track Icon
	// 0x5b - tube1 -- Roos Tubes Track Icon
	// 0x5c - asphalt1a -- Coco Park Map Top
	// 0x5d - asphalt1b -- Coco Park Map Bottom
	// 0x5e - asphalt2a -- Tiny Arena Map Top
	// 0x5f - asphalt2b -- Tiny Arena Map Bottom
	// 0x60 - blimp1a -- Hot Air Skyway Map Top
	// 0x61 - blimp1b -- Hot Air Skyway Map Bottom
	// 0x62 - castle1a -- Cortex Castle Map Top
	// 0x63 - castle1b -- Cortex Castle Map Bottom
	// 0x64 - cave1a -- Mystery Caves Map Top
	// 0x65 - cave1b -- Mystery Caves Map Bottom
	// 0x66 - desert2a -- Blizzard Bluff Map Top
	// 0x67 - desert2b -- Blizzard Bluff Map Bottom
	// 0x68 - ice1a -- Polar Pass Map Top
	// 0x69 - ice2b -- Polar Pass Map Bottom
	// 0x6a - island1a -- Crash Cove Map Top
	// 0x6b - island1b -- Crash Cove Map Bottom
	// 0x6c - labs1a -- N. Gin Labs Map Top
	// 0x6d - labs1b -- N. Gin Labs Map Bottom
	// 0x6e - desert1a -- Dingo Canyon Map Top
	// 0x6f - desert1b -- Dingo Canyon Map Bottom
	// 0x70 - proto9a -- Dragon Mines Map Top
	// 0x71 - proto9b -- Dragon Mines Map Bottom
	// 0x72 - secret1a -- Slide Coliseum Map Top
	// 0x73 - secret1b -- Slide Coliseum Map Bottom
	// 0x74 - secret2a -- Turbo Track Map Top
	// 0x75 - secret2b -- Turbo Track Map Bottom
	// 0x76 - sewer1a -- Sewer Speedway Map Top
	// 0x77 - sewer1b -- Sewer Speedway Map Bottom
	// 0x78 - spacea -- Oxide Station Map Top
	// 0x79 - spaceb -- Oxide Station Map Bottom
	// 0x7a - temple1a -- Tiger Temple Map Top
	// 0x7b - temple1b -- Tiger Temple Map Bottom
	// 0x7c - temple2a -- Papu Pyramid Map Top
	// 0x7d - temple2b -- Papy Pyramid Map Bottom
	// 0x7e - tube1a -- Roo's Tubes Map Top
	// 0x7f - tube1b -- Roo's Tubes Map Bottom
	// 0x80 - circlebutton -- Circle button (large font)
	// 0x81 - crossbutton -- Cross button (large font)
	// 0x82 - squarebutton -- Square button (large font)
	// 0x83 - trianglebutton -- Triangle button (large font)

	// Battle icons

	// 0x84 - health -- Lives icon
	// 0x85 - death -- Kills icon
	// 0x86 - time -- Appears to be corrupted/not exist?

	// 0x87 - flare -- Lensflare (1/4th image, drawn 4 times)

	// return to FUN_80050654 for battle icons,
	// those are probably the bottom ones

	// 210C
	int unk210c;

	// No clue if this is right, I just know that
	// 4 bytes were addded between the start of
	// the icon array, and teh start of iconGroup,
	// between Sep3 and UsaRetail
	#if BUILD >= UsaRetail
	int unk2110;
	#endif

	// 2114 -- UsaRetail, JpnTrial
	// 211c -- JpnRetail
	// 2098 -- SepReview
	struct IconGroup* iconGroup[0x11];

	// Different pointer struct than 1f6c

	// 0x00 - tireAnim
	// 0x01 - dustpuff
	// 0x02 - sparkle
	// 0x03 - smokering
	// 0x04 - largefont
	// 0x05 - middlefont

	// 0x06 - ???

	// 0x07 - bubble
	// 0x08 - bubblepop (underwater)
	// 0x09 - falling ("drop" in JpnTrial) (only on some tracks)
	// 0x0A - fire (mystery cave, tiger temple)

	// 0x0B - wumpaposter
	// 0x0C - trtireAnim
	// 0x0D - mud (in Tiny Arena only)

	// 0x0E - map-hub-02 in UsaRetail, jfontBigAnim in Japanese builds (118 icons)
	// 0x0F - hub-dust-puff in UsaRetail, jfontSmallAnim in Japanese builds (118 icons)
	// 0x10 - hubdustpuff (doesn't exist in 1006?)

	// ----------------------------------------------

	// 2158
	int unk2158;

	// 215C
	int unk215C;

	// 2160
	// always one more than the
	// array of Init Func Info
	#if BUILD == SepReview
	struct Model* modelPtr[0xdf];
	#elif BUILD >= UsaRetail
	struct Model* modelPtr[0xe3];
	#endif

	// 0x00 - NO_FUNC
	// 0x01 - ANIMATE_IF_HIT
	// 0x02 - PU_WUMPA_FRUIT (on track)
	// 0x03 - PU_SMALL_BOMB
	// 0x04 - PU_LARGE_BOMB
	// 0x05 - PU_MISSILE
	// 0x06 - PU_EXPLOSIVE_CRATE (nitro)
	// 0x07 - PU_FRUIT_CRATE
	// 0x08 - PU_RANDOM_CRATE (Weapon Box)
	// 0x09 - PU_TIME_CRATE_1
	// 0x0A - PU_TIME_CRATE_2
	// 0x0B - PU_TIME_CRATE_3
	// 0x0C - PU_POISON
	// 0x0D - PU_SHIELD
	// 0x0E - PU_INVINCIBILITY
	// 0x0F - PU_SPRING
	// 0x10 - PU_CLOCK
	// 0x11 - PU_TURBO
	// 0x12 - FLAME_JET (spits fire in tiger temple)
	// 0x13 - PIRANHA_PLANT (papu pyramid)
	// 0x14 - GATE
	// 0x15 - START_LINE
	// 0x16 - SPRING
	// 0x17 - TURBO

	// not intended for "model" array,
	// used in thread+44, to describe behavior
	// 0x18 - DYNAMIC_PLAYER (Human Player of any kind)

	// 0x19 - DYNAMIC_SMALL_BOMB
	// 0x1a - DYNAMIC_LARGE_BOMB
	// 0x1b - DYNAMIC_MISSILE
	// 0x1c - DYNAMIC_EXPLOSIVE_CRATE
	// 0x1d - DYNAMIC_POISON
	// 0x1e - DYNAMIC_INVICIBILITY
	// 0x1f - DYNAMIC_SPLINE_FOLLOWER
	// 0x20 - DYNAMIC_SNOWBALL
	// 0x21 - DYNAMIC_MINE_CART
	// 0x22 - TEMP_SNOWBALL (blizzard bluff boulder)
	// 0x23 - FINISH_LINE
	// 0x24 - ARMADILLO (armadillo)
	// 0x25 - BLADE
	// 0x26 - STATIC_CRATE_EXPLOSION
	// 0x27 - STATIC_CRATE_TNT
	// 0x28 - STATIC_CRATE_NITRO
	// 0x29 - DYNAMIC_ROCKET "bombtracker"
	// 0x2a - DYNAMIC_BIGROCKET
	// 0x2b - STATIC_WARPEDBURST "explosion2"

	// 0x2c - 0x33 (8 frames)
	// kart fire animation frames
	// STATIC_TURBO_EFFECT
	// STATIC_TURBO_EFFECT1
	// STATIC_TURBO_EFFECT2
	// STATIC_TURBO_EFFECT3
	// STATIC_TURBO_EFFECT4
	// STATIC_TURBO_EFFECT5
	// STATIC_TURBO_EFFECT6
	// STATIC_TURBO_EFFECT7

	// 0x34 - STATIC_TURBO_EFFECT_DARK
	// 0x35 - STATIC_SHOCKWAVE
	// 0x36 - DYNAMIC_WARPBALL
	// 0x37 - STATIC_FRUITDISP (HUD)
	// 0x38 - STATIC_BIG1 "Empty" used for Oxide Podium

	// 0x39 - STATIC_AKUAKU
	// 0x3a - STATIC_UKAUKA
	// 0x3b - DYNAMIC_BOMB
	// 0x3c - STATIC_BEAKER
	// 0x3d - STATIC_BEAKERBREAK
	// 0x3e - STATIC_AKUBEAM

	// not intended for "model" array,
	// used in thread+44, to describe behavior
	// 0x3f - DYNAMIC_ROBOT_CAR (Robot AI of any kind)

	// 0x40 - STATIC_UKABEAM
	// 0x41 - STATIC_SHIELD
	// 0x42 - STATIC_CLOUD
	// 0x43 - STATIC_WAKE
	// 0x44 - STATIC_SHOCKWAVE_RED
	// 0x45 - STATIC_SHOCKWAVE_GREEN
	// 0x46 - STATIC_BEAKER_RED
	// 0x47 - STATIC_BEAKER_GREEN
	// 0x48 - STATIC_BEAKERBREAK_RED
	// 0x49 - STATIC_BEAKERBREAK_GREEN

	// 0x4a - LENSFLARE

	// 0x4b - DYNAMIC_GHOST (Ghost of any kind)

	// 0x4c - DYNAMIC_SEAL (polar pass)
	// 0x4d - DYNAMIC_ORCA
	// 0x4e - DYNAMIC_BARREL
	// 0x4f - DYNAMIC_VONLABASS
	// 0x50 - DYNAMIC_SKUNK
	// 0x51 - DYNAMIC_TURTLE (mystery caves)
	// 0x52 - DYNAMIC_SPIDER (cortex castle)
	// 0x53 - DYNAMIC_SPIDERSHADOW
	// 0x54 - DYNAMIC_FIREBALL (mystery caves fireball)
	// 0x55 - DYNAMIC_DRUM (n gin labs barrel)
	// 0x56 - DYNAMIC_SHIELD (blue shield)

	// 57 and 59 are lab basement
	// 0x57 - STATIC_PIPE1
	// 0x58 - STATIC_PIPE2
	// 0x59 - STATIC_VENT

	// 0x5a - DYNAMIC_SHIELD_DARK
	// 0x5b - STATIC_CASTLE_SIGN
	// 0x5c - STATIC_TIME_CRATE_01
	// 0x5d - DYNAMIC_HIGHLIGHT
	// 0x5e - DYNAMIC_SHIELD_GREEN

	// 0x5f - STATIC_GEM
	// 0x60 - STATIC_CRYSTAL
	// 0x61 - STATIC_RELIC
	// 0x62 - STATIC_TROPHY
	// 0x63 - STATIC_KEY
	// 0x64 - STATIC_TIME_CRATE_02
	// 0x65 - STATIC_TIME_CRATE_03

	// main menu
	// 0x66 - STATIC_INTRO_TROPHY
	// 0x67 - STATIC_INTRO_CRASH
	// 0x68 - STATIC_RINGTOP
	// 0x69 - STATIC_RINGBOTTOM
	// 0x6a - STATIC_CTR
	// 0x6b - STATIC_BANNER

	// Adv Hub
	// 0x6C - STATIC_WARPPAD
	// 0x6D - STATIC_BIG0
	// 0x6e - STATIC_BIG9
	// 0x6f - STATIC_BIGX

	// 0x70 - STATIC_TEETH
	// 0x71 - STATIC_STARTTEXT

	// 0x72 - STATIC_SAVEOBJ
	// 0x73 - STATIC_PINGARAGE
	// 0x74 - STATIC_PAPUGARAGE
	// 0x75 - STATIC_ROOGARAGE
	// 0x76 - STATIC_JOEGARAGE
	// 0x77 - STATIC_OXIDEGARAGE
	// 0x78 - STATIC_SCAN (load/save screen)

	// 0x79 - STATIC_SUBTRACT

	// 0x7a - STATIC_DOOR
	// 0x7b - STATIC_BEAM (warppad vortex)
	// 0x7c - STATIC_BOTTOMRING (warppad spiral dots)
	// 0x7d - STATIC_TOKEN

	// 0x7e - STATIC_CRASHDANCE
	// 0x7f - STATIC_CORTEXDANCE
	// 0x80 - STATIC_TINYDANCE
	// 0x81 - STATIC_COCODANCE
	// 0x82 - STATIC_NGINDANCE
	// 0x83 - STATIC_DINGODANCE
	// 0x84 - STATIC_POLARDANCE
	// 0x85 - STATIC_PURADANCE
	// 0x86 - STATIC_PINSTRIPEDANCE
	// 0x87 - STATIC_PAPUDANCE
	// 0x88 - STATIC_ROODANCE
	// 0x89 - STATIC_JOEDANCE
	// 0x8a - STATIC_NTROPYDANCE
	// 0x8b - STATIC_PENDANCE
	// 0x8c - STATIC_FAKEDANCE
	// 0x8d - STATIC_OXIDEDANCE

	// 0x8e - STATIC_GARAGETOP

	// 0x8f - STATIC_TAWNA1
	// 0x90 - STATIC_TAWNA2
	// 0x91 - STATIC_TAWNA3
	// 0x92 - STATIC_TAWNA4

	// 0x93 - STATIC_C
	// 0x94 - STATIC_T
	// 0x95 - STATIC_R

	// 0x96 - STATIC_CRASHINTRO
	// 0x97 - STATIC_COCOINTRO
	// 0x98 - STATIC_CORTEXINTRO
	// 0x99 - STATIC_TINYINTRO
	// 0x9A - STATIC_POLARINTRO
	// 0x9B - STATIC_DINGOINTRO
	// 0x9C - STATIC_OXIDEINTRO
	// 0x9D - STATIC_SIMPLEKARTINTRO
	// 0x9E - STATIC_TINYKARTINTRO
	// 0x9F - STATIC_DINGOKARTINTRO
	// 0xA0 - STATIC_SIMPLEOBJINTRO
	// 0xA1 - STATIC_PPOINTTHINGINTRO
	// 0xA2 - STATIC_PRTHINGINTRO
	// 0xA3 - STATIC_OXIDELILSHIP
	// 0xA4 - STATIC_INTROOXIDECAM
	// 0xA5 - STATIC_INTROOXIDEBODY

	// 0xa6 - STATIC_STARTBANNERWAVE
	// 0xa7 - STATIC_DOOR2
	// 0xa8 - STATIC_PODIUM

	// 0xa9 - STATIC_PINHEAD
	// 0xaa - STATIC_PAPUHEAD
	// 0xab - STATIC_ROOHEAD
	// 0xac - STATIC_JOEHEAD
	// 0xad - STATIC_OXIDEHEAD
	// 0xae - STATIC_AKUMOUTH
	// 0xaf - STATIC_DINGOFIRE

	// 0xb0 - STATIC_TOMBSTONE
	// 0xb1 - STATIC_AKUBIG
	// 0xb2 - STATIC_UKABIG
	// 0xb3 - STATIC_UKAMOUTH
	// 0xb4 - STATIC_UNUSED03
	// 0xb5 - STATIC_DOOR3

	// 0xb6 - NDI_BOX_BOX_01
	// 0xb7 - NDI_BOX_BOX_02
	// 0xb8 - NDI_BOX_BOX_02_BOTTOM
	// 0xb9 - NDI_BOX_BOX_02_FRONT
	// 0xba - NDI_BOX_BOX_02A
	// 0xbb - NDI_BOX_BOX_03
	// 0xbc - NDI_BOX_CODE
	// 0xbd - NDI_BOX_GLOW
	// 0xbe - NDI_BOX_LID
	// 0xbf - NDI_BOX_LID2
	// 0xc0 - NDI_BOX_PARTICLES_01

	// 0xc1 - NDI_KART0
	// 0xc2 - NDI_KART1
	// 0xc3 - NDI_KART2
	// 0xc4 - NDI_KART3
	// 0xc5 - NDI_KART4
	// 0xc6 - NDI_KART5
	// 0xc7 - NDI_KART6
	// 0xc8 - NDI_KART7

	// 0xc9 - NDI_BOX_LIDB
	// 0xca - NDI_BOX_LIDC
	// 0xcb - NDI_BOX_LIDD

	// 0xcc - STATIC_INTRO_FLASH
	// 0xcd - STATIC_INTRODOORS

	// 0xce - STATIC_CRASHSELECT
	// 0xcf - STATIC_CORTEXSELECT
	// 0xd0 - STATIC_TINYSELECT
	// 0xd1 - STATIC_COCOSELECT
	// 0xd2 - STATIC_NGINSELECT
	// 0xd3 - STATIC_DINGOSELECT
	// 0xd4 - STATIC_POLARSELECT
	// 0xd5 - STATIC_PURASELECT

	// 0xd6 - STATIC_ENDDOORS
	// 0xd7 - STATIC_ENDFLASH
	// 0xd8 - STATIC_ENDINGOXIDE
	// 0xd9 - STATIC_ENDIGNOXIDE_02 (mispelled in-game)
	// 0xda - STATIC_ENDOXIDEBIGSHIP
	// 0xdb - STATIC_ENDOXIDELILSHIP

	// 0xdc - STATIC_OXIDECAMEND
	// 0xdd - STATIC_OXIDECAMEND02
	// 0xde - STATIC_JLOGO_FLAG
	// 0xdf - STATIC_OXIDESPEAKER

	// 0xe0 - STATIC_INTROSPARKS
	// 0xe1 - STATIC_GNORMALZ

	// same thing?
	// 0xe1 - AdvHub door signs (above wooden doors)

	// 0xe2 - NUM_TYPES

	// +24EC  8009900C
	struct Driver* drivers[8];

	// +250C  8009902C
	struct Driver* driversInRaceOrder[8];

	//252c
	//this stuct is passed to FUN_8006c684 and updates every frame (this is func with 0xdeadc0ed)
	struct
	{
		//252c
		int unk1;

		//2530
		int unk2;
	} deadcoed_struct;

	// 0x2534
	char final_filler_mostly_null[0x0B];

	// 0x253f,
	// Debug_ToggleNormalSpawn
	// always 1, in normal gameplay
	// set to 0, to immediately spawn at (0,0,0)
	char Debug_ToggleNormalSpawn;

	//2540
	char overlayIndex_LOD;
	char overlayIndex_Threads;
	char overlayIndex_null_notUsed;
	char overlayIndex_EndOfRace;

	// 2544
	int unk_filler_between_OvrIndex_levIDs;

	// 2548
	// records if hub was swapped at least once,
	// useless really
	short boolHubSwapped;

	// 254a
	short activeMempackIndex; // 0,1,2

	// 254c
	// for swapping adv hubs, async,
	// index 0,3 are not used,
	// index 1,2 are used
	short levID_in_each_mempack[4];

	// 2554
	int unk_filler_between_levIDs_winnerIndex;

	// 2558,
	int winnerIndex[4];

	// 2568
	unsigned int numWinners;

	//256c
	//uint bitwise rendering flags, controls rendering flow. checked a lot in FUN_80035e70, which is game drawing func

	//00000001 - draw lev
	//00000002 - draw rain
	//00000004 - draw confetti
	//00000008 - draw stars
	//00000010 - "rain pool" -- red beaker
	//00000020 - execute RenderBucket (draw instances)

	//00000040 - battle mode, player flicker on damage, etc
	// what? no it's not, happens in Cortex Castle Arcade

	//00000080 - wheels on karts
	//00000100 - draw model to texture low res lod in 2p-4p
	//00000200 - draw particles (fire, smoke)
	//00000400 - draw shadow
	//00000800 - draw heat effect
	//00001000 - draw checkered flag
	//00002000 - clear back buffer between frames
	//00004000 - ?
	//00008000 - Draw 2D lines between multiplayer
	//				screens, plus screen outline (battle)

	//rest unknown or no visible effects
	unsigned int renderFlags;

	//2570
	//bit0 enabled clock effect, rest does nothing visually
	unsigned short clockEffectEnabled;

	// =======================================
	// =======================================

	// all this is in 233 overlay,
	// all podium related?

	//2572
	unsigned short podiumRewardID;

	//2574
	unsigned char bool_AdvHub_NeedToSwapLEV;

	//2575
	unsigned char podium_modelIndex_First;
	unsigned char podium_modelIndex_Second;
	unsigned char podium_modelIndex_Third;

	//2578
	unsigned char podium_modelIndex_tawna;


	// transition from podium overlay to
	// adv hub overlay, controls thread spawns

	//2579
	// 2 or 3 -- request overlay load
	// 1 - spawn lev threads with 232
	// 0 - null
	unsigned char overlayTransition;

	// =======================================
	// =======================================

	//257a
	//only updated for human players
	unsigned char humanPlayerPositions[8];

	//2582
	// determines if you see Oxide Intro,
	// or Demo Mode, from main menu inactivity
	unsigned short boolSeenOxideIntro;

	//2584 (end of UsaRetail)

	// not in UsaRetail
	#if BUILD >= JpnTrial

	// 2584
	struct
	{
	// Will not draw in ePSXe, emu bug.
	// should draw while transitioning hubs

	// draws max of 0x5a (90) frames (3 sec)
	int countdown_ThreeSeconds;

	// 2588
	int lngIndex_AdvHubName;

	} AdvHubTitle_3Seconds;

	// 258C (end of jpnTrial)
	#endif
};

#if BUILD == SepReview
_Static_assert(sizeof(struct GameTracker) == 0x24F8);
#elif BUILD == UsaRetail
_Static_assert(sizeof(struct GameTracker) == 0x2584);
#elif BUILD == JpnTrial
_Static_assert(sizeof(struct GameTracker) == 0x258C);
#elif BUILD >= EurRetail
_Static_assert(sizeof(struct GameTracker) == 0x2594);
#endif