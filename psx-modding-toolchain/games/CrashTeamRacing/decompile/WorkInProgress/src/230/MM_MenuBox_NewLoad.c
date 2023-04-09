#include <common.h>

void DECOMP_MM_MenuBox_NewLoad(struct MenuBox* mb)
{
  short row;
  
  // row number
  row = mb->rowSelected;
  
  // if you choose New
  if (row == 0) {
    *(int*)0x800b59e0 = 0;
  }
  
  // if not
  else {
    if (row < 1) {
      if (row != -1) {
        return;
      }
      mb->ptrPrevMenuBox_InHierarchy->state &= 0xffffffeb;
      return;
    }
	
	// if you did not choose Load
    if (row != 1) {
      return;
    }
	
	// if Load was chosen
    *(int*)0x800b59e0 = row;
  }
  
  // MM_Title transitioning out
  *(int*)0x800b5a1c = 2;
  
  mb->state |= 4;
  return;
}
 