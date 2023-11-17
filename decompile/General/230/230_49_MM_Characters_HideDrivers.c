#include <common.h>

void DECOMP_MM_Characters_HideDrivers(void) 
{
  char i;
  struct GameTracker *gGT = sdata->gGT;

  for (i = 0; i < 4; i++) 
  {
    DECOMP_TileView_Init(&gGT->tileView[i], 0, 1);
    
#ifndef REBUILD_PS1
	// player structure's instane flags, make invisible
    gGT->drivers[i]->instSelf->flags |= 0x80;
#endif
  }
  
  return;
}