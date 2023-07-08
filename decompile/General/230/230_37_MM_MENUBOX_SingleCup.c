#include <common.h>

void DECOMP_MM_MENUBOX_SingleCup(struct MenuBox* mb)

{
  short row;
  struct GameTracker* gGT;
  
  gGT = sdata->gGT;
  row = mb->rowSelected;
  
  if (row == -1) 
  {
    mb->ptrPrevBox_InHierarchy->state &= ~(ONLY_DRAW_TITLE | DRAW_NEXT_MENU_IN_HIERARCHY);
	return;
  }
  
  
  if ((unsigned char)row < 2)
  { 
    // disable Cup mode
    gGT->gameMode2 &= 0xffffffef;
    
    // if you choose cup mode
    if (mb->rowSelected != 0) 
    {
  	  // enable cup mode
      gGT->gameMode2 &= 0xffffffef; 
	  gGT->gameMode2 |= 0x10;
    }
    
	mb->state |= 0x14;
    
    // if mode is Arcade
    if ((gGT->gameMode1 & ARCADE_MODE) != 0) 
    {
  	  // set next menuBox to 1P+2P select
      mb->ptrNextBox_InHierarchy = &OVR_230.menubox_players1P2P;
      OVR_230.transitionState = 1;
      return;
    }
    
    // if mode is VS
    
    // set next menuBox to 2P+3P+4P (vs or battle)
    mb->ptrNextBox_InHierarchy = &OVR_230.menubox_players2P3P4P;
    OVR_230.transitionState = 2;
  }
}
 