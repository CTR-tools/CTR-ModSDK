#include <common.h>

void DECOMP_MM_MenuProc_SingleCup(struct RectMenu* menu)

{
  short row;
  struct GameTracker* gGT;
  
  gGT = sdata->gGT;
  row = menu->rowSelected;
  
  if (row == -1) 
  {
    menu->ptrPrevBox_InHierarchy->state &= ~(ONLY_DRAW_TITLE | DRAW_NEXT_MENU_IN_HIERARCHY);
	return;
  }
  
  
  if ((unsigned char)row < 2)
  { 
    // disable Cup mode
    gGT->gameMode2 &= ~(CUP_ANY_KIND);
    
    // if you choose cup mode
    if (menu->rowSelected != 0) 
    {
  	  // enable cup mode
	  gGT->gameMode2 |= CUP_ANY_KIND;
    }
    
	menu->state |= 0x14;
    
    // if mode is Arcade
    if ((gGT->gameMode1 & ARCADE_MODE) != 0) 
    {
  	  // set next menu to 1P+2P select
      menu->ptrNextBox_InHierarchy = &D230.menuPlayers1P2P;
      D230.characterSelect_transitionState = 1;
      return;
    }
    
    // if mode is VS
    
    // set next menu to 2P+3P+4P (vs or battle)
    menu->ptrNextBox_InHierarchy = &D230.menuPlayers2P3P4P;
    D230.characterSelect_transitionState = 2;
  }
}
 