#include <ctr/profiler.h>
#include <ctr/nd.h>

#ifdef REWRITE_PROFILER

// No Vehicle.h
struct MetaPhys
{
	// assume USA build
	char* name;
	int offset;
	int size;
	int value[4];
};

// block the including of common.h via inheritance
#define COMMON_H
#include <gccHeaders.h>
#include <macros.h>
#include <prim.h>
#include <namespace_Bots.h>
#include <namespace_Camera.h>
#include <namespace_Cdsys.h>
#include <namespace_Coll.h>
#include <namespace_Decal.h>
#include <namespace_Display.h>
#include <namespace_Gamepad.h>
#include <namespace_Ghost.h>
#include <namespace_Howl.h>
#include <namespace_Instance.h>
#include <namespace_Level.h>
#include <namespace_List.h>
#include <namespace_JitPool.h>
#include <namespace_Load.h>
#include <namespace_Memcard.h>
#include <namespace_Mempack.h>
#include <namespace_Particle.h>
#include <namespace_Proc.h>
#include <namespace_PushBuffer.h>
#include <namespace_RectMenu.h>
#include <namespace_Main.h>
#include <namespace_UI.h>
#include <regionsEXE.h>

void ND_DrawOTag(int a);
void ND_DecalFont_DrawLine(char* a, int b, int c, int d, int e);


int ND_GetRCnt(int a);

int Debug_GetPreciseTime()
{
	int sysClock =
		ND_GetRCnt(0xf2000001) +
		sdata->rcntTotalUnits;

	return sysClock;
}

// Jam this here, cause byte budget
static int timeRed=0;
static int timeStart=0;
static int timeEnd=0;
void Hook_DrawOTag(int a)
{
	// Calculate ONE time, then save persistently
	if (timeRed == 0)
	{
		timeStart = Debug_GetPreciseTime();

		void RunBenchmark();
		RunBenchmark();

		timeEnd = Debug_GetPreciseTime();


		timeRed = timeEnd - timeStart;
	}

	struct GameTracker* gGT = sdata->gGT;

	if((gGT->gameMode1 & (LOADING|1)) == 0)
	{
		// reset depth to CLOSEST
		gGT->pushBuffer_UI.ptrOT =
			gGT->otSwapchainDB[gGT->swapchainIndex];


		#ifndef REBUILD_PC
		char* string = (char*)0x1f800000;
		#else
		char string[128];
		#endif

		ND_sprintf(string, "RED  %d", timeRed);
		ND_DecalFont_DrawLine(string, 0x14, 0x5C, FONT_SMALL, 0);
	}

	ND_DrawOTag(a);
}

#define JMP(dest) (((unsigned long)dest & 0x3FFFFFF) >> 2 | 0x8000000)
#define JAL(dest) (((unsigned long)dest & 0x3FFFFFF) >> 2 | 0xC000000)

void LoadProfilerPatches()
{
	*(int*)0x800379b0 = JAL(Hook_DrawOTag);
}

#endif // REWRITE_PROFILER