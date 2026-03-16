#include <common.h>

void DECOMP_MM_ToggleRows_Difficulty(void)
{
  char boolLocked;
  struct GameTracker* gGT;
  short bitIndex;
  u_short menuStringIndex;
  u_int check_progress;
  unsigned char i;
  
  gGT = sdata->gGT;
  
  // check 3 mods (easy, medium, hard)
  for (i = 0; i < 3; i++) 
  {
    bitIndex = D230.cupDifficultyUnlockFlags[i];
    
	// if -1 (for EASY row), skip
	if (bitIndex == -1) continue; 
	
	// assume unlocked
    check_progress = 1;
	
	// check 4 bits starting at bitIndex,
	// one for each track in cup
    for(unsigned char j = 0; j < 4; j++) 
	{
      boolLocked = (check_progress != 0);
      check_progress = 0;
      
	  // if not determined locked
	  if (boolLocked) 
	  {
	  	check_progress = (int)bitIndex + j;
	  
		// check what is unlocked
	  	check_progress = sdata->gameProgress.unlocks[check_progress >> 5] >> check_progress & 1;
	  }
	}
	
	// get current value of lng index,
	// for easy, medium, hard
    menuStringIndex = D230.cupDifficultyLngIndex[i];
	  
    if (
		// if locked
		(check_progress == 0) && 

// dont bother checking Arcade,
// waste of instructions
#if 0
		// If you're in Arcade mode
		((gGT->gameMode1 & ARCADE_MODE) != 0) &&
#endif

		// if you are in Arcade or VS cup
		((gGT->gameMode2 & CUP_ANY_KIND) != 0)
	  ) 
	{
	// set locked string flag (disables selection) --TODO: enum
      menuStringIndex |= 0x8000;
    }
	
	// save new value
    D230.rowsDifficulty[i].stringIndex = menuStringIndex;
  }
  
  return;
}
 