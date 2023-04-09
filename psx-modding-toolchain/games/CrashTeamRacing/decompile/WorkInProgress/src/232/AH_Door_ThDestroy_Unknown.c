#include <common.h>

void DECOMP_AH_Door_ThDestroy(struct Thread* doorThread)
{
  int *piVar1;
  int i;
  
  // get door object attached to thread
  piVar1 = doorThread->object;
  
  for (i = 0; i < 4; i++)
  {
    if (piVar1[i] != NULL)
    {
      INSTANCE_Death(piVar1[i]);
      piVar1[i] = NULL;
    }
  } 
  return;
}