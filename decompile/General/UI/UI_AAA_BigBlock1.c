#include <common.h>

#include "UI_DrawPosSuffix.c"
#include "UI_DrawLapCount.c"
#include "UI_DrawBattleScores.c"
#include "UI_Weapon_DrawSelf.c"
#include "UI_Weapon_DrawBG.c"
#include "UI_DrawNumWumpa.c"
#include "UI_DrawNumKey.c"
#include "UI_DrawNumRelic.c"
#include "UI_DrawNumTrophy.c"
#include "UI_DrawNumCrystal.c"
#include "UI_DrawNumTimebox.c"
#include "UI_DrawSpeedBG.c"
#include "UI_DrawSpeedNeedle.c" 
#include "UI_JumpMeter_Draw.c"
#include "UI_JumpMeter_Update.c" 
#include "UI_DrawSlideMeter.c"
#include "UI_DrawRankedDrivers.c"
#include "UI_RenderFrame_Racing.c"
#include "UI_RenderFrame_AdvHub.c"
#include "UI_RenderFrame_CrystChall.c"

// This wont fit inside UI_Map_DrawMap
// function that calculates and sets the width of both minimap primitives and alters texpage on a certain condition
// doesn't exist in ghidra disassembly, created from UI_Map_DrawMap for optimization
void UI_Map_DrawMap_ExtraFunc(struct Icon* icon, POLY_FT4* p, short posX, short empty, struct PrimMem* primMem, u_long* otMem, u_int colorID)
{
	short leftX;
	short sizeX;
	
	sizeX = icon->texLayout.u1 - icon->texLayout.u0;
	
	// posX is the right side,
	// letftX is the left side
	leftX = posX - sizeX;
	
	#ifdef USE_16BY9
	
	// 12% size
	short len = (sizeX * 125) / 1000;
	
	if((sdata->gGT->gameMode1 & 0x2000) != 0)
	{
		// 12% from each side
		leftX += len;
		posX -= len;
	}
	
	else
	{
		// Must scale around 3D->2D origin,
		// Otherwise we'd never get the map
		// and icons to scale together
		
		void** pointers = ST1_GETPOINTERS(sdata->gGT->level1->ptrSpawnType1);
		void* levPtrMap = pointers[ST1_MAP];
		
		int midX = 0;
		int midY = 0;
		DECOMP_UI_Map_GetIconPos(levPtrMap, &midX, &midY);
		
		leftX += ((midX-leftX) * 250) / 1000;
		posX -= ((posX-midX) * 250) / 1000;
		
		if (sdata->gGT->numPlyrCurrGame == 1)
		{
			// 462 is midX of Crash Cove
			leftX += ((462 - midX) / 4) + 5;
			posX += ((462 - midX) / 4) + 5;
		}
	}
	
	#endif

	p->x0 = leftX;
	p->x1 = posX;
	p->x2 = leftX;
	p->x3 = posX;

	// set header
	setPolyFT4(p);

	// UVs
	*(int*)&p->u0 = *(int*)&icon->texLayout.u0;
	*(int*)&p->u1 = *(int*)&icon->texLayout.u1;
	*(int*)&p->u2 = *(int*)&icon->texLayout.u2;
	*(short*)&p->u3 = *(short*)&icon->texLayout.u3;

	// check for if the minimap being drawn is white, if it's white then alter the blending mode bits of the texpage from 11 to 01
	if (colorID == 1)
	{
		p->tpage = p->tpage & 0xff9f | (u_short)(1 << 5);
	}

	p->code |= 2;

	AddPrim(otMem, p);
}

#include "../AltMods/Mods1.c"

void Mods1_EndOfFile()
{
	// leave empty
}