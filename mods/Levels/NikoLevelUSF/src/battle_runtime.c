#include <common.h>
#include "trackSpecificData.h"

struct Instance* INSTANCE_Birth3D(struct Model* m, char* name, struct Thread* t);
void ConvertRotToMatrix(MATRIX* m, short* rot);

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
	
	// set battle menubox to use adv cup rows
	*(unsigned int*)(0x80084474 + 0xC) = 0x800844A0;
	
	if(gGT->levelID != 0x14) return;
	
	sdata->ptrActiveMenuBox = 0;
}

struct MenuRow NewRowsMM[2] =
{
	[0] =
	{
		.stringIndex = 0x4D, // time trial
		.rowOnPressUp = 0,
		.rowOnPressDown = 1,
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
	if(sdata->ptrActiveMenuBox == &OVR_230.menubox_mainMenu)
	{
		sdata->ptrActiveMenuBox->rows = &NewRowsMM[0];
	}
	
	// battle end of race
	if(sdata->ptrActiveMenuBox == 0x800A01B4)
	{
		sdata->ptrActiveMenuBox->rows = &NewRowsEND[0];
	}
	
	if(gGT->levelID != 0x14) return;
	
	d = gGT->drivers[0];
	
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
		for(loop = Bsp1_StraightWay1; loop <= Bsp2_Last; loop++)
			firstQuad[loop].draw_order_low &= ~(0x80000000);
		
		for(loop = Bsp0_BehindStart1; loop <= Bsp0_UpRamp8_Turbo_1840; loop++)
			firstQuad[loop].draw_order_low |= 0x80000000;
	}
	
	else
	{
		for(loop = Bsp1_StraightWay1; loop <= Bsp2_Last; loop++)
			firstQuad[loop].draw_order_low |= 0x80000000;	

		for(loop = Bsp0_BehindStart1; loop <= Bsp0_UpRamp8_Turbo_1840; loop++)
			firstQuad[loop].draw_order_low &= ~(0x80000000);	
	}
}

