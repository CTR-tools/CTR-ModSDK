#include <common.h>

void DECOMP_UI_DrawNumRelic(short, short);
void DECOMP_UI_DrawNumKey(short, short);
void DECOMP_UI_DrawNumTrophy(short, short);

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
  ptrHudData = data.hudStructPtr[gGT->numPlyrCurrGame - 1];
  iVar1 = TitleFlag_GetCanDraw();
  if (iVar1 == 0) {
    TitleFlag_SetCanDraw(1);
  }
  
  if (
		// if Aku Hint is not unlocked
		((sdata->advProgress.rewards[3] & 0x400000) == 0) && 
		
		(iVar1 = TitleFlag_IsFullyOffScreen(), iVar1 != 0)
	 ) 
  {
	// Trigger Aku Hint:
	// Welcome to Adventure Arena
    MainFrame_RequestMaskHint(0,0);
  }
  
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
  
  // LEV -> trial_data -> numPointers
  if (gGT->level1->ptrSpawnType1->count != 0) 
  {
    hubPtrs = gGT->level1->ptrSpawnType1->pointers[0];
  }
  
  // if game is not paused
  if ((gGT->gameMode1 & (PAUSE_1 | PAUSE_2 | PAUSE_3 | PAUSE_4)) == 0) 
  {
	// Jump meter and landing boost
    DECOMP_UI_JumpMeter_Update(advDriver);
  }
  
  // Check a HUD flag
  if ((gGT->hudFlags & 0x10) == 0) {

    local_1e[0] = 0;
    *(int*)0x800b5670 = 0;
	
    UI_Map_DrawDrivers(hubPtrs,gGT->threadBuckets[0],&local_20);
	
    AH_Map_Warppads(hubPtrs,gGT->threadBuckets[5],&local_1e[0]);
	
    AH_Map_HubItems(hubPtrs,&local_1e[0]);
	
    UI_Map_DrawMap(
                gGT->ptrIcons[3],

                gGT->ptrIcons[4],

                500,195,

				 // pointer to PrimMem struct
                &gGT->backBuffer->primMem,

                // pointer to OT memory
                gGT->tileView->ptrOT,
                 
				1);
	
    DECOMP_UI_DrawSlideMeter(ptrHudData[0x10].x,ptrHudData[0x10].y,advDriver);
  }
  
  DECOMP_UI_DrawNumRelic	(ptrHudData[0x1C].x + 0x10, ptrHudData[0x1C].y - 10);
  DECOMP_UI_DrawNumKey		(ptrHudData[0x1E].x + 0x10, ptrHudData[0x1E].y - 10);
  DECOMP_UI_DrawNumTrophy	(ptrHudData[0x20].x + 0x10, ptrHudData[0x20].y - 10);
  
  return;
}
