#include <common.h>

// byte budget
// 840/1108

void DECOMP_MM_MenuBox_Main(struct MenuBox* mainMenu)
{
  int choose;
  struct GameTracker* gGT = sdata->gGT;
  
  // if scrapbook is unlocked
  if ((sdata->gameProgress.unlocks[0] & 0x10) != 0) 
  {  
	// change OVR_230.rows_mainMenu_Basic
	// to OVR_230.rows_mainMenu_WithScrapbook
	mainMenu->rows = &OVR_230.rows_mainMenu_WithScrapbook[0];
  }

  DECOMP_MM_ParseCheatCodes();
  
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
			(*(int*)0x800b59a0 != NULL)
		) &&
        (0xe5 < *(int*)0x800b5a14)
	   ) 
	{
	  // "TM" trademark string
      DecalFont_DrawLineOT(
		sdata->lngStrings[0x244],0x10e,0x9c,FONT_SMALL,ORANGE,
        &gGT->backBuffer->otMem.startPlusFour[3]);
    }
    
	if ((OVR_230.menubox_mainMenu.state & 0x10) == 0) 
	{
      gGT->numPlyrNextGame = 1;
	  
	  // if no buttons pressed, check demo mode
      if (sdata->gGamepads->anyoneHeldCurr == 0) 
	  {
        gGT->demoCountdownTimer--;
        
		// If time runs out
        if (gGT->demoCountdownTimer < 1) 
		{
		  // Transition out of main menu
          *(int*)0x800b5a1c = 2;
		  
		  // Go to a cutscene of some kind
		  // (either oxide intro or demo mode)
		  *(int*)0x800b59e0 = 4;
        }
      }
	  
	  // if button pressed, reset timer
      else 
	  {
		// 900 = 30 seconds at 30fps
        gGT->demoCountdownTimer = 900;
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
  
  struct Title* titleObj = *(int*)0x800b59a0;

  // if "title" object exists
  if (titleObj != NULL) 
  {
	// CameraPosOffset X
    titleObj->cameraPosOffset[0] = 0;
  }
  
  // if you are at highest level of menu hierarchy
  if (mainMenu->unk1e != 0) 
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
  
  // choose Adventure
  if (choose == 0x4c) 
  {
    // Turn on Adventure Mode, turn off cheats
	gGT->gameMode1 |= 0x80000;
    gGT->gameMode2 &= 0xffbef1ff;
    
    // menubox for new/load
	mainMenu->ptrNextMenuBox_InHierarchy = &OVR_230.menubox_adventure;
    mainMenu->state |= 0x10;
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
    gGT->numPlyrNextGame = 1;
    
    // set game mode to Time Trial Mode
    gGT->gameMode1 |= 0x20000;
    gGT->gameMode2 &= 0xffbef1ff;
    return;
  }
  
  // if one-lap-race cheat is enabled
  // works in Arcade, VS, not Adv, not Time Trial
  if ((gGT->gameMode2 & 0x800000) != 0) 
  {
    gGT->numLaps = 1;
  }
  
  if (choose == 0x4e)
  {
	// set game mode to Arcade Mode
    gGT->gameMode1 |= 0x400000;

	// set next menuBox
	mainMenu->ptrNextMenuBox_InHierarchy = &OVR_230.menubox_raceType;
	mainMenu->state |= 0x10;
	return;
  }
  
  // if you entered VS mode
  if (choose == 0x4f) 
  {
	// next menuBox is choosing single+cup
    mainMenu->ptrNextMenuBox_InHierarchy = &OVR_230.menubox_raceType;
	mainMenu->state |= 0x10;
	return;
  }
  
  // if you chose Battle
  if (choose == 0x50) 
  {
  	*(int*)0x800b5a08 = 2;
  
  	// set game mode to Battle Mode
  	gGT->gameMode1 |= 0x20;
  
  	// set next menuBox to 2P,3P,4P
  	mainMenu->ptrNextMenuBox_InHierarchy = &OVR_230.menubox_players2P3P4P;
  	mainMenu->state |= 0x10;
  	return;
  }

  // if you chose High Score
  if (choose == 0x51) 
  {
	// Set next stage to high score menu
    *(int*)0x800b59e0 = 3;
	  
	// Leave main menu hierarchy
	*(int*)0x800b5a1c = 2;
	
	return;
  }
  
  // if you chose Scrapbook
  if (choose == 0x234) 
  {
	// Set next stage to Scrapbook
    *(int*)0x800b59e0 = 5;
  
	// Leave main menu hierarchy
	*(int*)0x800b5a1c = 2;
	
	return;
  }
}

