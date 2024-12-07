#include <common.h>

struct MenuRow NewRowsPAUSE[5] =
{
	[0] =
	{
		.stringIndex = 2, // resume
		.rowOnPressUp = 0,
		.rowOnPressDown = 1,
		.rowOnPressLeft = 0,
		.rowOnPressRight = 0,
	},
	
	[1] =
	{
		.stringIndex = 1, // restart
		.rowOnPressUp = 0,
		.rowOnPressDown = 2,
		.rowOnPressLeft = 1,
		.rowOnPressRight = 1,
	},
	
	[2] =
	{
		.stringIndex = 3, // quit
		.rowOnPressUp = 1,
		.rowOnPressDown = 3,
		.rowOnPressLeft = 2,
		.rowOnPressRight = 2,
	},
	
	[3] =
	{
		.stringIndex = 0xE, // options
		.rowOnPressUp = 2,
		.rowOnPressDown = 3,
		.rowOnPressLeft = 3,
		.rowOnPressRight = 3,
	},
	
	[4] =
	{
		.stringIndex = 0xFFFF,
	}
};

void RunInitHook()
{
	unsigned int loop;
	unsigned int loop2;
	unsigned int numBytes;
	short rot[3];
	struct Thread* th;
	struct InstDef* def;
	struct GameTracker* gGT;
	struct BattleGame* bg = 0x8000F000;
	gGT = sdata->gGT;
	
	// for Console only, disable ghosts
	#if 0
	*(int*)0x80027838 = 0x3E00008;
	*(int*)0x8002783C = 0;
	#endif
	
	// set arcade/TT menu to use adv cup rows
	*(unsigned int*)(0x80084510 + 0xC) = NewRowsPAUSE;
	
	// required for AI Nav, cause I dont have
	// offsets [0xA] or [0xC] and it gets stuck
	// in a loop, so this breaks the loop
	*(int*)0x800150c0 = 0;
	
	// this should happen in main menu,
	// but we skip the ghost selection
	if(sdata->ptrGhostTapePlaying == 0)
	{
		SelectProfile_ToggleMode(0x30);
		sdata->boolReplayHumanGhost = 0;
		sdata->ptrGhostTapePlaying = MEMPACK_AllocHighMem(0x3e00);
	}
	
	// wont clear itself?
	sdata->ptrLoadSaveObj = 0;
	
	if(gGT->levelID != 0x14) return;
	
	sdata->ptrActiveMenu = 0;
}

struct MenuRow NewRowsMM[2] =
{
	[0] =
	{
		.stringIndex = 0x4D, // time trial
		.rowOnPressUp = 0,
		.rowOnPressDown = 0,
		.rowOnPressLeft = 0,
		.rowOnPressRight = 0,
	},
	
	[1] =
	{
		.stringIndex = 0xFFFF,
	}
};

struct MenuRow NewRowsEND[3] =
{
	[0] =
	{
		.stringIndex = 4, // retry
		.rowOnPressUp = 0,
		.rowOnPressDown = 1,
		.rowOnPressLeft = 0,
		.rowOnPressRight = 0,
	},
	
	[1] =
	{
		.stringIndex = 3, // quit
		.rowOnPressUp = 0,
		.rowOnPressDown = 1,
		.rowOnPressLeft = 1,
		.rowOnPressRight = 1,
	},
	
	[2] =
	{
		.stringIndex = 0xFFFF,
	}
};

void RunUpdateHook()
{
	unsigned int loop;
	unsigned int loop2;
	short rot[3];
	struct GameTracker* gGT;
	struct Driver* d;
	struct QuadBlock* firstQuad;
	struct BattleGame* bg = 0x8000F000;
	gGT = sdata->gGT;
	firstQuad = gGT->level1->ptr_mesh_info->ptrQuadBlockArray;

	// main menu
	if(sdata->ptrActiveMenu == &D230.menuMainMenu)
	{
		sdata->ptrActiveMenu->rows = &NewRowsMM[0];
	}
	
	// time trial end of race
	if(
		(sdata->ptrActiveMenu == 0x800a0458) ||
		(sdata->ptrActiveMenu == 0x800A04A4)
	  )
	{
		sdata->ptrActiveMenu->rows = &NewRowsEND[0];
	}
	
	if(gGT->levelID != 0x14) return;
	
	// TT_EndEvent_DrawHighScore - JR RA
	*(int*)0x8009f8c0 = 0x3E00008;
	*(int*)0x8009f8c4 = 0;
	
	// disable end-of-race high score saving,
	// but &1 is needed for the ghosts to work
	gGT->unknownFlags_1d44 = 1;

	#if 0
	d = gGT->drivers[0];
	
	// get AI Nav data
	printf("{.pos = {%d,%d,%d},.rot={%d,%d,%d,%d}},\n",
		d->posCurr[0]/256, d->posCurr[1]/256, d->posCurr[2]/256,
		d->rotCurr.x/16, d->rotCurr.y/16, d->rotCurr.z/16, d->rotCurr.w/16);
	#endif

	// this gets triggered by the injector
	if(*(int*)0x8000c000 == 1)
	{
		while(!ReadyToContinue(2)) {}
		
		void FakeVramCallback();
		FakeVramCallback();

		// finished uploading
		*(int*)0x8000c000 = 3;
		while(!ReadyToContinue(4)) {}
	
		gGT->visMem1 = gGT->level1->visMem;
		gGT->visMem2 = gGT->visMem1;
		
		*(int*)0x8000c000 = 0;
	}
}

__attribute__((optimize("O0")))
int ReadyToContinue(int x)
{
	return *(int*)0x8000c000 == x;
}

void FakeVramCallback()
{
	int* vramBuf = 0x80200000;
	struct VramHeader* vh = vramBuf;
	
	// if multiple TIMs are packed together
	if(vramBuf[0] == 0x20)
	{
		int size = vramBuf[1];
		vh = &vramBuf[2];
		
		while(size != 0)
		{	
			LoadImage(&vh->rect, VRAMHEADER_GETPIXLES(vh));
			
			vramBuf = (int*)vh;
			vramBuf = &vramBuf[size>>2];
			size = vramBuf[0];
			vh = &vramBuf[1];
		}
	}
	
	// if just one TIM
	else
	{
		LoadImage(&vh->rect, VRAMHEADER_GETPIXLES(vh));
	}
}