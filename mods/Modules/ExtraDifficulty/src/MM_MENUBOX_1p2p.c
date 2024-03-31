#include <common.h>

extern struct RectMenu extra_difficulty;

void DECOMP_MM_MenuProc_1p2p(struct RectMenu* menu)
{
  short row = menu->rowSelected;
  struct GameTracker *gGT = sdata->gGT;

  // if uninitialized
  if (row == -1)
  {
    menu->ptrPrevBox_InHierarchy->state &= ~(ONLY_DRAW_TITLE | DRAW_NEXT_MENU_IN_HIERARCHY);

    gGT->numPlyrNextGame = 1;

    D230.characterSelect_transitionState = 0;
    return;
  }

  // if on row 0 or 1
  if ((unsigned char)row < 2)
  {
    // row 0 is 1P, row 1 is 2P
    gGT->numPlyrNextGame = menu->rowSelected + 1;

    // go to difficulty box
    menu->ptrNextBox_InHierarchy = &extra_difficulty; // this one-line change is the only reason this file is needed
    menu->state |= 0x14;
  }
}