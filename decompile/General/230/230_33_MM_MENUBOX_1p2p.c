#include <common.h>

void DECOMP_MM_MENUBOX_1p2p(struct MenuBox* mb)

{
  short row;
  
  struct GameTracker* gGT;
  gGT = sdata->gGT;
  
  row = mb->rowSelected;
  
  // if uninitialized
  if (row == -1) 
  {
    mb->ptrPrevBox_InHierarchy->state &= 0xffffffeb;
    
	gGT->numPlyrNextGame = 1;
    
	*(int*)0x800b5a08 = 0;
  }
  
  else 
  {
	// if on row 0 or 1
    if ((unsigned char)row < 2)
	{
	  // row 0 is 1P, row 1 is 2P
	  gGT->numPlyrNextGame = mb->rowSelected + 1;
	  
	  // go to difficulty box
	  mb->ptrNextBox_InHierarchy = &OVR_230.menubox_difficulty;
      
	  mb->state|= 0x14;
	  return;
    }
  }
  return;
}
 