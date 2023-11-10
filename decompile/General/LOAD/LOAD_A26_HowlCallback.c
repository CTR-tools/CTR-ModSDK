#include <common.h>

void DECOMP_LOAD_HowlCallback(char result)
{
  // disable callback
  CdReadCallback(0);
  
  if(result == CdlComplete)
	  sdata->howlChainState = 0;
  else
	  sdata->howlChainState = -1;
}