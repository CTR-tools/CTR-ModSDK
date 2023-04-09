#include <common.h>

void DECOMP_AH_Garage_ThDestroy(struct Thread* garageThread)
{
  struct BossGarageDoor* garage;
  
  // thread -> object
  garage = garageThread->object;
  
  // if garage -> garagetop exists
  if (garage->garageTopInst != NULL) 
  {
    INSTANCE_Death();
	
	// erase pointer
    garage->garageTopInst = NULL;
  }
  return;
}