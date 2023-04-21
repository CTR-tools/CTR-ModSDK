#include <common.h>

void DECOMP_RB_Teeth_LInB(undefined4 unused,struct Instance* inst)
{
  // Do not make a thread for time trial, or relic.
  // Time Trial will be forever closed
  // Relic will be forever open
	
  inst->unk50 += 2;
  
  // If in relic race
  if ((sdata->gGT->gameMode1 & 0x4000000) != 0) 
  {
	// enable access through a door (disable collision)
    sdata->doorAccessFlags |= 1;
	
	// Make invisible
    inst->flags |= 0x80;
  }
  return;
}