#include <common.h>
//  (tnt, potion, warpball, etc) (not hazard? moving explosive?)
// param_1 - BSP result
// param_2 - thread
unsigned short DECOMP_RB_Hazard_CollLevInst(struct ScratchpadStruct* sps,struct Thread* th)
{
  struct InstDef* iVar1;
  struct Instance* iVar4;
  unsigned short uVar2;
  int modelID;
  
  if (((sps->bspHitbox->flag & 0x80) != 0) &&
      (iVar1 = sps->bspHitbox->data.hitbox.instDef, iVar1 != NULL)) &&
     
	 (iVar4 = iVar1->ptrInstance, iVar4 != NULL)) 
  {
	// get modelID from InstDef
    modelID = iVar4->model->id;
	
    iVar1 = COLL_LevModelMeta(modelID);
	
	// if LInC is not nullptr
    if ((*(code **)(iVar1 + 8) != NULL)) 
	{		
	  // execute LInC, make thread for this instance
	  // upon collision with the instance, let it run thread->funcThCollide
      uVar2 = (**(code **)(iVar1 + 8))(iVar4,th,sps);
	  
	  // if not PU_WUMPA_FRUIT
      if (CheckModelID(modelID, PU_WUMPA_FRUIT)) 
      {
      // useless
          if (modelID < 2) {
            return uVar2;
          }
      
      // anything except for
      // 7: PU_FRUIT_CRATE,
      // 8: PU_RANDOM_CRATE (weapon box)
          if (8 < modelID) {
            return uVar2;
          }
          if (modelID < 7) {
            return uVar2;
          }
        }
      return 0;
    }
  }
  
  // make potion open teeth,
  // or make warpball turn around
  return 1;
}
 