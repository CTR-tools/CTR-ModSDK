#include <common.h>

void DECOMP_RB_Burst_CollLevInst(struct ScratchpadStruct* sps,struct VisData* vis)
{
  short model;
  struct InstDef* instdef;
  struct Thread* meta;
  struct Instance* inst;
  
  instdef = vis->data.hitbox.instDef;
  
  if (
		// if InstDef exists
		(instdef != NULL) && 
		
		(inst = instdef->ptrInstance, inst != NULL)
	  ) 
  {
    model = instdef->modelID;
    
	if (6 < model) 
	{
	  // check 7 and 8,
	  // 7: PU_FRUIT_CRATE
	  // 8: PU_RANDOM_CRATE (weapon box)
      if (model < 9) 
	  {
        meta = COLL_LevModelMeta();
		
		// if funcLevThreadsBirth is not nullptr
        if ((meta != 0) && (*(code **)(meta + 8) != NULL)) 
		{
		  // execute funcLevThreadsBirth, make thread for this instance
		  // upon collision with the instance, let it run thread->funcThCollide
          (**(code **)(meta + 8))(inst,sps->Union.ThBuckOnCollide.thread,sps);
        }
      }
      else 
	  {
		// modelID == teeth
        if (model == 0x70) 
		{
          RB_Teeth_OpenDoor(inst);
        }
      }
    }
  }
  return;
}