#include <common.h>

void DECOMP_AH_WarpPad_MenuBoxFuncPtr(struct MenuBox* mb)
{
  MenuBox_Hide();
  
  // If row selected is 0
  if (mb->rowSelected == 0) 
  {
	// Turn on CTR Challenge Mode
    sdata->gGT->gameMode2 |= 8;
  }
  // if row selected is 1
  else if (mb->rowSelected == 1) 
  {
	// Turn on Relic Mode
    sdata->gGT->gameMode1 |= 0x4000000;
  }
  return;
}