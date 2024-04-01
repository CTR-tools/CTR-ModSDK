#include <common.h>

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
	
	// set battle menu to use adv cup rows
	*(unsigned int*)(0x80084474 + 0xC) = 0x800844A0;
	
	// required for AI Nav, cause I dont have
	// offsets [0xA] or [0xC] and it gets stuck
	// in a loop, so this breaks the loop
	*(int*)0x800150c0 = 0;
	
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
	if(sdata->ptrActiveMenu == 0x800A04A4)
	{
		sdata->ptrActiveMenu->rows = &NewRowsEND[0];
	}
	
	if(gGT->levelID != 0x14) return;
	
	// TT_EndEvent_DrawHighScore - JR RA
	*(int*)0x8009f8c0 = 0x3E00008;
	*(int*)0x8009f8c4 = 0;
}