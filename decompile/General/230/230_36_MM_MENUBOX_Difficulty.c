#include <common.h>

void DECOMP_MM_MENUBOX_Difficulty(struct MenuBox* mb)
{
  short row;
  
  row = mb->rowSelected;
  
  // if uninitialized
  if (row == -1) {
    mb->ptrPrevBox_InHierarchy->state &= 0xffffffeb;
  }
  
  else 
  {
	// if you are on a valid row
    if ((unsigned char)row < 3) 
	{
	  // set difficulty to value, from array of fixed difficulty values
      sdata->gGT->arcadeDifficulty = OVR_230.cupDifficultySpeed[row];
      
	  OVR_230.MM_State = 2;
	  OVR_230.desiredMenu = 2;
      
	  mb->state |= 4;
      return;
    }
  }
  return;
}
 