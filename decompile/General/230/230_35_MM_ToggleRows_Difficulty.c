#include <common.h>

void DECOMP_MM_ToggleRows_Difficulty(void)
{
  char bVar1;
  struct GameTracker* gGT;
  int iVar3;
  short bitIndex;
  u_short uVar5;
  u_int uVar6;
  int iVar7;
  
  gGT = sdata->gGT;
  iVar3 = 0;
  
  // check 3 mods (easy, medium, hard)
  for (iVar7 = 0; iVar7 < 3; iVar7++) 
  {
    bitIndex = D230.cupDifficultyUnlockFlags[iVar7];
    
	// if -1 (for EASY row), skip
	if (-1 == bitIndex) continue; 
	
	// assume unlocked
    uVar6 = 1;
	
	// check 4 bits starting at bitIndex,
	// one for each track in cup
    for(iVar3 = 0; iVar3 < 4; iVar3++) 
	{
      bVar1 = (uVar6 != 0);
      uVar6 = 0;
      
	  // if not determined locked
	  if (bVar1) 
	  {
	  	uVar6 = (int)bitIndex + iVar3;
	  
		// check what is unlocked
	  	uVar6 = sdata->gameProgress.unlocks[uVar6 >> 5] >> uVar6 & 1;
	  }
	}
	
	// get current value of lng index,
	// for easy, medium, hard
    uVar5 = D230.cupDifficultyLngIndex[iVar7];
	  
    if (
		// if locked
		(uVar6 == 0) && 

// dont bother checking Arcade,
// waste of instructions
#if 0
		// If you're in Arcade mode
		((gGT->gameMode1 & ARCADE_MODE) != 0) &&
#endif

		// if you are in Arcade or VS cup
		((gGT->gameMode2 & 0x10) != 0)
	  ) 
	{
	// use high bits for "LOCKED"
      uVar5 = uVar5 | 0x8000;
    }
	
	// save new value
    D230.rowsDifficulty[iVar7].stringIndex = uVar5;
  }
}
 