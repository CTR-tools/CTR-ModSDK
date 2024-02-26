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
	BI_OVERLAYFILES = BI_MAINMENUFILE + 6,
	
	// LNG for english, french, etc
	BI_LANGUAGEFILE = BI_OVERLAYFILES + 5+4+4,
	
	BI_RACERMODELHI = BI_LANGUAGEFILE + 8,
	
	BI_SHAREDMPKVRM = BI_RACERMODELHI + 16,
	
	BI_1PARCADEPACK = BI_SHAREDMPKVRM + 2,
	
	BI_ADVENTUREPACK = BI_1PARCADEPACK + 16,
	
	BI_TIMETRIALPACK = BI_ADVENTUREPACK + 16,
	
	BI_RACERMODELMED = BI_TIMETRIALPACK + 16,
	
	BI_2PARCADEPACK = BI_RACERMODELMED + 16,
	
	BI_RACERMODELLOW = BI_2PARCADEPACK + 8,
	
	BI_4PARCADEPACK = BI_RACERMODELLOW + 16,
	
	BI_CUTSCENEVRMS = BI_4PARCADEPACK + 16,
	
	BI_DANCEMODELWIN = BI_CUTSCENEVRMS + 2,
	
	BI_DANCEMODELLOSE = BI_DANCEMODELWIN + 16*2,
	
	BI_DANCETAWNAGIRL = BI_DANCEMODELLOSE + 16*2,

	BI_MISCMODELS = BI_DANCETAWNAGIRL + 4*2,

	BI_BOSSHEAD = BI_MISCMODELS + 6*2,

	BI_LOSEHEAD = BI_BOSSHEAD + 5*2,

	BI_BOSSBODY = BI_LOSEHEAD + 5*2,

	BI_VLCTABLE = BI_BOSSBODY + 5*2,

	BI_THUMBS = BI_VLCTABLE + 1,

	BI_LOADINGSCREENS = BI_THUMBS + 26,

	BI_CUTSCENES = BI_LOADINGSCREENS + 6,

	BI_CREDITS = BI_CUTSCENES + 33,

	BI_SCRAPBOOK = BI_CREDITS + 20*3
	
	// up to 606
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