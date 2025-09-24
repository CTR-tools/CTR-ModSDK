#ifdef REWRITE_PROFILER

#include <ctr/profiler.h>
#include <ctr/nd.h>

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

void ND_EnterCriticalSection();
void ND_ExitCriticalSection();

void ND_DrawOTag(int a);
void ND_DecalFont_DrawLine(char* a, int b, int c, int d, int e);

int ND_GetRCnt(int a);
int ND_ResetRCnt(int a);

// OG = Original
// RW = Rewrite
int timeOG_COLL_ProjectPointToEdge;
int timeRW_COLL_ProjectPointToEdge;

#define JMP(dest) (((unsigned long)dest & 0x3FFFFFF) >> 2 | 0x8000000)
#define JAL(dest) (((unsigned long)dest & 0x3FFFFFF) >> 2 | 0xC000000)

void Hook_DrawOTag(int a);
void RunCollOG();
void RunCollRW();

// When running OG functions,
// dont forget to undefine these in ctr\test.h:
// TEST_MATH_IMPL, TEST_RNG_IMPL, TEST_COLL_IMPL

// Also, required to run RW function before OG,
// because of how assembly hooking system works

void LoadProfilerPatches()
{	
	*(int*)0x800379b0 = JAL(Hook_DrawOTag);
}

int doThisOnce=0;
void RunAllBenchmarks()
{
	if(doThisOnce != 0)
		return;
	
	int r = 0;
	doThisOnce = 1;
	
	ND_ResetRCnt(0xf2000001);
	RunCollRW();
	r = ND_GetRCnt(0xf2000001);
	timeRW_COLL_ProjectPointToEdge = r;
	
	ND_ResetRCnt(0xf2000001);
	RunCollOG();
	r = ND_GetRCnt(0xf2000001);
	timeOG_COLL_ProjectPointToEdge = r;
}

void Hook_DrawOTag(int a)
{
	ND_EnterCriticalSection();
	RunAllBenchmarks();
	ND_ExitCriticalSection();

	// Why does this break on console?
	// struct GameTracker* gGT = sdata->gGT;
	struct GameTracker* gGT = (struct GameTracker*)0x80096b20;
	
	if((gGT->gameMode1 & (LOADING|1)) == 0)
	{
		// reset depth to CLOSEST
		gGT->pushBuffer_UI.ptrOT =
			gGT->otSwapchainDB[gGT->swapchainIndex];	

		char string[128];
		
		ND_DecalFont_DrawLine("1s  15720", 0x14, 0x8, FONT_SMALL, 0);
		
		ND_sprintf(string, "RW  %d", timeRW_COLL_ProjectPointToEdge);
		ND_DecalFont_DrawLine(string, 0x14, 0x10, FONT_SMALL, 0);
		
		ND_sprintf(string, "OG  %d", timeOG_COLL_ProjectPointToEdge);
		ND_DecalFont_DrawLine(string, 0x14, 0x18, FONT_SMALL, 0);
	}
	
	ND_DrawOTag(a);
}

#endif