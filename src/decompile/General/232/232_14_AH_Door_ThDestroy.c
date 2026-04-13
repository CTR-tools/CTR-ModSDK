#include <common.h>

void DECOMP_AH_Door_ThDestroy(struct Thread* t)
{
  int i;
  struct WoodDoor* woodDoor = t->object;
  struct Instance** instPtrArr = &woodDoor->otherDoor;
  
  // otherDoor, and 4 keys, all next to each other
  for (i = 0; i < 5; i++)
  {
    if (instPtrArr[i] != NULL)
    {
      DECOMP_INSTANCE_Death(instPtrArr[i]);
      instPtrArr[i] = NULL;
    }
  } 
  return;
}