#include <common.h>

void DECOMP_MM_MenuBox_Difficulty(struct MenuBox* mb)
{
  short row;
  
  // get row highlighted
  row = mb->rowSelected;
  
  // if uninitialized
  if (row == -1) {
    mb->ptrPrevMenuBox_InHierarchy->state &= 0xffffffeb;
  }
  
  else 
  {
	// if you are on a valid row
    if ((-2 < row) && (row < 3)) 
	{
	  // set difficulty to value, from array of fixed difficulty values
      sdata->gGT->arcadeDifficulty = OVR_230.cupDifficultySpeed[row];
      
	  *(int*)0x800b5a1c = 2;
    *(int*)0x800b59e0 = 2;
      
	  mb->state |= 4;
      return;
    }
  }
  return;
}
 