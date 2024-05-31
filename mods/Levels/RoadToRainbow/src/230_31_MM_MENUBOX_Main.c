#include <common.h>

void DECOMP_MM_MenuProc_Main(struct RectMenu* mainMenu)
{
  int choose;
  struct GameTracker* gGT = sdata->gGT;
  
  // disabled for CustomLevel3
  
  //// if scrapbook is unlocked
  //if ((sdata->gameProgress.unlocks[1] & 0x10) != 0) 
  //{  
	//// change D230.rowsMainMenuBasic
	//// to D230.rowsMainMenuWithScrapbook
	//mainMenu->rows = &D230.rowsMainMenuWithScrapbook[0];
  //}

  #if 1
  char* info = "Road To Rainbow: Battle";
  DecalFont_DrawLine(info, 		5, 197, FONT_SMALL, ORANGE);
  DecalFont_DrawLine(__DATE__, 	5, 206, FONT_SMALL, ORANGE);
  DecalFont_DrawLine(__TIME__, 	170, 206, FONT_SMALL, ORANGE);
  #endif

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
			(D230.titleObj != NULL)
		) &&
        (0xe5 < *(int*)0x800b5a14)
	   ) 
	{
	  // "TM" trademark string
      DecalFont_DrawLineOT(
		sdata->lngStrings[0x244],0x10e,0x9c,FONT_SMALL,ORANGE,
        &gGT->backBuffer->otMem.startPlusFour[3]);
    }
    
	#if 0
	// DISABLED DEMO MODE
	#endif
	
	// 900 = 30 seconds at 30fps
	gGT->demoCountdownTimer = 900;
  }
  
  MM_Title_Init();
  
  // if drawing ptrNextBox_InHierarchy
  if ((mainMenu->state & 0x10) != 0) {
    *(int*)0x800b5a14 = 1000;
  }
  
  if ((mainMenu->state & 0x400) == 0) {
    return;
  }
  
  struct Title* titleObj = D230.titleObj;

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
  gGT->gameMode1 &= ~(BATTLE_MODE | ADVENTURE_MODE | TIME_TRIAL | ADVENTURE_ARENA | ARCADE_MODE | ADVENTURE_CUP);
  
  // clear more game mode flags
  gGT->gameMode2 &= ~(CUP_ANY_KIND);
  
  // set a flag that you're in main menu
  mainMenu->state |= 4;
  
  // number of laps is 3
  gGT->numLaps = 3;
  
  // get LNG index of row selected
  choose = (int)mainMenu->rows[mainMenu->rowSelected].stringIndex;
  
  // choose Adventure
  if (choose == 0x4c) 
  {
    // Turn on Adventure Mode, turn off item cheats
    gGT->gameMode1 |= ADVENTURE_MODE;
    gGT->gameMode2 &= ~(CHEAT_WUMPA | CHEAT_MASK | CHEAT_TURBO | CHEAT_ENGINE | CHEAT_BOMBS);
    
    // menu for new/load
    mainMenu->ptrNextBox_InHierarchy = &D230.menuAdventure;
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
    gGT->gameMode1 |= TIME_TRIAL;
    gGT->gameMode2 &= ~(CHEAT_WUMPA | CHEAT_MASK | CHEAT_TURBO | CHEAT_ENGINE | CHEAT_BOMBS);
    return;
  }
  
  // if one-lap-race cheat is enabled
  // works in Arcade, VS, not Adv, not Time Trial
  if ((gGT->gameMode2 & CHEAT_ONELAP) != 0) 
  {
    gGT->numLaps = 1;
  }
  
  if (choose == 0x4e)
  {
	// set game mode to Arcade Mode
    gGT->gameMode1 |= ARCADE_MODE;

	// set next menu
	mainMenu->ptrNextBox_InHierarchy = &D230.menuRaceType;
	mainMenu->state |= 0x10;
	return;
  }
  
  // if you entered VS mode
  if (choose == 0x4f) 
  {
	// next menu is choosing single+cup
    mainMenu->ptrNextBox_InHierarchy = &D230.menuRaceType;
	mainMenu->state |= 0x10;
	return;
  }
  
  // if you chose Battle
  if (choose == 0x50) 
  {
  	*(int*)0x800b5a08 = 2;
  
  	// set game mode to Battle Mode
  	gGT->gameMode1 |= BATTLE_MODE;
  
  	// set next menu to 2P,3P,4P
  	mainMenu->ptrNextBox_InHierarchy = &D230.menuPlayers2P3P4P;
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

