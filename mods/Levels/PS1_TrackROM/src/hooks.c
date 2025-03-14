#include <common.h>
#include "utils.h"

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

static int once = 1;

void RunInitHook()
{
	struct GameTracker* gGT = sdata->gGT;

	// set arcade/TT menu to use adv cup rows
	*(unsigned int*)(0x80084510 + 0xC) = NewRowsPAUSE;

	// required for AI Nav, cause I dont have
	// offsets [0xA] or [0xC] and it gets stuck
	// in a loop, so this breaks the loop
	*(int*)0x800150c0 = 0;

	// wont clear itself?
	sdata->ptrLoadSaveObj = 0;

	if (once)
	{
		once = 0;
		// adds VRAM to loading queue
		LOAD_AppendQueue(sdata->ptrBigfile1, LT_VRAM, 222, 0x80200000, 0);
		// adds LEV to loading queue
		LOAD_AppendQueue(sdata->ptrBigfile1, LT_DRAM, 221, 0x80300000, 0);

		char* currDriver = 0x80290000;
		for (int i = 0; i < 15; i++) // load every character except oxide. oxide will come with time trial pack
		{
			int fileSize;
			LOAD_ReadFile(sdata->ptrBigfile1, LT_DRAM, BI_RACERMODELHI + i, currDriver, &fileSize, 0);
			int* pMap = (int*) (currDriver + 4 + (*(int*)currDriver));
			LOAD_RunPtrMap(currDriver + 4, pMap + 1, *pMap >> 2);
			struct Model** g_charModelPtrs = CHAR_MODEL_PTRS;
			g_charModelPtrs[i] = (struct Model*) (currDriver + 4);
			currDriver += fileSize;
		}
	}

	if(gGT->levelID != CUSTOM_LEVEL_ID) return;

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

struct MenuRow NewRowsEND[] =
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
		.rowOnPressDown = 2,
		.rowOnPressLeft = 1,
		.rowOnPressRight = 1,
	},

	[2] =
	{
		.stringIndex = 9,
		.rowOnPressUp = 1,
		.rowOnPressDown = 2,
		.rowOnPressLeft = 2,
		.rowOnPressRight = 2,
	},

	[3] =
	{
		.stringIndex = 0xFFFF,
	}
};

void RunUpdateHook()
{
	struct GameTracker* gGT = sdata->gGT;

	// main menu
	if (sdata->ptrActiveMenu == &D230.menuMainMenu)
	{
		sdata->ptrActiveMenu->rows = &NewRowsMM[0];
	}

	// time trial end of race
	if ((sdata->ptrActiveMenu == 0x800a0458) || (sdata->ptrActiveMenu == 0x800A04A4))
	{
		sdata->ptrActiveMenu->rows = &NewRowsEND[0];
	}

	if (gGT->levelID != CUSTOM_LEVEL_ID) return;
}

void HotReloadVRAM()
{
	int* vramBuf = (int *)CUSTOM_VRAM_ADDR;
	struct VramHeader* vh = (struct VramHeader*) vramBuf;
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
	else { LoadImage(&vh->rect, VRAMHEADER_GETPIXLES(vh)); }
}

void HotReload()
{
	volatile int* g_triggerVRMReload = TRIGGER_VRM_RELOAD;
	if (*g_triggerVRMReload)
	{
		HotReloadVRAM();
		*g_triggerVRMReload = 0;
		return;
	}

	struct GameTracker* gGT = sdata->gGT;
	volatile int* g_triggerHotReload = TRIGGER_HOT_RELOAD;
	if (*g_triggerHotReload == HOT_RELOAD_LOAD && (gGT->gameMode1 & LOADING || gGT->levelID == MAIN_MENU_LEVEL))
	{
		*g_triggerHotReload = HOT_RELOAD_READY;
		while (*g_triggerHotReload != HOT_RELOAD_EXEC) {};
		return;
	}

	if (*g_triggerHotReload != HOT_RELOAD_START || gGT->gameMode1 & LOADING) { return; }

	*g_triggerHotReload = HOT_RELOAD_LOAD;
	if (gGT->levelID == MAIN_MENU_LEVEL) { return; }
	GhostTape_Destroy();
	sdata->mainMenuState = 0;
	gGT->gameMode1 |= MAIN_MENU;
	MainRaceTrack_RequestLoad(MAIN_MENU_LEVEL);
}