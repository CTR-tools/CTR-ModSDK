#include <common.h>

void DECOMP_MM_MENUBOX_2p3p4p(struct MenuBox * mb) 
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

    *(int*) 0x800b5a08 = 0;
  } 
  else 
  {
    // row is 0, 1, 2
    if ((unsigned char)row < 3)
	{
      // row 0 is 2P, row 1 is 3P, row 2 is 4P
      gGT->numPlyrNextGame = mb->rowSelected + 2;

      OVR_230.MM_State = 2;
      *(int*) 0x800b59e0 = 2;

      mb->state |= 4;
      return;
    }
  }
  return;
}
 