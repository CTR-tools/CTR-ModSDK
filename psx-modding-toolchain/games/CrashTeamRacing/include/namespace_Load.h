enum LevelID
{
	DINGO_CANYON=0, // 0.
	DRAGON_MINES=1, // 1.
	BLIZZARD_BLUFF,
	CRASH_COVE,
	TIGER_TEMPLE,
	PAPU_PYRAMID,
	ROO_TUBES,
	HOT_AIR_SKYWAY,
	SEWER_SPEEDWAY,
	MYSTERY_CAVES,
	CORTEX_CASTLE,
	N_GIN_LABS,
	POLAR_PASS,
	OXIDE_STATION,
	COCO_PARK,
	TINY_ARENA,
	SLIDE_COLISEUM,
	TURBO_TRACK,
	NITRO_COURT, // 18.
	RAMPAGE_RUINS,
	PARKING_LOT,
	SKULL_ROCK,
	THE_NORTH_BOWL,
	ROCKY_ROAD,
	LAB_BASEMENT,
	GEM_STONE_VALLEY, // 25.
	N_SANITY_BEACH,
	THE_LOST_RUINS,
	GLACIER_PARK,
	CITADEL_CITY,
	INTRO_RACE_TODAY, // 30.
	INTRO_COCO,
	INTRO_TINY,
	INTRO_POLAR,
	INTRO_DINGODILE,
	INTRO_CORTEX,
	INTRO_SPACE,
	INTRO_CRASH,
	INTRO_OXIDE,
	MAIN_MENU_LEVEL, // 39.
	ADVENTURE_CHARACTER_SELECT, // 40.
	NAUGHTY_DOG_CRATE, // 41.
	OXIDE_ENDING,
	OXIDE_TRUE_ENDING,
	CREDITS_LEVEL, // 44.
	CREDITS_CRASH,
	CREDITS_TINY,
	CREDITS_COCO,
	CREDITS_N_GIN,
	CREDITS_DINGO,
	CREDITS_POLAR,
	CREDITS_PURA,
	CREDITS_PINSTRIPE,
	CREDITS_PAPU,
	CREDITS_ROO,
	CREDITS_JOE,
	CREDITS_TROPY,
	CREDITS_PENTA,
	CREDITS_FAKE_CRASH,
	CREDITS_OXIDE,
	CREDITS_AMI,
	CREDITS_ISABELLA,
	CREDITS_LIZ,
	CREDITS_MEGUMI,
	SCRAPBOOK // 64.
};


struct BigEntry
{
	int offset;
	int size;
};

struct BigHeader
{
	int cdpos;
	int numEntry;

	// "numEntry" number of entries
	struct BigEntry entry[1];
};

struct LoadQueueSlot {

	// 0x0
	struct BigHeader* ptrBigfileCdPos;

	// 0x4
	unsigned short flags;

	// 0x6
	unsigned short type;

	// 0x8
	unsigned int subfileIndex;

	// 0xC
	void* ptrDestination;

	// 0x10
	unsigned int size;

	// 0x14
	union
	{
		// last 4 bytes will either be a function pointer,
		// or a flag that signifies there is no function pointer

		void (*funcPtr)(struct LoadQueueSlot*);

		unsigned int flags;

	} callback;
};