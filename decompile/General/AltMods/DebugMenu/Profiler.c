#include "DebugStructs.h"

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

void DebugMenu_Draw(struct DebugMenu* dm)
{
	struct GameTracker* gGT = sdata->gGT;
	
	struct PrimMem* primMem = &gGT->backBuffer->primMem;
	
	// must be room for 100 POLY_F4s
	POLY_F4* test = primMem->curr;
	test = test + 100;
	if(test > primMem->endMin100) return;
	
	void* ot = gGT->pushBuffer_UI.ptrOT;
	
	RECT* r = &dm->posX;
	DECOMP_CTR_Box_DrawClearBox(r, 0x808080, 0, ot);
	
	
	int rowCount = 0;
	struct DebugRow* dr;
	
	dr = dm->rowArr;
	while(dr->actionFlag != 0)
	{
		void DebugFont_DrawLine(char* text, int posX, int posY, int color);
		
		// Need background box
		// Need arrow indication,
		// Need color
		
		int color = 0x808080;
		if(dr->subMenu == dm->childMenu)
			color = 0x804000;
		
		DebugFont_DrawLine(
			dr->rowText,
			dm->posX,
			dm->posY + (rowCount * 8),
			color
		);
		
		dr++;
		rowCount++;
	}
	
	// TEMPORARY TEST
	if(dm->rowArr[0].actionFlag == 1)
		dm->childMenu = dm->rowArr[0].subMenu;
	
	dr = dm->rowArr;
	while(dr->actionFlag != 0)
	{
		if(dr->actionFlag == 1)
		{
			if(dr->subMenu == dm->childMenu)
			{
				DebugMenu_Draw(dr->subMenu);	
			}
		}
		
		dr++;
	}
}