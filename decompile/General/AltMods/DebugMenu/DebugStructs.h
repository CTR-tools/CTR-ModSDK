#ifndef DEBUGSTRUCTS
#define DEBUGSTRUCTS

struct ProfilerSection
{
	// 0x0
	char* name;

	// 0x4
	char a;
	char r;
	char g;
	char b;
	
#if 0
	// 0x8
	int unk8;
#endif
	
	// 0xC
	int timeStart;
	
	// 0x10
	int timeEnd;
	
	// 0x14
	// 1 - DrawV
	// 2 - DrawD
	// 4 - DrawT
	int flagsVDT;
	
	// 0x18
	// VSyncCallback
	int posV;
	
	// 0x1c
	// DrawSyncCallback
	int posD;
	
#if 0
	// 0x20
	// Unused
	int posT;
#endif

	// size = 0x20
};

struct DebugRow;

#ifdef REBUILD_PC

// Visual Studio forces
// the reorder, so work around it
#define DMENU_GETROWS(x) \
	(struct DebugRow*)(x->firstRow)

#else

// GCC has no reordering
#define DMENU_GETROWS(x) \
	(struct DebugRow*)((unsigned int)x + sizeof(struct DebugMenu))

#endif

struct DebugMenu
{
	// initialized at runtime
	struct DebugMenu* parentMenu;
	
	#ifdef REBUILD_PC
	struct DebugRow* firstRow;
	#endif
	
	// set by compiler
	struct DebugRow* currRow;
	
	// initialized at runtime
	struct DebugMenu* childMenu;
	
	// This is actually RECT,
	// x,y,w,h
	
	// 0xC
	short posX;
	short posY;
	
	// 0x10
	short sizeX;
	short sizeY;
	
	// RowArray[0]
};

struct DebugRow
{
	// & 0 -> null terminator
	// & 1 -> leads to submenu
	// & 3 -> leads to function
	int actionFlag;
	
	// levelID, characterID, etc
	int actionParam;
	
	char* rowText;
	
	union
	{
		// & 1
		struct DebugMenu* subMenu;
		
		// & 3
		void (*funcDbg)(struct GameTracker* gGT, int param);
	};
};

#endif