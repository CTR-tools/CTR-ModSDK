#include <common.h>

void DECOMP_MM_MenuProc_2p3p4p(struct RectMenu * menu) 
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
    // row is 0, 1, 2
    if ((unsigned char)row < 3)
	{
      // row 0 is 2P, row 1 is 3P, row 2 is 4P
      gGT->numPlyrNextGame = menu->rowSelected + 2;

      D230.MM_State = 2;
      D230.desiredMenuIndex = 2;

      menu->state |= 4;
      return;
    }
  }
  return;
}
 