#include <common.h>

void DECOMP_MM_MENUBOX_NewLoad(struct MenuBox* mb)
{
  short row;
  
  // row number
  row = mb->rowSelected;
  
  if(row == -1)
	  mb->ptrPrevBox_InHierarchy->state &= ~(ONLY_DRAW_TITLE | DRAW_NEXT_MENU_IN_HIERARCHY);
  
  if((unsigned char)row > 1) return;
  
  // if Load was chosen
  OVR_230.desiredMenu = row;
  
  // MM_Title transitioning out
  OVR_230.MM_State = 2;
  
  mb->state |= 4;
  return;
}
 