#include <common.h>

void DECOMP_AH_Map_Main(void)
{
  struct GameTracker* gGT = sdata->gGT;
  struct Driver* advDriver;
  struct UiElement2D* ptrHudData;
  int iVar1;
  int hubPtrs;
  short local_20;
  short local_1e[3];
  
  // force disable speedometer
  sdata->HudAndDebugFlags &= 0xfffffff7;
  
  local_20 = 0;
  advDriver = gGT->drivers[0];
  ptrHudData = data.hudStructPtr[0];
  
  iVar1 = DECOMP_RaceFlag_GetCanDraw();
  if (iVar1 == 0) 
  {
    DECOMP_RaceFlag_SetCanDraw(1);
  }
  
  if (
		// if Aku Hint is not unlocked
		((sdata->advProgress.rewards[3] & 0x400000) == 0) && 
		
		(iVar1 = DECOMP_RaceFlag_IsFullyOffScreen(), iVar1 != 0)
	 ) 
  {
	// Trigger Aku Hint:
	// Welcome to Adventure Arena
    DECOMP_MainFrame_RequestMaskHint(0,0);
  }
  
  #ifdef USE_HIGHMP
  if (gGT->numPlyrCurrGame != 1)
  return;
  #endif
  
  // in the OG code, is this even possible?
#if 0
  if ((gGT->numPlyrCurrGame == 0) &&
  
	// if this is an AI, not a human
     ((advDriver->actionsFlagSet & 0x100000) != 0)) 
  {
	// force draw speedometer, not map, why?
    sdata->HudAndDebugFlags = 8;
  }
#endif
  
  if (gGT->level1->ptrSpawnType1->count != 0) 
  {
	void** pointers = ST1_GETPOINTERS(gGT->level1->ptrSpawnType1);
    hubPtrs = pointers[ST1_MAP];
  }
  
  // if game is not paused
  if ((gGT->gameMode1 & PAUSE_ALL) == 0) 
  {
	// Jump meter and landing boost
    DECOMP_UI_JumpMeter_Update(advDriver);
  }
  
  // Check a HUD flag
  if ((gGT->hudFlags & 0x10) == 0) {

    local_1e[0] = 0;
	
    D232.unkModeHubItems = 0;
	
    DECOMP_UI_Map_DrawDrivers(hubPtrs,gGT->threadBuckets[0].thread,&local_20);

    DECOMP_AH_Map_Warppads(hubPtrs,gGT->threadBuckets[5].thread,&local_1e[0]);
	
    DECOMP_AH_Map_HubItems(hubPtrs,&local_1e[0]);
	
    DECOMP_UI_Map_DrawMap(
        gGT->ptrIcons[3],
        gGT->ptrIcons[4],

        500,195,

        &gGT->backBuffer->primMem,
		gGT->pushBuffer_UI.ptrOT, 1);
	
    DECOMP_UI_DrawSlideMeter(ptrHudData[8].x, ptrHudData[8].y, advDriver);
  }
  
  DECOMP_UI_DrawNumRelic	(ptrHudData[0xE].x + 0x10,  ptrHudData[0xE].y - 10);
  DECOMP_UI_DrawNumKey		(ptrHudData[0xF].x + 0x10,  ptrHudData[0xF].y - 10);
  DECOMP_UI_DrawNumTrophy	(ptrHudData[0x10].x + 0x10, ptrHudData[0x10].y - 10);
  
  return;
}
