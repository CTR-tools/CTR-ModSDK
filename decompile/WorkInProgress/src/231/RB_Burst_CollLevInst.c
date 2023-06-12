#include <common.h>

void DECOMP_RB_Burst_CollLevInst(struct ScratchpadStruct* sps,struct BSP* bspHitbox)
{
  short modelID;
  struct InstDef* instdef;
  struct Thread* meta;
  struct Instance* inst;
  
  instdef = bspHitbox->data.hitbox.instDef;
  
  if (
		// if InstDef exists
		(instdef != NULL) && 
		
		(inst = instdef->ptrInstance, inst != NULL)
	  ) 
  {
    modelID = instdef->modelID;
    
	if (6 < modelID) 
	{
	  // check 7 and 8,
	  // 7: PU_FRUIT_CRATE
	  // 8: PU_RANDOM_CRATE (weapon box)
      if (modelID < 9) 
	  {
        meta = COLL_LevModelMeta();
		
		// if funcLevThreadsBirth is not nullptr
        if ((meta != 0) && (*(code **)(meta + 8) != NULL)) 
		{
		  // execute funcLevThreadsBirth, make thread for this instance
		  // upon collision with the instance, let it run thread->funcThCollide
          (**(code **)(meta + 8))(inst,sps->Union.ThBuckColl.thread,sps);
        }
      }
      else 
	  {
		// modelID == teeth
        if (CheckModelID(modelID, STATIC_TEETH)) 
		{
          RB_Teeth_OpenDoor(inst);
        }
      }
    }
  }
  return;
}