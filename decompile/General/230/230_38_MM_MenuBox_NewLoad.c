#include <common.h>

void DECOMP_MM_MENUBOX_NewLoad(struct MenuBox* mb)
{
  short row;
  
  // row number
  row = mb->rowSelected;
  
  if(row == -1)
	  mb->ptrPrevBox_InHierarchy->state &= 0xffffffeb;
  
  if((unsigned char)row > 1) return;
  
  // if Load was chosen
  *(int*)0x800b59e0 = row;
  
  // MM_Title transitioning out
  *(int*)0x800b5a1c = 2;
  
  mb->state |= 4;
  return;
}
 