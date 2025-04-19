#include <common.h>
#include "utils.h"

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
	data.metaDataLEV[CUSTOM_LEVEL_ID].timeTrial = 0x7FFFFFFF;
	sdata->gameProgress.highScoreTracks[CUSTOM_LEVEL_ID].timeTrialFlags = 0;
	MainRaceTrack_RequestLoad(MAIN_MENU_LEVEL);
}