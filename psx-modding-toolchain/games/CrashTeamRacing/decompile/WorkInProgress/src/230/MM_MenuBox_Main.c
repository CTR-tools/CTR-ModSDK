#include <common.h>

void DECOMP_MM_MenuBox_Main(struct MenuBox* mainMenu)
{
  short choose;
  int iVar1;
  struct GameTracker* gGT = sdata->gGT;
  
  // DAT_800b59e0 is the next stage you 
  // will enter after leaving main menu
  // 0 - advanture character selection
  // 1 - adventure save/load
  // 2 - regular character selection screen
  // 3 - high score menu
  // 4 - cutscene (intro + demo mode)
  // 5 - scrapbook
  
  // if scrapbook is unlocked
  if ((sdata->gameProgress.unlocks[0] & 0x10) != 0) 
  {
	// old dll said
	// _DAT_800b454c = 0x800b4510;
	
	// override main menu hierarchy rows
	// to be the rows that include scrapbook
    OVR_230.rows_mainMenu_Basic[0] = &OVR_230.rows_mainMenu_WithScrapbook;
  }

  MM_ParseCheatCodes();
  
  MM_ToggleRows_Difficulty();
  
  MM_ToggleRows_PlayerCount();
  
  // If you are at the highest hierarchy level of main menu
  if (mainMenu->unk1e == 1) 
  {
    MM_Title_MenuUpdate();
	
    if (
		(
			// If you are in main menu
			(*(int*)0x800b5a1c == 1) && 
			
			// if "title" object exists
			((struct Title*)0x800b59a0 != NULL)
		) &&
        (0xe5 < *(int*)0x800b5a14)
	   ) 
	{
	  // Trademark? Like at main menu with Crash holding trophy?
		
	  // sdata->lngStrings[0x910]
	  // "TM"
	  
      DecalFont_DrawLineOT((sdata->lngStrings[0x910]),
                            0x10e,0x9c,2,0,
                   
                   ((sdata->gGT->backBuffer) + 0xa0) + 0xc);
    }
    
	if ((OVR_230.menubox_mainMenu.state & 0x10) == 0) 
	{
	  // set number of players to 1
      gGT->numPlyrCurrGame = 1;
	  
	  // If nobody presses any button
      if (sdata->gGamepads->anyoneHeldCurr == 0) 
	  {
		// Reduce number of frames remaining until Cutscene
        iVar1 = gGT->demoCountdownTimer - 1;
        gGT->demoCountdownTimer = iVar1;
		
		// If time runs out
        if (iVar1 < 1) 
		{
		  // Transition out of main menu
          *(int*)0x800b5a1c = 2;
		  
		  // Go to a cutscene of some kind
		  // (either oxide intro or demo mode)
         *(int*)0x800b59e0 = 4;
        }
      }
	  
	  // If anyone presses any button at all
      else 
	  {
		// Set countdown to 900 frames, which is approximately 30 seconds at 30fps,
		// When this timer runs out, you leave the main menu and enter Cutscene
        sdata->gGT->demoCountdownTimer = 900;
      }
    }
  }
  
  MM_Title_Init();
  
  // if drawing ptrNextMenuBox_InHierarchy
  if ((mainMenu->state & 0x10) != 0) {
    *(int*)0x800b5a14 = 1000;
  }
  
  if ((mainMenu->state & 0x400) == 0) {
    return;
  }
  
  struct Title* titleObj = (struct Title*)0x800b59a0;

  // if "title" object exists
  if (titleObj != NULL) 
  {
	// CameraPosOffset X
    titleObj->cameraPosOffset[0] = 0;
  }
  
  // if you are at highest level of menu hierarchy
  if ((mainMenu + 0x1e) != 0) 
  {
	// leave the function
    return;
  }
  
  // If you are here, then you must not be 
  // at the highest level of menu hierarchy
  
  // if row is negative, do nothing
  if ((mainMenu->rowSelected) < 0) {
    return;
  }
  
  // clear flags from game mode
  gGT->gameMode1 &= 0xefa5ffdf;
  
  // clear more game mode flags
  gGT->gameMode2 &= 0xffffffef;
  
  // set a flag that you're in main menu
  mainMenu->state |= 4;
  
  // number of laps is 3
  gGT->numLaps = 3;
  
  // get LNG index of row selected
  choose = (int)mainMenu->rows[mainMenu->rowSelected].stringIndex;
  
  // if you entered VS mode
  if (choose == 0x4f) 
  {
	// if one-lap-race cheat is enabled
    if (((gGT->gameMode2) & 0x800000) != 0) 
	{
	  // set number of laps to 1
      gGT->numLaps = 1;
    }
	
	// next menuBox is choosing single+cup
    mainMenu->ptrNextMenuBox_InHierarchy = &OVR_230.menubox_raceType;
  }
  
  // if you did not enter VS
  else 
  {
    if (0x4f < choose) 
	{
	  // if you chose High Score
      if (choose == 0x51) 
	  {
		// Set next stage to high score menu
        *(int*)0x800b59e0 = 3;
      }
	  
	  // if you did not choose High Score
      else 
	  {
		// if you chose Battle
        if (choose < 0x51) {
          *(int*)0x800b5a08 = 2;
		  
		  // set game mode to Battle Mode
          sdata->gGT->gameMode1 |= 0x20;
		  
		  // set next menuBox to 2P,3P,4P
          mainMenu->ptrNextMenuBox_InHierarchy = &OVR_230.menubox_players2P3P4P;
          
		  goto LAB_800ad3f8;
        }
		
		// if you did not choose Scrapbook
        if (choose != 0x234) 
		{
		  // quit the function
          return;
        }
		
		// sVar must be 0x234
		
		// Set next stage to Scrapbook
        *(int*)0x800b59e0 = 5;
      }
	  
	  // Leave main menu hierarchy
      *(int*)0x800b5a1c = 2;
      return;
    }
	
	// If you choose Time Trial in Main Menu
    if (choose == 0x4d) 
	{
	  // Leave main menu hierarchy
      *(int*)0x800b5a1c = 2;
	  
	  // Set next stage to 2 for Time Trial
      *(int*)0x800b59e0 = 2;
	  
	  // set number of players to 1
      gGT->numPlyrCurrGame = 1;
	  
	  // set game mode to Time Trial Mode
      gGT->gameMode1 |= 0x20000;
      gGT->gameMode2 &= 0xffbef1ff;
      return;
    }
    
	if (choose < 0x4e) 
	{
	  // if you did not choose Adventure
      if (choose != 0x4c) 
	  {
		// quit
        return;
      }
	  
	  // sVar1 must be 0x4c
	  
	  // Turn on Adventure Mode
     gGT->gameMode1 |= 0x80000;
	  
	  // menubox for new/load
    mainMenu->ptrNextMenuBox_InHierarchy = &OVR_230.menubox_adventure;
	  
      mainMenu->state |= 0x10;
      gGT->gameMode2 &= 0xffbef1ff;
      return;
    }
	
	// If you chose Arcade mode
	
	// if one-lap-race cheat is enabled
    if (((sdata->gGT->gameMode2) & 0x800000) != 0) 
	{
	  // set number of laps to 1
      sdata->gGT->numLaps = 1;
    }
	
	// set game mode to Arcade Mode
    sdata->gGT->gameMode1 |= 0x400000;

  // set next menuBox
  mainMenu->ptrNextMenuBox_InHierarchy = &OVR_230.menubox_raceType;
  }
LAB_800ad3f8:

  mainMenu->state |= 0x10;
  return;
}

