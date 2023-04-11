#include <common.h>

void DECOMP_MM_Title_MenuUpdate(void)
{
  char cVar1;
  struct GameTracker* gGT = sdata->gGT;
  u_short uVar3;
  int iVar4;
  
  // 0 - watching Crash + C-T-R letters animation
  // 1 - in the main menu
  // 2 - leaving main menu
  // 3 - coming back to main menu after exiting another menu
	
  // If main menu is in focus
  if (*(unsigned char*)0x800b5a1c == 1) 
  {
	// no transitioning action is needed, 
	// skip to end of function
	goto switchD_800abde8_caseD_6;
  }
  
  // If you aren't in main menu
  
  // if not transitioning out
  if (*(unsigned char*)0x800b5a1c < 2) {
	  
	// If your state is less than 2, and 
	// not 1, then it must be 0 by default
	  
	// If not transitioning in
    if (*(unsigned char*)0x800b5a1c != 0) 
		
		// error, just skip everything
		goto switchD_800abde8_caseD_6;
		
	// assume main menu state = 0,
	// if you are transitioning in
		
	// if not done watching C-T-R letters
    if (*(int*)0x800b5a14 < 0xe6) {
      *(int*)0x800b5a40 = *(int*)0x800b4840;
	  
	  // end function
      goto switchD_800abde8_caseD_6;
    }
	
    *(u_int*)0x800b4548 &= 0xffffffdf | 0x400;
	
    MM_TransitionInOut((u_short*)0x800b4864,*(int*)0x800b5a40,*(int*)0x800b4844);
	
	// If the animation ends
    if (*(int*)0x800b5a40 == 0) 
	{
	  // you are now in main menu
      *(unsigned char*)0x800b5a1c = 1;
	  
	  // no further transitioning is needed,
	  // skip to end of function
      goto switchD_800abde8_caseD_6;
    }
	
LAB_800ac004:

	// decrease amount of time remaining in animation
    *(int*)0x800b5a40 -= 1;
    goto switchD_800abde8_caseD_6;
  }
  
  // If not transitioning out
  if (*(unsigned char*)0x800b5a1c != 2) 
  {
	// if you are not returning from another menu,
	// so either in main menu or watching C-T-R trophy animation
    if (*(unsigned char*)0x800b5a1c != 3) 
	{
		// no further action is needed
		goto switchD_800abde8_caseD_6;
	}
	
	// assume *(unsigned char*)0x800b5a1c = 3
	// if you are returning from another menu
	
    MM_TransitionInOut((u_short*)0x800b4864,*(int*)0x800b5a40,*(int*)0x800b4844);
    
	// If "fade-in" animation from other menu is done
	if (*(int*)0x800b5a40 == 0) 
	{
	  // you are now in main menu
      *(unsigned char*)0x800b5a1c = 1;
	  
	  // end the function
      goto switchD_800abde8_caseD_6;
    }
	
	// If you're transitioning from another menu,
	// and the animation is not done, loop back and
	// check again if the transition is done
    goto LAB_800ac004;
  }
  
  // assume *(unsigned char*)0x800b5a1c = 2
  // If you are transitioning out
  
  // MM_TransitionInOut
  MM_TransitionInOut((u_short*)0x800b4864,*(int*)0x800b5a40,*(int*)0x800b4844);
  
  // Increment frame timer, increase time left in "fade-in" 
  // animation, which plays it in reverse, as "fade-out"
  *(int*)0x800b5a40 += 1;
  
  // If the "fade-out" animation is not over, skip "switch" statemenet
  if (*(int*)0x800b5a40 <= *(int*)0x800b4840) goto switchD_800abde8_caseD_6;
  
  // If you are transitioning out of the menu,
  // and if the "fade-out" animation is done,
  // time to figure out where you're going next
  
  switch(*(short*)0x800b59e0) 
  {

  // advanture character selection
  case 0:
  
    GAMEPROG_NewProfile_InsideAdv(&sdata->advProgress.rewards);
    *(short*)0x8008d96c = 0xffff;
	
	// go to adventure character select screen
    sdata->mainMenuState = 4;
	
    MM_Title_CameraReset(); 
    MM_Title_KillThread();
	
	// Load lev 40, adventure character selection screen
    MainRaceTrack_RequestLoad(0x28);
    break;
	
  // adventure save/load
  case 1:
  
	// Go to save/load
    sdata->ptrDesiredMenuBox = &data.MenuBox_DrawSelfFourAdvProfiles;
	
    MM_Title_CameraReset();
	
    LoadSave_ToggleMode(0x10);
    break;
	
  // regular character selection screen
  case 2:
  
    MM_Title_CameraReset();
	
    MM_Title_KillThread();
	
	// return to character selection
    sdata->ptrDesiredMenuBox = &OVR_230.menubox_characterSelect;
	
    DECOMP_MM_Characters_RestoreIDs();
    break;
	
  // high score menu
  case 3:
  
    MM_Title_CameraReset();
	
    MM_HighScore_Init();
	
	// Go to high score menu
    sdata->ptrDesiredMenuBox = &OVR_230.menubox_highScores;
    break;
	
  case 4:
  
    MM_Title_CameraReset();
	
    MM_Title_KillThread();
	
    gGT->gameMode1 &= 0xefa5ffdf;
    gGT->gameMode2 &= 0xffffffef;
	
	// enable Arcade Mode
    gGT->gameMode1 |= 0x400000;
	
	// If you have not viewed Oxide cutscene yet
    if (gGT->boolSeenOxideIntro == 0) 
	{
      gGT->boolSeenOxideIntro = 1;
      iVar4 = 0x1e;
    }
	
	// If you've already seen Oxide Cutscene
    else 
	{
	  // enable Demo Mode
      gGT->boolDemoMode = 1;
	  
	  // number of times you've seen Demo Mode,
      uVar3 = sdata->demoModeIndex;
	  
      gGT->demoCountdownTimer = 0x708;
	  
	  // use the number of time's you've seen 
	  // Demo Mode, to decide the order of characters
	  
      for (iVar4 = 0; iVar4 < 8; iVar4++)
	  {
		// set character ID
        data.characterIDs[iVar4] = uVar3;
		
		// iterate character ID
        uVar3 += 1;
      } 
	  
	  // set number of players to 1
      gGT->numPlyrCurrGame = 1;
	  
	  // get trackID from demo mode index, 
	  // in order of Single Race track selection
      iVar4 = OVR_230.arcadeTracks[sdata->demoModeIndex].levID;
      
	  // increment number of times you've been in demo mode
	  sdata->demoModeIndex += 1;
    }
    goto LAB_800abfc0;
	
  // scrapbook
  case 5:
  
    MM_Title_CameraReset();
	
    MM_Title_KillThread();
	
	// go to scrapbook
    sdata->mainMenuState = 5;
	
	// Lev 64, Scrapbook
    iVar4 = 0x40;
LAB_800abfc0:

	// Load level
    MainRaceTrack_RequestLoad(iVar4);
	
	// make main menu disappear
    MenuBox_Hide((struct MenuBox*)0x800b4540);
  }
  
switchD_800abde8_caseD_6:

  // All these might be various timers for audio,
  // flashing highlight menu bars, waving flag, etc

  // if you're entering menu for first time in
  // Crash + C-T-R animation cutscene
  if (*(unsigned char*)0x800b5a1c == 0) {
    OVR_230.titleCameraPosRot[0] = DAT_800b485c;
    OVR_230.titleCameraPosRot[2] = DAT_800b485e;
    OVR_230.titleCameraPosRot[4] = DAT_800b4860;
  }
  
  // If you are not watching Crash + C-T-R animation
  else {
    OVR_230.titleCameraPosRot[0] = DAT_800b485c + DAT_800b489c;
    OVR_230.titleCameraPosRot[2] = DAT_800b485e + DAT_800b489e;
    OVR_230.titleCameraPosRot[4] = DAT_800b4860 + DAT_800b48a6;
  }
  DAT_800b4542 = DAT_800b4848 + DAT_800b486a;
  DAT_800b4544 = DAT_800b484a + DAT_800b486c;
  DAT_800b4582 = DAT_800b4854 + DAT_800b4888;
  DAT_800b4584 = DAT_800b4856 + DAT_800b488a;
  DAT_800b45c6 = DAT_800b4854 + DAT_800b4888;
  DAT_800b45c8 = DAT_800b4856 + DAT_800b488a;
  DAT_800b460a = DAT_800b4858 + DAT_800b4892;
  DAT_800b460c = DAT_800b485a + DAT_800b4894;
  DAT_800b464a = DAT_800b4850 + DAT_800b487e;
  DAT_800b464c = DAT_800b4852 + DAT_800b4880;
  DAT_800b468a = DAT_800b484c + DAT_800b4874;
  DAT_800b468c = DAT_800b484e + DAT_800b4876;
  return;
}
 