#include <common.h>

void DECOMP_AH_WarpPad_ThDestroy(struct Thread* warpThread)
{
  struct WarpPad* warpPad;
  int i;
  
  // Get warppad object from thread
  warpPad = (struct WarpPad*)warpThread->object;
  
  // the original code seems to imply there are 8 instances in this object
  for (i = 5; i > -1; i--)
  {
    if (warpPad->inst[i] != NULL)
    {
      INSTANCE_Death();
      warpPad->inst[i] = NULL;
    }

  }
  return;
}