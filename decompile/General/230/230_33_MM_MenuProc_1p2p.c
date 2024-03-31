#include <common.h>

void DECOMP_MM_MenuProc_1p2p(struct RectMenu* menu)

{
  short row;
  
  struct GameTracker* gGT;
  gGT = sdata->gGT;
  
  row = menu->rowSelected;
  
  // if uninitialized
  if (row == -1) 
  {
    menu->ptrPrevBox_InHierarchy->state &= ~(ONLY_DRAW_TITLE | DRAW_NEXT_MENU_IN_HIERARCHY);
    
	gGT->numPlyrNextGame = 1;
    
	D230.characterSelect_transitionState = 0;
  }
  
  else 
  {
	// if on row 0 or 1
    if ((unsigned char)row < 2)
	{
	  // row 0 is 1P, row 1 is 2P
	  gGT->numPlyrNextGame = menu->rowSelected + 1;
	  
	  // go to difficulty box
	  menu->ptrNextBox_InHierarchy = &D230.menuDifficulty;
      
	  menu->state|= 0x14;
	  return;
    }
  }
  return;
}
 