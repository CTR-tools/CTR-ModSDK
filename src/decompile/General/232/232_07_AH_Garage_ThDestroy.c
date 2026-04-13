#include <common.h>

void DECOMP_AH_Garage_ThDestroy(struct Thread* t)
{
  struct BossGarageDoor* garage;
  garage = t->object;
  
  if (garage->garageTopInst != NULL) 
  {
    DECOMP_INSTANCE_Death(garage->garageTopInst);
	garage->garageTopInst = NULL;
  }
  
  return;
}