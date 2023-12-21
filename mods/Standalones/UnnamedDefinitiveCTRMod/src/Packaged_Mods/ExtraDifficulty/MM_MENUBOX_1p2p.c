#include <common.h>

extern struct MenuBox UDCTRM_ED_MenuBox;

void DECOMP_MM_MENUBOX_1p2p(struct MenuBox *mb)
{
  short row = mb->rowSelected;
  struct GameTracker *gGT = sdata->gGT;

  // if uninitialized
  if (row == -1)
  {
    mb->ptrPrevBox_InHierarchy->state &= ~(ONLY_DRAW_TITLE | DRAW_NEXT_MENU_IN_HIERARCHY);

    gGT->numPlyrNextGame = 1;

    D230.characterSelect_transitionState = 0;
    return;
  }

  // if on row 0 or 1
  if ((unsigned char)row < 2)
  {
    // row 0 is 1P, row 1 is 2P
    gGT->numPlyrNextGame = mb->rowSelected + 1;

    // go to difficulty box
    mb->ptrNextBox_InHierarchy = &UDCTRM_ED_MenuBox; // this one-line change is the only reason this file is needed
    mb->state |= 0x14;
  }
}