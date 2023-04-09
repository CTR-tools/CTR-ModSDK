#include <common.h>

void DECOMP_MM_MenuBox_1p2p(struct MenuBox* mb)

{
  short row;
  short numPlayer = sdata->gGT->numPlyrCurrGame;
  
  // get row highlighted
  row = mb->rowSelected;
  
  // if uninitialized
  if (row == -1) 
  {
    mb->ptrPrevMenuBox_InHierarchy->state &= 0xffffffeb;
    
	// set number of players to 1
	numPlayer = 1;
    
	*(int*)0x800b5a08 = 0;
  }
  
  else 
  {
	// if you are on a valid row
    if ((-2 < row) && (row < 2)) 
	{
	  // set number of players to row + 1
       numPlayer = mb->rowSelected + 1;
	  
	  // set next menuBox to difficulty selection ???
    mb->ptrNextMenuBox_InHierarchy = &OVR_230.menubox_difficulty;
      
	  mb->state|= 0x14;
	  return;
    }
  }
  return;
}
 