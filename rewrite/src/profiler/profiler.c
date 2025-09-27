
#include <ctr/profiler.h>
#include <ctr/nd.h>
#include <ctr/test.h>


#include <gccHeaders.h>
#include <namespace_Display.h>
#include <namespace_PushBuffer.h>

#ifdef TEST_MATH_IMPL
#error Please go to ModSDK/include/ctr/test.h, and disable TEST_MATH_IMPL
#endif

#ifdef TEST_RNG_IMPL
#error Please go to ModSDK/include/ctr/test.h, and disable TEST_RNG_IMPL
#endif

#ifdef TEST_COLL_IMPL
#error Please go to ModSDK/include/ctr/test.h, and disable TEST_COLL_IMPL
#endif

// Required declarations
void ND_EnterCriticalSection();
void ND_ExitCriticalSection();
void ND_DrawOTag(int a);
void ND_DecalFont_DrawLine(char* a, int b, int c, int d, int e);
int ND_GetRCnt(int a);
int ND_ResetRCnt(int a);

struct BenchTest { char* name; void (*funcPtr)(); int val; };
#define ADDTEST(x) {.name = #x, .funcPtr = x, .val = 0}

#include "benchmark.h"

// real ND name
struct GameTracker_Local
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
	
	// 0x160
	char buf[0x1768];
	
	// pointers to OT memory,
	// used in ClearOTagR
	// 0x18c8
	// 0x18cc
	// one for each DB
	void* otSwapchainDB[2];
	
};

void DrawResults()
{
	// avoid header headaches,
	// this is gGT, and gGT->pushBuffer_UI
	struct GameTracker_Local* gGT = (struct GameTracker_Local*)(0x80096b20);
	struct PushBuffer* pb = (struct PushBuffer*)(0x80096b20+0x1388);

	#define LOADING 0x40000000
	if((gGT->gameMode1 & (LOADING|1)) == 0)
	{
		// reset depth to CLOSEST
		pb->ptrOT = gGT->otSwapchainDB[gGT->swapchainIndex];

		char string[128];

		// Draw text centered on-screen
		// 0x100 - midpoint, 0x800 - center
		ND_sprintf(string, "%s    %s", __DATE__, __TIME__);
		ND_DecalFont_DrawLine(string, 0x100, 0x8, 2, 0x8000);
		
		int numTest = sizeof(tests) / sizeof(struct BenchTest);
		
		for(int i = 0; i < numTest; i++)
		{
			ND_sprintf(string, "%s  %d", &tests[i].name[8], tests[i].val);
			ND_DecalFont_DrawLine(string, 0x14, 0x10+(i*8), 2, 0);
		}
	}
}

int testIndex=0;
void RunTest()
{
	int numTest = sizeof(tests) / sizeof(struct BenchTest);
	
	int timer = *(int*)(0x80096b20+0x1cec);
	
	// In between each test, run 15 frames
	if((timer & 0xF) != 0xF)
		return;
	
	if(testIndex < numTest)
	{
		// Stop XA
		void ND_CDSYS_XAPauseForce();
		ND_CDSYS_XAPauseForce();
		
		// From Spyro 2 Demo Launcher
		void ND_Music_Stop();
		void ND_howl_StopAudio(int a, int b, int c);
		void ND_Bank_DestroyAll();
		void ND_howl_Disable();
		
		// From Spyro 2 Demo Launcher
		ND_Music_Stop();
		ND_howl_StopAudio(1,1,1);
		ND_Bank_DestroyAll();
		ND_howl_Disable();
		
		ND_EnterCriticalSection();

		ND_ResetRCnt(0xf2000001);
		ND_printf("%d\n", ND_GetRCnt(0xf2000001));
		tests[testIndex].funcPtr();
		tests[testIndex].val = ND_GetRCnt(0xf2000001);
		ND_printf("%d\n", ND_GetRCnt(0xf2000001));

		ND_ExitCriticalSection();
		
		testIndex++;
	}
}

void Hook_DrawOTag(int a)
{
	DrawResults();
	ND_DrawOTag(a);
	
	// Run first test AFTER first DrawOTag,
	// so it does not take forever for screen to refresh,
	// Therefore, always run a test after DrawOTag
	RunTest();
}

void LoadProfilerPatches()
{
	#define JAL(dest) (((unsigned long)dest & 0x3FFFFFF) >> 2 | 0xC000000)
	*(int*)0x800379b0 = JAL(Hook_DrawOTag);
	
	// JR RA so main menu never loads
	*(int*)0x8003cfc0 = 0x3E00008;
	*(int*)0x8003cfc4 = 0;
	
	// JR RA so RaceFlag does not drawpoly
	*(int*)0x800444e8 = 0x3E00008;
	*(int*)0x800444ec = 0;
	
	// skip XA on boot "Start Your Engines..."
	*(int*)0x8003c958 = 0;
}