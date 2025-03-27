#include <common.h>
#include "DebugStructs.h"

// June 1999 used 64, reduced for Retail CTR
#define MAX_SECTIONS 32

// No room, need MEMPACK_AllocMem
// static struct ProfilerSection sections[32];
static struct ProfilerSection* ptrSectArr=0;
static struct ProfilerSection* ptrOpenSect=0;

// No room, use global PrimMem instead,
// especially since we have PrimMem expansion
// POLY_F4 polyArrF4[128];

static int numSectionsUsed = 0;

int Debug_GetNumSections()
{
	return numSectionsUsed;
}

int Debug_GetFirstSect()
{
	return ptrSectArr;
}

int Debug_GetPreciseTime()
{
	int sysClock =
		GetRCnt(0xf2000001) +
		sdata->rcntTotalUnits;
		
	return sysClock;
}

struct ProfilerSection* DebugProfiler_GetOpen()
{
	return ptrOpenSect;
}

void DebugProfiler_Init()
{
	ptrSectArr = 0x8000F000;
}

void DebugProfiler_Reset()
{
	// normally happens in DebugMenu_DrawMenuTwice,
	// debug menu is not implemented in retail yet
	numSectionsUsed = 0;
}

void DebugProfiler_SectionStart(char* name, char r, char g, char b)
{
	if(numSectionsUsed >= 32)
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
	bool fakeSectionOpen = 0;
	
	if(sdata->boolPlayVideoSTR == 1)
		return;

	if(ptrOpenSect == 0)
	{
		// dont let fake sections explode on-boot
		if(numSectionsUsed > 20)
			return;
		
		fakeSectionOpen = 1;
		
		void DebugProfiler_SectionStart(char* name, char r, char g, char b);
		DebugProfiler_SectionStart(0, 0xFF, 0xFF, 0xFF);
	}

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
	
	if (fakeSectionOpen)
	{
		int DebugProfiler_SectionEnd();
		DebugProfiler_SectionEnd();
	}
}

void DebugProfiler_SectionRestart(int time)
{
	if(ptrOpenSect == 0)
		return;
	
	ptrOpenSect->timeStart = time;
}

int DebugProfiler_SectionEnd()
{
	if(ptrOpenSect == 0)
		return 0;
	
	ptrOpenSect->timeEnd = Debug_GetPreciseTime();
	
	int ret = ptrOpenSect->timeEnd - ptrOpenSect->timeStart;
	
	ptrOpenSect = 0;
	numSectionsUsed++;
	
	return ret;
}

int DebugProfiler_Scale(int input)
{
	int cFS = sdata->gGT->clockFrameStart; 
	
	int scaledInput = (input * 1000) / 0x147e;
	int relativeToStart = WIDE_34(scaledInput - cFS);
	int scaledGraph = ((relativeToStart * 0x104) / 100) + 0x14;
	
	return scaledGraph;
}

void DebugProfiler_Draw()
{
	void DebugProfiler_ListAllDebugStats();
	DebugProfiler_ListAllDebugStats();
	
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
			DecalFont_DrawLine("V", 
				DebugProfiler_Scale(s->posV),
				0x2F,
				FONT_BIG,
				0xffff8000);
		}
		
		if((s->flagsVDT & 2) != 0)
		{
			DecalFont_DrawLine("D", 
				DebugProfiler_Scale(s->posD),
				0x2B,
				FONT_BIG,
				0xffff8000);
		}
		
		#if 0
		if((s->flagsVDT & 4) != 0)
		{
			DecalFont_DrawLine("T", 
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

// Jam this here, cause byte budget
static int timeFrame;
static int timeCpu;
static int timeGpu;
static int timeRed;
static int timeGreen;
static int timeBlue;

void DebugProfiler_ListAllDebugStats()
{
	if((sdata->gGT->gameMode1 & DEBUG_MENU) != 0)
		return;
	
	int Debug_GetNumSections();
	int numSectionsUsed = Debug_GetNumSections();
	
	int Debug_GetFirstSect();
	struct ProfilerSection* ptrSectArr = Debug_GetFirstSect();
	
	if((sdata->gGT->timer & (FPS_DOUBLE(16)-1)) == 0)
	{
		timeFrame =
			ptrSectArr[numSectionsUsed-1].timeEnd -
			ptrSectArr[0].timeStart;
			
		timeCpu =
			ptrSectArr[numSectionsUsed-2].timeEnd -
			ptrSectArr[0].timeStart;
			
		for(int i = 0; i < numSectionsUsed; i++)
		{
			if((ptrSectArr[i].flagsVDT & 2) != 0)
			{
				timeGpu = 
					ptrSectArr[i].posD -
					ptrSectArr[0].timeStart;
			}
			
			if(*(int*)&ptrSectArr[i].a == 0xff00)
			{
				timeRed =
					ptrSectArr[i].timeEnd -
					ptrSectArr[i].timeStart;
			}
			
			if(*(int*)&ptrSectArr[i].a == 0xff0000)
			{
				timeGreen =
					ptrSectArr[i].timeEnd -
					ptrSectArr[i].timeStart;
			}
			
			if(*(int*)&ptrSectArr[i].a == 0xff000000)
			{
				timeBlue =
					ptrSectArr[i].timeEnd -
					ptrSectArr[i].timeStart;
			}
		}
	}
	
	if(timeFrame == 0) return;
	if(timeCpu == 0) return;
	if(timeGpu == 0) return;
	if(timeRed == 0) return;
	if(timeGreen == 0) return;
	if(timeBlue == 0) return;
	
	#ifndef REBUILD_PC
	char* string = 0x1f800000;
	#else
	char string[128];
	#endif

	// Time units:
	// 262 -> 1 vsync (60fps)
	// 524 -> 2 vsync (30fps)
	// 15720 -> 1 full second

	sprintf(string, "FULL %d %dFPS", timeFrame, 15720/timeFrame);
	DecalFont_DrawLine(string, 0x14, 0x44, FONT_SMALL, 0);
	
	sprintf(string, "CPU  %d %dFPS", timeCpu, 15720/timeCpu);
	DecalFont_DrawLine(string, 0x14, 0x4C, FONT_SMALL, 0);
	
	sprintf(string, "GPU  %d %dFPS", timeGpu, 15720/timeGpu);
	DecalFont_DrawLine(string, 0x14, 0x54, FONT_SMALL, 0);
	
	sprintf(string, "RED  %d", timeRed);
	DecalFont_DrawLine(string, 0x14, 0x5C, FONT_SMALL, 0);
	
	sprintf(string, "GREN %d", timeGreen);
	DecalFont_DrawLine(string, 0x14, 0x64, FONT_SMALL, 0);
	
	sprintf(string, "BLUE %d", timeBlue);
	DecalFont_DrawLine(string, 0x14, 0x6C, FONT_SMALL, 0);
}

void DebugProfiler_DrawOTag()
{
	// VSYNC Profiler
	int DebugProfiler_SectionEnd();
	DebugProfiler_SectionEnd();
	
	struct GameTracker* gGT = sdata->gGT;
	
	if((gGT->gameMode1 & (LOADING|1)) == 0)
	{
		// reset depth to CLOSEST
		gGT->pushBuffer_UI.ptrOT =
			gGT->otSwapchainDB[gGT->swapchainIndex];
		
		void DebugProfiler_Draw();
		DebugProfiler_Draw();
		
		#if 0
		void DebugMenu_DrawIfOpen();
		DebugMenu_DrawIfOpen();
		#endif
	}
}

void RunEntryHook()
{
	// 4P 1 pad: Set 800255c4 to 1-byte 0x04
	
	// Find each by breakpointing function,
	// then find $ra and go back 2 instructions
	
	// [JAL hook] 	[RaceFlag_DrawSelf] 	(pink start/end)
	// [unk]								(black stall start)
	// [JAL hook]	[RenderBucket_Execute]	(green start/end)
	// [JAL hook]	[CTR_ClearRenderLists_1P2P]	(blue start) -- 1p
	// [JAL hook]	[CTR_ClearRenderLists_1P2P]	(blue start) -- 2p
	// [JAL hook]	[CTR_ClearRenderLists_3P4P]	(blue start) -- 3p
	// [JAL hook]	[CTR_ClearRenderLists_3P4P]	(blue start) -- 4p
	// [JAL hook]	[DrawSky_Full]			(blue end) -- 1p
	// [JAL hook]	[227]					(blue end) -- 2p
	// [JAL hook]	[228]					(blue end) -- 3p
	// [JAL hook]	[229]					(blue end) -- 4p
	// [JAL hook]	[DrawOTag]				(black end)
	// [JAL hook]	[MainFrame_GameLogic]	(red start/end)
}