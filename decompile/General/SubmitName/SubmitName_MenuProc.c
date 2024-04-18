#include <common.h>

void DECOMP_SubmitName_MenuProc(struct RectMenu* menu)
{
  struct GameTracker *gGT = sdata->gGT;

  short selection = DECOMP_SubmitName_DrawMenu(0x13f);
  menu->rowSelected = selection;
  
  // not finished yet
  if (selection == 0)
  {
    return;
  }

  // if name entered for Time Trial
  if (sdata->data10_bbb[0xd] == 1)
  {
	#ifndef REBUILD_PS1
	// if hit CANCEL
    if (selection < 0)
    {
      // end of race menu with "Save Ghost" option
	  extern struct RectMenu menu224;
      sdata->ptrDesiredMenu = &menu224;
    }
	
	// if hit SAVE
    else
    {
      // GhostMode
      SelectProfile_ToggleMode(0x31);
      sdata->ptrDesiredMenu = &data.menuGhostSelection;
    }
	#endif
  }

  // if name entered for Adventure
  else if (sdata->data10_bbb[0xd] == 0)
  {
	// if hit CANCEL
    if (selection < 0)
    {
      // Change active Menu back to Adv char select
      sdata->ptrDesiredMenu = DECOMP_CS_Garage_GetMenuPtr();
      DECOMP_CS_Garage_ZoomOut(1);
    }
    else
    {
      // make backup of name entered
      *(int*)&sdata->advProgress.name[0x0] = *(int*)&gGT->prevNameEntered[0x0];
      *(int*)&sdata->advProgress.name[0x4] = *(int*)&gGT->prevNameEntered[0x4];
      *(int*)&sdata->advProgress.name[0x8] = *(int*)&gGT->prevNameEntered[0x8];
      *(int*)&sdata->advProgress.name[0xc] = *(int*)&gGT->prevNameEntered[0xc];
	  
	  #ifndef REBUILD_PS1
	  
      // AdventureMode
      SelectProfile_ToggleMode(1);
      sdata->ptrDesiredMenu = &data.menuFourAdvProfiles;
	  
	  #else
		  
	  DECOMP_MainRaceTrack_RequestLoad(N_SANITY_BEACH);
	  sdata->ptrActiveMenu = 0;
	  
	  #endif
    }
  }
}