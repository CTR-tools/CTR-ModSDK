#include <common.h>
#include "trackSpecificData.h"

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
	
	d = gGT->drivers[0];
	
	#if 0
	// get AI Nav data
	printf("{.pos = {%d,%d,%d},.rot={%d,%d,%d,%d}},\n",
		d->posCurr[0]/256, d->posCurr[1]/256, d->posCurr[2]/256,
		d->rotCurr.x/16, d->rotCurr.y/16, d->rotCurr.z/16, d->rotCurr.w/16);
	#endif
	
	// top 180-degree U-turn with 4 turbos,
	// make them double-sided or single-sided
	
	// while on top of the surface, disable double-sided quads
	if(d->posCurr[2] > 0x1D0000)
	{
		for(loop = Bsp3_FlatTop1; loop <= Bsp3_FlatTop7; loop++)
			firstQuad[loop].draw_order_low &= ~(0x80000000);
	
		for(loop = Bsp1_TurnLeft1; loop <= Bsp1_TurnBack10; loop++)
			firstQuad[loop].draw_order_low &= ~(0x80000000);
	}
	
	// not on top of the surface, enable double-sided quads
	else
	{
		for(loop = Bsp3_FlatTop1; loop <= Bsp3_FlatTop7; loop++)
			firstQuad[loop].draw_order_low |= 0x80000000;
	
		for(loop = Bsp1_TurnLeft1; loop <= Bsp1_TurnBack10; loop++)
			firstQuad[loop].draw_order_low |= 0x80000000;
	}
	
	if(d->posCurr[0] > 0x30000)
	{
		for(loop = Bsp2_FirstBlock; loop <= Bsp2_Last; loop++)
			firstQuad[loop].draw_order_low &= ~(0x80000000);
		
		for(loop = Bsp4_FirstBlock; loop <= Bsp4_Last; loop++)
			firstQuad[loop].draw_order_low &= ~(0x80000000);
		
		for(loop = Bsp0_BehindStart1; loop <= Bsp0_UpRamp8_Turbo_1840; loop++)
			firstQuad[loop].draw_order_low |= 0x80000000;
	}
	
	else
	{
		for(loop = Bsp2_FirstBlock; loop <= Bsp2_Last; loop++)
			firstQuad[loop].draw_order_low |= 0x80000000;	
		
		for(loop = Bsp4_FirstBlock; loop <= Bsp4_Last; loop++)
			firstQuad[loop].draw_order_low |= 0x80000000;	

		for(loop = Bsp0_BehindStart1; loop <= Bsp0_UpRamp8_Turbo_1840; loop++)
			firstQuad[loop].draw_order_low &= ~(0x80000000);	
	}
}

