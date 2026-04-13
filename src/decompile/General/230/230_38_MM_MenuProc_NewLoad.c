#include <common.h>

void DECOMP_MM_MenuProc_NewLoad(struct RectMenu* menu)
{
  short row;
  
  // row number
  row = menu->rowSelected;
  
  if(row == -1)
	  menu->ptrPrevBox_InHierarchy->state &= ~(ONLY_DRAW_TITLE | DRAW_NEXT_MENU_IN_HIERARCHY);
  
  if((unsigned char)row > 1) return;
  
  // if Load was chosen
  D230.desiredMenuIndex = row;
  
  // MM_Title transitioning out
  D230.MM_State = 2;
  
  menu->state |= 4;
  return;
}
 