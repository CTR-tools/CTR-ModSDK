#include <common.h>

void DECOMP_MM_Characters_RestoreIDs(void) 
{
  struct GameTracker *gGT = sdata->gGT;
  short *currID;
  int iVar3;
  int iVar4;
  char i;
  short uVar1;

  // erase select bits
  sdata->characterSelectFlags = 0;
  D230.transitionFrames = FPS_DOUBLE(0xc);
  D230.isMenuTransitioning = 0;

  // This uses 80086e84, which controls character IDs
  // loop 8 times
  // shouldn't it only need to loop a maximum of 4 times?
  for (i = 0; i < 8; i++)
  {
    // set character ID to the last ID you entered
    data.characterIDs[i] = sdata->characterIDs_backup[i];
  }

  DECOMP_MM_Characters_SetMenuLayout();

#ifndef USE_OXIDE
  #define NUM_ICONS 0xF
#else
  #define NUM_ICONS 0x10
#endif

  for (i = 0; i < NUM_ICONS; i++) 
  {  
	// would not need this if CSM was sorted 
	// by order of character ID

    // Basically sets them to 0, 1, 2, 3, 4... up to 0xE,
    // setting Oxide's manually to 0xF is needed to make his icon appear

    D230.characterMenuID[D230.csm_Active[i].characterID] = i;
  }

    for (i = 0; i < gGT->numPlyrNextGame; i++) 
	{
      // Determine if this icon is unlocked (and drawing)

      // get character ID
      currID = &data.characterIDs[i];

      // get unlock requirement for this character
      uVar1 = D230.csm_Active[*currID].unlockFlags;

      if (
			// If Icon has an unlock requirement
			(uVar1 != -1) &&
		  
			// If Character is Locked
			(((sdata->gameProgress.unlocks[uVar1 >> 5] >> (uVar1&0x1f)) & 1) == 0)
		  ) 
	  {
        // change character to Crash
        *currID = 0;
      }
    }

  DECOMP_MM_Characters_PreventOverlap();

  for (i = 0; i < gGT->numPlyrNextGame; i++) 
  {
	// set name string ID to the character ID of each player.
	// The string will only draw if both these variables match
	D230.characterSelect_charIDs_curr[i] = data.characterIDs[i];
	D230.characterSelect_charIDs_desired[i] = data.characterIDs[i];
	
	// something to do with transitioning between icons
	D230.timerPerPlayer[i] = 0;
	
	// rotation of each driver, 90 degrees difference
	D230.characterSelect_angle[i] = (i * 0x400) + 400;
  }

  DECOMP_MM_Characters_DrawWindows(0);
  return;
}

