#include <common.h>
//  (tnt, potion, warpball, etc) (not hazard? moving explosive?)
// param_1 - BSP result
// param_2 - VisData (hitbox)
unsigned short DECOMP_RB_Hazard_CollLevInst(struct ScratchpadStruct* param_1,struct VisData* param_2)
{
  struct InstDef* iVar1;
  struct Instance* iVar4;
  unsigned short uVar2;
  int modelId;
  
  if (((((struct VisData *)(param_1 + 0x48))->flag & 0x80) != 0) &&
      (iVar1 = (((struct VisData *)(param_1 + 0x48))->data.hitbox.instDef, iVar1 != NULL)) &&
     
	 (iVar4 = iVar1->ptrInstance, iVar4 != NULL)) 
  {
	// get modelID from InstDef
    modelId = iVar4->model->id;
	
    iVar1 = COLL_LevModelMeta(modelId);
	
	// if funcLevThreadsBirth is not nullptr
    if ((*(code **)(iVar1 + 8) != NULL)) 
	{		
	  // execute funcLevThreadsBirth, make thread for this instance
	  // upon collision with the instance, let it run thread->funcThCollide
      uVar2 = (**(code **)(iVar1 + 8))(iVar4,param_2,param_1);
	  
	  // if not PU_WUMPA_FRUIT
      if (modelId != 2) 
	  {
		// useless
        if (modelId < 2) {
          return uVar2;
        }
		
		// anything except for
		// 7: PU_FRUIT_CRATE,
		// 8: PU_RANDOM_CRATE (weapon box)
        if (8 < modelId) {
          return uVar2;
        }
        if (modelId < 7) {
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
 