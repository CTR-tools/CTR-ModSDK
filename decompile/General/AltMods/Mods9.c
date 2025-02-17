
// ==== Contains Profiler and Debug Menu ====

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

// No room, need MEMPACK_AllocMem
// static struct ProfilerSection sections[64];
struct ProfilerSection* ptrSectArr=0;
struct ProfilerSection* ptrOpenSect=0;

// No room, use global PrimMem instead,
// especially since we have PrimMem expansion
// POLY_F4 polyArrF4[128];

static int numSectionsUsed = 0;

int Debug_GetPreciseTime()
{
	int sysClock =
		GetRCnt(0xf2000001) +
		sdata->rcntTotalUnits;
		
	return sysClock;
}

void DebugProfiler_Init()
{
	int size = sizeof(struct ProfilerSection) * 64;
	ptrSectArr = DECOMP_MEMPACK_AllocMem(size);
}

void DebugProiler_Reset()
{
	// normally happens in DebugMenu_DrawMenuTwice,
	// debug menu is not implemented in retail yet
	numSectionsUsed = 0;
}

void DebugProfiler_SectionStart(char* name, char r, char g, char b)
{
	if(numSectionsUsed >= 64)
	{
		printf("Out of sections\n");
		while(1) {}
	}
	
	if(ptrOpenSect != 0)
	{
		printf("Another section is open\n");
		while(1) {}
	}
	
	struct ProfilerSection* s = 
		&ptrSectArr[numSectionsUsed];
	
	ptrOpenSect = s;
	
	ptrOpenSect->r = r;
	ptrOpenSect->g = g;
	ptrOpenSect->b = b;
	ptrOpenSect->a = 0;
	
	ptrOpenSect->flagsVDT = 0;
	
	ptrOpenSect->timeStart = Debug_GetPreciseTime();
}

void DebugProfiler_Subsection(int flag)
{
	if(ptrOpenSect == 0)
		return;

	ptrOpenSect->flagsVDT |= flag;
	
	int time = Debug_GetPreciseTime();
	
	if((flag & 1) != 0)
	{
		ptrOpenSect->posV = time;
	}
	
	if((flag & 2) != 0)
	{
		ptrOpenSect->posD = time;
	}
	
	#if 0
	if((flag & 2) != 0)
	{
		ptrOpenSect->posT = time;
	}
	#endif
}

void DebugProfiler_SectionRestart(int time)
{
	if(ptrOpenSect == 0)
		return;
	
	ptrOpenSect->timeStart = time;
}

void DebugProfiler_SectionEnd()
{
	if(ptrOpenSect == 0)
		return;
	
	ptrOpenSect->timeEnd = Debug_GetPreciseTime();
	ptrOpenSect = 0;
	
	numSectionsUsed++;
}

int DebugProfiler_Scale(int input)
{
	int cFS = sdata->gGT->clockFrameStart; 
	
	int scaledInput = (input * 1000) / 0x147e;
	int relativeToStart = scaledInput - cFS;
	int scaledGraph = ((relativeToStart * 0x104) / 100) + 0x14;
	
	return scaledGraph;
}

void DebugProfiler_Draw()
{
	struct GameTracker* gGT = sdata->gGT;
	
	struct PrimMem* primMem = &gGT->backBuffer->primMem;
	
	// must be room for 100 POLY_F4s
	POLY_F4* test = primMem->curr;
	test = test + 100;
	if(test > primMem->endMin100) return;
	
	void* ot = gGT->pushBuffer_UI.ptrOT;
	
	for(int i = 0; i < numSectionsUsed; i++)
	{
		struct ProfilerSection* s = &ptrSectArr[i];
		
		if((s->flagsVDT & 1) != 0)
		{
			DECOMP_DecalFont_DrawLine("V", 
				DebugProfiler_Scale(s->posV),
				0x2F,
				FONT_BIG,
				0xffff8000);
		}
		
		if((s->flagsVDT & 2) != 0)
		{
			DECOMP_DecalFont_DrawLine("D", 
				DebugProfiler_Scale(s->posD),
				0x2B,
				FONT_BIG,
				0xffff8000);
		}
		
		#if 0
		if((s->flagsVDT & 4) != 0)
		{
			DECOMP_DecalFont_DrawLine("T", 
				DebugProfiler_Scale(s->posT),
				0x33,
				FONT_BIG,
				0xffff8000);
		}
		#endif
		
		POLY_F4* f4 = primMem->curr;
		primMem->curr = f4 + 1;
		
		f4->r0 = s->r;
		f4->g0 = s->g;
		f4->b0 = s->b;
		
		setPolyF4(f4);
		
		int posLeft = DebugProfiler_Scale(s->timeStart);
		int posRight = DebugProfiler_Scale(s->timeEnd) + 1;
		
		f4->x0 = posLeft;
		f4->x2 = posLeft;
		
		f4->x1 = posRight;
		f4->x3 = posRight;
		
		f4->y0 = 0x28;
		f4->y1 = 0x28;
		f4->y2 = 0x40;
		f4->y3 = 0x40;
		
		AddPrim(ot, f4);
	}
}

// === End of DebugProfiler ===

// === Start of DebugMenu ===

void DebugMenu_LoadGame_GivenLevelId(struct GameTracker* gGT, int levelID)
{
	gGT->levelID = levelID;
	DECOMP_MainRaceTrack_RequestLoad(gGT->levelID);
}

void DebugMenu_LoadGame_GivenIndexE3(struct GameTracker* gGT, int index)
{
	/*
		Row 1: 1P Dingo Canyon, P1 Crash
		Row 2: 1P Crash Cove, P1 Coco
		Row 3: 1P Blizzard Bluff, P1 Tiny
		Row 4: 1P Tiger Temple, P1 Polar
		Row 5: 1P Papu Pyramid, P1 Cortex
		Row 6: 2P Papu Pyramid, drivers are Crash, Cortex, Tiny, Coco, NGin, Dingo (standard 2 players 4 AIs)
		Row 7: 4P Tiger Temple, Crash Cortex Tiny Coco
		Row 8: 4P Blizzard Bluff, Crash Cortex Tiny Coco
	*/
	
	DECOMP_MainRaceTrack_RequestLoad(gGT->levelID);
}

// Set by menu
static int debugPlayerIndex = 0;

void DebugMenu_LoadGame_GivenCharacterId(struct GameTracker* gGT, int charID)
{
	data.characterIDs[debugPlayerIndex] = charID;
	DECOMP_MainRaceTrack_RequestLoad(gGT->levelID);
}

void DebugMenu_LoadGame_GivenNumPlyr(struct GameTracker* gGT, int numPlyr)
{
	gGT->numPlyrNextGame = numPlyr;
	DECOMP_MainRaceTrack_RequestLoad(gGT->levelID);
}

void DebugMenu_SetLapCount(struct GameTracker* gGT, int numLaps)
{
	gGT->numLaps = numLaps;
}

static int debugModeArr[6] =
{
	ADVENTURE_MODE,
	ADVENTURE_MODE | ADVENTURE_ARENA,
	TIME_TRIAL,
	BATTLE_MODE,
	ARCADE_MODE,
	0x0, // VS mode
};

void DebugMenu_SetGameMode(struct GameTracker* gGT, int index)
{
	int removeBits = ~(
        ADVENTURE_MODE |
        ADVENTURE_ARENA |
        TIME_TRIAL |
        BATTLE_MODE |
        ARCADE_MODE
	);
	
	gGT->gameMode1 &= removeBits;
	gGT->gameMode1 |= debugModeArr[index];
};

struct DebugRow;

struct DebugMenu
{
	struct DebugMenu* parentMenu;
	struct DebugRow* rowArr;
	int unk1;
	
	short posX;
	short posY;
	short sizeX;
	short sizeY;
	
	// RowArray[0]
};

struct DebugRow
{
	// & 0 -> null terminator
	// & 1 -> leads to submenu
	// & 3 -> run function
	int actionFlag;
	
	// levelID, characterID, etc
	int actionParam;
	
	char* rowText;
	
	union
	{
		// & 1
		struct DebugMenu* subMenu;
		
		// & 3
		int funcPtr;
	};
};

// June 1999
// 80083788 - Levels/Players Menu
// 80082b10 - Levels submenu
// 8008314c - Players submenu