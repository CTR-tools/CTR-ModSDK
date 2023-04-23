#include <common.h>

void DECOMP_AH_Garage_ThDestroy(struct Thread* garageThread)
{
  struct BossGarageDoor* garage;
  
  garage = garageThread->object;
  
  if (garage->garageTopInst != NULL) 
  {
    INSTANCE_Death(garage->garageTopInst);
	garage->garageTopInst = NULL;
  }
  
  return;
}