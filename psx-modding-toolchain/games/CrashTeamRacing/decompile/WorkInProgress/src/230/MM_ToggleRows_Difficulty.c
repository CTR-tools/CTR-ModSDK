#include <common.h>

void DECOMP_MM_ToggleRows_Difficulty(void)
{
  char bVar1;
  struct GameTracker* gGT;
  int iVar3;
  short *psVar4;
  ushort uVar5;
  uint uVar6;
  int iVar7;
  
  gGT = sdata->gGT;
  iVar3 = 0;
  for (iVar7 = 0; iVar7 < 3; iVar7++) {
    psVar4 = (short *)((int)&DAT_800b4d2c + (iVar3 >> 0xf));
    if (-1 < *psVar4) {
      uVar6 = 1;
      for(iVar3 = 0; iVar3 < 4; iVar3++) {
        bVar1 = (uVar6 != 0);
        uVar6 = 0;
        if (bVar1) {
          uVar6 = (int)*psVar4 + iVar3;
		  
		  // check what is unlocked
          uVar6 = sdata->gameProgress.unlocks[uVar6 >> 5] >> uVar6 & 1;
        }
      }
	  
	  // get current value of lng index,
	  // for easy, medium, hard
      uVar5 = sdata->cupDifficultyLngIndex[iVar7];
	  
      if (
			(
				(uVar6 == 0) && 
				
				// If you're in Arcade mode
				((gGT->gameMode1 & 0x400000) != 0)
			) &&
         
			// if you are in Arcade or VS cup
			((gGT->gameMode2 & 0x10) != 0)
		  ) 
	  {
		// use high bits for "LOCKED"
        uVar5 = uVar5 | 0x8000;
      }
	  
	  // save new value
      OVR_230.rows_difficulty[iVar7].stringIndex = uVar5;
    }
    iVar3 = iVar7 * 0x10000;
  }
  return;
}
 