#include <common.h>

void DECOMP_LOAD_HowlCallback(char result)
{
  // disable callback
  CdReadCallback(0);
  
  // definitely not bool: can be -1, 0, 1
  
  if(result == CdlComplete)
	  sdata->boolLoadKartHWL = 0;
  else
	  sdata->boolLoadKartHWL = -1;
}