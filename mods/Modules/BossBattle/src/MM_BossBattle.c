#include <common.h>

#include "boss_battle.h"

void MM_MenuBox_BossBattle(struct MenuBox* mb)

{
  
  short row;
  struct GameTracker* gGT;
  
  gGT = sdata->gGT;
  row = mb->rowSelected;
  
  if (row == -1) 
  {
    mb->ptrPrevBox_InHierarchy->state &= 0xffffffeb;
	return;
  }
  
  
  if ((unsigned char)row < 3)
  { 
    // disable Cup mode
    gGT->gameMode2 &= 0xffffffef;
    
    // if you choose cup mode
    if (mb->rowSelected == 1) 
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
      mb->ptrNextBox_InHierarchy = &OVR_230.menubox_players1P2P;  //menubox_players1P2P;
      *(int*)0x800b5a08 = 1;
      return;
    }
    
    
    // if mode is VS
    
    // set next menuBox to 2P+3P+4P (vs or battle)
    mb->ptrNextBox_InHierarchy = &OVR_230.menubox_players2P3P4P;
    *(int*)0x800b5a08 = 2;
  }
}
 