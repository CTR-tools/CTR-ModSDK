#include <common.h>

void DECOMP_MM_MenuBox_2p3p4p(struct MenuBox * mb) 
{
  short row;
  char numPlayer = sdata->gGT->numPlyrCurrGame;

  // get row highlighted
  row = (mb->rowSelected);

  // if uninitialized
  if (row == -1) {
    mb->ptrPrevMenuBox_InHierarchy->state &= 0xffffffeb;

    // set number of players to 1
    numPlayer = 1;

    *(int*) 0x800b5a08 = 0;
  } else {
    // if you are on a valid row
    if ((-2 < row) && (row < 3)) {
      // set number of players to row + 1 (or 2?)
      numPlayer = mb->rowSelected + '\x02';

      *(int*) 0x800b5a1c = 2;
      *(int*) 0x800b59e0 = 2;

      mb->state |= 4;
      sdata->gGT->numPlyrCurrGame = numPlayer;
      return;
    }
  }
  return;
}
 