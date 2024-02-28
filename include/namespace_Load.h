enum BigIndex
{
	// 1p, 2p, 4p, relic
	BI_ARCADETRACKS = 0,
	
	// 1p, 2p, 3p, 4p
	BI_BATTLETRACKS = BI_ARCADETRACKS + (18*8),
	
	// lev, vrm, ptr
	BI_ADVENTUREHUB = BI_BATTLETRACKS + (7*8),
	
	// lev, vrm (menu_models, adv garage, jpnfont)
	BI_MAINMENUFILE = BI_ADVENTUREHUB + (5*3),
	
	// 221-233
	BI_OVERLAYSECT1 = BI_MAINMENUFILE + 6,
	BI_OVERLAYSECT2 = BI_OVERLAYSECT1 + 5,
	BI_OVERLAYSECT3 = BI_OVERLAYSECT2 + 4,
	
	// LNG for english, french, etc
	BI_LANGUAGEFILE = BI_OVERLAYSECT3 + 4,
	
	// 0x110 for sep3
	// 0xf2 for all Retails
	BI_RACERMODELHI = BI_LANGUAGEFILE + 8,
	
	BI_SHAREDMPKVRM = BI_RACERMODELHI + 16,
	
	BI_1PARCADEPACK = BI_SHAREDMPKVRM + 2,
	
	BI_ADVENTUREPACK = BI_1PARCADEPACK + 16,
	
	BI_TIMETRIALPACK = BI_ADVENTUREPACK + 16,
	
	BI_RACERMODELMED = BI_TIMETRIALPACK + 16,
	
	BI_2PARCADEPACK = BI_RACERMODELMED + 16,
	
	BI_RACERMODELLOW = BI_2PARCADEPACK + 8,
	
	BI_4PARCADEPACK = BI_RACERMODELLOW + 16,
	
	BI_PODIUMVRMS = BI_4PARCADEPACK + 16,
	
	BI_DANCEMODELWIN = BI_PODIUMVRMS + 2,
	
	BI_DANCEMODELLOSE = BI_DANCEMODELWIN + 16*2,
	
	BI_DANCETAWNAGIRL = BI_DANCEMODELLOSE + 16*2,

	BI_UKAHEAD = BI_DANCETAWNAGIRL + 4*2,
	
	BI_AKUHEAD = BI_UKAHEAD + 2*2,
	
	BI_DINGOFIRE = BI_AKUHEAD + 2*2,
	
	BI_PODIUM = BI_DINGOFIRE + 2,

	BI_BOSSHEAD = BI_PODIUM + 2,
	
	BI_LOSEHEAD = BI_BOSSHEAD + 5*2,

	BI_BOSSBODY = BI_LOSEHEAD + 5*2,

	BI_VLCTABLE = BI_BOSSBODY + 5*2,

	BI_THUMBS = BI_VLCTABLE + 1,

	BI_LOADINGSCREENS = BI_THUMBS + 26,

	BI_NDBOX = BI_LOADINGSCREENS + 6,
	
	BI_CUTSCENES_INTRO = BI_NDBOX + 2,
	
	BI_CUTSCENES_OUTRO = BI_CUTSCENES_INTRO + 9*3,

	BI_CREDITS = BI_CUTSCENES_OUTRO + 2*2,

	BI_SCRAPBOOK = BI_CREDITS + 20*3
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
	//struct BigEntry entry[0];
};
#define BIG_GETENTRY(x) \
	((unsigned int)x + sizeof(struct BigHeader))

struct DramPointerMap
{
	int numBytes;
	
	//int offsets[0];
};

#define DRAM_GETOFFSETS(x) \
	((unsigned int)x + sizeof(struct DramPointerMap))

struct VramHeader
{
	char data[0xC];
	
	// 0xC
	RECT rect;
	
	// 0x14
	//u_char pixels[0];
};

#define VRAMHEADER_GETPIXLES(x) \
	((unsigned int)x + sizeof(struct VramHeader))

enum LevVramIndex
{
	LVI_VRAM = 0,
	LVI_LEV = 1,
	LVI_PTR = 2,
};

enum LoadType
{
	// ordinary read to ram
	LT_RAW = 1,
	
	// read with pointer map at the end
	LT_DRAM = 2,
	
	// read with vram transfer
	LT_VRAM = 3
};

struct LoadQueueSlot
{
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

_Static_assert(sizeof(struct LoadQueueSlot) == 0x18);